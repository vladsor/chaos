/*
 * heat
 *
 *   Hardware monitoring software for FreeBSD 3.3-STABLE and above.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include "config.h"

/*
 * For getopt()
 */
extern char *optarg;
extern int optind;

/*
 * Global variables
 */
unsigned int debug		= 0;
unsigned int show_all_fans	= 0;
unsigned int swap_cpu_temps	= 0;
unsigned int quiet		= 0;
unsigned int vendor_id		= 0x0000;
unsigned char chip_id		= 0x00;
unsigned char chip[16];

extern unsigned char get_chip_id(void);
extern unsigned int get_vendor_id(void);
extern void get_fan_statistics(long *FAN1, long *FAN2, long *FAN3);
extern void get_cpu_temperatures(double *CPU1, double *CPU2);
extern void get_system_temperature(signed int *SYSTEMP);

/*
 * C2F(double CELCIUS);
 */
unsigned int C2F(double C)
{
  return ((C*1.8)+32.0);
}

/*
 * usage()
 */
void usage(void)
{
  printf("Usage: heat [-Adqt] [-f device]\n\n");
  printf("  -A             Show all fan information (ignore zero RPMs)\n");
  printf("  -d             Enable debugging\n");
  printf("  -f DEVICE      Use DEVICE instead of default (/dev/io)\n");
  printf("  -q             Quiet mode (don't display header)\n");
  printf("  -t             Flip CPU1/CPU2 thermistor input\n");
  printf("\nReport bugs to <yoshi@parodius.com>\n");
  exit(1);
}

void display_fan(const char *FAN_NAME, unsigned long INFO)
{
  printf("%s\t\t\t%lu RPMs (%s)\n",
	FAN_NAME, INFO, INFO ? "functional" : "non-functional");
}

/*
 * ---===--- MAIN ---===---
 */
int main(int argc, char *argv[])
{
  int iofd;
  int ch;
  unsigned long fan1_info = 0;
  unsigned long fan2_info = 0;
  unsigned long fan3_info = 0;
  signed int system_temp = 0;
  double cpu1_temp = 0;
  double cpu2_temp = 0;
  char io_dev[FILENAME_MAX];

  strcpy(io_dev, "/dev/io");		// FreeBSD default

  /*
   * 'h' and '?' are not listed, to give an error message when used.
   */
  while ( (ch = getopt(argc, argv, "Adf:qt")) != -1 )
  {
    switch (ch)
    {
      case 'A':
        show_all_fans = 1;
        break;
      case 'd':
        debug = 1;
        break;
      case 'f':
        strcpy(io_dev, optarg);
        break;
      case 'q':
        quiet = 1;
        break;
      case 't':
        swap_cpu_temps = 1;
        break;
      case 'h':
      case '?':
      default:
        usage();
    }
  }
  argc -= optind;
  argv += optind;

  /*
   * Open /dev/io for inb() and outb() permissions.
   */
  if ( (iofd = open(io_dev, O_RDWR)) == -1 )
  {
    perror("open() failed");
    exit(1);
  }

  /*
   * Check to see if the vendor ID code returned from the chip matches
   * 0x5CA3 (Winbond chipset).
   */
  if ( (vendor_id = get_vendor_id()) != 0x5CA3 )
  {
    printf("You do not have a Winbond hardware monitoring chipset.\n");
    printf("Your vendor ID code is: 0x%4.4X\n", vendor_id);
    close(iofd);
    exit(1);
  }
  switch ( chip_id = get_chip_id() )
  {
    case 0x10:		strcpy(chip, "W83781D <untested>");	break;
    case 0x20:		strcpy(chip, "W83627HF <untested>");	break;
    case 0x30:		strcpy(chip, "W83782D");		break;
    case 0x40:		strcpy(chip, "W83783S <untested>");	break;
    default:		strcpy(chip, "(unknown)");		break;
  }

  if (!quiet)
  {
    printf("Winbond %s detected (vendor=0x%4.4X, chip=0x%2.2X)\n\n",
      chip, vendor_id, chip_id);
  }

  if (swap_cpu_temps)
  {
    /*
     * Swap CPU1 and CPU2 temperatures; the Abit BP6 has thermistors 1
     * and 2 reversed (hardware bug).
     */
    get_cpu_temperatures(&cpu2_temp, &cpu1_temp);
  }
  else
  {
    get_cpu_temperatures(&cpu1_temp, &cpu2_temp);
  }
  get_fan_statistics(&fan1_info, &fan2_info, &fan3_info);
  get_system_temperature(&system_temp);

  printf("System Temperature\t%3dF (%d.0C)\n",
	 C2F(system_temp), system_temp);
  printf("CPU1 Temperature\t%3dF (%3.01fC)\n",
	 C2F(cpu1_temp), cpu1_temp);
  printf("CPU2 Temperature\t%3dF (%3.01fC)\n",
	 C2F(cpu2_temp), cpu2_temp);
  if (show_all_fans == 1)
  {
    display_fan("FAN1", fan1_info);
    display_fan("FAN2", fan2_info);
    display_fan("FAN3", fan3_info);
  }
  else
  {
    if (fan1_info != 0)		display_fan("FAN1", fan1_info);
    if (fan2_info != 0)		display_fan("FAN2", fan2_info);
    if (fan3_info != 0)		display_fan("FAN3", fan3_info);
  }

  close(iofd);
  exit(0);
}

