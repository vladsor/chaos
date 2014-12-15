library_name := pci

source_dirs := .


override compile_flags += -pipe -fno-leading-underscore -fno-builtin -funsigned-char  -Wall -W -Werror -Wmissing-prototypes -Wmissing-declarations -Wmissing-noreturn
override compile_flags += $(flags)

override preprocessor_flags += -nostdinc
override preprocessor_flags += -D__STORM_KERNEL__ -DSTORM_VERSION_STRING='"G4 v0.0.8"' -DCREATOR='"Vladimir Sorokin"' -DCOMPILER='"gcc"'

include_flags := $(addprefix -I,$(include_directories))

source_dirs          := $(addprefix ../,$(source_dirs))

c_search_wildcards   := $(addsuffix /*.c,$(source_dirs)) 
asm_search_wildcards := $(addsuffix /*.S,$(source_dirs))

sources := $(wildcard $(c_search_wildcards))
objects          := $(patsubst %.c,%.o,$(wildcard $(c_search_wildcards)))
objects          += $(patsubst %.S,%.o,$(wildcard $(asm_search_wildcards)))

objects := $(patsubst ../%,%,$(objects))
#objects := $(addprefix $(destination_directory)/Objects,$(objects))

dependencies          := $(patsubst %.c,%.d,$(wildcard $(c_search_wildcards)))
dependencies          += $(patsubst %.S,%.d,$(wildcard $(asm_search_wildcards)))

dependencies := $(patsubst ../%,%,$(dependencies))


$(library_name).a: $(objects) $(libraries)
	@echo Linking $@...
	ar cru $(@) $(objects) $(libraries)
	ranlib $(@)

VPATH := $(source_dirs)

deps: $(dependencies) 

pci-id.c: pci.pl pci.ids
	./pci.pl pci.ids

%.d: %.c
	@echo Generate dependencies for $<...
	mkdir -p $(patsubst ../%,%, $(<D))
	cpp -M $(preprocessor_flags) $(include_flags) -MF $@ $< >/dev/null

%.d: %.S
	@echo Generate dependencies for $<...
	mkdir -p $(patsubst ../%,%, $(<D))
	cpp -M $(preprocessor_flags) $(include_flags) -MF $@ $< >/dev/null

%.o: %.c
	@echo Compiling $<... 
	mkdir -p $(patsubst ../%,./%, $(<D))
	gcc -c $(preprocessor_flags) $(compile_flags) $(include_flags) $< -o $@

%.o: %.S
	@echo Compiling $<...
	mkdir -p $(patsubst ../%,%, $(<D))
	gcc -c $(preprocessor_flags) $(compile_flags) $(include_flags) $< -o $@



include $(dependencies)
