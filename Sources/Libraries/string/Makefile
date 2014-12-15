target_name := $(addprefix $(destination_directory)/,$(target))

source_dirs := . 


warning_flags := \
    -Wmissing-prototypes -Wmissing-declarations \
    -Wmissing-noreturn -Wformat=2 -Wparentheses -Wmissing-braces -Wreturn-type\
    -Wunused -Wwrite-strings -Winline \
    -fmessage-length=80 -fdiagnostics-show-location=once \
    -Wpadded -W -Wall -Werror

override compile_flags += -pipe -fno-leading-underscore -fno-builtin \
    -funsigned-char -fpack-struct $(warning_flags)

override preprocessor_flags += -nostdinc
override preprocessor_flags += -DCREATOR='"Vladimir Sorokin"' -DCOMPILER='"gcc"'

include_flags := $(addprefix -I,$(include_directories))

source_dirs          := $(addprefix $(source_directory)/,$(source_dirs))

c_search_wildcards   := $(addsuffix /*.c,$(source_dirs)) 
asm_search_wildcards := $(addsuffix /*.S,$(source_dirs))

sources := $(wildcard $(c_search_wildcards))
sources += $(wildcard $(asm_search_wildcards))

objects := $(patsubst %.c,%.o,$(sources))


objects := $(patsubst $(source_directory)/%,%,$(objects))

libraries := 
#list.a pool_of_integers.a pool_of_ranges.a avl_tree.a hash_table.a\
#    string.a
#unicode.a


libraries := $(addprefix $(library_directories)/, $(libraries))

dependencies         := $(patsubst %.c,%.d,$(wildcard $(c_search_wildcards)))
dependencies         += $(patsubst %.S,%.d,$(wildcard $(asm_search_wildcards)))

dependencies         := $(patsubst $(source_directory)/%,%,$(dependencies))


$(target_name).a: $(objects) $(libraries)
	@echo Linking $@...
	ar cru $(@) $(objects) $(libraries)
	ranlib $(@)

VPATH := $(source_dirs)

deps: $(dependencies) 

%.d: %.c
	@echo Generate dependencies for: $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	cpp -M $(preprocessor_flags) $(include_flags) -MF $@ $< >/dev/null

%.d: %.S
	@echo Generate dependencies for: $< $(include_directories)
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	cpp -M $(preprocessor_flags) $(include_flags) -MF $@ $< >/dev/null

-include $(dependencies)

%.o: %.c
	@echo Compiling: $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	gcc -c $(preprocessor_flags) $(compile_flags) $(include_flags) $< -o $@

%.o: %.S
	@echo Compiling: $<
	mkdir -p $(patsubst $(source_directory)/%,%, $(@D))
	gcc -c $(preprocessor_flags) $(compile_flags) $(include_flags) $< -o $@

install: $(compressed_kernel_name)
	@echo mounting $(IMAGE_FILE)...
	mount $(IMAGE_FILE) /mnt/floppy
	@echo Coping $(compressed_kernel_name) to /system/kernel/storm...
	cp $(compressed_kernel_name) /mnt/floppy/system/kernel/storm
	sync
	@echo unmounting $(IMAGE_FILE)...
	umount /mnt/floppy

