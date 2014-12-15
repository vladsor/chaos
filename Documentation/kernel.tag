<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="file">
    <name>clock.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>clock_8h</filename>
    <member kind="function">
      <type>return_t</type>
      <name>clock_init</name>
      <anchor>a0</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Common/cpu.h</name>
    <path>/root/Chaos/Enviroments/Kernel/Common/</path>
    <filename>Common_2cpu_8h</filename>
    <class kind="struct">cpu_info_t</class>
    <member kind="enumeration">
      <name>halt_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>HALT_REBOOT</name>
      <anchor>a2a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>HALT_SHUTDOWN</name>
      <anchor>a2a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/cpu.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>System_2cpu_8h</filename>
    <member kind="function">
      <type>return_t</type>
      <name>cpu_init</name>
      <anchor>a0</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>cpu_halt</name>
      <anchor>a1</anchor>
      <arglist>(enum halt_t type)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>cpu_lock</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>cpu_unlock</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>cpu_get_info</name>
      <anchor>a4</anchor>
      <arglist>(cpu_info_t *cpu_info)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Common/debug.h</name>
    <path>/root/Chaos/Enviroments/Kernel/Common/</path>
    <filename>Common_2debug_8h</filename>
    <member kind="enumvalue">
      <name>DEBUG_LEVEL_PANIC</name>
      <anchor>a8a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_LEVEL_ERROR</name>
      <anchor>a8a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_LEVEL_NONE</name>
      <anchor>a8a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_LEVEL_WARNING</name>
      <anchor>a8a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_LEVEL_INFORMATIVE</name>
      <anchor>a8a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_LEVEL_INFORMATIVE1</name>
      <anchor>a8a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_LEVEL_INFORMATIVE2</name>
      <anchor>a8a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_LEVEL_INFORMATIVE3</name>
      <anchor>a8a7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/debug.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>System_2debug_8h</filename>
    <member kind="function">
      <type>return_t</type>
      <name>system_debug_init</name>
      <anchor>a0</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>system_debug_print</name>
      <anchor>a1</anchor>
      <arglist>(uint8_t level, const char *module_name, const char *function_name, uint32_t line, const char *message)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>system_debug_printw</name>
      <anchor>a2</anchor>
      <arglist>(uint8_t level, const wchar_t *module_name, const char *function_name, uint32_t line, const wchar_t *message)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>defines.h</name>
    <path>/root/Chaos/Enviroments/Kernel/</path>
    <filename>defines_8h</filename>
    <class kind="struct">storm_memory_map_t</class>
    <class kind="struct">storm_module_info_t</class>
    <class kind="struct">storm_info_t</class>
    <member kind="define">
      <type>#define</type>
      <name>COMMAND_LINE_SIZE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MEMORY_MAP_TYPE_RAM</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX_NUMBER_OF_STORM_MEMORY_MAPS</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX_NUMBER_OF_STORM_MODULES</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>KERNEL_START</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>KERNEL_END</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>KERNEL_SIZE</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THREAD_STACK_SIZE</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>THREAD_NEW_EFLAGS</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_KERNEL</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_USER</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_DIRECTORY_FLAGS</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BASE_DMA</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_KERNEL_CODE</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_KERNEL_DATA</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_PROCESS_CODE</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_PROCESS_DATA</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_TSS1</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_TSS2</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>storm_memory_map_t *</type>
      <name>p_storm_memory_map_t</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>storm_module_info_t *</type>
      <name>p_storm_module_info_t</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>descriptor_index_t</name>
      <anchor>a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_INDEX_NULL</name>
      <anchor>a31a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_INDEX_KERNEL_CODE</name>
      <anchor>a31a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_INDEX_KERNEL_DATA</name>
      <anchor>a31a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_INDEX_PROCESS_CODE</name>
      <anchor>a31a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_INDEX_PROCESS_DATA</name>
      <anchor>a31a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_INDEX_TSS1</name>
      <anchor>a31a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_INDEX_TSS2</name>
      <anchor>a31a29</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_start</name>
      <anchor>a30</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>storm_info_t</type>
      <name>storm_info</name>
      <anchor>a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>_end</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Common/dma.h</name>
    <path>/root/Chaos/Enviroments/Kernel/Common/</path>
    <filename>Common_2dma_8h</filename>
    <member kind="enumvalue">
      <name>STORM_DMA_OPERATION_WRITE</name>
      <anchor>a9a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_DMA_OPERATION_READ</name>
      <anchor>a9a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_DMA_OPERATION_VERIFY</name>
      <anchor>a9a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_DMA_TRANSFER_MODE_DEMAND</name>
      <anchor>a10a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_DMA_TRANSFER_MODE_SINGLE</name>
      <anchor>a10a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_DMA_TRANSFER_MODE_BLOCK</name>
      <anchor>a10a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_DMA_TRANSFER_MODE_CASCADE</name>
      <anchor>a10a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_DMA_AUTOINIT_ENABLE</name>
      <anchor>a11a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_DMA_AUTOINIT_DISABLE</name>
      <anchor>a11a8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/dma.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>System_2dma_8h</filename>
    <member kind="function">
      <type>return_t</type>
      <name>dma_init</name>
      <anchor>a0</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_register</name>
      <anchor>a1</anchor>
      <arglist>(int dma_channel, void **buffer)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_unregister</name>
      <anchor>a2</anchor>
      <arglist>(int dma_channel)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_transfer</name>
      <anchor>a3</anchor>
      <arglist>(unsigned int channel, unsigned int length, unsigned int operation, unsigned int transfer_mode, bool autoinit)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>elf.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>elf_8h</filename>
    <class kind="struct">function_info_t</class>
    <class kind="struct">elf_header_t</class>
    <class kind="struct">elf_section_header_t</class>
    <class kind="struct">elf_program_header_t</class>
    <class kind="struct">elf_symbol_t</class>
    <class kind="struct">elf_relocation_t</class>
    <class kind="struct">elf_parsed_t</class>
    <class kind="struct">elf_parsed_program_t</class>
    <member kind="typedef">
      <type>elf_parsed_t *</type>
      <name>p_elf_parsed_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>elf_parsed_program_t *</type>
      <name>p_elf_parsed_program_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_class_t</name>
      <anchor>a90</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_CLASS_NONE</name>
      <anchor>a90a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_CLASS_32BIT</name>
      <anchor>a90a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_CLASS_64BIT</name>
      <anchor>a90a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_type_t</name>
      <anchor>a91</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_TYPE_NONE</name>
      <anchor>a91a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_TYPE_RELOCATABLE</name>
      <anchor>a91a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_TYPE_EXECUTABLE</name>
      <anchor>a91a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_TYPE_DYNAMIC</name>
      <anchor>a91a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_TYPE_CORE</name>
      <anchor>a91a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_machine_t</name>
      <anchor>a92</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_NONE</name>
      <anchor>a92a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_M32</name>
      <anchor>a92a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_SPARC</name>
      <anchor>a92a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_386</name>
      <anchor>a92a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_68000</name>
      <anchor>a92a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_88000</name>
      <anchor>a92a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_860</name>
      <anchor>a92a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_RS3000</name>
      <anchor>a92a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_RS4000</name>
      <anchor>a92a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_PARISC</name>
      <anchor>a92a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_SPARC32PLUS</name>
      <anchor>a92a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_PPC</name>
      <anchor>a92a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_PPC64</name>
      <anchor>a92a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_S390</name>
      <anchor>a92a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_ARM</name>
      <anchor>a92a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_SH</name>
      <anchor>a92a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_SPARCV9</name>
      <anchor>a92a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_IA_64</name>
      <anchor>a92a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_X8664</name>
      <anchor>a92a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_CRIS</name>
      <anchor>a92a29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_MACHINE_S390_OLD</name>
      <anchor>a92a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_version_t</name>
      <anchor>a93</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_VERSION_NONE</name>
      <anchor>a93a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_VERSION_CURRENT</name>
      <anchor>a93a32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_endian_t</name>
      <anchor>a94</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_ENDIAN_NONE</name>
      <anchor>a94a33</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_ENDIAN_LITTLE</name>
      <anchor>a94a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_ENDIAN_BIG</name>
      <anchor>a94a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_section_type_t</name>
      <anchor>a95</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_NULL</name>
      <anchor>a95a36</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_UNDEFINED</name>
      <anchor>a95a37</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_SYMBOL_TABLE</name>
      <anchor>a95a38</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_STRING_TABLE</name>
      <anchor>a95a39</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_RELOCATION_ADDENDS</name>
      <anchor>a95a40</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_SYMBOL_HASH_TABLE</name>
      <anchor>a95a41</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_DYNAMIC</name>
      <anchor>a95a42</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_NOTE</name>
      <anchor>a95a43</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_NO_SPACE</name>
      <anchor>a95a44</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_RELOCATION</name>
      <anchor>a95a45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_SHARED_LIBRARY</name>
      <anchor>a95a46</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_TYPE_DYNAMIC_SYMBOL_TABLE</name>
      <anchor>a95a47</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_program_type_t</name>
      <anchor>a96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_PROGRAM_TYPE_NULL</name>
      <anchor>a96a48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_PROGRAM_TYPE_LOAD</name>
      <anchor>a96a49</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_PROGRAM_TYPE_DYNAMIC</name>
      <anchor>a96a50</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_PROGRAM_TYPE_INTERPRETER</name>
      <anchor>a96a51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_PROGRAM_TYPE_NOTE</name>
      <anchor>a96a52</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_PROGRAM_TYPE_SHARED_LIBRARY</name>
      <anchor>a96a53</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_PROGRAM_TYPE_PROGRAM_HEADER</name>
      <anchor>a96a54</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_program_flag_t</name>
      <anchor>a97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PF_EXECUTE</name>
      <anchor>a97a55</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PF_WRITE</name>
      <anchor>a97a56</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PF_READ</name>
      <anchor>a97a57</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_section_flag_t</name>
      <anchor>a98</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_FLAG_WRITE</name>
      <anchor>a98a58</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_FLAG_ALLOCATE</name>
      <anchor>a98a59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SECTION_FLAG_EXECUTE</name>
      <anchor>a98a60</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_symbol_binding_t</name>
      <anchor>a99</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SYMBOL_BINDING_LOCAL</name>
      <anchor>a99a61</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SYMBOL_BINDING_GLOBAL</name>
      <anchor>a99a62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SYMBOL_BINDING_WEAK</name>
      <anchor>a99a63</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_symbol_type_t</name>
      <anchor>a100</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SYMBOL_TYPE_NONE</name>
      <anchor>a100a64</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SYMBOL_TYPE_OBJECT</name>
      <anchor>a100a65</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SYMBOL_TYPE_FUNCTION</name>
      <anchor>a100a66</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SYMBOL_TYPE_SECTION</name>
      <anchor>a100a67</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_SYMBOL_TYPE_FILE</name>
      <anchor>a100a68</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>elf_relocation_type_t</name>
      <anchor>a101</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_NONE</name>
      <anchor>a101a69</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_386_32</name>
      <anchor>a101a70</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_386_PC32</name>
      <anchor>a101a71</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_GOT_32</name>
      <anchor>a101a72</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_PLT_32</name>
      <anchor>a101a73</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_COPY</name>
      <anchor>a101a74</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_GLOB_DAT</name>
      <anchor>a101a75</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_JMP_SLOT</name>
      <anchor>a101a76</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_RELATIVE</name>
      <anchor>a101a77</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_GOTOFF</name>
      <anchor>a101a78</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ELF_RELOCATION_GOTPC</name>
      <anchor>a101a79</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>enum storm_elf_t</type>
      <name>elf_identify</name>
      <anchor>a80</anchor>
      <arglist>(elf_header_t *elf_header)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_parse</name>
      <anchor>a81</anchor>
      <arglist>(elf_header_t *elf_header, elf_parsed_t *elf_parsed)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_resolve</name>
      <anchor>a82</anchor>
      <arglist>(elf_parsed_t *elf_parsed, function_info_t *function)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_relocate</name>
      <anchor>a83</anchor>
      <arglist>(elf_parsed_t *elf_parsed)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_symbol_find_by_index</name>
      <anchor>a84</anchor>
      <arglist>(elf_parsed_t *elf_parsed, unsigned int index, address_t *address)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_symbol_find_by_name</name>
      <anchor>a85</anchor>
      <arglist>(elf_parsed_t *elf_parsed, const char *name, address_t *address)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_load_module</name>
      <anchor>a86</anchor>
      <arglist>(elf_parsed_t *elf_parsed)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_parse_program</name>
      <anchor>a87</anchor>
      <arglist>(elf_header_t *elf_header, elf_parsed_program_t *elf_parsed)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_load_program</name>
      <anchor>a88</anchor>
      <arglist>(elf_parsed_program_t *elf_parsed, virtual_memory_t *memory)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_get_entry_point</name>
      <anchor>a89</anchor>
      <arglist>(elf_parsed_program_t *elf_parsed, address_t *address)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Common/exception.h</name>
    <path>/root/Chaos/Enviroments/Kernel/Common/</path>
    <filename>Common_2exception_8h</filename>
    <class kind="struct">exception_info_t</class>
    <class kind="struct">exception_context_t</class>
    <class kind="struct">exception_hardware_info_t</class>
    <class kind="struct">exception_hardware_segment_info_t</class>
    <class kind="struct">exception_hardware_page_info_t</class>
    <class kind="struct">exception_hardware_with_error_code_info_t</class>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_TYPE_HARDWARE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_TYPE_SYSTEM</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_TYPE_USER</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>exception_info_t *</type>
      <name>p_exception_info_t</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>exception_context_t *</type>
      <name>p_exception_context_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>exception_hardware_info_t *</type>
      <name>p_exception_hardware_info_t</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>exception_hardware_segment_info_t *</type>
      <name>p_exception_hardware_segment_info_t</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>exception_hardware_page_info_t *</type>
      <name>p_exception_hardware_page_info_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>exception_hardware_with_error_code_info_t *</type>
      <name>p_exception_hardware_with_error_code_info_t</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>exception_handler_t</name>
      <anchor>a9</anchor>
      <arglist>)(p_void_t parameter, exception_hardware_info_t info)</arglist>
    </member>
    <member kind="typedef">
      <type>exception_handler_t *</type>
      <name>p_exception_handler_t</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/exception.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>System_2exception_8h</filename>
    <class kind="struct">exception_hardware_description_t</class>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_EXCEPTIONS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXCEPTION_CODE_NONE</name>
      <anchor>a9a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXCEPTION_CODE_SEGMENT</name>
      <anchor>a9a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXCEPTION_CODE_PAGE</name>
      <anchor>a9a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>exception_init</name>
      <anchor>a5</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>exception_register</name>
      <anchor>a6</anchor>
      <arglist>(unsigned int exception_number, p_exception_handler_t function, p_void_t parameter)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>exception_unregister</name>
      <anchor>a7</anchor>
      <arglist>(unsigned int exception_number)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_print_screen</name>
      <anchor>a8</anchor>
      <arglist>(uint32_t class_id, const char *description, const char *reason, uint32_t error_code_type, exception_hardware_info_t *exception_info)</arglist>
    </member>
    <member kind="variable">
      <type>exception_hardware_description_t</type>
      <name>exception_hardware_descriptions</name>
      <anchor>a1</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>io_port.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>io__port_8h</filename>
    <member kind="function">
      <type>return_t</type>
      <name>io_port_init</name>
      <anchor>a0</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>io_port_register</name>
      <anchor>a1</anchor>
      <arglist>(unsigned int start, size_t ports, const char *description)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>io_port_unregister</name>
      <anchor>a2</anchor>
      <arglist>(unsigned int start)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Common/irq.h</name>
    <path>/root/Chaos/Enviroments/Kernel/Common/</path>
    <filename>Common_2irq_8h</filename>
    <class kind="struct">irq_cpu_registers_t</class>
    <member kind="typedef">
      <type>irq_cpu_registers_t *</type>
      <name>p_irq_cpu_registers_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>irq_handler_t</name>
      <anchor>a1</anchor>
      <arglist>)(unsigned int irq_number, p_void_t parameter, irq_cpu_registers_t irq_cpu_registers)</arglist>
    </member>
    <member kind="typedef">
      <type>irq_handler_t *</type>
      <name>p_irq_handler_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/irq.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>System_2irq_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>BASE_IRQ</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDT_ENTRY_FOR_IRQ</name>
      <anchor>a1</anchor>
      <arglist>(irq)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>irq_init</name>
      <anchor>a3</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>irq_register</name>
      <anchor>a4</anchor>
      <arglist>(unsigned int irq_number, p_irq_handler_t function, p_void_t parameter)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>irq_unregister</name>
      <anchor>a5</anchor>
      <arglist>(unsigned int irq_number)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>irq_set_post_handler</name>
      <anchor>a6</anchor>
      <arglist>(unsigned int irq_number, p_function_t function)</arglist>
    </member>
    <member kind="variable">
      <type>uint8_t *</type>
      <name>current_stack_pointer</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>kernel.h</name>
    <path>/root/Chaos/Enviroments/Kernel/</path>
    <filename>kernel_8h</filename>
    <includes id="defines_8h" name="defines.h" local="yes">defines.h</includes>
    <includes id="limits_8h" name="limits.h" local="yes">limits.h</includes>
    <includes id="Common_2debug_8h" name="Common/debug.h" local="yes">Common/debug.h</includes>
    <includes id="System_2debug_8h" name="System/debug.h" local="yes">System/debug.h</includes>
    <includes id="Common_2cpu_8h" name="Common/cpu.h" local="yes">Common/cpu.h</includes>
    <includes id="System_2cpu_8h" name="System/cpu.h" local="yes">System/cpu.h</includes>
    <includes id="Common_2exception_8h" name="Common/exception.h" local="yes">Common/exception.h</includes>
    <includes id="System_2exception_8h" name="System/exception.h" local="yes">System/exception.h</includes>
    <includes id="physical__memory_8h" name="physical_memory.h" local="yes">System/physical_memory.h</includes>
    <includes id="virtual__memory_8h" name="virtual_memory.h" local="yes">System/virtual_memory.h</includes>
    <includes id="io__port_8h" name="io_port.h" local="yes">System/io_port.h</includes>
    <includes id="Common_2dma_8h" name="Common/dma.h" local="yes">Common/dma.h</includes>
    <includes id="System_2dma_8h" name="System/dma.h" local="yes">System/dma.h</includes>
    <includes id="Common_2irq_8h" name="Common/irq.h" local="yes">Common/irq.h</includes>
    <includes id="System_2irq_8h" name="System/irq.h" local="yes">System/irq.h</includes>
    <includes id="clock_8h" name="clock.h" local="yes">System/clock.h</includes>
    <includes id="Common_2timer_8h" name="Common/timer.h" local="yes">Common/timer.h</includes>
    <includes id="System_2timer_8h" name="System/timer.h" local="yes">System/timer.h</includes>
    <includes id="task__state_8h" name="task_state.h" local="yes">System/task_state.h</includes>
    <includes id="elf_8h" name="elf.h" local="yes">System/elf.h</includes>
    <includes id="system__call_8h" name="system_call.h" local="yes">System/system_call.h</includes>
    <member kind="function">
      <type>void</type>
      <name>main_bootup</name>
      <anchor>a1</anchor>
      <arglist>(int argument_count, char *arguments[])</arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>kernel_stack</name>
      <anchor>a0</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>limits.h</name>
    <path>/root/Chaos/Enviroments/Kernel/</path>
    <filename>limits_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>KERNEL_STACK_SIZE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>physical_memory.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>physical__memory_8h</filename>
    <class kind="struct">physical_memory_t</class>
    <member kind="typedef">
      <type>physical_memory_t *</type>
      <name>p_physical_memory_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_init</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_reserve</name>
      <anchor>a3</anchor>
      <arglist>(p_physical_memory_t memory, page_number_t start_page, unsigned int pages)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_allocate</name>
      <anchor>a4</anchor>
      <arglist>(p_physical_memory_t memory, page_number_t *start_page, unsigned int pages)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_deallocate</name>
      <anchor>a5</anchor>
      <arglist>(p_physical_memory_t memory, page_number_t start_page, unsigned int pages)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_reallocate</name>
      <anchor>a6</anchor>
      <arglist>(p_physical_memory_t memory, page_number_t *start_page, unsigned int pages)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_check</name>
      <anchor>a7</anchor>
      <arglist>(p_physical_memory_t memory, page_number_t start_page, unsigned int pages, unsigned int flags)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>physical_memory_get_total_pages</name>
      <anchor>a8</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>physical_memory_get_free_pages</name>
      <anchor>a9</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="variable">
      <type>physical_memory_t</type>
      <name>physical_memory_global</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>system_call.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>system__call_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_CALL_IDT_ENTRY</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>system_call_init</name>
      <anchor>a1</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>task_state.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>task__state_8h</filename>
    <class kind="struct">task_state_t</class>
    <class kind="struct">iret_data_t</class>
    <member kind="define">
      <type>#define</type>
      <name>TASK_STATE_INIT_FLAGS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TASK_STATE_NEW_EFLAGS</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>task_state_t *</type>
      <name>p_task_state_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>iret_data_t *</type>
      <name>p_iret_data_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_create</name>
      <anchor>a5</anchor>
      <arglist>(p_task_state_t task_state, p_void_t virtual_memory UNUSED, p_function_t instruction_pointer, p_uint8_t stack_pointer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_destroy</name>
      <anchor>a6</anchor>
      <arglist>(p_task_state_t task_state)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_switch_prepare</name>
      <anchor>a7</anchor>
      <arglist>(p_task_state_t task_state)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_switch_finish</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_switch_finish2</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_switch_finish_internal</name>
      <anchor>a10</anchor>
      <arglist>(irq_cpu_registers_t reg)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>task_state_init</name>
      <anchor>a11</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="variable">
      <type>task_state_t</type>
      <name>task_state_kernel</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Common/timer.h</name>
    <path>/root/Chaos/Enviroments/Kernel/Common/</path>
    <filename>Common_2timer_8h</filename>
    <includes id="Common_2irq_8h" name="Common/irq.h" local="yes">irq.h</includes>
    <member kind="typedef">
      <type>void(</type>
      <name>timer_handler_t</name>
      <anchor>a0</anchor>
      <arglist>)(unsigned int timer_number, p_void_t parameter, p_irq_cpu_registers_t irq_cpu_registers)</arglist>
    </member>
    <member kind="typedef">
      <type>timer_handler_t *</type>
      <name>p_timer_handler_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TIMER_NUMBER_SYSTEM</name>
      <anchor>a3a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/timer.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>System_2timer_8h</filename>
    <member kind="enumeration">
      <name>timer_mode_t</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TIMER_MODE_ONE_SHOT</name>
      <anchor>a11a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TIMER_MODE_PERIODIC</name>
      <anchor>a11a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>timer_init</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>timer_start</name>
      <anchor>a3</anchor>
      <arglist>(unsigned int timer_number)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>timer_stop</name>
      <anchor>a4</anchor>
      <arglist>(unsigned int timer_number)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>timer_set_period</name>
      <anchor>a5</anchor>
      <arglist>(unsigned int timer_number, uint32_t period)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>timer_set_mode</name>
      <anchor>a6</anchor>
      <arglist>(unsigned int timer_number, unsigned int mode)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>timer_read</name>
      <anchor>a7</anchor>
      <arglist>(unsigned int timer_number, uint32_t *value)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>timer_write</name>
      <anchor>a8</anchor>
      <arglist>(unsigned int timer_number, uint32_t value)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>timer_register_handler</name>
      <anchor>a9</anchor>
      <arglist>(unsigned int timer_number, p_timer_handler_t timer_handler, p_void_t parameter)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>timer_unregister_handler</name>
      <anchor>a10</anchor>
      <arglist>(unsigned int timer_number)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>virtual_memory.h</name>
    <path>/root/Chaos/Enviroments/Kernel/System/</path>
    <filename>virtual__memory_8h</filename>
    <class kind="struct">virtual_memory_t</class>
    <member kind="typedef">
      <type>virtual_memory_t *</type>
      <name>p_virtual_memory_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LEVEL_SYSTEM</name>
      <anchor>a16a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LEVEL_USER</name>
      <anchor>a16a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VIRTUAL_MEMORY_OPTION_ONLY_VIRTUAL</name>
      <anchor>a17a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VIRTUAL_MEMORY_OPTION_READONLY</name>
      <anchor>a17a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VIRTUAL_MEMORY_OPTION_NON_CACHABLE</name>
      <anchor>a17a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_init</name>
      <anchor>a7</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_create</name>
      <anchor>a8</anchor>
      <arglist>(p_virtual_memory_t virtual_memory, p_physical_memory_t physical_memory, unsigned int level)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_destroy</name>
      <anchor>a9</anchor>
      <arglist>(p_virtual_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_reserve</name>
      <anchor>a10</anchor>
      <arglist>(p_virtual_memory_t virtual_memory, page_number_t start_virtual_page, uint32_t pages, p_page_number_t start_physical_page, unsigned int options)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_allocate</name>
      <anchor>a11</anchor>
      <arglist>(p_virtual_memory_t virtual_memory, p_page_number_t start_virtual_page, uint32_t pages, p_page_number_t start_physical_page, unsigned int options)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_deallocate</name>
      <anchor>a12</anchor>
      <arglist>(p_virtual_memory_t memory, page_number_t start_page, unsigned int pages)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_check</name>
      <anchor>a13</anchor>
      <arglist>(p_virtual_memory_t memory, page_number_t start_page, unsigned int pages, unsigned int flags)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_lookup</name>
      <anchor>a14</anchor>
      <arglist>(p_virtual_memory_t memory, page_number_t virtual_page, p_page_number_t physical_page, unsigned int *flags)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_map</name>
      <anchor>a15</anchor>
      <arglist>(p_virtual_memory_t memory, page_number_t virtual_page, page_number_t physical_page, unsigned int pages, unsigned int flags)</arglist>
    </member>
    <member kind="variable">
      <type>virtual_memory_t</type>
      <name>virtual_memory_global</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_info_t</name>
    <filename>structcpu__info__t.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>platform</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>cpu_type_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>cpu_sub_type_id</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>fpu_type_id</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>vendor_id</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>hard_cpu_name</name>
      <anchor>o5</anchor>
      <arglist>[49]</arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>vendor_string</name>
      <anchor>o6</anchor>
      <arglist>[13]</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>frequency</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>family</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>model</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>stepping</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>generation</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>data_cache_l1_size</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>instructions_cache_l1_size</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>cache_l2_size</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>features</name>
      <anchor>o15</anchor>
      <arglist>[NUMBER_OF_FEATURES]</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>bugs</name>
      <anchor>o16</anchor>
      <arglist>[NUMBER_OF_BUGS]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>elf_header_t</name>
    <filename>structelf__header__t.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>identification</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>class</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>endian</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>version</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>pad</name>
      <anchor>o4</anchor>
      <arglist>[9]</arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>type</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>machine</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>version2</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>entry_point</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>program_header_offset</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>section_header_offset</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>flags</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>elf_header_size</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>program_header_entry_size</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>program_header_entries</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>section_header_entry_size</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>section_header_entries</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>section_string_index</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>elf_parsed_program_t</name>
    <filename>structelf__parsed__program__t.html</filename>
    <member kind="variable">
      <type>elf_header_t *</type>
      <name>elf_header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>elf_parsed_t</name>
    <filename>structelf__parsed__t.html</filename>
    <member kind="variable">
      <type>elf_header_t *</type>
      <name>elf_header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>elf_section_header_t *</type>
      <name>string_header</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>elf_section_header_t *</type>
      <name>symbol_header</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>elf_section_header_t *</type>
      <name>relocation_header</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>image</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>elf_program_header_t</name>
    <filename>structelf__program__header__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>type</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>offset</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>virtual_address</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>physical_address</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>file_size</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>memory_size</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>flags</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>align</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>elf_relocation_t</name>
    <filename>structelf__relocation__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>offset</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>symbol_type</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>symbol_index</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>elf_section_header_t</name>
    <filename>structelf__section__header__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>type</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>flags</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>address</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>offset</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>size</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>link</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>info</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>address_align</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>entry_size</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>elf_symbol_t</name>
    <filename>structelf__symbol__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>value</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>type</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>bind</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>other</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>section_header</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>exception_context_t</name>
    <filename>structexception__context__t.html</filename>
    <member kind="variable">
      <type></type>
      <name>LIST_NODE_PART</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>is_raised</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_void_t</type>
      <name>catch_point</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>catch_stack_pointer</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>edi</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esi</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ebp</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ebx</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>edx</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ecx</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eax</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>invoke_stack_pointer</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>exception_hardware_description_t</name>
    <filename>structexception__hardware__description__t.html</filename>
    <member kind="variable">
      <type>void *</type>
      <name>handler</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>class_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>reason</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>error_code_type</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>exception_hardware_info_t</name>
    <filename>structexception__hardware__info__t.html</filename>
    <member kind="variable">
      <type>exception_info_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eflags</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>cs</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ss</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>gs</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>fs</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>es</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ds</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>edi</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esi</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ebp</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esp</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ebx</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>edx</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ecx</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eax</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>exception_hardware_page_info_t</name>
    <filename>structexception__hardware__page__info__t.html</filename>
    <member kind="variable">
      <type>exception_hardware_info_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>page_error_t</type>
      <name>page_error</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>address_t</type>
      <name>address</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>exception_hardware_segment_info_t</name>
    <filename>structexception__hardware__segment__info__t.html</filename>
    <member kind="variable">
      <type>exception_hardware_info_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>segment_error_t</type>
      <name>segment_error</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>exception_hardware_with_error_code_info_t</name>
    <filename>structexception__hardware__with__error__code__info__t.html</filename>
    <member kind="variable">
      <type>exception_hardware_info_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>error_code</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>exception_info_t</name>
    <filename>structexception__info__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>pc</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>type</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>id</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>function_info_t</name>
    <filename>structfunction__info__t.html</filename>
    <member kind="variable">
      <type>const char *</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_function_t</type>
      <name>function</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>iret_data_t</name>
    <filename>structiret__data__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eip</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>cs</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eflags</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>irq_cpu_registers_t</name>
    <filename>structirq__cpu__registers__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>edi</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esi</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ebp</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esp</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ebx</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>edx</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ecx</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eax</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eip</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>cs</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eflags</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>physical_memory_t</name>
    <filename>structphysical__memory__t.html</filename>
    <member kind="variable">
      <type>pool_t</type>
      <name>block_pool</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_pool_of_integers_t</type>
      <name>node_allocator</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_range_node_t</type>
      <name>node_pool</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>raw_memory_t</type>
      <name>raw_memory</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>storm_info_t</name>
    <filename>structstorm__info__t.html</filename>
    <member kind="variable">
      <type>const char *</type>
      <name>version</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>compiler</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>compiler_version</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>maintainer</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>build_date</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>build_time</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>command_line</name>
      <anchor>o6</anchor>
      <arglist>[COMMAND_LINE_SIZE]</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>memory_size</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_memory_maps</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>storm_memory_map_t</type>
      <name>memory_map</name>
      <anchor>o9</anchor>
      <arglist>[MAX_NUMBER_OF_STORM_MEMORY_MAPS]</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_modules</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>storm_module_info_t</type>
      <name>module_info</name>
      <anchor>o11</anchor>
      <arglist>[MAX_NUMBER_OF_STORM_MODULES]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>storm_memory_map_t</name>
    <filename>structstorm__memory__map__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>size</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_uint8_t</type>
      <name>base_address</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>size_t</type>
      <name>length</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>type</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>storm_module_info_t</name>
    <filename>structstorm__module__info__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>start</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>end</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>name</name>
      <anchor>o2</anchor>
      <arglist>[STRING_MAX_LENGTH]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>task_state_t</name>
    <filename>structtask__state__t.html</filename>
    <member kind="variable">
      <type>tss_t</type>
      <name>tss</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>virtual_memory_t</name>
    <filename>structvirtual__memory__t.html</filename>
    <member kind="variable">
      <type>p_physical_memory_t</type>
      <name>physical_memory</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>level</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>code_selector</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>data_selector</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>stack_selector</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_page_directory_t</type>
      <name>page_directory</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>is_direct</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_pool_t</type>
      <name>block_pool</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_pool_of_integers_t</type>
      <name>node_allocator</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_range_node_t</type>
      <name>node_pool</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>raw_memory_t</type>
      <name>raw_memory</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
