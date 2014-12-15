gcc -c -I/$CHAOS_ROOT/Include -D__STORM_PROGRAM__ startup.c
gcc -c -I/$CHAOS_ROOT/Include -D__STORM_PROGRAM__ test.c

gcc -O0 -g -ggdb -o test test.o startup.o string.a -nostdlib -Wl,-T,program.ld
# 
#	mount -o loop ../../Images/chaos.flp /mnt/floppy
#	cp test /mnt/floppy/system/programs
#	sync
#	umount /mnt/floppy
