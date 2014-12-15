/* Abstract: ACPI server. */
/* Authors: Vladimir Sorokin */

/* Copyright 1999-2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#include "config.h"
#include "acpi.h"

static struct ctl_table_header *acpi_sysctl = NULL;

// current system sleep state (S0 - S4)
static acpi_sstate_t acpi_sleep_state = ACPI_S0;
// time sleep began
static unsigned long acpi_sleep_start = 0;

static volatile u32 acpi_pm1_status = 0;
static volatile u32 acpi_gpe_status = 0;
static volatile u32 acpi_gpe_level = 0;
static volatile acpi_sstate_t acpi_event_state = ACPI_S0;

/* Make it impossible to enter C2/C3 until after we've initialized */
static unsigned long acpi_enter_lvl2_lat = ACPI_INFINITE_LAT;
static unsigned long acpi_enter_lvl3_lat = ACPI_INFINITE_LAT;
static unsigned long acpi_p_lvl2_lat = ACPI_INFINITE_LAT;
static unsigned long acpi_p_lvl3_lat = ACPI_INFINITE_LAT;

/* Statistics.. */
struct Cx_stat_struct {
	unsigned long time;
	unsigned long min;
	unsigned long max;
	unsigned long avg;
} Cx_stat[3];

static unsigned long acpi_p_blk = 0;

static int acpi_p_lvl2_tested = 0;
static int acpi_p_lvl3_tested = 0;

enum
{
  ACPI_ENABLED =       0x00000000, // use ACPI if present
  ACPI_DISABLED =      0x00000001, // never use ACPI
  ACPI_TABLES_ONLY =   0x00000002, // never use chipset-specific driver
  ACPI_CHIPSET_ONLY =  0x00000004, // always use chipset-specific driver
  ACPI_IGNORE_ERRATA = 0x00000008, // ignore any listed platform errata
  ACPI_COPY_TABLES  =  0x00000010, // copy ACPI tables before use
  ACPI_TRUST_TABLES =  0x00000020, // use tables even after ioremap fails
  ACPI_SCI_DISABLED =  0x00000040, // never enable ACPI (info. only)
  ACPI_C2_DISABLED  =  0x00000080, // never enter C2
  ACPI_C3_DISABLED  =  0x00000100, // never enter C3
  ACPI_S1_DISABLED  =  0x00000200, // never enter S1
  ACPI_S5_DISABLED  =  0x00000400, // never enter S5
};

struct acpi_option_info
{
	const char *name;
	unsigned long value;
};

static struct acpi_option_info acpi_options[] =
{
  {"on", ACPI_ENABLED},
  {"off", ACPI_DISABLED},
  {"tables", ACPI_TABLES_ONLY},
  {"chipset", ACPI_CHIPSET_ONLY},
  {"no-errata", ACPI_IGNORE_ERRATA},
  {"copy-tables", ACPI_COPY_TABLES},
  {"trust-tables", ACPI_TRUST_TABLES},
  {"no-sci", ACPI_SCI_DISABLED},
  {"no-c2", ACPI_C2_DISABLED},
  {"no-c3", ACPI_C3_DISABLED},
  {"no-s1", ACPI_S1_DISABLED},
  {"no-s5", ACPI_S5_DISABLED},
  {NULL, 0},
};

static unsigned long acpi_opts = ACPI_ENABLED;

struct acpi_errata_info
{
	const char *signature; // table signature (eg. "RSDT")
	const char *oem;       // OEM name
	const char *oem_table; // OEM table identifier (optional)
	u32 oem_rev;           // OEM table revision (optional)
	unsigned long options; // errata options
};

/*
 * We must identify systems that need ACPI_TRUST_TABLES solely from the
 * RSDP ("RSD PTR ").  All other options should be flagged from the
 * RSDT ("RSDT") which can be better identified.
 */
struct acpi_errata_info acpi_errata[] =
{
	{"RSD PTR ", "AMI   ", NULL, 0, ACPI_TRUST_TABLES | ACPI_COPY_TABLES},
	{NULL, NULL, NULL, 0, 0},
};

// bits 8-15 are SLP_TYPa, bits 0-7 are SLP_TYPb
static unsigned long acpi_slp_typ[] = 
{
	ACPI_SLP_TYP_DISABLED, /* S0 */
	ACPI_SLP_TYP_DISABLED, /* S1 */
	ACPI_SLP_TYP_DISABLED, /* S2 */
	ACPI_SLP_TYP_DISABLED, /* S3 */
	ACPI_SLP_TYP_DISABLED, /* S4 */
	ACPI_SLP_TYP_DISABLED  /* S5 */
};

struct acpi_table_info
{
	u32 expected_signature;
	u32 expected_size;

	struct acpi_table *table;
	unsigned int size;
	int mapped;
};

