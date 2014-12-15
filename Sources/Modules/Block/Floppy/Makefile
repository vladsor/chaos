override target_name := $(addprefix $(destination_directory)/,$(target_name))
map_name := $(target_name).map

source_dirs := $(source_directories)

override compile_flags += -pipe -fno-leading-underscore -fno-builtin \
	-funsigned-char -Wall -W -Werror -Wmissing-prototypes \
	-Wmissing-declarations -Wmissing-noreturn
override compile_flags += $(flags)

override preprocessor_flags += -nostdinc
override preprocessor_flags += \
	-DCREATOR='"Vladimir Sorokin"' \
	-DCOMPILER='"gcc"'

include_flags         := $(addprefix -I,$(include_directories))

source_dirs           := $(addprefix $(source_root_directory)/,$(source_dirs))

c_search_wildcards    := $(addsuffix /*.c,$(source_dirs)) 
asm_search_wildcards  := $(addsuffix /*.S,$(source_dirs))
nasm_search_wildcards := $(addsuffix /*.asm,$(source_dirs))


objects          := $(patsubst %.c,%.o,$(wildcard $(c_search_wildcards)))
objects          += $(patsubst %.S,%.o,$(wildcard $(asm_search_wildcards)))
objects          += $(patsubst %.asm,%.o,$(wildcard $(nasm_search_wildcards)))

objects := $(patsubst $(source_root_directory)/%,%,$(objects))

override libraries := $(addprefix $(library_directories)/, $(libraries))

dependencies         := $(patsubst %.c,%.d,$(wildcard $(c_search_wildcards)))
dependencies         += $(patsubst %.S,%.d,$(wildcard $(asm_search_wildcards)))

dependencies := $(patsubst $(source_directory)/%,%,$(dependencies))

VPATH := $(source_dirs)

$(target_name).a: $(objects)
	@echo Linking: $@
	ar cru $(@) $(objects) $(libraries)
	ranlib $(@)
	nm $(@) >$(map_name)

$(target_name).so: $(objects)
	@echo Linking: $@
	gcc -shared $< -o $@

deps: $(dependencies) 

%.d: %.c
	@echo Generate dependencies for $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	cpp -M $(preprocessor_flags) $(include_flags) -MF $@ $< >/dev/null

%.d: %.S
	@echo Generate dependencies for $< $(include_directories)
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	cpp -M $(preprocessor_flags) $(include_flags) -MF $@ $< >/dev/null

include $(dependencies)

%.o: %.c
	@echo Compiling $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	gcc -c $(preprocessor_flags) $(compile_flags) $(include_flags) $< -o $@

%.o: %.S
	@echo Compiling $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	gcc -c $(preprocessor_flags) $(compile_flags) $(include_flags) $< -o $@

%.o: %.asm
	@echo Compiling $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	nasm $(include_flags) $< -o $@ -f elf

install: $(compressed_kernel_name)
	@echo mounting $(IMAGE_FILE)...
	mount $(IMAGE_FILE) /mnt/floppy
	@echo Coping $(compressed_kernel_name) to /system/kernel/storm...
	cp $(compressed_kernel_name) /mnt/floppy/system/kernel/storm
	sync
	@echo unmounting $(IMAGE_FILE)...
	umount /mnt/floppy


