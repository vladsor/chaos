<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="file">
    <name>alignment.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>alignment_8h</filename>
  </compound>
  <compound kind="file">
    <name>atomic.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/</path>
    <filename>atomic_8h</filename>
    <includes id="integer__operations_8h" name="integer_operations.h" local="yes">Atomic/integer_operations.h</includes>
    <includes id="bit__operations_8h" name="bit_operations.h" local="yes">Atomic/bit_operations.h</includes>
  </compound>
  <compound kind="file">
    <name>bit.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>bit_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>LOW_32</name>
      <anchor>a0</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HIGH_32</name>
      <anchor>a1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOW_16</name>
      <anchor>a2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HIGH_16</name>
      <anchor>a3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOW_8</name>
      <anchor>a4</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HIGH_8</name>
      <anchor>a5</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_SET</name>
      <anchor>a6</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_CLEAR</name>
      <anchor>a7</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_SWITCH</name>
      <anchor>a8</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_GET</name>
      <anchor>a9</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_IN_BYTES</name>
      <anchor>a10</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_VALUE</name>
      <anchor>a11</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_SELECT_HIGH</name>
      <anchor>a12</anchor>
      <arglist>(x, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_SELECT_LOW</name>
      <anchor>a13</anchor>
      <arglist>(x, high)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_SELECT</name>
      <anchor>a14</anchor>
      <arglist>(x, high, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_GET_HIGH</name>
      <anchor>a15</anchor>
      <arglist>(x, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_GET_LOW</name>
      <anchor>a16</anchor>
      <arglist>(x, high)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_GET</name>
      <anchor>a17</anchor>
      <arglist>(x, high, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_SET_HIGH</name>
      <anchor>a18</anchor>
      <arglist>(x, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_SET_LOW</name>
      <anchor>a19</anchor>
      <arglist>(x, high)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_SET</name>
      <anchor>a20</anchor>
      <arglist>(x, high, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_CLEAR_HIGH</name>
      <anchor>a21</anchor>
      <arglist>(x, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_CLEAR_LOW</name>
      <anchor>a22</anchor>
      <arglist>(x, high)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_CLEAR</name>
      <anchor>a23</anchor>
      <arglist>(x, high, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_SWITCH_HIGH</name>
      <anchor>a24</anchor>
      <arglist>(x, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_SWITCH_LOW</name>
      <anchor>a25</anchor>
      <arglist>(h, high)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BITS_SWITCH</name>
      <anchor>a26</anchor>
      <arglist>(x, high, low)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_MAP_DECLARE</name>
      <anchor>a27</anchor>
      <arglist>(name, length)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_MAP_SET</name>
      <anchor>a28</anchor>
      <arglist>(name, index)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_MAP_CLEAR</name>
      <anchor>a29</anchor>
      <arglist>(name, index)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIT_MAP_SWITCH</name>
      <anchor>a30</anchor>
      <arglist>(name, index)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bit_operations.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Atomic/</path>
    <filename>bit__operations_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>LOCK_PREFIX</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ADDR</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>find_first_zero_bit</name>
      <anchor>a2</anchor>
      <arglist>(void *addr, size_t size)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>find_next_zero_bit</name>
      <anchor>a3</anchor>
      <arglist>(void *addr, int size, int offset)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>unsigned long</type>
      <name>ffz</name>
      <anchor>a4</anchor>
      <arglist>(unsigned long word)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>ffs</name>
      <anchor>a5</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_bit_set</name>
      <anchor>a6</anchor>
      <arglist>(volatile void *addr, int nr)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_bit_clear</name>
      <anchor>a7</anchor>
      <arglist>(volatile void *addr, int nr)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_bit_change</name>
      <anchor>a8</anchor>
      <arglist>(volatile void *addr, int nr)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>byte_order.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>byte__order_8h</filename>
    <member kind="function" static="yes">
      <type>uint32_t</type>
      <name>byte_swap_uint32</name>
      <anchor>a0</anchor>
      <arglist>(uint32_t x)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint16_t</type>
      <name>byte_swap_uint16</name>
      <anchor>a1</anchor>
      <arglist>(uint16_t x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>clear.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Memory/</path>
    <filename>clear_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>memory_clear</name>
      <anchor>a0</anchor>
      <arglist>(void *address, size_t size)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>memory_clear_page</name>
      <anchor>a1</anchor>
      <arglist>(void *address)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>common_enviroment.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>common__enviroment_8h</filename>
    <includes id="stdint_8h" name="stdint.h" local="yes">stdint.h</includes>
    <includes id="stdint__ext_8h" name="stdint_ext.h" local="yes">stdint_ext.h</includes>
    <includes id="standart__arguments_8h" name="standart_arguments.h" local="yes">standart_arguments.h</includes>
    <includes id="defines_8h" name="defines.h" local="yes">defines.h</includes>
    <includes id="bit_8h" name="bit.h" local="yes">bit.h</includes>
    <includes id="limits_8h" name="limits.h" local="yes">limits.h</includes>
    <includes id="return__value_8h" name="return_value.h" local="yes">return_value.h</includes>
    <includes id="iterator_8h" name="iterator.h" local="yes">iterator.h</includes>
    <includes id="byte__order_8h" name="byte_order.h" local="yes">byte_order.h</includes>
    <includes id="endian_8h" name="endian.h" local="yes">endian.h</includes>
    <includes id="cpu__common_8h" name="cpu_common.h" local="yes">ia32/cpu_common.h</includes>
    <includes id="flags_8h" name="flags.h" local="yes">ia32/flags.h</includes>
    <includes id="port_8h" name="port.h" local="yes">ia32/port.h</includes>
    <includes id="page_8h" name="page.h" local="yes">ia32/page.h</includes>
    <includes id="cpu__features_8h" name="cpu_features.h" local="yes">ia32/cpu_features.h</includes>
    <includes id="cpu__bugs_8h" name="cpu_bugs.h" local="yes">ia32/cpu_bugs.h</includes>
    <includes id="locks_8h" name="locks.h" local="yes">ia32/locks.h</includes>
    <includes id="memory_8h" name="memory.h" local="yes">ia32/memory.h</includes>
    <member kind="typedef">
      <type>int(*</type>
      <name>compare_function_t</name>
      <anchor>a0</anchor>
      <arglist>)(void *key1, void *key2)</arglist>
    </member>
    <member kind="enumeration">
      <name>condition_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONDITION_EQUAL</name>
      <anchor>a7a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONDITION_MORE</name>
      <anchor>a7a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONDITION_LESS</name>
      <anchor>a7a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONDITION_NOT_EQUAL</name>
      <anchor>a7a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONDITION_EQUAL_OR_MORE</name>
      <anchor>a7a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CONDITION_EQUAL_OR_LESS</name>
      <anchor>a7a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>compare.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Memory/</path>
    <filename>compare_8h</filename>
    <member kind="function" static="yes">
      <type>int</type>
      <name>memory_compare</name>
      <anchor>a0</anchor>
      <arglist>(void *memory1, void *memory2, unsigned int size)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>copy.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Memory/</path>
    <filename>copy_8h</filename>
    <member kind="function" static="yes">
      <type>void *</type>
      <name>memory_copy</name>
      <anchor>a0</anchor>
      <arglist>(void *to, void *from, unsigned int size)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cpu_bugs.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/</path>
    <filename>cpu__bugs_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_BUGS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>cpu_bug_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_BUG_POPAD</name>
      <anchor>a4a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_BUG_F0_0F</name>
      <anchor>a4a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_BUG_LAST</name>
      <anchor>a4a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cpu_common.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/</path>
    <filename>cpu__common_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>cpu_push_all</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>cpu_pop_all</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>cpu_no_operation</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint32_t</type>
      <name>cpu_esp_get</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cpu_features.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/</path>
    <filename>cpu__features_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_FEATURES</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>platform_t</name>
      <anchor>a127</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PLATFORM_I386</name>
      <anchor>a127a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PLATFORM_ARM</name>
      <anchor>a127a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PLATFORM_MIPS</name>
      <anchor>a127a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PLATFORM_SPARC</name>
      <anchor>a127a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>cpu_vendor_t</name>
      <anchor>a128</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VENDOR_UNKNOWN</name>
      <anchor>a128a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VENDOR_AMD</name>
      <anchor>a128a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VENDOR_INTEL</name>
      <anchor>a128a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VENDOR_CYRIX</name>
      <anchor>a128a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VENDOR_CENTAUR</name>
      <anchor>a128a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VENDOR_UMC</name>
      <anchor>a128a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VENDOR_NEXGEN</name>
      <anchor>a128a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VENDOR_RISETECHNOLOGY</name>
      <anchor>a128a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VENDOR_TRANSMETA</name>
      <anchor>a128a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>cpu_t</name>
      <anchor>a129</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_PROCESSOR</name>
      <anchor>a129a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_Intel</name>
      <anchor>a129a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_AMD</name>
      <anchor>a129a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_Cyrix</name>
      <anchor>a129a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_Centaur</name>
      <anchor>a129a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_Transmeta</name>
      <anchor>a129a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_8086</name>
      <anchor>a129a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_80186</name>
      <anchor>a129a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_80286</name>
      <anchor>a129a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_80386</name>
      <anchor>a129a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_80486</name>
      <anchor>a129a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_80586</name>
      <anchor>a129a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_80686</name>
      <anchor>a129a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_INTEL_Pentium</name>
      <anchor>a129a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_INTEL_P6</name>
      <anchor>a129a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UNKNOWN_AMD_Athlon</name>
      <anchor>a129a29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_AMD_486</name>
      <anchor>a129a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_AMD_486DX2</name>
      <anchor>a129a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_AMD_486DX4</name>
      <anchor>a129a32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_AMD_5x86</name>
      <anchor>a129a33</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_AMD_K5</name>
      <anchor>a129a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_AMD_K6</name>
      <anchor>a129a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_AMD_K6_2</name>
      <anchor>a129a36</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_AMD_K6_3</name>
      <anchor>a129a37</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_AMD_Athlon</name>
      <anchor>a129a38</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Cyrix_5x86</name>
      <anchor>a129a39</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Cyrix_MediaGX</name>
      <anchor>a129a40</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Cyrix_MediaGXm</name>
      <anchor>a129a41</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Cyrix_M1</name>
      <anchor>a129a42</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Cyrix_M2</name>
      <anchor>a129a43</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Cyrix_III</name>
      <anchor>a129a44</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Cyrix_6x86</name>
      <anchor>a129a45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Cyrix_6x86MX</name>
      <anchor>a129a46</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Centaur_C6</name>
      <anchor>a129a47</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Centaur_C2</name>
      <anchor>a129a48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Centaur_C3</name>
      <anchor>a129a49</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Rise_mP6</name>
      <anchor>a129a50</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UMC_U5D</name>
      <anchor>a129a51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_UMC_U5S</name>
      <anchor>a129a52</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_486</name>
      <anchor>a129a53</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_486DX</name>
      <anchor>a129a54</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_486SX</name>
      <anchor>a129a55</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_486SL</name>
      <anchor>a129a56</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_486DX2</name>
      <anchor>a129a57</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_486SX2</name>
      <anchor>a129a58</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_486DX4</name>
      <anchor>a129a59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_Pentium</name>
      <anchor>a129a60</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_Pentium_Pro</name>
      <anchor>a129a61</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_Pentium_II</name>
      <anchor>a129a62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_Pentium_III</name>
      <anchor>a129a63</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_INTEL_Pentium_4</name>
      <anchor>a129a64</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Transmeta_TM3200</name>
      <anchor>a129a65</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Transmeta_TM5400</name>
      <anchor>a129a66</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_TYPE_Transmeta_TM5600</name>
      <anchor>a129a67</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>cpu_sub_t</name>
      <anchor>a130</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_A_step</name>
      <anchor>a130a68</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_Standart</name>
      <anchor>a130a69</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_Mobile</name>
      <anchor>a130a70</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_Overdrive</name>
      <anchor>a130a71</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_WriteBackEnhanced</name>
      <anchor>a130a72</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_MMX</name>
      <anchor>a130a73</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_Celeron</name>
      <anchor>a130a74</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_CeleronII</name>
      <anchor>a130a75</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_Xeon</name>
      <anchor>a130a76</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_Coppermine</name>
      <anchor>a130a77</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_Duron</name>
      <anchor>a130a78</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_SUB_TYPE_Thinderbird</name>
      <anchor>a130a79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>fpu_t</name>
      <anchor>a131</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FPU_TYPE_NONE</name>
      <anchor>a131a80</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FPU_TYPE_8087</name>
      <anchor>a131a81</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FPU_TYPE_80287</name>
      <anchor>a131a82</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FPU_TYPE_80387</name>
      <anchor>a131a83</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FPU_TYPE_BUILT_IN</name>
      <anchor>a131a84</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>cpu_feature_t</name>
      <anchor>a132</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_CPUID</name>
      <anchor>a132a85</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_CPU_NAME</name>
      <anchor>a132a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_FPU</name>
      <anchor>a132a87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_CACHE_L1_INFO</name>
      <anchor>a132a88</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_CACHE_L2_INFO</name>
      <anchor>a132a89</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_HARD_NAME</name>
      <anchor>a132a90</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_VME</name>
      <anchor>a132a91</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_DEBUG</name>
      <anchor>a132a92</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_PSE</name>
      <anchor>a132a93</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_TSC</name>
      <anchor>a132a94</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_MSR</name>
      <anchor>a132a95</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_PAE</name>
      <anchor>a132a96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_MCE</name>
      <anchor>a132a97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_CMPXCHG8</name>
      <anchor>a132a98</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_APIC</name>
      <anchor>a132a99</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_SEP</name>
      <anchor>a132a100</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_MTRR</name>
      <anchor>a132a101</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_PGE</name>
      <anchor>a132a102</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_MCA</name>
      <anchor>a132a103</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_CMOV</name>
      <anchor>a132a104</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_PAT</name>
      <anchor>a132a105</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_PSE36</name>
      <anchor>a132a106</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_PSN</name>
      <anchor>a132a107</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_CLFLSH</name>
      <anchor>a132a108</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_DS</name>
      <anchor>a132a109</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_ACPI</name>
      <anchor>a132a110</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_MMX</name>
      <anchor>a132a111</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_MMX_EXT</name>
      <anchor>a132a112</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_FXSR</name>
      <anchor>a132a113</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_3DNOW</name>
      <anchor>a132a114</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_3DNOW_EXT</name>
      <anchor>a132a115</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_SSE</name>
      <anchor>a132a116</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_SSE_FP</name>
      <anchor>a132a117</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_SSE_MMX</name>
      <anchor>a132a118</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_SSE2</name>
      <anchor>a132a119</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_SS</name>
      <anchor>a132a120</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_TM</name>
      <anchor>a132a121</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_IA_64</name>
      <anchor>a132a122</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_AA_64</name>
      <anchor>a132a123</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_VIDC</name>
      <anchor>a132a124</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_BMC</name>
      <anchor>a132a125</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FEATURE_LAST</name>
      <anchor>a132a126</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>defines.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>defines_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>NULL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRUE</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FALSE</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MIN</name>
      <anchor>a3</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX</name>
      <anchor>a4</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>KIB</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MIB</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GIB</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NORETURN</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNUSED</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEPRECATED</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PACKED</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ABS</name>
      <anchor>a12</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ROUND_DOWN</name>
      <anchor>a13</anchor>
      <arglist>(N, S)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ROUND_UP</name>
      <anchor>a14</anchor>
      <arglist>(N, S)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ALIGN</name>
      <anchor>a15</anchor>
      <arglist>(x, align)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>offset_of</name>
      <anchor>a16</anchor>
      <arglist>(TYPE, MEMBER)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>endian.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>endian_8h</filename>
  </compound>
  <compound kind="file">
    <name>endian_big.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>endian__big_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_BIG_ENDIAN</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>big_endian_to_native_uint64</name>
      <anchor>a1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>big_endian_to_native_uint32</name>
      <anchor>a2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>big_endian_to_native_uint16</name>
      <anchor>a3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>little_endian_to_native_uint64</name>
      <anchor>a4</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>little_endian_to_native_uint32</name>
      <anchor>a5</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>little_endian_to_native_uint16</name>
      <anchor>a6</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_big_endian_uint64</name>
      <anchor>a7</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_big_endian_uint32</name>
      <anchor>a8</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_big_endian_uint16</name>
      <anchor>a9</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_little_endian_uint64</name>
      <anchor>a10</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_little_endian_uint32</name>
      <anchor>a11</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_little_endian_uint16</name>
      <anchor>a12</anchor>
      <arglist>(x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>endian_little.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>endian__little_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_LITTLE_ENDIAN</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>little_endian_to_native_uint64</name>
      <anchor>a1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>little_endian_to_native_uint32</name>
      <anchor>a2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>little_endian_to_native_uint16</name>
      <anchor>a3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>big_endian_to_native_uint64</name>
      <anchor>a4</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>big_endian_to_native_uint32</name>
      <anchor>a5</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>big_endian_to_native_uint16</name>
      <anchor>a6</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_big_endian_uint64</name>
      <anchor>a7</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_big_endian_uint32</name>
      <anchor>a8</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_big_endian_uint16</name>
      <anchor>a9</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_little_endian_uint64</name>
      <anchor>a10</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_little_endian_uint32</name>
      <anchor>a11</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>native_to_little_endian_uint16</name>
      <anchor>a12</anchor>
      <arglist>(x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>flags.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/</path>
    <filename>flags_8h</filename>
    <class kind="struct">cpu_flags_t</class>
    <member kind="define">
      <type>#define</type>
      <name>cpu_flags_save</name>
      <anchor>a0</anchor>
      <arglist>(save_flags)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>cpu_flags_load</name>
      <anchor>a1</anchor>
      <arglist>(load_flags)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>cpu_flags_enable</name>
      <anchor>a2</anchor>
      <arglist>(enable_flags)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>cpu_flags_disable</name>
      <anchor>a3</anchor>
      <arglist>(mask_flags)</arglist>
    </member>
    <member kind="enumeration">
      <name>cpu_flag_t</name>
      <anchor>a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_CARRY</name>
      <anchor>a24a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_SET</name>
      <anchor>a24a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_PARITY</name>
      <anchor>a24a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_ADJUST</name>
      <anchor>a24a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_ZERO</name>
      <anchor>a24a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_SIGN</name>
      <anchor>a24a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_TRAP</name>
      <anchor>a24a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_INTERRUPT_ENABLE</name>
      <anchor>a24a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_DIRECTION</name>
      <anchor>a24a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_OVERFLOW</name>
      <anchor>a24a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_IOPL_LOW</name>
      <anchor>a24a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_IOPL_HIGH</name>
      <anchor>a24a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_NESTED_TASK</name>
      <anchor>a24a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_RESUME_TASK</name>
      <anchor>a24a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_V8086_MODE</name>
      <anchor>a24a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_ALIGNMENT_CHECK</name>
      <anchor>a24a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_VIRTUAL_INTERRUPT</name>
      <anchor>a24a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_VIRTUAL_INTERRUPT_PENDING</name>
      <anchor>a24a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CPU_FLAG_ID</name>
      <anchor>a24a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>cpu_flags_test</name>
      <anchor>a23</anchor>
      <arglist>(uint32_t test_flags)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>integer_operations.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Atomic/</path>
    <filename>integer__operations_8h</filename>
    <class kind="struct">atomic_uint32_t</class>
    <member kind="define">
      <type>#define</type>
      <name>LOCK</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ATOMIC_UINT32_INIT</name>
      <anchor>a1</anchor>
      <arglist>(i)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>atomic_uint32_read</name>
      <anchor>a2</anchor>
      <arglist>(variable)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>atomic_uint32_set</name>
      <anchor>a3</anchor>
      <arglist>(variable, i)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_uint32_add</name>
      <anchor>a4</anchor>
      <arglist>(atomic_uint32_t *variable, uint32_t i)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_uint32_subtract</name>
      <anchor>a5</anchor>
      <arglist>(atomic_uint32_t *variable, uint32_t i)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_uint32_increment</name>
      <anchor>a6</anchor>
      <arglist>(atomic_uint32_t *variable)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_uint32_decrement</name>
      <anchor>a7</anchor>
      <arglist>(atomic_uint32_t *variable)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_uint32_clear_mask</name>
      <anchor>a8</anchor>
      <arglist>(atomic_uint32_t *variable, uint32_t mask)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_uint32_set_mask</name>
      <anchor>a9</anchor>
      <arglist>(atomic_uint32_t *variable, uint32_t mask)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>atomic_uint32_change_mask</name>
      <anchor>a10</anchor>
      <arglist>(atomic_uint32_t *variable, uint32_t mask)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>atomic_uint32_subtract_and_test</name>
      <anchor>a11</anchor>
      <arglist>(atomic_uint32_t *variable, uint32_t i)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>atomic_uint32_increment_and_test</name>
      <anchor>a12</anchor>
      <arglist>(atomic_uint32_t *variable, uint32_t i)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>atomic_uint32_decrement_and_test</name>
      <anchor>a13</anchor>
      <arglist>(atomic_uint32_t *variable, uint32_t i)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>atomic_add_negative</name>
      <anchor>a14</anchor>
      <arglist>(atomic_uint32_t *variable, uint32_t i)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iso646.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>iso646_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>_COMMON_ENVIROMENT_ISO646</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>and</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>and_eq</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>bitand</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>bitor</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>compl</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>not</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>not_eq</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>or</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>or_eq</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>xor</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>xor_eq</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iterator.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>iterator_8h</filename>
    <class kind="struct">iterator_t</class>
    <member kind="define">
      <type>#define</type>
      <name>iterator</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>iterator</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bool(</type>
      <name>iterator_has_next_function_t</name>
      <anchor>a2</anchor>
      <arglist>)(struct iterator_t *iterator)</arglist>
    </member>
    <member kind="typedef">
      <type>void *(</type>
      <name>iterator_get_next_function_t</name>
      <anchor>a3</anchor>
      <arglist>)(struct iterator_t *iterator)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>limits.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>limits_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>STRING_MAX_LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX_NUMBER_OF_MULTIBOOT_MODULES</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>locks.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/</path>
    <filename>locks_8h</filename>
    <includes id="spinlock_8h" name="spinlock.h" local="yes">Locks/spinlock.h</includes>
    <includes id="multilock_8h" name="multilock.h" local="yes">Locks/multilock.h</includes>
  </compound>
  <compound kind="file">
    <name>memory.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/</path>
    <filename>memory_8h</filename>
    <includes id="copy_8h" name="copy.h" local="yes">Memory/copy.h</includes>
    <includes id="move_8h" name="move.h" local="yes">Memory/move.h</includes>
    <includes id="set_8h" name="set.h" local="yes">Memory/set.h</includes>
    <includes id="clear_8h" name="clear.h" local="yes">Memory/clear.h</includes>
    <includes id="compare_8h" name="compare.h" local="yes">Memory/compare.h</includes>
  </compound>
  <compound kind="file">
    <name>MMX.C</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Memory/</path>
    <filename>MMX_8C</filename>
    <member kind="function">
      <type>void *</type>
      <name>_mmx_memcpy</name>
      <anchor>a0</anchor>
      <arglist>(void *to, const void *from, size_t len)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>fast_clear_page</name>
      <anchor>a1</anchor>
      <arglist>(void *page)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>fast_copy_page</name>
      <anchor>a2</anchor>
      <arglist>(void *to, void *from)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>slow_zero_page</name>
      <anchor>a3</anchor>
      <arglist>(void *page)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mmx_clear_page</name>
      <anchor>a4</anchor>
      <arglist>(void *page)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>slow_copy_page</name>
      <anchor>a5</anchor>
      <arglist>(void *to, void *from)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mmx_copy_page</name>
      <anchor>a6</anchor>
      <arglist>(void *to, void *from)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>move.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Memory/</path>
    <filename>move_8h</filename>
    <member kind="function" static="yes">
      <type>void *</type>
      <name>memory_move</name>
      <anchor>a0</anchor>
      <arglist>(void *dest, const void *src, size_t n)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>multilock.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Locks/</path>
    <filename>multilock_8h</filename>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>multilock_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>multilock_t</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MULTI_UNLOCKED</name>
      <anchor>a8a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MULTI_LOCKED</name>
      <anchor>a8a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MULTI_WRITE_LOCKED</name>
      <anchor>a8a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>multi_read_lock</name>
      <anchor>a4</anchor>
      <arglist>(multilock_t *lock)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>multi_write_lock</name>
      <anchor>a5</anchor>
      <arglist>(multilock_t *lock)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>multi_read_unlock</name>
      <anchor>a6</anchor>
      <arglist>(multilock_t *lock)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>multi_write_unlock</name>
      <anchor>a7</anchor>
      <arglist>(multilock_t *lock)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>page.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/</path>
    <filename>page_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>PAGE_SIZE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SIZE_IN_PAGES</name>
      <anchor>a1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_PAGE_NUMBER</name>
      <anchor>a2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_OFFSET_IN_PAGE</name>
      <anchor>a3</anchor>
      <arglist>(x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>port.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/</path>
    <filename>port_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint8_out</name>
      <anchor>a0</anchor>
      <arglist>(uint16_t port, uint8_t data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint16_out</name>
      <anchor>a1</anchor>
      <arglist>(uint16_t port, uint16_t data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint32_out</name>
      <anchor>a2</anchor>
      <arglist>(uint16_t port, uint32_t data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint8_t</type>
      <name>port_uint8_in</name>
      <anchor>a3</anchor>
      <arglist>(uint16_t port)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint16_t</type>
      <name>port_uint16_in</name>
      <anchor>a4</anchor>
      <arglist>(uint16_t port)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint32_t</type>
      <name>port_uint32_in</name>
      <anchor>a5</anchor>
      <arglist>(uint16_t port)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint8_out_pause</name>
      <anchor>a6</anchor>
      <arglist>(uint16_t port, uint8_t data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint16_out_pause</name>
      <anchor>a7</anchor>
      <arglist>(uint16_t port, uint16_t data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint32_out_pause</name>
      <anchor>a8</anchor>
      <arglist>(uint16_t port, uint32_t data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint8_out_string</name>
      <anchor>a9</anchor>
      <arglist>(uint16_t port, uint8_t *data, size_t length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint16_out_string</name>
      <anchor>a10</anchor>
      <arglist>(uint16_t port, uint8_t *data, size_t length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint32_out_string</name>
      <anchor>a11</anchor>
      <arglist>(uint16_t port, uint32_t *data, size_t length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint8_in_string</name>
      <anchor>a12</anchor>
      <arglist>(uint16_t port, uint8_t *data, size_t length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint16_in_string</name>
      <anchor>a13</anchor>
      <arglist>(uint16_t port, uint16_t *data, size_t length)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>port_uint32_in_string</name>
      <anchor>a14</anchor>
      <arglist>(uint16_t port, uint32_t *data, size_t length)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>return_value.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>return__value_8h</filename>
    <member kind="enumvalue">
      <name>STORM_RETURN_SUCCESS</name>
      <anchor>a9a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_RETURN_NOT_IMPLEMENTED</name>
      <anchor>a9a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_RETURN_OUT_OF_MEMORY</name>
      <anchor>a9a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_RETURN_INTERNAL_DATA_ERROR</name>
      <anchor>a9a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_RETURN_MODULE_INVALID</name>
      <anchor>a9a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_RETURN_BUSY</name>
      <anchor>a9a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_RETURN_INVALID_ARGUMENT</name>
      <anchor>a9a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_RETURN_NOT_FOUND</name>
      <anchor>a9a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_RETURN_ACCESS_DENIED</name>
      <anchor>a9a8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>set.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Memory/</path>
    <filename>set_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>memory_set_uint8</name>
      <anchor>a0</anchor>
      <arglist>(uint8_t *address, uint8_t value, unsigned int count)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>memory_set_uint16</name>
      <anchor>a1</anchor>
      <arglist>(uint16_t *address, uint16_t value, unsigned int count)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>memory_set_uint32</name>
      <anchor>a2</anchor>
      <arglist>(uint32_t *address, uint32_t value, unsigned int count)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>spinlock.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/ia32/Locks/</path>
    <filename>spinlock_8h</filename>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>spinlock_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>spinlock_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SPIN_UNLOCKED</name>
      <anchor>a7a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SPIN_LOCKED</name>
      <anchor>a7a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>spin_init</name>
      <anchor>a3</anchor>
      <arglist>(spinlock_t *lock)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>spin_lock</name>
      <anchor>a4</anchor>
      <arglist>(spinlock_t *lock)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>spin_lock_interrupt</name>
      <anchor>a5</anchor>
      <arglist>(spinlock_t *lock)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>spin_unlock</name>
      <anchor>a6</anchor>
      <arglist>(spinlock_t *lock)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>standart_arguments.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>standart__arguments_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>__va_promote</name>
      <anchor>a0</anchor>
      <arglist>(type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>va_start</name>
      <anchor>a1</anchor>
      <arglist>(ap, last)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>va_arg</name>
      <anchor>a2</anchor>
      <arglist>(ap, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>va_end</name>
      <anchor>a3</anchor>
      <arglist>(ap)</arglist>
    </member>
    <member kind="typedef">
      <type>char *</type>
      <name>va_list</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>stdint.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>stdint_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>_STDINT_H</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>__INT64_C</name>
      <anchor>a1</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>__UINT64_C</name>
      <anchor>a2</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT8_MIN</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT16_MIN</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT32_MIN</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT64_MIN</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT8_MAX</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT16_MAX</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT32_MAX</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT64_MAX</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT8_MAX</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT16_MAX</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT32_MAX</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT64_MAX</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_LEAST8_MIN</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_LEAST16_MIN</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_LEAST32_MIN</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_LEAST64_MIN</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_LEAST8_MAX</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_LEAST16_MAX</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_LEAST32_MAX</name>
      <anchor>a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_LEAST64_MAX</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT_LEAST8_MAX</name>
      <anchor>a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT_LEAST16_MAX</name>
      <anchor>a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT_LEAST32_MAX</name>
      <anchor>a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT_LEAST64_MAX</name>
      <anchor>a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_FAST8_MIN</name>
      <anchor>a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_FAST16_MIN</name>
      <anchor>a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_FAST32_MIN</name>
      <anchor>a29</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_FAST64_MIN</name>
      <anchor>a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_FAST8_MAX</name>
      <anchor>a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_FAST16_MAX</name>
      <anchor>a32</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_FAST32_MAX</name>
      <anchor>a33</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT_FAST64_MAX</name>
      <anchor>a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT_FAST8_MAX</name>
      <anchor>a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT_FAST16_MAX</name>
      <anchor>a36</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT_FAST32_MAX</name>
      <anchor>a37</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT_FAST64_MAX</name>
      <anchor>a38</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INTPTR_MIN</name>
      <anchor>a39</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INTPTR_MAX</name>
      <anchor>a40</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINTPTR_MAX</name>
      <anchor>a41</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INTMAX_MIN</name>
      <anchor>a42</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INTMAX_MAX</name>
      <anchor>a43</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINTMAX_MAX</name>
      <anchor>a44</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PTRDIFF_MIN</name>
      <anchor>a45</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PTRDIFF_MAX</name>
      <anchor>a46</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SIZE_MAX</name>
      <anchor>a47</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WCHAR_MIN</name>
      <anchor>a48</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WCHAR_MAX</name>
      <anchor>a49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WINT_MIN</name>
      <anchor>a50</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WINT_MAX</name>
      <anchor>a51</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT8_C</name>
      <anchor>a52</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT16_C</name>
      <anchor>a53</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT32_C</name>
      <anchor>a54</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT64_C</name>
      <anchor>a55</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT8_C</name>
      <anchor>a56</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT16_C</name>
      <anchor>a57</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT32_C</name>
      <anchor>a58</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINT64_C</name>
      <anchor>a59</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INTMAX_C</name>
      <anchor>a60</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UINTMAX_C</name>
      <anchor>a61</anchor>
      <arglist>(c)</arglist>
    </member>
    <member kind="typedef">
      <type>signed char</type>
      <name>int8_t</name>
      <anchor>a62</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>short int</type>
      <name>int16_t</name>
      <anchor>a63</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>int32_t</name>
      <anchor>a64</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>long long int</type>
      <name>int64_t</name>
      <anchor>a65</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned char</type>
      <name>uint8_t</name>
      <anchor>a66</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned short int</type>
      <name>uint16_t</name>
      <anchor>a67</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>uint32_t</name>
      <anchor>a68</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long long int</type>
      <name>uint64_t</name>
      <anchor>a69</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>signed char</type>
      <name>int_least8_t</name>
      <anchor>a70</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>short int</type>
      <name>int_least16_t</name>
      <anchor>a71</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>int_least32_t</name>
      <anchor>a72</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>long long int</type>
      <name>int_least64_t</name>
      <anchor>a73</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned char</type>
      <name>uint_least8_t</name>
      <anchor>a74</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned short int</type>
      <name>uint_least16_t</name>
      <anchor>a75</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>uint_least32_t</name>
      <anchor>a76</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long long int</type>
      <name>uint_least64_t</name>
      <anchor>a77</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>signed char</type>
      <name>int_fast8_t</name>
      <anchor>a78</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>int_fast16_t</name>
      <anchor>a79</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>int_fast32_t</name>
      <anchor>a80</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>long long int</type>
      <name>int_fast64_t</name>
      <anchor>a81</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned char</type>
      <name>uint_fast8_t</name>
      <anchor>a82</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>uint_fast16_t</name>
      <anchor>a83</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>uint_fast32_t</name>
      <anchor>a84</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long long int</type>
      <name>uint_fast64_t</name>
      <anchor>a85</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>intptr_t</name>
      <anchor>a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>uintptr_t</name>
      <anchor>a87</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>long long int</type>
      <name>intmax_t</name>
      <anchor>a88</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long long int</type>
      <name>uintmax_t</name>
      <anchor>a89</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>stdint_ext.h</name>
    <path>D:/chaos.latest/ChaosG4.v007/Enviroments/Common/</path>
    <filename>stdint__ext_8h</filename>
    <class kind="struct">sequence_t</class>
    <member kind="typedef">
      <type>void *</type>
      <name>p_void_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint8_t *</type>
      <name>p_uint8_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint16_t *</type>
      <name>p_uint16_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t *</type>
      <name>p_uint32_t</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint64_t *</type>
      <name>p_uint64_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>bool</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>size_t</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>return_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>function_t</name>
      <anchor>a8</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>function_t *</type>
      <name>p_function_t</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>address_t</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>atomic_uint32_t</name>
    <filename>structatomic__uint32__t.html</filename>
    <member kind="variable">
      <type>volatile uint32_t</type>
      <name>value</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_flags_t</name>
    <filename>structcpu__flags__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>carry</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__pad0__</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>parity</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__pad1__</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>adjust</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__pad2__</name>
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
      <name>sign</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>trap</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>interrupt_enable</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>direction</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>overflow</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>io_privilege_level</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>nested</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__pad3__</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>resume</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>virtual_8086_mode</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>alignment_check</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>virtual_interrupt</name>
      <anchor>o18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>virtual_interrupt_pending</name>
      <anchor>o19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>identification</name>
      <anchor>o20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__pad4__</name>
      <anchor>o21</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>iterator_t</name>
    <filename>structiterator__t.html</filename>
    <member kind="variable">
      <type>iterator_has_next_function_t *</type>
      <name>has_next</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>iterator_get_next_function_t *</type>
      <name>get_next</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>sequence_t</name>
    <filename>structsequence__t.html</filename>
    <member kind="variable">
      <type>p_void_t</type>
      <name>data</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>count</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>block_size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
