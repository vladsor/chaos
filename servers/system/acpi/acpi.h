/*
 *  acpi.h - ACPI driver interface
 *
 *  Copyright (C) 1999 Andrew Henroid
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _ACPI_H
#define _ACPI_H

/*
 * System sleep states
 */
enum
{
	ACPI_S0, /* working */
	ACPI_S1, /* sleep */
	ACPI_S2, /* sleep */
	ACPI_S3, /* sleep */
	ACPI_S4, /* non-volatile sleep */
	ACPI_S5, /* soft-off */
};

typedef int acpi_sstate_t;

/*
 * Device states
 */
enum
{
	ACPI_D0, /* fully-on */
	ACPI_D1, /* partial-on */
	ACPI_D2, /* partial-on */
	ACPI_D3, /* fully-off */
};

typedef int acpi_dstate_t;

/* RSDP location */
#define ACPI_BIOS_ROM_BASE (0x0e0000)
#define ACPI_BIOS_ROM_END  (0x100000)

/* Table signatures */
#define ACPI_RSDP1_SIG 0x20445352 /* 'RSD ' */
#define ACPI_RSDP2_SIG 0x20525450 /* 'PTR ' */
#define ACPI_RSDT_SIG  0x54445352 /* 'RSDT' */
#define ACPI_FACP_SIG  0x50434146 /* 'FACP' */
#define ACPI_DSDT_SIG  0x54445344 /* 'DSDT' */
#define ACPI_FACS_SIG  0x53434146 /* 'FACS' */

/* PM1_STS/EN flags */
#define ACPI_TMR    0x0001
#define ACPI_BM	    0x0010
#define ACPI_GBL    0x0020
#define ACPI_PWRBTN 0x0100
#define ACPI_SLPBTN 0x0200
#define ACPI_RTC    0x0400
#define ACPI_WAK    0x8000

/* PM1_CNT flags */
#define ACPI_SCI_EN   0x0001
#define ACPI_BM_RLD   0x0002
#define ACPI_GBL_RLS  0x0004
#define ACPI_SLP_TYP0 0x0400
#define ACPI_SLP_TYP1 0x0800
#define ACPI_SLP_TYP2 0x1000
#define ACPI_SLP_EN   0x2000

#define ACPI_SLP_TYP_MASK  0x1c00
#define ACPI_SLP_TYP_SHIFT 10

/* PM_TMR masks */
#define ACPI_TMR_MASK	0x00ffffff
#define ACPI_TMR_HZ	3580000 /* 3.58 MHz */

/* strangess to avoid integer overflow */
#define ACPI_uS_TO_TMR_TICKS(val) \
  (((val) * (ACPI_TMR_HZ / 10000)) / 100)
#define ACPI_TMR_TICKS_TO_uS(ticks) \
  (((ticks) * 100) / (ACPI_TMR_HZ / 10000))

/* PM2_CNT flags */
#define ACPI_ARB_DIS 0x01

/* FACP flags */
#define ACPI_WBINVD	  0x00000001
#define ACPI_WBINVD_FLUSH 0x00000002
#define ACPI_PROC_C1	  0x00000004
#define ACPI_P_LVL2_UP	  0x00000008
#define ACPI_PWR_BUTTON	  0x00000010
#define ACPI_SLP_BUTTON	  0x00000020
#define ACPI_FIX_RTC	  0x00000040
#define ACPI_RTC_64	  0x00000080
#define ACPI_TMR_VAL_EXT  0x00000100
#define ACPI_DCK_CAP	  0x00000200

/* FACP BOOT_ARCH flags */
#define FACP_BOOT_ARCH_LEGACY_DEVICES	0x0001
#define FACP_BOOT_ARCH_KBD_CONTROLLER	0x0002

/* FACS flags */
#define ACPI_S4BIOS	  0x00000001

/* processor block offsets */
#define ACPI_P_CNT	  0x00000000
#define ACPI_P_LVL2	  0x00000004
#define ACPI_P_LVL3	  0x00000005

/* C-state latencies (microseconds) */
#define ACPI_MAX_P_LVL2_LAT 100
#define ACPI_MAX_P_LVL3_LAT 1000
#define ACPI_INFINITE_LAT   (~0UL)

struct acpi_rsdp {
  u32 signature[2];
  u8 checksum;
  u8 oem[6];
  u8 reserved;
  u32 rsdt;
} __attribute__ ((packed));

struct acpi_table {
  u32 signature;
  u32 length;
  u8 rev;
  u8 checksum;
  u8 oem[6];
  u8 oem_table[8];
  u32 oem_rev;
  u32 creator;
  u32 creator_rev;
} __attribute__ ((packed));

