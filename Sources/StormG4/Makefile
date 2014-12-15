kernel_name := $(addprefix $(destination_directory)/,storm)
compressed_kernel_name := $(addsuffix .gz,$(kernel_name))
stripped_kernel_name := $(addsuffix .s,$(kernel_name))
kernel_map := $(addsuffix .map,$(kernel_name))

hardware_dirs := . Boot SystemDebug Cpu Irq Exception Clock Dma Timer \
    PhysicalMemory VirtualMemory TaskState IoPort Elf SystemCall
rep_descr_dirs = . Method Interface Class Event
repository_dirs := . Reference \
    $(addprefix Descriptions/,$(rep_descr_dirs)) \
    Method Interface \
    EventSupplierInterface EventSupplier EventConsumerInterface EventConsumer \
    Class Security Cpu Memory Computer Object Handle EventQueue Quality 
object_kernel_dirs = . Interfaces Events Classes

source_dirs := . \
	$(addprefix Hardware/,$(hardware_dirs)) \
	$(addprefix Repository/,$(repository_dirs)) \
	$(addprefix Kernel/,$(object_kernel_dirs))

warning_flags := \
    -Wmissing-prototypes -Wmissing-declarations \
    -Wmissing-noreturn -Wformat=2 -Wparentheses -Wmissing-braces -Wreturn-type\
    -Wunused -Wwrite-strings -Winline \
    -fmessage-length=80 -fdiagnostics-show-location=once \
    -Wpadded -W -Wall -Werror

override compile_flags += -pipe -fno-leading-underscore -fno-builtin \
    -funsigned-char -fpack-struct $(warning_flags)

override preprocessor_flags += -nostdinc
override preprocessor_flags += -D__STORM_KERNEL__ \
	-DSTORM_VERSION_STRING='"$(version)"' -DCREATOR='"Vladimir Sorokin"' \
	-DCOMPILER='"gcc"'

include_flags := $(addprefix -I,$(include_directories))

source_dirs          := $(addprefix $(source_directory)/,$(source_dirs))

c_search_wildcards   := $(addsuffix /*.c,$(source_dirs)) 
asm_search_wildcards := $(addsuffix /*.S,$(source_dirs))

sources := $(wildcard $(c_search_wildcards))
sources += $(wildcard $(asm_search_wildcards))

objects          := $(patsubst %.c,%.o,$(wildcard $(c_search_wildcards)))
objects          += $(patsubst %.S,%.o,$(wildcard $(asm_search_wildcards)))
objects          := $(patsubst $(source_directory)/%,%,$(objects))

dependencies         := $(patsubst %.c,%.d,$(wildcard $(c_search_wildcards)))
dependencies         += $(patsubst %.S,%.d,$(wildcard $(asm_search_wildcards)))
dependencies         := $(patsubst $(source_directory)/%,%,$(dependencies))

override libraries := $(addprefix $(library_directories)/, $(libraries))
override modules := $(addprefix $(modules_directory)/, $(modules))

$(compressed_kernel_name): $(stripped_kernel_name)
	@echo Compressing: $<
	gzip -9c $< >$@

$(stripped_kernel_name): $(kernel_name)
	@echo Stripping: $<
	cp $< $@
	strip --remove-section=.stabs $@
	strip --remove-section=.sbss $@
	strip --remove-section=.comment $@

package-source: $(sources)
	@echo Compressing: sources
	tar -c $(source_directory) | gzip -9c \
		> $(archive_directory)/storm-sources-$(date_string).tgz

#$(objects): Makefile

package-binaries: $(binaries)
	@echo Compressing: binaries
	tar -c $(binaries_directory) | gzip -9c \
		> $(archive_directory)/storm-binaries-$(date_string).tgz

$(kernel_name): $(objects) $(libraries) $(modules)
	@echo Linking: $@
	gcc $(objects) $(modules) $(libraries) -o $@ \
        -Xlinker -Map -Xlinker $(kernel_map) -nostdlib $(linker_flags)
	@echo Reformating: $@
	$(reformat_command) $@
	@echo Current build: `expr 1 + $(build_count)`
	@echo `expr 1 + $(build_count)` > $(destination_directory)/.build
#	rm -f $(program_name)

VPATH := $(source_dirs)

deps: $(dependencies) 

%.d: %.c
	@echo Generate dependencies for: $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	cpp -M $(preprocessor_flags) $(include_flags) \
        -MT '$(patsubst $(source_directory)/%,%,$(patsubst %.c,%.o,$<))' \
        -MF '$@' $< >/dev/null

%.d: %.S
	@echo Generate dependencies for: $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	cpp -M $(preprocessor_flags) $(include_flags) \
        -MT '$(patsubst $(source_directory)/%,%,$(patsubst %.S,%.o,$<))' \
        -MF '$@' $< >/dev/null

%.o: %.c
	@echo Compiling: $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	gcc -c $(preprocessor_flags) $(compile_flags) $(include_flags) $< -o $@

%.o: %.S
	@echo Compiling: $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	gcc -c $(preprocessor_flags) $(compile_flags) $(include_flags) $< -o $@

install: $(compressed_kernel_name)
	@echo mounting: $(IMAGE_FILE)
	mount $(IMAGE_FILE) /mnt/floppy
	@echo Coping: $(compressed_kernel) to: /system/kernel/$(compressed_kernel)
	cp $(compressed_kernel) /mnt/floppy/system/kernel/$(compressed_kernel)
	sync
	@echo unmounting: $(IMAGE_FILE)
	umount /mnt/floppy

-include $(dependencies)