static struct acpi_table_info acpi_facp
	= {ACPI_FACP_SIG, sizeof(struct acpi_facp), NULL, 0, 0};
static struct acpi_table_info acpi_dsdt = {ACPI_DSDT_SIG, 0, NULL, 0, 0};
static struct acpi_table_info acpi_facs
	= {ACPI_FACS_SIG, sizeof(struct acpi_facs), NULL, 0, 0};

/*
 * Init PIIX4 device, create a fake FACP
 */
static bool acpi_init_piix4(pci_device_info_type *pci_device_info)
{
#if FALSE
	struct acpi_facp *facp;
	u32 base;
	u16 cmd;
	u8 pmregmisc;

	pci_read_config_word(dev, PCI_COMMAND, &cmd);
	if (!(cmd & PCI_COMMAND_IO))
		return -ENODEV;
	
	pci_read_config_byte(dev, ACPI_PIIX4_PMREGMISC, &pmregmisc);
	if (!(pmregmisc & ACPI_PIIX4_PMIOSE))
		return -ENODEV;
	
	base = pci_resource_start (dev, PCI_BRIDGE_RESOURCES);
	if (!base)
		return -ENODEV;

	printk(KERN_INFO "ACPI: found PIIX4 at 0x%04x\n", base);

	facp = kmalloc(sizeof(struct acpi_facp), GFP_KERNEL);
	if (!facp)
		return -ENOMEM;

	memset(facp, 0, sizeof(struct acpi_facp));
	facp->hdr.signature = ACPI_FACP_SIG;
	facp->hdr.length = sizeof(struct acpi_facp);
	facp->int_model = ACPI_PIIX4_INT_MODEL;
	facp->sci_int = ACPI_PIIX4_SCI_INT;
	facp->smi_cmd = ACPI_PIIX4_SMI_CMD;
	facp->acpi_enable = ACPI_PIIX4_ACPI_ENABLE;
	facp->acpi_disable = ACPI_PIIX4_ACPI_DISABLE;
	facp->s4bios_req = ACPI_PIIX4_S4BIOS_REQ;
	facp->pm1a_evt = base + ACPI_PIIX4_PM1_EVT;
	facp->pm1a_cnt = base + ACPI_PIIX4_PM1_CNT;
	facp->pm2_cnt = ACPI_PIIX4_PM2_CNT;
	facp->pm_tmr = base + ACPI_PIIX4_PM_TMR;
	facp->gpe0 = base + ACPI_PIIX4_GPE0;
	facp->pm1_evt_len = ACPI_PIIX4_PM1_EVT_LEN;
	facp->pm1_cnt_len = ACPI_PIIX4_PM1_CNT_LEN;
	facp->pm2_cnt_len = ACPI_PIIX4_PM2_CNT_LEN;
	facp->pm_tm_len = ACPI_PIIX4_PM_TM_LEN;
	facp->gpe0_len = ACPI_PIIX4_GPE0_LEN;
	facp->p_lvl2_lat = (__u16) ACPI_INFINITE_LAT;
	facp->p_lvl3_lat = (__u16) ACPI_INFINITE_LAT;

	acpi_init_table(&acpi_facp, facp, 0);
	acpi_init_table(&acpi_dsdt, NULL, 0);

	acpi_p_blk = base + ACPI_PIIX4_P_BLK;
#endif
	return TRUE;
}

/*
 * Init VIA ACPI device and create a fake FACP
 */
