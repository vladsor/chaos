#include <enviroment.h>

#include "Include/interface.h"
#include "Include/ne2000.h"


ne_start_card ()
{
        printf ("Starting card.. (pid %ld wants this..)", from);
        ne_init_chip (&card, 1);
        break;
}

ne_stop_card ()
{
        printf ("Stopping card.. (pid %ld wants this..)", from);
        ne_init_chip (&card, 0);

}

ne_get_status ()
{
        printf ("** Status of NE2k card at 0x%x on irq %d:", card.io, card.irq);
        printf ("** Interrupts processed: %ld", card.num_interrupts);
        printf ("** Dropped packets: %ld", card.num_dropped);
        printf ("** Status: 0x%x", card.status);
}

ne_rst_overrun ()
{
        printf ("-- RX overrun occured. Stop, reset, start card..");
        ne_init_chip (&card, 0);

        ne_handle_overflow (&card);
        /* XXX - fix this */

        ne_init_chip (&card, 1);
}
/*
      case ETHERNET_REGISTER_TARGET:
        if (num_users == MAX_USERS)
        {
          printf ("Too many users on card!");
          break;
        }

        users[num_users].pid = from;
        users[num_users].proto = htons (message[1]);
        printf ("** Pid %ld requested ETHERNET_REGISTER_TARGET", from);
        num_users++;
        break;

      case ETHERNET_PACKET_SEND:
        printf ("** Pid %ld requested PACKET_SEND", from);
        break;
*/

get_ethernet_address ()
{
        memcpy (&message[1], card.mac, 6);
        printf ("** Pid %ld requested ETHERNET_ADDRESS_GET", from);
        syscall_message_send (from, &message, 12);
}

int main (int argc, char *argv[], char **envp UNUSED) 
{
  pid_type from;

  syscall_process_name_set ("ne");

  /* Self promotion */
  printf ("NE2000 server by noah williamsson");

  syscall_process_control (syscall_process_get_pid_by_name ("ne"),
                          PROCESS_SLEEP, 1000);


  if (argc != 3)
  {
    printf ("Heya. Load this module as ne2000 <io> <irq>\n"
            "Ex: module=ne2000 0x260 3");

    return 0;
  }

  card.num_dropped = 0;
  card.num_interrupts = 0;


  card.io = hex2dec (argv[1]);
  card.irq = argv[2][0] - '0';

  if (argv[2][1] >= '0')
    card.irq = 10 + argv[2][1] - '0';

  if (card.irq == 2)
    card.irq = 9;

  if (card.io < 0x240 || card.io > 0x360 || card.irq <= 1 || card.irq > 15)
  {
    printf ("Invalid io address(0x%x) or irq(%d) specified", card.io, card.irq);
    return 0;
  }

  if (card.irq == 2)
    card.irq = 9;

  printf ("Probing for a card at 0x%x with irq %d", card.io, card.irq);
  if (ne_detect (&card)) /* No card found */
    return 0;

  printf ("NE2000 card found at 0x%x using irq %d", card.io, card.irq);
  ne_init_chip (&card, 1);


}
