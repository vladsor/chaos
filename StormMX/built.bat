gcc -c -I../Include -g -ggdb \
-D__STORM_KERNEL__ \
-DSTORM_VERSION_STRING='"G4 v0.0.7"' \
-DCREATOR='"Vladimir Sorokin"' \
-DCOMPILER='"gcc"' \
  main.c

#    ../Libraries/pool_of_integers/pool_of_integers.a \
#    ../Libraries/pool_of_ranges/pool_of_ranges.a 
#    ../Common/ata/ata.a \
#    ../Common/Ramdisk/ramdisk.a \
#    ../Modules/Ata/ata.a \
#    ../Modules/Vfat/vfat.a \
#    ../Modules/Floppy/floppy.a \
#    ../Modules/Ata/ata2.a \
#    ../Modules/Partition/partition.a \
#    ../Modules/Vga/vga.a \
#    ../Modules/Riva/riva.a \
#    ../Modules/Keyboard/keyboard.a \
#    ../Modules/Console/console.a \
#    ../Modules/Pci/pci.a \

gcc -o storm main.o Init/init.o SystemDebug/debug.a Irq/irq.a Clock/clock.a \
    Dma/dma.a Timer/timer.a Init/init.a \
    Register/register.a Exception/exception.a  \
    Register/Objects/object_wrappers.a Cpu/cpu.a IoPort/port.a \
    Executive/Thread/thread.a Executive/Process/process.a Executive/Elf/elf.a \
    Memory/global/global_memory.a \
    Memory/virtual/virtual_memory.a \
    Memory/physical/physical_memory.a \
    ./Libraries/string.a \
    ./Libraries/list.a \
    ./Libraries/library_random.a \
    ./Libraries/pool_of_integers.a \
    ./Libraries/pool_of_ranges.a \
    ./Libraries/avl_tree.a \
    ./Libraries/hash_table.a \
    ./Libraries/unicode.a -nostdlib -Wl,-T,kernel.ld
#    bash.a libbuiltins.a libglob.a libreadline.a libtilde.a libtermcap.a posix.a -nostdlib -Wl,-T,kernel.ld
mount -o loop /mnt/chaos.flp /mnt/floppy

cp storm /storm

strip --remove-section=.stabs storm
strip --remove-section=.sbss storm
strip --remove-section=.comment storm
objcopy --rename-section .text=.code_section storm
objcopy --rename-section .data=.data_section storm
objcopy --rename-section .rodata=.read_only_data_section storm

gzip storm
cp storm.gz /mnt/floppy/system/kernel/storm.1
mv storm.gz /mnt/chaos/storm.gz
sync

umount /mnt/chaos.flp



