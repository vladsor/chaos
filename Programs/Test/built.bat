gcc -c -I/root/ChaosG4.v006/Include -D__STORM_PROGRAM__ startup.c
gcc -c -I/root/ChaosG4.v006/Include -D__STORM_PROGRAM__ test.c

gcc -o test test.o startup.o -nostdlib -Wl,-T,program.ld

	mount -o loop ../../Images/chaos.flp /mnt/floppy
	cp test /mnt/floppy/system/programs
	sync
	umount /mnt/floppy
