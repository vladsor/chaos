
/* these helpers provide future and backwards compatibility
 * for accessing popular PCI BAR info */
#define pci_resource_start(dev,bar)   ((dev)->resource[(bar)].start)
#define pci_resource_end(dev,bar)     ((dev)->resource[(bar)].end)
#define pci_resource_flags(dev,bar)   ((dev)->resource[(bar)].flags)
#define pci_resource_len(dev,bar) \
    ((pci_resource_start((dev),(bar)) == 0 &&   \
      pci_resource_end((dev),(bar)) ==      \
      pci_resource_start((dev),(bar))) ? 0 :    \
                            \
     (pci_resource_end((dev),(bar)) -       \
      pci_resource_start((dev),(bar)) + 1))

/* Return whether the given PCI device DMA address mask can
 * be supported properly.  For example, if your device can
 * only drive the low 24-bits during PCI bus mastering, then
 * you would pass 0x00ffffff as the mask to this function.
 */
static inline int pci_dma_supported (handle_reference_t hwdev UNUSED, 
	uint64_t mask)
{
    /*
     * we fall back to GFP_DMA when the mask isn't all 1s,
     * so we can't guarantee allocations that must be
     * within a tighter range than GFP_DMA..
     */
    
    if (mask < 0x00ffffff)
        return 0;

    return 1;
}
