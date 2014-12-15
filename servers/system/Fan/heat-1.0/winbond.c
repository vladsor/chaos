/*
 *   Winbond hardware monitoring chipset driver.
 *
 *   Supported chipsets:
 *     - Winbond 83782D
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <machine/cpufunc.h>
#include "config.h"


/*
 * OUT(PORT, VALUE);
 *
 * PORT=  16-bit I/O port
 * VALUE= Value to write to PORT
 * RETURNS= void
 *
 *   The datasheet from Winbond seems ambiguous in reference to D7 of
 *   port REG_ADDR; it claims this bit defines busy status, but appar-
 *   ently is only when READING data. Writing can be done at any time.
 *   I don't see how this is legitimate.
 *
 */
void OUT(unsigned int PORT, unsigned int VALUE)
{
  if (debug)
    printf("DEBUG: outb(0x%3.3X, %2.2X)\n", PORT, VALUE);

  outb(PORT, VALUE);
}

/*
 * IN(PORT);
 *
 * PORT= 16-bit I/O port
 * RETURNS= 8-bit value retrieved from PORT
 *
 */
unsigned char IN(unsigned int PORT)
{
  unsigned char status = inb(REG_ADDR);
  unsigned char retval = 0x00;

  while ( (status & 0x80) != 0x80 )
  {
    status = inb(REG_ADDR);
  }
  retval = inb(PORT);

  if (debug)
    printf("DEBUG: inb(0x%4.4X) <-- %2.2X\n", PORT, retval);

  return(retval);
}


/*
 * SET_PAGE(VALUE);
 *
 * VALUE= 3-bit page value (0-7)
 * RETURNS= void
 *
 */
void SET_PAGE(unsigned char VALUE)
{
  OUT(REG_ADDR, 0x4E);
  OUT(REG_DATA, (VALUE & 0x03) );
}


/*
 * get_fan_statistics(long *FAN1, long *FAN2, long *FAN3);
 *
 * c = (1.35 * 10^6) / (r * d)    ...therefore...
 * r = (1350000) / (d * c)
 *
 */
void get_fan_statistics(	unsigned long *FAN1,
				unsigned long *FAN2,
				unsigned long *FAN3 )
{
  unsigned char fan1_div, fan2_div, fan3_div;
  unsigned char fan1_count, fan2_count, fan3_count;
  unsigned char d;

  SET_PAGE(0);
  OUT(REG_ADDR, 0x5D);		// Register $5D (FAN1,2,3 divisor (bit 2))
  d = IN(REG_DATA);		// --
  fan3_div = ((d & 0x80) >> 5);	// D2 in fan3_div
  fan2_div = ((d & 0x40) >> 4);	// D2 in fan2_div
  fan1_div = ((d & 0x20) >> 3);	// D2 in fan1_div

  OUT(REG_ADDR, 0x47);		// Register $47 (FAN1+2 Divisor/VID)
  d = IN(REG_DATA);
  fan1_div += ((d & 0x30) >> 4);
  fan2_div += ((d & 0xC0) >> 6);
  OUT(REG_ADDR, 0x4B);		// Register $4B (FAN3 Divisor (D7-D6))
  d = IN(REG_DATA);
  fan3_div += ((d & 0xC0) >> 6);

  fan1_div = (1 << fan1_div);	// Convert D2-D0 into actual divisor
  fan2_div = (1 << fan2_div);	// Convert D2-D0 into actual divisor
  fan3_div = (1 << fan3_div);	// Convert D2-D0 into actual divisor

  OUT(REG_ADDR, 0x28);		// Value RAM $28 - FAN1 Count
  fan1_count = IN(REG_DATA);	// --
  OUT(REG_ADDR, 0x29);		// Value RAM $29 - FAN2 Count
  fan2_count = IN(REG_DATA);	// --
  OUT(REG_ADDR, 0x2A);		// Value RAM $2A - FAN3 Count
  fan3_count = IN(REG_DATA);	// --

  if (fan1_count == 0xFF)
    *FAN1 = 0;
  else
    *FAN1 = ( 1350000 / (fan1_div * fan1_count));

  if (fan2_count == 0xFF)
    *FAN2 = 0;
  else
    *FAN2 = ( 1350000 / (fan2_div * fan2_count));

  if (fan3_count == 0xFF)
    *FAN3 = 0;
  else
    *FAN3 = ( 1350000 / (fan3_div * fan3_count));

  return;
}

