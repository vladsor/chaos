cp storm storm.o

strip --remove-section=.stabs storm
strip --remove-section=.sbss storm
strip --remove-section=.comment storm
objcopy --rename-section .text=.code_section storm
objcopy --rename-section .data=.data_section storm
objcopy --rename-section .rodata=.read_only_data_section storm

gzip storm