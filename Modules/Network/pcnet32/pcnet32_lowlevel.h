
extern uint16_t pcnet32_wio_read_csr (unsigned long addr, int index);
extern void pcnet32_wio_write_csr (unsigned long addr, int index, uint16_t val);
extern uint16_t pcnet32_wio_read_bcr (unsigned long addr, int index);
extern void pcnet32_wio_write_bcr (unsigned long addr, int index, uint16_t val);
extern uint16_t pcnet32_wio_read_rap (unsigned long addr);
extern void pcnet32_wio_write_rap (unsigned long addr, uint16_t val);
extern void pcnet32_wio_reset (unsigned long addr);
extern int pcnet32_wio_check (unsigned long addr);

extern pcnet32_access_t pcnet32_wio;

extern uint16_t pcnet32_dwio_read_csr (unsigned long addr, int index);
extern void pcnet32_dwio_write_csr (unsigned long addr, int index, uint16_t val);
extern uint16_t pcnet32_dwio_read_bcr (unsigned long addr, int index);
extern void pcnet32_dwio_write_bcr (unsigned long addr, int index, uint16_t val);
extern uint16_t pcnet32_dwio_read_rap (unsigned long addr);
extern void pcnet32_dwio_write_rap (unsigned long addr, uint16_t val);
extern void pcnet32_dwio_reset (unsigned long addr);
extern int pcnet32_dwio_check (unsigned long addr);

extern pcnet32_access_t pcnet32_dwio;
