program_name := storm
source_dirs  := . Init SystemDebug Cpu Irq Exception Clock Dma Timer IoPort Memory Executive

override compile_flags += -pipe
override compile_flags += $(flags) 

source_dirs      := $(addprefix ../,$(source_dirs))
search_wildcards := $(addsuffix /*.[cS],$(source_dirs))

$(program_name):$(notdir$(patsubst %.[cS],%.o,$(wildcard $(search_wildcards))))
gcc $^ -o $@ -nostdlib -Wl,-T,kernel.ld

VPATH := $(source_dirs) 

%.o: %.c
    @echo Compiling $<...
gcc -c -MD $(compile_flags) $(addprefix -I,$(source_dirs)) $<

%.o: %.S
    @echo Compiling $<...
gcc -c -MD $(compile_flags) $(addprefix -I,$(source_dirs)) $<

include $(wildcard *.d) 