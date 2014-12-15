#include <enviroment.h>

#include "Include/types.h"
#include "Include/pcnet32_lowlevel.h"

/* Offsets from base I/O address. */
#define PCNET32_WIO_RDP		0x10
#define PCNET32_WIO_RAP		0x12
#define PCNET32_WIO_RESET	0x14
#define PCNET32_WIO_BDP		0x16

#define PCNET32_DWIO_RDP	0x10
#define PCNET32_DWIO_RAP	0x14
#define PCNET32_DWIO_RESET	0x18
#define PCNET32_DWIO_BDP	0x1C

uint16_t pcnet32_wio_read_csr (unsigned long addr, int index)
{
    port_uint16_out (addr + PCNET32_WIO_RAP, index);
    return port_uint16_in (addr + PCNET32_WIO_RDP);
}

void pcnet32_wio_write_csr (unsigned long addr, int index, uint16_t val)
{
    port_uint16_out (addr + PCNET32_WIO_RAP, index);
    port_uint16_out (addr + PCNET32_WIO_RDP, val);
}

uint16_t pcnet32_wio_read_bcr (unsigned long addr, int index)
{
    port_uint16_out (addr + PCNET32_WIO_RAP, index);
    return port_uint16_in (addr + PCNET32_WIO_BDP);
}

void pcnet32_wio_write_bcr (unsigned long addr, int index, uint16_t val)
{
    port_uint16_out (addr + PCNET32_WIO_RAP, index);
    port_uint16_out (addr + PCNET32_WIO_BDP, val);
}

uint16_t pcnet32_wio_read_rap (unsigned long addr)
{
    return port_uint16_in (addr + PCNET32_WIO_RAP);
}

void pcnet32_wio_write_rap (unsigned long addr, uint16_t val)
{
    port_uint16_out (addr + PCNET32_WIO_RAP, val);
}

void pcnet32_wio_reset (unsigned long addr)
{
    port_uint16_in (addr + PCNET32_WIO_RESET);
}

int pcnet32_wio_check (unsigned long addr)
{
    port_uint16_out (addr + PCNET32_WIO_RAP, 88);
    return (port_uint16_in (addr + PCNET32_WIO_RAP) == 88);
}

pcnet32_access_t pcnet32_wio = 
{
    pcnet32_wio_read_csr,
    pcnet32_wio_write_csr,
    pcnet32_wio_read_bcr,
    pcnet32_wio_write_bcr,
    pcnet32_wio_read_rap,
    pcnet32_wio_write_rap,
    pcnet32_wio_reset
};

uint16_t pcnet32_dwio_read_csr (unsigned long addr, int index)
{
    port_uint32_out (addr + PCNET32_DWIO_RAP, index);
    return (port_uint32_in (addr + PCNET32_DWIO_RDP) & 0xFFFF);
}

void pcnet32_dwio_write_csr (unsigned long addr, int index, uint16_t val)
{
    port_uint32_out (addr + PCNET32_DWIO_RAP, index);
    port_uint32_out (addr + PCNET32_DWIO_RDP, val);
}

uint16_t pcnet32_dwio_read_bcr (unsigned long addr, int index)
{
    port_uint32_out (addr + PCNET32_DWIO_RAP, index);
    return (port_uint32_in (addr + PCNET32_DWIO_BDP) & 0xFFFF);
}

void pcnet32_dwio_write_bcr (unsigned long addr, int index, uint16_t val)
{
    port_uint32_out (addr + PCNET32_DWIO_RAP, index);
    port_uint32_out (addr + PCNET32_DWIO_BDP, val);
}

uint16_t pcnet32_dwio_read_rap (unsigned long addr)
{
    return (port_uint32_in (addr + PCNET32_DWIO_RAP) & 0xFFFF);
}

void pcnet32_dwio_write_rap (unsigned long addr, uint16_t val)
{
    port_uint32_out (addr + PCNET32_DWIO_RAP, val);
}

void pcnet32_dwio_reset (unsigned long addr)
{
    port_uint32_in (addr + PCNET32_DWIO_RESET);
}

int pcnet32_dwio_check (unsigned long addr)
{
    port_uint32_out (addr + PCNET32_DWIO_RAP, 88);
    return ((port_uint32_in (addr + PCNET32_DWIO_RAP) & 0xFFFF) == 88);
}

pcnet32_access_t pcnet32_dwio = 
{
    pcnet32_dwio_read_csr,
    pcnet32_dwio_write_csr,
    pcnet32_dwio_read_bcr,
    pcnet32_dwio_write_bcr,
    pcnet32_dwio_read_rap,
    pcnet32_dwio_write_rap,
    pcnet32_dwio_reset
};