/*
 * get_vendor_id();
 *
 * RETURNS= 16-bit vendor ID.
 *
 *   Obtains the 16-bit vendor ID (hopefully) from the Winbond chip.
 *   Winbond 83781D chipsets return $5CA3.
 *
 *   Data is obtained via REG_DATA after setting up two internal
 *   registers on the chip: $4E and $4F.
 */
unsigned int get_vendor_id(void)
{
  unsigned int code;

  SET_PAGE(0);
  OUT(REG_ADDR, 0x4E);		// Register $4E
  OUT(REG_DATA, 0x80);		// D7=1 == Access high byte of $4F
  OUT(REG_ADDR, 0x4F);		// Register $4F (Winbond Vendor ID (high))
  code = IN(REG_DATA);		// --
  code <<= 8;			// Shift data into high byte
  OUT(REG_ADDR, 0x4E);		// Register $4E
  OUT(REG_DATA, 0x00);		// D7=0 == Access low byte of $4F
  OUT(REG_ADDR, 0x4F);		// Register $4F (Winbond Vendor ID (low))
  code += IN(REG_DATA);		// --
  return(code);			// Return 16-bit result
}

/*
 * get_chip_id();
 *
 * RETURNS= 8-bit chipset ID.
 *
 *   Obtains the 8-bit chipset ID from the Winbond chip. The
 *   following values represent the following chipsets:
 *
 *   0x10: Winbond 83781D
 *   0x20: Winbond 83627HF
 *   0x30: Winbond 83782D
 *   0x40: Winbond 83783S
 */
unsigned char get_chip_id(void)
{
  SET_PAGE(0);
  OUT(REG_ADDR, 0x58);		// Register $58 (Chip ID)
  return (IN(REG_DATA));	// --
}

/*
 * get_system_temperature(int *SYSTEMP);
 *
 */
void get_system_temperature(	signed int *SYSTEMP )
{
  SET_PAGE(0);
  OUT(REG_ADDR, 0x67);		// Register $67 (System Temperature)
  *SYSTEMP = IN(REG_DATA);	// --
  return;
}

/*
 * get_cpu_temperatures(int *CPU1, int *CPU2);
 *
 */
void get_cpu_temperatures(	double *CPU1,
				double *CPU2 )
{
  double cpu_temp1 = 0;
  double cpu_temp2 = 0;
  unsigned int d;

  SET_PAGE(1);
  OUT(REG_ADDR, 0x50);		// Register $50 (CPU1 Temperature (hi))
  d = IN(REG_DATA);		// --
  d <<= 1;			// Shift D7-D0 into D8-D1
  OUT(REG_ADDR, 0x51);		// Register $51 (CPU1 Temperature (lo))
  d += ( ((IN(REG_DATA)) & 0x80) >> 7 );
  cpu_temp1 = (d >> 1);
  if ((d & 0x01) == 0x01)
    cpu_temp1 += 0.5;

  SET_PAGE(2);
  OUT(REG_ADDR, 0x50);		// Register $50 (CPU2 Temperature (hi))
  d = IN(REG_DATA);		// --
  d <<= 1;			// Shift D7-D0 into D8-D1
  OUT(REG_ADDR, 0x51);		// Register $51 (CPU2 Temperature (lo))
  d += ( ((IN(REG_DATA)) & 0x80) >> 7 );
  cpu_temp2 = (d >> 1);
  if ((d & 0x01) == 0x01)
    cpu_temp2 += 0.5;

  *CPU1 = cpu_temp1;
  *CPU2 = cpu_temp2;
  return;
}