static bool acpi_init_via(pci_device_info_type *device_info)
{
#if TRUE
  struct acpi_facp *facp;
  u32 base = 0;
  u8 tmp = 0;
  u8 irq = 0;
  unsigned int counter;

  for (counter = 0; counter < PCI_NUMBER_OF_RESOURCES; counter++)
  {
    log_print_formatted (&log_structure, LOG_URGENCY_INFORMATIVE, 
      "flags: %lu, start: %lu, end: %lu", 
      device_info->resource[counter].flags, 
      device_info->resource[counter].start, 
      device_info->resource[counter].end);
    if ((device_info->resource[counter].flags & PCI_RESOURCE_IRQ) != 0)
    {
       irq = device_info->resource[counter].start;
    }
  }

/*
  pci_read_config_byte(dev, 0x41, &tmp);
  if (!(tmp & 0x80))
     return -ENODEV;
*/

  base = device_info->resource[PCI_BRIDGE_RESOURCES].start;
  if (!base) 
  {
    base = device_info->resource[PCI_BASE_ADDRESS_4].start;
    if (!base)
    {
      return FALSE;
    }
  }

/*
	base = pci_resource_start(dev, PCI_BRIDGE_RESOURCES);
	if (!base) {
		base = pci_resource_start(dev, PCI_BASE_ADDRESS_4);
		if (!base)
			return -ENODEV;
	}

	pci_read_config_byte(dev, 0x42, &irq);
*/

  log_print_formatted (&log_structure, LOG_URGENCY_INFORMATIVE, 
      "ACPI: found %s at 0x%04x, irq: %u\n", 
      device_info->device_name, base, (unsigned int)irq );

  memory_allocate( (void **)&facp, sizeof(struct acpi_facp) );
  if (!facp)
  {
    return FALSE;
  }

  memory_set_u8( (u8 *)facp, 0, sizeof(struct acpi_facp) );
	
  facp->hdr.signature = ACPI_FACP_SIG;
  facp->hdr.length = sizeof(struct acpi_facp);
  facp->int_model = ACPI_VIA_INT_MODEL;
  facp->sci_int = irq;
  facp->smi_cmd = base + ACPI_VIA_SMI_CMD;
  facp->acpi_enable = ACPI_VIA_ACPI_ENABLE;
  facp->acpi_disable = ACPI_VIA_ACPI_DISABLE;
  facp->pm1a_evt = base + ACPI_VIA_PM1_EVT;
  facp->pm1a_cnt = base + ACPI_VIA_PM1_CNT;
  facp->pm_tmr = base + ACPI_VIA_PM_TMR;
  facp->gpe0 = base + ACPI_VIA_GPE0;

  facp->pm1_evt_len = ACPI_VIA_PM1_EVT_LEN;
  facp->pm1_cnt_len = ACPI_VIA_PM1_CNT_LEN;
  facp->pm_tm_len = ACPI_VIA_PM_TM_LEN;
  facp->gpe0_len = ACPI_VIA_GPE0_LEN;
  facp->p_lvl2_lat = (u16) ACPI_INFINITE_LAT;
  facp->p_lvl3_lat = (u16) ACPI_INFINITE_LAT;

  facp->duty_offset = ACPI_VIA_DUTY_OFFSET;
  facp->duty_width = ACPI_VIA_DUTY_WIDTH;

  facp->day_alarm = ACPI_VIA_DAY_ALARM;
  facp->mon_alarm = ACPI_VIA_MON_ALARM;
  facp->century = ACPI_VIA_CENTURY;

//	acpi_init_table(&acpi_facp, facp, 0);
//	acpi_init_table(&acpi_dsdt, NULL, 0);

  acpi_p_blk = base + ACPI_VIA_P_BLK;
#endif
  return TRUE;
}


typedef enum
{
	CH_INTEL_PIIX4 = 0,
	CH_VIA_586 = 1,
	CH_VIA_686A = 2,
} acpi_chip_type;


/* indexed by value of each enum in acpi_chip_t */
const static struct
{
	bool (*chip_init)(pci_device_info_type *pci_device_info);
	char *name;
} acpi_chip_info[] = {
  [CH_INTEL_PIIX4] = {acpi_init_piix4, "Intel PIIX4"},
  [CH_VIA_586] = {acpi_init_via, "Via 586"},
  [CH_VIA_686A] = {acpi_init_via, "Via 686A"},
};

#if FALSE	
static struct pci_device_id acpi_pci_tbl[] =
{
	{0x8086, 0x7113, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_INTEL_PIIX4},
	{0x1106, 0x3040, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_VIA_586},
	{0x1106, 0x3057, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_VIA_686A},
	{0,} /* terminate list */
};
#endif

pci_device_probe_type pci_device_probe[] =
{
  [CH_INTEL_PIIX4] = { 0x8086, 0x7113 },
  [CH_VIA_586] = { 0x1106, 0x3040 },
  [CH_VIA_686A] = { 0x1106, 0x3057 },
};

static unsigned int number_of_probed_devices = sizeof(pci_device_probe) /
                                               sizeof(pci_device_probe_type);  
static bool pci_driver_registered = FALSE;

/*
 * Locate a known ACPI chipset
 */
static bool acpi_find_chipset(void)
{
  unsigned int probe_counter;
  pci_device_info_type *device_info;
  unsigned int number_of_devices;
  
  for (probe_counter = 0; probe_counter < number_of_probed_devices ; 
       probe_counter++)
  {
    pci_device_exists (&pci_structure, &pci_device_probe[probe_counter],
                       &device_info, &number_of_devices);
    
    if (number_of_devices != 0)
    {
      pci_driver_registered = TRUE;
      log_print_formatted (&log_structure, LOG_URGENCY_INFORMATIVE, 
                          "ACPI founded: %s", 
			  acpi_chip_info[probe_counter].name);
      acpi_chip_info[probe_counter].chip_init (&device_info[0]);
      return TRUE;
    }
  }
  return FALSE;
}

/*
 * Initialize and enable ACPI
 */
bool acpi_init(void)
{
 return acpi_find_chipset();
}

