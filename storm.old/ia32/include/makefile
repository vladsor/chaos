# This makefile was generated by autochaos 0.2.0. Please do not
# tamper with it unless you are very certain about what you are doing.

ALL_ARGUMENTS = 

PREFIX = /mnt/chaos
PACKAGE = storm

# Compiler flags.

CFLAGS = -Wall -W -Wshadow -Wpointer-arith -Waggregate-return \
-Wstrict-prototypes -Wredundant-decls -Winline -Wmissing-prototypes \
-Werror -Wcast-align -Wbad-function-cast -Wmissing-noreturns -Wsign-compare \
-Wmissing-declarations -pipe \
-Wnested-externs -O3 -fno-builtin -funsigned-char -g -fomit-frame-pointer -ffreestanding $(EXTRA_CFLAGS) $(DEFINES)

INCLUDES = \
-I../include \
-I.. \
-I. -I$(PREFIX)/data/programming/c/headers

ALL_OBJECTS = \
ia32/cluster.o \
ia32/cpuid.o \
ia32/debug.o \
ia32/dispatch.o \
ia32/dma.o \
ia32/elf.o \
ia32/gdt.o \
ia32/idt.o \
ia32/init.o \
ia32/irq.o \
ia32/irq_handlers.o \
ia32/limits.o \
ia32/main.o \
ia32/memory.o \
ia32/memory_global.o \
ia32/memory_physical.o \
ia32/memory_virtual.o \
ia32/multiboot.o \
ia32/mutex.o \
ia32/port.o \
ia32/process.o \
ia32/schedule.o \
ia32/string.o \
ia32/system_calls-auto.o \
ia32/system_calls.o \
ia32/thread.o \
ia32/time.o \
ia32/timer.o \
ia32/trap.o \
ia32/trap_handlers.o \
ia32/wrapper.o \
generic/arguments.o \
generic/avl.o \
generic/avl_debug.o \
generic/avl_rotate.o \
generic/avl_update.o \
generic/avl_delete.o \
generic/debug.o \
generic/idle.o \
generic/init.o \
generic/kernelfs.o \
generic/log.o \
generic/mailbox.o \
generic/event_queue.o \
generic/memory.o \
generic/port.o \
generic/service.o \
generic/slab.o \
generic/tag.o \
generic/time.o

STATIC_LIBRARY_PATH = $(PREFIX)/data/programming/libraries/static

# Ideally, this would be -lwhatever, but we have not started patching
# the GNU tools yet...

LIBS = 

HEADERS =  \
avl.h \
avl_debug.h \
avl_rotate.h \
avl_update.h \
avl_delete.h \
bit.h \
cluster.h \
cpu.h \
cpuid.h \
dataarea.h \
debug.h \
defines.h \
descriptor.h \
dispatch.h \
dma.h \
elf.h \
flags.h \
gdt.h \
idt.h \
irq.h \
memory.h \
memory_global.h \
memory_physical.h \
memory_virtual.h \
multiboot.h \
mutex.h \
port.h \
process.h \
return_values.h \
string.h \
string-inlines.h \
string-prototypes.h \
system_calls.h \
thread.h \
timer.h \
trap.h \
tss.h \
types.h \
wrapper.h

HEADER_PATH = $(PREFIX)/data/programming/c/headers/$(PACKAGE)//ia32

# TODO: Those should be overridable.

CC = gcc
NASM = nasm
AR = ar
RANLIB = ranlib
GZIP = gzip -f

%.o: %.c
	@echo Compiling $<...
	@$(CC) -o $(@) $(CFLAGS) $(INCLUDES) $(DEFS) -c $<
	@$(CC) -M $< $(CFLAGS) $(INCLUDES) $(DEFS) > $(*F).dep

%.o: %.S
	@echo Compiling $<...
	@$(CC) -o $(@) $(CFLAGS) $(INCLUDES) $(DEFS) -c $<
	@$(CC) -M $< $(CFLAGS) $(INCLUDES) $(DEFS) > $(*F).dep

%.o: %.asm
	$(NASM) -o $(@) $< -f elf

.PHONY: splash all clean install package-source

all: splash makefile 

clean: makefile
	rm -f *.dep
	-$(MAKE) clean-local
splash:


LDFLAGS = -nostdlib -Wl,-T,current-arch/kernel.ld -lgcc $(EXTRA_LDFLAGS)

storm: $(OBJECTS) $(ALL_OBJECTS)
	@echo "Linking..."
	@$(CC) -o $(@) $(OBJECTS) $(ALL_OBJECTS) $(LIBS) $(LDFLAGS)

install: all

package-source:
	mkdir -p /root/Development/chaos/storm.old/package-source/include/storm/ia32
	-cp -f makefile.template $(EXTRA_FILES) /root/Development/chaos/storm.old/package-source/include/storm/ia32
	for header in $(HEADERS) ; do cp $$header /root/Development/chaos/storm.old/package-source/include/storm/ia32 ; done
package-check: package-source
	     cd package-source && ./configure $(ALL_ARGUMENTS) && $(MAKE) && $(MAKE) clean
	     find package-source -name makefile -exec rm {} ';'
	     rm package-source/config.h
package: package-check
	rm -rf storm-0.5.2a
	mv package-source storm-0.5.2a
	tar cvIf storm-0.5.2a.tar.bz2 storm-0.5.2a
	     