struct acpi_facp {
  struct acpi_table hdr;
  u32 facs;
  u32 dsdt;
  u8 int_model;
  u8 reserved;
  u16 sci_int;
  u32 smi_cmd;
  u8 acpi_enable;
  u8 acpi_disable;
  u8 s4bios_req;
  u8 reserved2;
  u32 pm1a_evt;
  u32 pm1b_evt;
  u32 pm1a_cnt;
  u32 pm1b_cnt;
  u32 pm2_cnt;
  u32 pm_tmr;
  u32 gpe0;
  u32 gpe1;
  u8 pm1_evt_len;
  u8 pm1_cnt_len;
  u8 pm2_cnt_len;
  u8 pm_tm_len;
  u8 gpe0_len;
  u8 gpe1_len;
  u8 gpe1_base;
  u8 reserved3;
  u16 p_lvl2_lat;
  u16 p_lvl3_lat;
  u16 flush_size;
  u16 flush_stride;
  u8 duty_offset;
  u8 duty_width;
  u8 day_alarm;
  u8 mon_alarm;
  u8 century;
  u16 boot_arch;
  u8 reserved6;
  u32 flags;
} __attribute__ ((packed));

struct acpi_facs {
  u32 signature;
  u32 length;
  u32 hw_signature;
  u32 fw_wake_vector;
  u32 global_lock;
  u32 flags;
} __attribute__ ((packed));

/*
 * Sysctl declarations
 */

enum
{
	CTL_ACPI = 10
};

enum
{
	ACPI_FACP = 1,
	ACPI_DSDT,
	ACPI_PM1_ENABLE,
	ACPI_GPE_ENABLE,
	ACPI_GPE_LEVEL,
	ACPI_EVENT,
	ACPI_P_BLK,
	ACPI_ENTER_LVL2_LAT,
	ACPI_ENTER_LVL3_LAT,
	ACPI_P_LVL2_LAT,
	ACPI_P_LVL3_LAT,
	ACPI_C1_TIME,
	ACPI_C2_TIME,
	ACPI_C3_TIME,
	ACPI_S0_SLP_TYP,
	ACPI_S1_SLP_TYP,
	ACPI_S5_SLP_TYP,
	ACPI_SLEEP,
};

#define ACPI_SLP_TYP_DISABLED	(~0UL)

/*
 * PIIX4-specific ACPI info (for systems with PIIX4 but no ACPI tables)
 */

#define ACPI_PIIX4_INT_MODEL	0x00
#define ACPI_PIIX4_SCI_INT	0x0009

#define ACPI_PIIX4_SMI_CMD	0x00b2
#define ACPI_PIIX4_ACPI_ENABLE	0xf0
#define ACPI_PIIX4_ACPI_DISABLE 0xf1
#define ACPI_PIIX4_S4BIOS_REQ	0xf2

#define ACPI_PIIX4_PM1_EVT	0x0000
#define ACPI_PIIX4_PM1_CNT	0x0004
#define	  ACPI_PIIX4_S0_MASK	(0x0005 << 10)
#define	  ACPI_PIIX4_S1_MASK	(0x0004 << 10)
#define	  ACPI_PIIX4_S2_MASK	(0x0003 << 10)
#define	  ACPI_PIIX4_S3_MASK	(0x0002 << 10)
#define	  ACPI_PIIX4_S4_MASK	(0x0001 << 10)
#define	  ACPI_PIIX4_S5_MASK	(0x0000 << 10)
#define ACPI_PIIX4_PM_TMR	0x0008
#define ACPI_PIIX4_GPE0		0x000c
#define ACPI_PIIX4_P_BLK	0x0010

#define ACPI_PIIX4_PM1_EVT_LEN	0x04
#define ACPI_PIIX4_PM1_CNT_LEN	0x02
#define ACPI_PIIX4_PM_TM_LEN	0x04
#define ACPI_PIIX4_GPE0_LEN	0x04

#define ACPI_PIIX4_PM2_CNT	0x0022
#define ACPI_PIIX4_PM2_CNT_LEN	0x01

#define ACPI_PIIX4_PMREGMISC	0x80
#define	  ACPI_PIIX4_PMIOSE	0x01

/*
 * VIA-specific ACPI info (for systems with VT82C586B but no ACPI tables)
 */

#define ACPI_VIA_INT_MODEL     0x00

#define ACPI_VIA_SMI_CMD       0x002f
#define ACPI_VIA_ACPI_ENABLE   0xa1
#define ACPI_VIA_ACPI_DISABLE  0xa0

#define ACPI_VIA_PM1_EVT       0x0000
#define ACPI_VIA_PM1_CNT       0x0004
#define ACPI_VIA_PM_TMR	       0x0008
#define ACPI_VIA_GPE0	       0x0020
#define ACPI_VIA_P_BLK	       0x0010

#define ACPI_VIA_PM1_EVT_LEN   0x04
#define ACPI_VIA_PM1_CNT_LEN   0x02
#define ACPI_VIA_PM_TM_LEN     0x04
#define ACPI_VIA_GPE0_LEN      0x04

#define ACPI_VIA_DUTY_OFFSET   1
#define ACPI_VIA_DUTY_WIDTH    3

#define ACPI_VIA_DAY_ALARM     0x7d
#define ACPI_VIA_MON_ALARM     0x7e
#define ACPI_VIA_CENTURY       0x7f

extern log_structure_type log_structure;
extern ipc_structure_type pci_structure;
extern bool acpi_init (void);

#endif /* _ACPI_H */
