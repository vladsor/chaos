/* $Id: ne2000.c,v 1.2 2000/10/14 09:21:24 plundis Exp $ */
/* Abstract: NE2000 server for chaos. */
/* Author noah williamsson <tm@ns2.crw.se> */

/* Copyright 1999-2000 chaos development. */


#include <enviroment.h>

#include "Include/ne2000.h"


uint8_t ne_detect(NIC *);
uint8_t ne_reset_chip(NIC *);
void ne_init_chip(NIC *, uint8_t);
void ne_int_handler(void);
void ne_recv(NIC *);
void ne_xmit(NIC *);
void ne_download_buf(NIC *, uint16_t, uint8_t *, uint16_t);
void ne_handle_overflow(NIC *);
uint16_t hex2dec(uint8_t *);
int main(int, char **);


NIC card;
uint32_t message[1024];
uint32_t data_buffer[1024]; /* xxx - was 400 before.. */
struct ne_user_t users[MAX_USERS];
uint8_t num_users = 0;


uint8_t ne_detect (NIC *n)
{
  uint8_t chk = 0, x;
  uint32_t i;

  if (!n || !n->io || !n->irq)
  {
    printf ("-- Invalid io(0x%x) address or irq(%d)", n->io, n->irq);
    return ERROR;
  }

  if (syscall_port_range_register (n->io, 0x1f))
  {
    printf ("-- Cannot allocate 0x%x => 0x%x", n->io, n->io+0x1f);
    return ERROR;
  }

  chk = port_in_uint8_t (n->io);
  if (chk == 0xff) /* No card found */
  {
    printf ("-- Nothing found on 0x%x", n->io);

    /* XXX - unallocate io space */
    return ERROR;
  }

  /* Check if it really is a NE2k card */
  outb (NE_NODMA + NE_PAGE1 + NE_STOP, n->io); /* Stop the card */
  x = inb (n->io + NE_R0_CNTR0);
  outb (0xff, n->io + NE_R0_CNTR0);
  outb (NE_NODMA + NE_PAGE0, n->io);
  inb (n->io + NE_R0_CNTR0); /* Clear the counter by reading */

  if (inb (n->io + NE_R0_CNTR0) != 0) /* Ooops ;) */
  {
    outb (chk, n->io);
    outb (chk, n->io + NE_R0_CNTR0);
    printf ("Something, but not a NE2k card, found. Aborting");
    return ERROR;
  }

  ne_reset_chip (n);

  /* We don't ack _all_ interrupts in ne_reset_chip(),
     so we do it here instead */
  outb (0xff, n->io + NE_R0_ISR);


  /* Init registers and shit */
  for (i = 0;i < sizeof (ne_preinit_program)/sizeof (ne_program);i++)
  {
    outb (ne_preinit_program[i].value, n->io + ne_preinit_program[i].offset);
  }

  /* It's time to read the station address prom now */
  for (i = 0, x = 0;i < 32;i += 2)
  {
    n->prom[i] = inb (n->io + NE_DATAPORT);
    n->prom[i+1] = inb (n->io + NE_DATAPORT);
    if (n->prom[i] != n->prom[i+1])
      x = 1;
  }

  if (x) /* This isn't a 16 bit card */
  {
    printf ("Haha! Your card isn't supported. Get a 16 bit card");
    return ERROR;
  }

  for (i = 0;i < 16;i++)
    n->prom[i] = n->prom[i+i];

  /* Put our phys addr in mac[] */
  for (i = 0;i < 6;i++)
    n->mac[i] = n->prom[i];

  printf ("MAC address is %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x"
         " and signature [0x%x 0x%x]",
         n->prom[0], n->prom[1], n->prom[2],
         n->prom[3], n->prom[4], n->prom[5], 
         n->prom[14], n->prom[15]);

  outb (0x49, n->io + NE_R0_DCR); /* Set the card in word-wide mode */


  if (syscall_irq_register (n->irq, &ne_int_handler))
  {
    printf ("$@!# Couldn't register irq %d :(", n->irq);
    /* XXX - Unallocate io space*/

    return ERROR;
  }


  ne_init_chip (n, 0);
  return 0;
}


