
static_module_info_t static_modules_info[] =
{
#if defined (STATIC_MODULE_PCI)
    { L"PCI",           &pci_main,          TRUE },
#endif

#if defined (STATIC_MODULE_PCNET32)
    { L"PCNet32",       &pcnet32_main,      TRUE },
#endif

#if defined (STATIC_MODULE_ATA)
    { L"ATA",           &ata_main,          TRUE },
#endif

#if defined (STATIC_MODULE_PARTITION)
    { L"Partition",     &partition_main,    TRUE },
#endif

#if defined (STATIC_MODULE_VFAT)
    { L"VFAT",          &vfat_main,         TRUE },
#endif

#if defined (STATIC_MODULE_KEYBOARD)
    { L"Keyboard",      &keyboard_main,     TRUE },
#endif

#if defined (STATIC_MODULE_MOUSE)
    { L"Mouse",         &mouse_main,        TRUE },
#endif

#if defined (STATIC_MODULE_VGA)
    { L"VGA",           &vga_main,          TRUE },
#endif

#if defined (STATIC_MODULE_CONSOLE)
    { L"Console",       &console_main,      TRUE },
#endif
};

#define NUMBER_OF_STATIC_MODULES (sizeof (static_modules_info) / \
    sizeof (static_module_info_t))
