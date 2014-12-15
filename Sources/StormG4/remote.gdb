set language c
set remotebaud 9600

symbol-file $STORM_BINARIES/DebugGDB/Kernel/storm
target remote /dev/ttyS0