uint8_t ne_reset_chip (NIC *n)
{
  uint16_t i;
  

  outb (inb (n->io + NE_RESET), n->io + NE_RESET);
  for (i = 0;i < 50;i++)
  {
    if ((inb (n->io + NE_R0_ISR) & BIT_ISR_RESET) != 0)
      break;

    syscall_process_control (syscall_process_get_pid_by_name ("ne"),
                            PROCESS_SLEEP, 1000);
  }

  outb (BIT_ISR_RESET, n->io + NE_R0_ISR); /* Ack. intrerrupt */
  if (i != 50)
    return 0;

  printf ("-- timeout while waiting for reset ack.");
  return ERROR;
}


void ne_init_chip (NIC *n, uint8_t startp)
{
  uint16_t i;

  /* This is what the datasheet recommends */
  /* Read more in ne2000.h */
  n->status |= NIC_INIT;
  for (i = 0;i < (sizeof (ne_init_program)/sizeof (ne_program));i++)
    outb (ne_init_program[i].value, n->io + ne_init_program[i].offset);

  outb (NE_NODMA + NE_PAGE1 + NE_STOP, n->io); /* Switch to page 1 */

  /* Hmm, can you change your phys addr? ;-) */
  /* XXX - this should be cleaned up! */
#ifdef TEST
  outb (0xc0,n->io+1);
  outb (0xff,n->io+2);
  outb (0xee,n->io+3);
  outb (0xc0,n->io+4);
  outb (0xff,n->io+5);
  outb (0xee,n->io+6);
#else
  for (i = 0;i < 6;i++)
  {
     outb (n->prom[i], n->io + i + 1);
     if (inb (n->io + i + 1) != n->prom[i])
       printf ("-- Argh. Cannot set phys. addr");
  }
#endif

  outb (NE_PG_RX_START, n->io + NE_PG_CURRENT); /* Init. current ptr */
  outb (NE_NODMA+NE_PAGE0+NE_STOP, n->io);

  n->status &= ~NIC_INT;
  n->status &= ~NIC_UP;
  n->status &= ~NIC_DOWN;
  if (startp)
  {
    outb (0xff, n->io + NE_R0_ISR);
    outb (BIT_ISR_ALL, n->io + NE_R0_IMR);

    /* Wheee. Start the card */
    outb (NE_NODMA + NE_START + NE_PAGE0, n->io);
    outb (NE_DEF_TXCFG, n->io + NE_R0_TCR); /* We're ready to transmit */
    outb (NE_DEF_RXCFG, n->io + NE_R0_RCR); /* ..and receive. */
    n->status |= NIC_UP;
  }
  else
    n->status |= NIC_DOWN;


  n->status &= ~NIC_INIT;
}


/* XXX - rewrite this! */
void ne_int_handler (void)
{
  int sreg;
  uint8_t num_handled;

  for (card.num_interrupts = 1;;card.num_interrupts++)
  {
    interrupt_enter ();
    if (debug >= 2)
      printf ("** Entering interrupt again");

    if (card.status & NIC_INT)
      printf ("-- Wtf, entering interrupt again?");

    card.status |= NIC_INT;

    /* Switch to page 0 */
    outb (NE_NODMA+NE_PAGE0, card.io);

    num_handled = 0;
    while (!(card.status & NIC_BUSY) && 
           (sreg = inb (card.io+NE_R0_ISR)) != 0 && 
           num_handled++ < MAX_INT_WORK)
    {
//      sreg = inb (card.io+NE_R0_ISR);
      if (debug == 2)
        printf ("** ISR:%2.2x ISM:%2.2x", sreg, inb(card.io+NE_R0_IMR));
  
      if (!(card.status & NIC_UP))
        printf ("-- Weird, this nic should be stopped!");

      if (sreg & BIT_ISR_OVERFLW)
      {
        if (debug >= 1)
          printf ("-- Overflow in rx buffer");

        /* This a little more than 10ms. */
#ifdef CAN_WAIT_10_MS
        ne_handle_overflow (&card);

#else /* XXX - this code probably DONT work */
#error "Tomtevarning; DEN H�R KODEN FUNKAR INTE"
        {
          uint32_t tomte;

          if (debug >= 1)
            printf ("** resetting card..");

          tomte = NE_RST_OVERRUN;
          card.status |= NIC_BUSY;
          syscall_message_send (syscall_process_get_pid_by_name ("ne"), &tomte, 4);
          break;
          /* Maybe we should ack. some interrupts.. */
        }
#endif
      }
  
      if (sreg & (BIT_ISR_RX+BIT_ISR_RX_ERR))
      {
        if (debug >= 2)
          printf ("** Packet received");

        ne_recv (&card);
      }
    
      if (sreg & BIT_ISR_TX)
        if (debug >= 1)
          printf ("** Transmit");
    
      if (sreg & BIT_ISR_TX_ERR)
        if (debug >= 1)
          printf ("-- Transmit error");

      if (sreg & BIT_ISR_CNTRS)
      {
        uint8_t x,y,z;
        x = inb (card.io+NE_R0_CNTR0);
        y = inb (card.io+NE_R0_CNTR1);
        z = inb (card.io+NE_R0_CNTR2);
        outb (BIT_ISR_CNTRS, card.io+NE_R0_ISR);
        if (debug >= 2)
          printf ("-- COUNTERS: frame:%d crc:%d missed:%d", x,y,z);
      }
  
      if (sreg & BIT_ISR_RDC)
      {
        if (debug >= 2)
          printf ("-- Ignoring RDC interrupt");

        outb (BIT_ISR_RDC, card.io+NE_R0_ISR);

        /* XXX - lock here for debugging purposes */
//        for(;;);
      }


     /* XXX - varf�r i helvete sitter det en // h�r? */
     /* Ack. all interrupts */
//      outb (0xff, card.io+NE_R0_ISR);


      /* XXX - does this enable the card again?
               does it make the card generate intr.:s. again? */

      outb (NE_NODMA+NE_PAGE0+NE_START, card.io);
    }

    if (num_handled == MAX_INT_WORK)
      if (debug >= 1)
        printf ("-- ** -- Max interrupt work done!!");

    card.status &= ~NIC_INT;
    if (debug >= 2)
      printf ("** ISR:%2.2x ISM:%2.2x NIC status:%.2x (Leaving interrupt handler)", inb(card.io+NE_R0_ISR),
             inb (card.io+NE_R0_IMR), card.status);

    interrupt_leave (card.irq);
  }
}


