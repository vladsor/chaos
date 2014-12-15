<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="file">
    <name>cpu_common.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/</path>
    <filename>cpu__common_8h</filename>
  </compound>
  <compound kind="file">
    <name>cr0.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Registers/</path>
    <filename>cr0_8h</filename>
    <class kind="struct">cpu_register_cr0_t</class>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_PE</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_MP</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_EM</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_TS</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_ET</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_NE</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_WP</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_AM</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_NW</name>
      <anchor>ga8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_CD</name>
      <anchor>ga9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_PG</name>
      <anchor>ga10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cr2.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Registers/</path>
    <filename>cr2_8h</filename>
    <class kind="struct">cpu_register_cr2_t</class>
  </compound>
  <compound kind="file">
    <name>cr3.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Registers/</path>
    <filename>cr3_8h</filename>
    <class kind="struct">cpu_register_cr3_t</class>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR3_PWT</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR3_PCD</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cr4.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Registers/</path>
    <filename>cr4_8h</filename>
    <class kind="struct">cpu_register_cr4_t</class>
  </compound>
  <compound kind="file">
    <name>descriptor.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Segmentation/</path>
    <filename>descriptor_8h</filename>
    <class kind="struct">descriptor_t</class>
    <class kind="struct">gate_descriptor_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DESCRIPTOR_NULL</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DESCRIPTOR_CODE</name>
      <anchor>ga8</anchor>
      <arglist>(base, limit, granularity, dpl, present, digit)</arglist>
    </member>
    <member kind="enumeration">
      <name>privilege_level_t</name>
      <anchor>ga15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>descriptor_type_t</name>
      <anchor>ga16</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_TASK_GATE_32</name>
      <anchor>gga16a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_TSS</name>
      <anchor>gga16a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_CALL_GATE</name>
      <anchor>gga16a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_INTERRUPT_GATE_32</name>
      <anchor>gga16a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_TRAP_GATE_32</name>
      <anchor>gga16a23</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>exceptions.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/</path>
    <filename>exceptions_8h</filename>
  </compound>
  <compound kind="file">
    <name>fpu.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/</path>
    <filename>fpu_8h</filename>
    <class kind="struct">fpu_status_word_t</class>
    <class kind="struct">fpu_control_word_t</class>
    <class kind="struct">fpu_tag_word_t</class>
    <class kind="struct">fpu_state_t</class>
    <member kind="define">
      <type>#define</type>
      <name>FPU_PRECISION_SINGLE</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_PRECISION_DOUBLE</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_PRECISION_EXTENDED</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_ROUND_TO_NEAREST</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_ROUND_DOWN</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_ROUND_UP</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_ROUND_TOWARD</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>fpu_state_save</name>
      <anchor>a11</anchor>
      <arglist>(fpu_state)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>fpu_state_restore</name>
      <anchor>a12</anchor>
      <arglist>(fpu_state)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>gdt.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Segmentation/</path>
    <filename>gdt_8h</filename>
    <member kind="variable">
      <type>descriptor_t</type>
      <name>gdt</name>
      <anchor>ga0</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>idt.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Segmentation/</path>
    <filename>idt_8h</filename>
    <member kind="variable">
      <type>descriptor_t</type>
      <name>idt</name>
      <anchor>ga0</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ia32/limits.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/</path>
    <filename>ia32_2limits_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>GDT_ENTRIES</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GDT_SIZE</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDT_ENTRIES</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IDT_SIZE</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>page.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Paging/</path>
    <filename>page_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_SIZE</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_BITS</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_ADDRESS</name>
      <anchor>ga3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_ALIGN_DOWN</name>
      <anchor>ga5</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_NUMBER</name>
      <anchor>ga6</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_PRESENT</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_WRITABLE</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_NON_PRIVILEGED</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_WRITE_THROUGH</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_CACHE_DISABLE</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_GLOBAL</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>page_number_t</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>page_directory.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Paging/</path>
    <filename>page__directory_8h</filename>
    <class kind="struct">page_directory_4mb_t</class>
    <class kind="struct">page_directory_t</class>
  </compound>
  <compound kind="file">
    <name>page_table.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Paging/</path>
    <filename>page__table_8h</filename>
    <class kind="struct">page_table_t</class>
  </compound>
  <compound kind="file">
    <name>paging.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/</path>
    <filename>paging_8h</filename>
    <includes id="page__directory_8h" name="page_directory.h" local="yes">Paging/page_directory.h</includes>
    <includes id="page__table_8h" name="page_table.h" local="yes">Paging/page_table.h</includes>
    <includes id="page_8h" name="page.h" local="yes">Paging/page.h</includes>
  </compound>
  <compound kind="file">
    <name>segmentation.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/</path>
    <filename>segmentation_8h</filename>
    <includes id="descriptor_8h" name="descriptor.h" local="yes">Segmentation/descriptor.h</includes>
    <includes id="selectors_8h" name="selectors.h" local="yes">Segmentation/selectors.h</includes>
    <includes id="gdt_8h" name="gdt.h" local="yes">Segmentation/gdt.h</includes>
    <includes id="tss_8h" name="tss.h" local="yes">Segmentation/tss.h</includes>
  </compound>
  <compound kind="file">
    <name>selectors.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Segmentation/</path>
    <filename>selectors_8h</filename>
    <class kind="struct">selector_t</class>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR</name>
      <anchor>ga0</anchor>
      <arglist>(index, ldt, rpl)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_TSS1</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_TSS2</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>system_registers.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/</path>
    <filename>system__registers_8h</filename>
  </compound>
  <compound kind="file">
    <name>tss.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/System/ia32/Segmentation/</path>
    <filename>tss_8h</filename>
    <class kind="struct">tss_t</class>
    <member kind="define">
      <type>#define</type>
      <name>TSS_NEW_EFLAGS</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_register_cr0_t</name>
    <filename>structcpu__register__cr0__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>PE</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>MP</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>EM</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>TS</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ET</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>NE</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>WP</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>AM</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>NW</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>CD</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>PG</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_register_cr2_t</name>
    <filename>structcpu__register__cr2__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>page_fault_linear_address</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_register_cr3_t</name>
    <filename>structcpu__register__cr3__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>writes_transparent</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>cache_disable</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>page_directory_base</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_register_cr4_t</name>
    <filename>structcpu__register__cr4__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>VME</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>PVI</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>TSD</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>DE</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>PSE</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>PAE</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>MCE</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>PGE</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>PCE</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>OSFXSR</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>OSXMMEXCPT</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>descriptor_t</name>
    <filename>structdescriptor__t.html</filename>
    <member kind="variable">
      <type>uint16_t</type>
      <name>limit_lo</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>base_lo</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>base_hi</name>
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
      <name>descriptor_type</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>dpl</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>segment_present</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>limit_hi</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>available</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>zero</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>default_operation_size</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>granularity</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>base_hi2</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fpu_control_word_t</name>
    <filename>structfpu__control__word__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>IM</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>DM</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ZM</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>OM</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>UM</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>PM</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>precision_control</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>rounding_control</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>infinity_control</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fpu_state_t</name>
    <filename>structfpu__state__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>fpu_status_word_t</name>
    <filename>structfpu__status__word__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>IE</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>DE</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ZE</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>OE</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>UE</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>PE</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>stack_fault</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>error_summary_status</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>C0</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>C1</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>C2</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>top_of_stack_pointer</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>C3</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>busy</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fpu_tag_word_t</name>
    <filename>structfpu__tag__word__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>gate_descriptor_t</name>
    <filename>structgate__descriptor__t.html</filename>
    <member kind="variable">
      <type>uint16_t</type>
      <name>offset_lo</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>segment_selector</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>params</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>dpl</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>present</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>offset_hi</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>page_directory_4mb_t</name>
    <filename>structpage__directory__4mb__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>present</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>read_write</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>user_supervisor</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>write_through</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>cache_disable</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>accessed</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>dirty</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>page_size</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>global</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>available</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>zero</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>page_base</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>page_directory_t</name>
    <filename>structpage__directory__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>present</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>read_write</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>user_supervisor</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>write_through</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>cache_disable</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>accessed</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>zero</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>page_size</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>global</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>available</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>page_table_base</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>page_error_t</name>
    <filename>structpage__error__t.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>p</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>w_r</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>u_s</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>rsvd</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>page_table_t</name>
    <filename>structpage__table__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>present</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>read_write</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>user_supervisor</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>write_through</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>cache_disable</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>accessed</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>dirty</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>zero</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>global</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>available</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>page_base</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>segment_error_t</name>
    <filename>structsegment__error__t.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>ext</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>idt</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ti</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>segment_selector_index</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>selector_t</name>
    <filename>structselector__t.html</filename>
    <member kind="variable">
      <type>uint16_t</type>
      <name>RPL</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>TI</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>index</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>tss_t</name>
    <filename>structtss__t.html</filename>
    <member kind="variable">
      <type>uint16_t</type>
      <name>previous_task_link</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esp0</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>ss0</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esp1</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>ss1</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esp2</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>ss2</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>cr3</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eip</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eflags</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eax</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ecx</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>edx</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ebx</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esp</name>
      <anchor>o18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>ebp</name>
      <anchor>o19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>esi</name>
      <anchor>o20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>edi</name>
      <anchor>o21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>es</name>
      <anchor>o22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>cs</name>
      <anchor>o24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>ss</name>
      <anchor>o26</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>ds</name>
      <anchor>o28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>fs</name>
      <anchor>o30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>gs</name>
      <anchor>o32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>ldt_selector</name>
      <anchor>o34</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>iomap_base</name>
      <anchor>o38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>iomap_size</name>
      <anchor>o39</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>iomap</name>
      <anchor>o40</anchor>
      <arglist>[0]</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_cpuid_vendor_strings</name>
    <title>Hardcoded vendors strings</title>
    <filename>group__group__cpuid__vendor__strings.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>VENDOR_UNKNOWN_STRING</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VENDOR_AMD_STRING</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VENDOR_INTEL_STRING</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VENDOR_CYRIX_STRING</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VENDOR_CENTAUR_STRING</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VENDOR_UMC_STRING</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VENDOR_NEXGEN_STRING</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VENDOR_RISETECHNOLOGY_STRING</name>
      <anchor>ga8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VENDOR_TRANSMETA_STRING</name>
      <anchor>ga9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_exception_classes</name>
    <title>Exception classifications</title>
    <filename>group__group__exception__classes.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_CLASS_FAULT</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_CLASS_TRAP</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_CLASS_ABORT</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_exception_codes</name>
    <title>Exception codes</title>
    <filename>group__group__exception__codes.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_DIVIDE_ERROR</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_DEBUG</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_NONMASKABLE_INTERRUPT</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_BREAKPOINT</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_OVERFLOW</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_BOUND_RANGE_EXCEEDED</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_INVALID_OPCODE</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_DEVICE_NOT_AVAILABLE</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_DOUBLE_FAULT</name>
      <anchor>ga8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN</name>
      <anchor>ga9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_INVALID_TSS</name>
      <anchor>ga10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_SEGMENT_NOT_PRESENT</name>
      <anchor>ga11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_STACK_FAULT</name>
      <anchor>ga12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_GENERAL_PROTECTION</name>
      <anchor>ga13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_PAGE_FAULT</name>
      <anchor>ga14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_DUMMY</name>
      <anchor>ga15</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_FLOATING_POINT_ERROR</name>
      <anchor>ga16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_ALIGNMENT_CHECK</name>
      <anchor>ga17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_MACHINE_CHECK</name>
      <anchor>ga18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_STREAMING_SIMD_EXTENSIONS</name>
      <anchor>ga19</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_exception_error_codes</name>
    <title>Exception error codes</title>
    <filename>group__group__exception__error__codes.html</filename>
    <class kind="struct">segment_error_t</class>
    <class kind="struct">page_error_t</class>
  </compound>
  <compound kind="group">
    <name>group_exceptions</name>
    <title>Exceptions</title>
    <filename>group__group__exceptions.html</filename>
    <subgroup>group_exception_classes</subgroup>
    <subgroup>group_exception_codes</subgroup>
    <subgroup>group_exception_error_codes</subgroup>
  </compound>
  <compound kind="group">
    <name>group_fpu_precision</name>
    <title>FPU precision flags</title>
    <filename>group__group__fpu__precision.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>FPU_PRECISION_SINGLE</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_PRECISION_DOUBLE</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_PRECISION_EXTENDED</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_fpu_round</name>
    <title>FPU round flags</title>
    <filename>group__group__fpu__round.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>FPU_ROUND_TO_NEAREST</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_ROUND_DOWN</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_ROUND_UP</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPU_ROUND_TOWARD</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_pages</name>
    <title>Pages</title>
    <filename>group__group__pages.html</filename>
    <subgroup>group_page_flags</subgroup>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_SIZE</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_BITS</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_ADDRESS</name>
      <anchor>ga3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_ALIGN_DOWN</name>
      <anchor>ga5</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_NUMBER</name>
      <anchor>ga6</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>page_number_t</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_page_flags</name>
    <title>Page flags</title>
    <filename>group__group__page__flags.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_PRESENT</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_WRITABLE</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_NON_PRIVILEGED</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_WRITE_THROUGH</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_CACHE_DISABLE</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_GLOBAL</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_page_directory</name>
    <title>Page directory</title>
    <filename>group__group__page__directory.html</filename>
    <class kind="struct">page_directory_4mb_t</class>
    <class kind="struct">page_directory_t</class>
  </compound>
  <compound kind="group">
    <name>group_page_table</name>
    <title>Page table</title>
    <filename>group__group__page__table.html</filename>
    <class kind="struct">page_table_t</class>
  </compound>
  <compound kind="group">
    <name>group_paging</name>
    <title>Paging</title>
    <filename>group__group__paging.html</filename>
    <subgroup>group_pages</subgroup>
    <subgroup>group_page_directory</subgroup>
    <subgroup>group_page_table</subgroup>
  </compound>
  <compound kind="group">
    <name>group_system_register_cr0</name>
    <title>CR0 register</title>
    <filename>group__group__system__register__cr0.html</filename>
    <class kind="struct">cpu_register_cr0_t</class>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_PE</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_MP</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_EM</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_TS</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_ET</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_NE</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_WP</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_AM</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_NW</name>
      <anchor>ga8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_CD</name>
      <anchor>ga9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR0_PG</name>
      <anchor>ga10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_system_register_cr2</name>
    <title>CR2 register</title>
    <filename>group__group__system__register__cr2.html</filename>
    <class kind="struct">cpu_register_cr2_t</class>
  </compound>
  <compound kind="group">
    <name>group_system_register_cr3</name>
    <title>CR3 register</title>
    <filename>group__group__system__register__cr3.html</filename>
    <class kind="struct">cpu_register_cr3_t</class>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR3_PWT</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CR3_PCD</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_system_register_cr4</name>
    <title>CR4 register</title>
    <filename>group__group__system__register__cr4.html</filename>
    <class kind="struct">cpu_register_cr4_t</class>
  </compound>
  <compound kind="group">
    <name>group_segmentation_descriptors</name>
    <title>Segment descriptors</title>
    <filename>group__group__segmentation__descriptors.html</filename>
    <class kind="struct">descriptor_t</class>
    <class kind="struct">gate_descriptor_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DESCRIPTOR_NULL</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DESCRIPTOR_CODE</name>
      <anchor>ga8</anchor>
      <arglist>(base, limit, granularity, dpl, present, digit)</arglist>
    </member>
    <member kind="enumeration">
      <name>privilege_level_t</name>
      <anchor>ga15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>descriptor_type_t</name>
      <anchor>ga16</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_TASK_GATE_32</name>
      <anchor>gga16a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_TSS</name>
      <anchor>gga16a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_CALL_GATE</name>
      <anchor>gga16a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_INTERRUPT_GATE_32</name>
      <anchor>gga16a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTOR_TYPE_TRAP_GATE_32</name>
      <anchor>gga16a23</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_segmentation_gdt</name>
    <title>GDT</title>
    <filename>group__group__segmentation__gdt.html</filename>
    <member kind="variable">
      <type>descriptor_t</type>
      <name>gdt</name>
      <anchor>ga0</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_segmentation_idt</name>
    <title>IDT</title>
    <filename>group__group__segmentation__idt.html</filename>
    <member kind="variable">
      <type>descriptor_t</type>
      <name>idt</name>
      <anchor>ga0</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_segmentation_selectors</name>
    <title>Segment selectors</title>
    <filename>group__group__segmentation__selectors.html</filename>
    <class kind="struct">selector_t</class>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR</name>
      <anchor>ga0</anchor>
      <arglist>(index, ldt, rpl)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_TSS1</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SELECTOR_TSS2</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_segmentation_tss</name>
    <title>TSS</title>
    <filename>group__group__segmentation__tss.html</filename>
    <class kind="struct">tss_t</class>
    <member kind="define">
      <type>#define</type>
      <name>TSS_NEW_EFLAGS</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>group_segmentation</name>
    <title>Segmentation</title>
    <filename>group__group__segmentation.html</filename>
    <subgroup>group_segmentation_descriptors</subgroup>
    <subgroup>group_segmentation_gdt</subgroup>
    <subgroup>group_segmentation_idt</subgroup>
    <subgroup>group_segmentation_selectors</subgroup>
    <subgroup>group_segmentation_tss</subgroup>
  </compound>
  <compound kind="group">
    <name>group_system_registers</name>
    <title>System registers</title>
    <filename>group__group__system__registers.html</filename>
    <subgroup>group_system_register_cr0</subgroup>
    <subgroup>group_system_register_cr2</subgroup>
    <subgroup>group_system_register_cr3</subgroup>
    <subgroup>group_system_register_cr4</subgroup>
  </compound>
</tagfile>
