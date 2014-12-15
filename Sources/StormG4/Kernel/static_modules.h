//#define TEST_EXC
#define MODULE_TYPE_MODULE

//#define NO_STATIC_MODULES
//#define STATIC_MODULE_KEYBOARD
//#define STATIC_MODULE_MOUSE

//#define STATIC_MODULE_VGA
//#define STATIC_MODULE_CONSOLE

#define STATIC_MODULE_ATA
#define STATIC_MODULE_PARTITION
#define STATIC_MODULE_VFAT

extern return_t pci_main (int argc, char *argv[], char **envp);
extern return_t pcnet32_main (int argc, char *argv[], char **envp);
extern return_t ata_main (int argc, char *argv[], char **envp);
extern return_t partition_main (int argc, char *argv[], char **envp);
extern return_t vfat_main (int argc, char *argv[], char **envp);

extern return_t keyboard_main (int argc, char *argv[], char **envp);
extern return_t mouse_main (int argc, char *argv[], char **envp);
extern return_t vga_main (int argc, char *argv[], char **envp);
extern return_t console_main (int argc, char *argv[], char **envp);

typedef return_t (module_main_t) (int argc, char *argv[], char **envp);
typedef module_main_t * p_module_main_t;

typedef struct
{
    const wchar_t *name;
    p_module_main_t main;
    bool enabled;
    
} static_module_info_t;

extern static_module_info_t static_modules[];