void ne_recv (NIC *card)
{
/* xxx - moved data_buffer to global .. */
   uint8_t *data = ((uint8_t *)data_buffer) + ((uint8_t) 8);
   uint8_t rx_packets = 0;
   uint8_t rx_page;
   uint8_t frame, next_frame, pkt_status;
   uint16_t current_offset, pkt_len;
   struct ne_pkt_hdr pkt_hdr;

  frame = 0;
  current_offset = 0;
  for (rx_packets = 0;rx_packets < 10;rx_packets++)
  {
    /* Switch to page 1 */  
    outb (NE_NODMA+NE_PAGE1, card->io);

    /* Get the packet ptr from current page */
    rx_page = inb (card->io+NE_PG_CURRENT);

    /* Switch back to page 0 */
    outb (NE_NODMA+NE_PAGE0, card->io);


    frame = inb (card->io+NE_BOUNDARY) + 1;
    if (frame >= NE_PG_STOP)
    {
      if (debug >= 2)
        printf ("-- hmm? weirdo. fixing frame: %x => %x", frame, NE_PG_RX_START);
      frame = NE_PG_RX_START;
    }
    
    if (debug >= 2)
      printf ("** rxpage:0x%x frame:0x%x startpg:0x%x stoppg:0x%x",
              rx_page, frame, NE_PG_TX_START, NE_PG_RX_START);


    if (frame == rx_page) /* D0h, we're done */
    {
      if (debug >= 1)
        printf ("** wow, we're done recv!");

      break;
    }

    current_offset = frame << 8;




    /* We're about to get the header from the chip */

    if (card->status & NIC_DMA)
      printf ("Wtf, dma active in recv?");
   
   
    card->status |= NIC_DMA;
    outb (NE_NODMA+NE_PAGE0+NE_START, card->io);

    /* We're gonna read some stuff soon */
    outb (sizeof (struct ne_pkt_hdr), card->io+NE_R0_RBCR0);
    outb (0, card->io+NE_R0_RBCR1);

    outb (0, card->io+NE_R0_RSAR0);
    outb (frame, card->io+NE_R0_RSAR1);

    /* Ok, let's start */
    outb (NE_RREAD+NE_START, card->io);
    *((uint32_t *)&pkt_hdr) = 0;
    if (debug >= 2)
      printf ("** Before: stat:0x%x next:0x%x len:0x%x",
             pkt_hdr.status, pkt_hdr.next,pkt_hdr.len);
 
/* xxx - chnaged void * from uint32_t *, och till _uint16_t ist.f. uint32_t etc.. */

    port_in_uint16_t_string (card->io+NE_DATAPORT,
                        (void *)&pkt_hdr, sizeof (struct ne_pkt_hdr)>>1);
       
    /* Ack. dma */
    outb (BIT_ISR_RDC, card->io+NE_R0_ISR);
    card->status &= ~NIC_DMA;
    /* Ok, have the header now */
        
       


    pkt_len = pkt_hdr.len-sizeof (struct ne_pkt_hdr);
    pkt_status = pkt_hdr.status;
    next_frame = frame+1+((pkt_len+4)>>8);
    if (debug >= 1)
      printf ("** Packet: stat:0x%x next:0x%x (nxtfrm:0x%x) len:0x%x",
              pkt_hdr.status, pkt_hdr.next, next_frame, pkt_hdr.len);
      
    if (pkt_hdr.next != next_frame &&
        pkt_hdr.next != next_frame+1 &&
        pkt_hdr.next != next_frame - (0x80-0x4c) &&
        pkt_hdr.next != next_frame + 1 - (0x80-0x4c))
      {
        outb (rx_page-1, card->io+NE_BOUNDARY);
        printf ("-- ERROR!!!");
        printf ("[%d:%d:%d:%d] hdr.nxt(%d) nxtfrm(%d) frm(%d)", pkt_hdr.next != next_frame, 
                pkt_hdr.next != next_frame+1, pkt_hdr.next != next_frame - (0x80-0x4c), 
                pkt_hdr.next != next_frame + 1 - (0x80-0x4c), pkt_hdr.next, next_frame, frame);

//        continue;
      }

      if (pkt_len < 60 || pkt_len > 1518)   
        printf ("-- Oops. Weird packet len, 0x%x", pkt_len);
   
      /* Do something useful */
      if ((pkt_status & 0x0f) == BIT_RSR_RXOK)
      {
        /* Wheee.. We recv. a good packet */
#define PROTO ((data[12]*256)+data[13])

        if (debug >= 1)
          printf ("++ Good packet");

        ne_download_buf (card, pkt_len, data, current_offset+sizeof (pkt_hdr));
        if (debug >= 2)
          printf ("** Download done!");


	{ /* XXX - This code doesn't belong here, heh. */
          struct ethhdr *e;
          struct iphdr *i;
          struct tcphdr *t;
          uint8_t *p = data;
          uint8_t n;

          printf ("** proto is [%.4x] ==> %s", PROTO,
                 PROTO == 0x800? "IP/ETH": 
                 PROTO == 0x806? "ARP/ETH": "unknown");

          e = (struct ethhdr *)p;
          p += sizeof(struct ethhdr);
          i = (struct iphdr *)p;
          p += sizeof(struct iphdr);
          t = (struct tcphdr *)p;
           
          if (htons (e->h_proto) == 0x800)
          {
            printf ("** IP: ver:0x%x prot:0x%x len:0x%x", 
                    i->version, i->protocol, 
                    htons(i->tot_len)-sizeof(struct ethhdr)-sizeof(struct iphdr));
            p = (uint8_t *)&i->saddr;
            printf ("++ %s/IP Packet received [%u.%u.%u.%u ==> %u.%u.%u.%u]",
                    i->protocol == 0x11? "UDP": i->protocol == 0x6? "TCP":
                    i->protocol == 0x1? "ICMP": "Unknown", 
                    p[0], p[1], p[2], p[3],
                    p[4], p[5], p[6], p[7]);

            if (i->protocol == 0x1)
            {
              p += sizeof (struct iphdr);
              printf("ICMP type is [%.2x : %.2x]", p[0], p[1]);
            }

          }
         
          for (n = 0;n < num_users;n++)
          {
            if (users[n].proto != e->h_proto)
            {
              printf ("** User proto: %d eth: %d\n", users[n].proto, (e->h_proto));
              continue;
            }

            data_buffer[0] = ETHERNET_PACKET_RECEIVED;
            data_buffer[1] = pkt_len;
            printf("Sending data to pid %ld: ETHERNET_PACKET_RECEIVED, len %d 0x%x\n", users[n].pid, pkt_len+8, pkt_len+8);
            syscall_message_send(users[n].pid, data_buffer, pkt_len+8);
          }
	} /* End of IP code */
      } /* End of RX ok code */
      else
      {
         printf ("-- Bogus packet with size(0x%x/%d):status(%x)", pkt_len, pkt_len, pkt_status);
         card->num_dropped++;
      }

      printf ("** %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x => %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x]", 
              data[6], data[7], data[8],
              data[9], data[10], data[11],
              data[0], data[1], data[2],
              data[3], data[4], data[5]);

      next_frame = pkt_hdr.next;
      outb (next_frame-1, card->io+NE_BOUNDARY);
   }

   outb (BIT_ISR_RX+BIT_ISR_RX_ERR, card->io+NE_R0_ISR);
}



