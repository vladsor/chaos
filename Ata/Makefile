kernel_name := storm
source_dirs  := . Init SystemDebug Cpu Irq Exception Clock Dma Timer IoPort Executive/Thread Executive/Elf Executive/Process Memory/physical Memory/virtual Memory/global SystemCall
# Register Register/Objects

compressed_kernel_name := $(addsuffix .gz,$(kernel_name))
kernel_map := $(addsuffix .map,$(kernel_name))

override compile_flags += -pipe
override compile_flags += $(flags)

override preprocessor_flags += -nostdinc
override preprocessor_flags += -D__STORM_KERNEL__ -DSTORM_VERSION_STRING='"G4 v0.0.7"' -DCREATOR='"Vladimir Sorokin"' -DCOMPILER='"gcc"'

source_dirs          := $(addprefix ../,$(source_dirs))
c_search_wildcards   := $(addsuffix /*.c,$(source_dirs)) 
asm_search_wildcards := $(addsuffix /*.S,$(source_dirs))

objects          := $(notdir $(patsubst %.c,%.o,$(wildcard $(c_search_wildcards))))
objects          += $(notdir $(patsubst %.S,%.o,$(wildcard $(asm_search_wildcards))))

dependencies          := $(notdir $(patsubst %.c,%.d,$(wildcard $(c_search_wildcards))))
dependencies          += $(notdir $(patsubst %.S,%.d,$(wildcard $(asm_search_wildcards))))

$(compressed_kernel_name): $(kernel_name)
	@echo Compressing $<...
	gzip -c $< >$@

$(kernel_name): $(objects)
	@echo Linking $(objects)
	gcc $(objects) $(LIBRARIES) -o $@ -Xlinker -Map -Xlinker $(kernel_map) -nostdlib -Wl,-T,$(LD_SCRIPT)

VPATH := $(source_dirs)

deps: $(dependencies) 

%.d: %.c
	@echo Generate dependencies for $<...
	cpp -M $(preprocessor_flags) $(addprefix -I,$(source_dirs)) $(INCLUDES) -MF $@ $< >/dev/null

%.d: %.S
	@echo Generate dependencies for $<...
	cpp -M $(preprocessor_flags) $(addprefix -I,$(source_dirs)) $(INCLUDES) -MF $@ $< >/dev/null

%.o: %.c
	@echo Compiling $<...
	gcc -c $(preprocessor_flags) $(compile_flags) $(addprefix -I,$(source_dirs)) $(INCLUDES) $<

%.o: %.S
	@echo Compiling $<...
	gcc -c $(preprocessor_flags) $(compile_flags) $(addprefix -I,$(source_dirs)) $(INCLUDES) $<

install: $(compressed_kernel_name)
	@echo mounting $(IMAGE_FILE)...
	mount -o loop $(IMAGE_FILE) /mnt/floppy
	@echo Coping $(compressed_kernel_name) to /system/kernel/storm...
	cp $(compressed_kernel_name) /mnt/floppy/system/kernel/storm
	sync
	@echo unmounting $(IMAGE_FILE)...
	umount /mnt/floppy


include $(wildcard *.d)