void ne_xmit (NIC *card)
{
  uint8_t status;

  status = inb (card->io+NE_R0_TSR);
  if (debug >= 1)
    printf ("** TSR status is 0x%x", status);

  /* Acknowledge interrupt */
  outb (BIT_ISR_TX, card->io+NE_R0_ISR);


  
  /* XXX - hehe,,, */
}


void ne_download_buf (NIC *n, uint16_t len, uint8_t *data, uint16_t offset)
{
  if (debug >= 2)
    printf ("** ne_download_buf(): Gonna read 0x%x bytes", len);

  n->status |= NIC_DMA;
  outb (NE_NODMA+NE_PAGE0+NE_START, n->io);
  outb (len & 0xff, n->io+NE_R0_RBCR0);
  outb (len >> 8, n->io+NE_R0_RBCR1);
  outb (offset & 0xff, n->io+NE_R0_RSAR0);
  outb (offset >> 8, n->io+NE_R0_RSAR1);
  outb (NE_RREAD+NE_START, n->io);
  
  if (debug >= 2)
    printf ("** ne_download_buf(): now we're about to read..");

  port_in_uint16_t_string (n->io+NE_DATAPORT, (uint16_t *)data, len>>1);
  if (len & 0x01)
    data[len-1] = inb (n->io+NE_DATAPORT);

  if (debug >= 2)
    printf ("** ne_download_buf(): all read done..");

  outb (BIT_ISR_RDC, n->io+NE_R0_ISR);
  n->status &= ~NIC_DMA;

}




void ne_handle_overflow (NIC *n)
{
 
  uint8_t txing, resend = 0;
  uint16_t x;
  
  txing = inb (n->io) & NE_TRANS;

  /* stop the card.. */
  outb (NE_NODMA+NE_PAGE0+NE_STOP, n->io);
  if (debug >= 1)
    printf ("-- Huh.. Overflow.. Sleeping one second!");

#if 0
  syscall_process_control (syscall_process_get_pid_by_name ("ne"),
                          PROCESS_SLEEP, 1000); /* Hmm, what about 10? */
#endif

  for(x = 1;x != 0;x++); /* XXX - Hmm, this is probably ok for now :) */
  outb (0, n->io+NE_R0_RBCR0);
  outb (0, n->io+NE_R0_RBCR1);

  if (txing)
  {
    if (!(inb (n->io+NE_R0_ISR) & (BIT_ISR_TX+BIT_ISR_TX_ERR)))
      resend++;
  }


  outb (BIT_TCR_LB, n->io+NE_R0_TCR); /* Enter loopback mode */
  outb (NE_NODMA+NE_PAGE0+NE_START, n->io);

  if (debug >= 1)
    printf ("** - Clearing rx buffer ring");
  /* Clear RX ring buffer */
  ne_recv (n);

  /* Ack. overflow interrupt */
  outb (BIT_ISR_OVERFLW, n->io+NE_R0_ISR);

  /* Leave loopback mode & resend any stopped packets */
  outb (0, n->io+NE_R0_TCR);
  if (resend)
    outb (NE_NODMA+NE_PAGE0+NE_START+NE_TRANS, n->io);

  /* we're finnished */

  printf ("** overflow reset done!");
  n->status &= ~NIC_BUSY;
}



uint16_t hex2dec (uint8_t *s)
{
  uint16_t ret = 0;
  uint8_t shift;
  

  if (s[0] != '0' || s[1] != 'x')
    return 0;

  s += 2;
  for (shift = 0;s[shift];shift++);
  shift = (shift-1) * 4;
  while (*s >= '0')
  {
    if (*s >= '0' && *s <= '9')
      ret += (*s - '0')<<shift;
    else
       ret += (*s - 'a' + 10)<<shift;

    s++;
    shift -= 4;
  }

  return ret;
}

