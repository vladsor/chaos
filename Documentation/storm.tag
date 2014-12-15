<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="file">
    <name>PhysicalMemory/allocate.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/PhysicalMemory/</path>
    <filename>PhysicalMemory_2allocate_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_allocate</name>
      <anchor>a2</anchor>
      <arglist>(p_physical_memory_t memory, p_page_number_t pointer, unsigned int pages)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>VirtualMemory/allocate.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/</path>
    <filename>VirtualMemory_2allocate_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="page_8h" name="page.h" local="yes">Include/page.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_allocate</name>
      <anchor>a2</anchor>
      <arglist>(p_virtual_memory_t virtual_memory, p_page_number_t start_virtual_page, uint32_t pages, p_page_number_t start_physical_page, unsigned int options)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>apic.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>apic_8c</filename>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DIVISOR</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_maxlvt</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_clear_local</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_connect_bsp</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_disconnect_bsp</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_disable_local</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>apic_verify_local</name>
      <anchor>a12</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sync_Arb_IDs</name>
      <anchor>a13</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>__error_in_apic_c</name>
      <anchor>a14</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_init_bsp</name>
      <anchor>a15</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_setup_local</name>
      <anchor>a16</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>detect_init_APIC</name>
      <anchor>a17</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_init_mappings</name>
      <anchor>a18</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>unsigned int</type>
      <name>get_8254_timer_count</name>
      <anchor>a19</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void __init</type>
      <name>wait_8254_wraparound</name>
      <anchor>a20</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_setup_LVTT</name>
      <anchor>a21</anchor>
      <arglist>(unsigned int clocks)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_setup_timer</name>
      <anchor>a22</anchor>
      <arglist>(void *data)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>apic_calibrate_clock</name>
      <anchor>a23</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_setup_clocks</name>
      <anchor>a24</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setup_profiling_timer</name>
      <anchor>a25</anchor>
      <arglist>(unsigned int multiplier)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>smp_local_timer_interrupt</name>
      <anchor>a26</anchor>
      <arglist>(struct pt_regs *regs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>smp_apic_timer_interrupt</name>
      <anchor>a27</anchor>
      <arglist>(struct pt_regs *regs)</arglist>
    </member>
    <member kind="function">
      <type>asmlinkage void</type>
      <name>smp_spurious_interrupt</name>
      <anchor>a28</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>asmlinkage void</type>
      <name>smp_error_interrupt</name>
      <anchor>a29</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>APIC_init_uniprocessor</name>
      <anchor>a30</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>using_apic_timer</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>prof_multiplier</name>
      <anchor>a2</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>prof_old_multiplier</name>
      <anchor>a3</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>prof_counter</name>
      <anchor>a4</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>unsigned int</type>
      <name>calibration_result</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_timer_irqs</name>
      <anchor>a6</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>apic.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>apic_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>NR_CPUS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FORCE_READ_AROUND_WRITE</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>apic_read_around</name>
      <anchor>a2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>apic_write_around</name>
      <anchor>a3</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NMI_NONE</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NMI_IO_APIC</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NMI_LOCAL_APIC</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NMI_INVALID</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>apic_write</name>
      <anchor>a10</anchor>
      <arglist>(unsigned long reg, unsigned long v)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>apic_write_atomic</name>
      <anchor>a11</anchor>
      <arglist>(unsigned long reg, unsigned long v)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>unsigned long</type>
      <name>apic_read</name>
      <anchor>a12</anchor>
      <arglist>(unsigned long reg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>apic_wait_icr_idle</name>
      <anchor>a13</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>apic_acknowledge_irq</name>
      <anchor>a14</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_maxlvt</name>
      <anchor>a15</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_local_APIC</name>
      <anchor>a16</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_bsp_APIC</name>
      <anchor>a17</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_bsp_APIC</name>
      <anchor>a18</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disable_local_APIC</name>
      <anchor>a19</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>verify_local_APIC</name>
      <anchor>a20</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cache_APIC_registers</name>
      <anchor>a21</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sync_Arb_IDs</name>
      <anchor>a22</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_bsp_APIC</name>
      <anchor>a23</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setup_local_APIC</name>
      <anchor>a24</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_apic_mappings</name>
      <anchor>a25</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>smp_local_timer_interrupt</name>
      <anchor>a26</anchor>
      <arglist>(struct pt_regs *regs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setup_APIC_clocks</name>
      <anchor>a27</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setup_apic_nmi_watchdog</name>
      <anchor>a28</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nmi_watchdog_tick</name>
      <anchor>a29</anchor>
      <arglist>(struct pt_regs *regs)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>APIC_init_uniprocessor</name>
      <anchor>a30</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>pm_dev *</type>
      <name>apic_pm_register</name>
      <anchor>a31</anchor>
      <arglist>(pm_dev_t, unsigned long, pm_callback)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_pm_unregister</name>
      <anchor>a32</anchor>
      <arglist>(struct pm_dev *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>check_nmi_watchdog</name>
      <anchor>a33</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_timer_irqs</name>
      <anchor>a8</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>nmi_watchdog</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>apicdef.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>apicdef_8h</filename>
    <class kind="struct">local_apic</class>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DEFAULT_PHYS_BASE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ID</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ID_MASK</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_APIC_ID</name>
      <anchor>a3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVR</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVR_MASK</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_APIC_VERSION</name>
      <anchor>a6</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_APIC_MAXLVT</name>
      <anchor>a7</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_INTEGRATED</name>
      <anchor>a8</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TASKPRI</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TPRI_MASK</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ARBPRI</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ARBPRI_MASK</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_PROCPRI</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_EOI</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_EIO_ACK</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_RRR</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LDR</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LDR_MASK</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_APIC_LOGICAL_ID</name>
      <anchor>a19</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SET_APIC_LOGICAL_ID</name>
      <anchor>a20</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ALL_CPUS</name>
      <anchor>a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DFR</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_SPIV</name>
      <anchor>a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_SPIV_FOCUS_DISABLED</name>
      <anchor>a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_SPIV_APIC_ENABLED</name>
      <anchor>a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ISR</name>
      <anchor>a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TMR</name>
      <anchor>a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_IRR</name>
      <anchor>a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ESR</name>
      <anchor>a29</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ESR_SEND_CS</name>
      <anchor>a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ESR_RECV_CS</name>
      <anchor>a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ESR_SEND_ACC</name>
      <anchor>a32</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ESR_RECV_ACC</name>
      <anchor>a33</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ESR_SENDILL</name>
      <anchor>a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ESR_RECVILL</name>
      <anchor>a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ESR_ILLREGA</name>
      <anchor>a36</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ICR</name>
      <anchor>a37</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DEST_SELF</name>
      <anchor>a38</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DEST_ALLINC</name>
      <anchor>a39</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DEST_ALLBUT</name>
      <anchor>a40</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ICR_RR_MASK</name>
      <anchor>a41</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ICR_RR_INVALID</name>
      <anchor>a42</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ICR_RR_INPROG</name>
      <anchor>a43</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ICR_RR_VALID</name>
      <anchor>a44</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_INT_LEVELTRIG</name>
      <anchor>a45</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_INT_ASSERT</name>
      <anchor>a46</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ICR_BUSY</name>
      <anchor>a47</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DEST_LOGICAL</name>
      <anchor>a48</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DM_FIXED</name>
      <anchor>a49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DM_LOWEST</name>
      <anchor>a50</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DM_SMI</name>
      <anchor>a51</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DM_REMRD</name>
      <anchor>a52</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DM_NMI</name>
      <anchor>a53</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DM_INIT</name>
      <anchor>a54</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DM_STARTUP</name>
      <anchor>a55</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_DM_EXTINT</name>
      <anchor>a56</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_VECTOR_MASK</name>
      <anchor>a57</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_ICR2</name>
      <anchor>a58</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_APIC_DEST_FIELD</name>
      <anchor>a59</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SET_APIC_DEST_FIELD</name>
      <anchor>a60</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVTT</name>
      <anchor>a61</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVTPC</name>
      <anchor>a62</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVT0</name>
      <anchor>a63</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVT_TIMER_BASE_MASK</name>
      <anchor>a64</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_APIC_TIMER_BASE</name>
      <anchor>a65</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SET_APIC_TIMER_BASE</name>
      <anchor>a66</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TIMER_BASE_CLKIN</name>
      <anchor>a67</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TIMER_BASE_TMBASE</name>
      <anchor>a68</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TIMER_BASE_DIV</name>
      <anchor>a69</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVT_TIMER_PERIODIC</name>
      <anchor>a70</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVT_MASKED</name>
      <anchor>a71</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVT_LEVEL_TRIGGER</name>
      <anchor>a72</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVT_REMOTE_IRR</name>
      <anchor>a73</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_INPUT_POLARITY</name>
      <anchor>a74</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_SEND_PENDING</name>
      <anchor>a75</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_APIC_DELIVERY_MODE</name>
      <anchor>a76</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SET_APIC_DELIVERY_MODE</name>
      <anchor>a77</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_MODE_FIXED</name>
      <anchor>a78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_MODE_NMI</name>
      <anchor>a79</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_MODE_EXINT</name>
      <anchor>a80</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVT1</name>
      <anchor>a81</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_LVTERR</name>
      <anchor>a82</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TMICT</name>
      <anchor>a83</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TMCCT</name>
      <anchor>a84</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDCR</name>
      <anchor>a85</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDR_DIV_TMBASE</name>
      <anchor>a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDR_DIV_1</name>
      <anchor>a87</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDR_DIV_2</name>
      <anchor>a88</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDR_DIV_4</name>
      <anchor>a89</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDR_DIV_8</name>
      <anchor>a90</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDR_DIV_16</name>
      <anchor>a91</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDR_DIV_32</name>
      <anchor>a92</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDR_DIV_64</name>
      <anchor>a93</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_TDR_DIV_128</name>
      <anchor>a94</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>APIC_BASE</name>
      <anchor>a95</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX_IO_APICS</name>
      <anchor>a96</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>lapic</name>
      <anchor>a97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>local_apic</type>
      <name>PACKED</name>
      <anchor>a98</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bugs.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/</path>
    <filename>bugs_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="bugs_8h" name="bugs.h" local="yes">Include/bugs.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_bugs_search</name>
      <anchor>a2</anchor>
      <arglist>(cpu_info_t *cpu_info)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bugs.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/Include/</path>
    <filename>bugs_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>cpu_bugs_search</name>
      <anchor>a0</anchor>
      <arglist>(cpu_info_t *cpu_info)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>bug_set</name>
      <anchor>a1</anchor>
      <arglist>(cpu_info_t *cpu_info, unsigned int bug, bool value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>bug_get</name>
      <anchor>a2</anchor>
      <arglist>(cpu_info_t *cpu_info, unsigned int bug)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>check.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/PhysicalMemory/</path>
    <filename>check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_check</name>
      <anchor>a2</anchor>
      <arglist>(p_physical_memory_t memory UNUSED, page_number_t start_page UNUSED, unsigned int pages UNUSED, unsigned int flags UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>class.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>class_8h</filename>
    <includes id="Repository_2Class_2Include_2internal_8h" name="Repository/Class/Include/internal.h" local="yes">../Class/Include/internal.h</includes>
  </compound>
  <compound kind="file">
    <name>classes.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/</path>
    <filename>classes_8h</filename>
    <class kind="struct">kernel_class_info_t</class>
    <member kind="typedef">
      <type>class_reference_t(</type>
      <name>kernel_class_init_function_t</name>
      <anchor>a0</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>kernel_class_init_function_t *</type>
      <name>p_kernel_class_init_function_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_CLASS_FLAT_NAMESPACE_INDEX</name>
      <anchor>a9a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_CLASS_STORM_MODULE_INDEX</name>
      <anchor>a9a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_CLASS_STORM_PROGRAM_INDEX</name>
      <anchor>a9a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>flat_namespace_class_init</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>storm_module_class_init</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>storm_program_class_init</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>kernel_class_info_t</type>
      <name>kernel_classes_info</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>computer.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>computer_8h</filename>
    <includes id="Repository_2Computer_2Include_2internal_8h" name="Repository/Computer/Include/internal.h" local="yes">../Computer/Include/internal.h</includes>
  </compound>
  <compound kind="file">
    <name>controller.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Dma/</path>
    <filename>controller_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="controller_8h" name="controller.h" local="yes">Include/controller.h</includes>
    <class kind="struct">dma_mode_register_t</class>
    <class kind="struct">dma_command_register_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_RESET</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MASK_ALL_CHANNELS</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CANCEL_DMA_TRANSFER</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>dma_channel_t</name>
      <anchor>a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMA_CHANNEL_0</name>
      <anchor>a31a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMA_CHANNEL_1</name>
      <anchor>a31a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMA_CHANNEL_2</name>
      <anchor>a31a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMA_CHANNEL_3</name>
      <anchor>a31a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMA_CHANNEL_4</name>
      <anchor>a31a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMA_CHANNEL_5</name>
      <anchor>a31a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMA_CHANNEL_6</name>
      <anchor>a31a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMA_CHANNEL_7</name>
      <anchor>a31a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMA_CHANNEL_CASCADE</name>
      <anchor>a31a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_controller_init</name>
      <anchor>a26</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_contoller_enable_channel</name>
      <anchor>a27</anchor>
      <arglist>(unsigned int channel)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_contoller_disable_channel</name>
      <anchor>a28</anchor>
      <arglist>(unsigned int channel)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_controller_transfer_start</name>
      <anchor>a29</anchor>
      <arglist>(unsigned int channel, address_t physical_buffer, unsigned int length, unsigned int mode)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_controller_transfer_cancel</name>
      <anchor>a30</anchor>
      <arglist>(unsigned int channel)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_command</name>
      <anchor>a4</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_state</name>
      <anchor>a5</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_request</name>
      <anchor>a6</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_reset</name>
      <anchor>a7</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_reset_mask</name>
      <anchor>a8</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_temporary_register</name>
      <anchor>a9</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_all_mask</name>
      <anchor>a10</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_mask</name>
      <anchor>a11</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_mode</name>
      <anchor>a12</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_flip_flop</name>
      <anchor>a13</anchor>
      <arglist>[NUMBER_OF_DMA_CONTROLLERS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_page</name>
      <anchor>a14</anchor>
      <arglist>[NUMBER_OF_DMA_CHANNELS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_address</name>
      <anchor>a15</anchor>
      <arglist>[NUMBER_OF_DMA_CHANNELS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const unsigned int</type>
      <name>dma_count</name>
      <anchor>a16</anchor>
      <arglist>[NUMBER_OF_DMA_CHANNELS]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>controller.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Dma/Include/</path>
    <filename>controller_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_DMA_CONTROLLERS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_DMA_CHANNELS</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_COMMAND_MEMORY_TO_MEMORY_DISABLE</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_COMMAND_MEMORY_TO_MEMORY_ENABLE</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_COMMAND_CHANNEL_0_ADDRESS_HOLD_ENABLE</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_COMMAND_CONTROLLER_DISABLE</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_COMMAND_COMPRESSED_TIMING</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_COMMAND_ROTATING_PRIORITY</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_COMMAND_EXTENDED_WRITE_SELECTION</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_COMMAND_DREQ_SENSE_ACTIVE_LOW</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_COMMAND_DACK_SENSE_ACTIVE_HIGH</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_READ</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_WRITE</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_VERIFY</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_AUTOINIT_ENABLE</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_AUTOINIT_DISABLE</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_ADDRESS_INCREMENT</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_ADDRESS_DECREMENT</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_DEMAND</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_SINGLE</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_BLOCK</name>
      <anchor>a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DMA_MODE_CASCADE</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_controller_init</name>
      <anchor>a23</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_contoller_enable_channel</name>
      <anchor>a24</anchor>
      <arglist>(unsigned int channel)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_contoller_disable_channel</name>
      <anchor>a25</anchor>
      <arglist>(unsigned int channel)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_controller_transfer_start</name>
      <anchor>a26</anchor>
      <arglist>(unsigned int channel, address_t physical_buffer, unsigned int length, unsigned int mode)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_controller_transfer_cancel</name>
      <anchor>a27</anchor>
      <arglist>(unsigned int channel)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cpu.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>cpu_8h</filename>
    <member kind="function">
      <type>p_cpu_t</type>
      <name>cpu_create_internal</name>
      <anchor>a0</anchor>
      <arglist>(uint32_t performance)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_destroy_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_cpu_t cpu)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_schedule_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_cpu_t cpu)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cpu_id.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/Include/</path>
    <filename>cpu__id_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>cpu_id_detect</name>
      <anchor>a0</anchor>
      <arglist>(cpu_info_t *cpu_info)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>feature_set</name>
      <anchor>a1</anchor>
      <arglist>(cpu_info_t *current_cpu_info, unsigned int feature, bool value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>feature_get</name>
      <anchor>a2</anchor>
      <arglist>(cpu_info_t *current_cpu_info, unsigned int feature)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cpuid-internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/Include/</path>
    <filename>cpuid-internal_8h</filename>
    <class kind="struct">vendor_record_t</class>
    <class kind="struct">cpu_type_record_t</class>
    <class kind="struct">cpu_sub_type_record_t</class>
    <class kind="struct">fpu_type_record_t</class>
    <class kind="struct">cpu_record_t</class>
    <class kind="struct">cpu_family_record</class>
    <class kind="struct">family_t</class>
    <class kind="struct">cpu_sub_record_t</class>
    <member kind="define">
      <type>#define</type>
      <name>NONE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LAST</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>create.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/</path>
    <filename>create_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="page_8h" name="page.h" local="yes">Include/page.h</includes>
    <includes id="Hardware_2VirtualMemory_2Include_2internal_8h" name="Hardware/VirtualMemory/Include/internal.h" local="yes">Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_create</name>
      <anchor>a2</anchor>
      <arglist>(p_virtual_memory_t virtual_memory, p_physical_memory_t physical_memory, unsigned int level)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PhysicalMemory/deallocate.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/PhysicalMemory/</path>
    <filename>PhysicalMemory_2deallocate_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_deallocate</name>
      <anchor>a2</anchor>
      <arglist>(p_physical_memory_t memory, page_number_t start_page, unsigned int pages)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>VirtualMemory/deallocate.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/</path>
    <filename>VirtualMemory_2deallocate_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="page_8h" name="page.h" local="yes">Include/page.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_deallocate</name>
      <anchor>a2</anchor>
      <arglist>(p_virtual_memory_t virtual_memory, page_number_t start_page, unsigned int pages)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/SystemDebug/debug.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/SystemDebug/</path>
    <filename>Hardware_2SystemDebug_2debug_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="debug_8h" name="debug.h" local="yes">Include/debug.h</includes>
    <includes id="gdb_8h" name="gdb.h" local="yes">Include/gdb.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>system_debug_init</name>
      <anchor>a8</anchor>
      <arglist>(int argc, char *argv[], char **envp UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>put_character</name>
      <anchor>a9</anchor>
      <arglist>(int x, int y, char character, int character_attribute)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>system_debug_print</name>
      <anchor>a10</anchor>
      <arglist>(uint8_t level, const char *module_name UNUSED, const char *function_name UNUSED, uint32_t line UNUSED, const char *string)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>system_debug_printw</name>
      <anchor>a11</anchor>
      <arglist>(uint8_t level, const wchar_t *module_name UNUSED, const char *function_name UNUSED, uint32_t line UNUSED, const wchar_t *string)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>uint32_t</type>
      <name>text_attribute</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>uint32_t</type>
      <name>background_attribute</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>uint32_t volatile</type>
      <name>x_position</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>uint32_t volatile</type>
      <name>y_position</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>debug_screen_t *</type>
      <name>debug_screen</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>bool</type>
      <name>output_enabled</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>uint8_t</type>
      <name>start_level</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Kernel/Computer/debug.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Computer/</path>
    <filename>Repository_2Kernel_2Computer_2debug_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <class kind="struct">object_debug_print_method_t</class>
    <member kind="define">
      <type>#define</type>
      <name>number_of_methods</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>object_debug_init</name>
      <anchor>a4</anchor>
      <arglist>(interface_id_t *interface_id)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>object_debug_print_method_t</type>
      <name>object_debug_print_method</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_t *</type>
      <name>methods</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>debug_interface_t</type>
      <name>object_debug_interface</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>debug.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/SystemDebug/Include/</path>
    <filename>debug_8h</filename>
    <class kind="struct">debug_screen_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_ATTRIBUTE_TEXT</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_ATTRIBUTE_BACKGROUND</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_SCREEN_WIDTH</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_SCREEN_HEIGHT</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BASE_SCREEN</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>debug_consumer_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Events/</path>
    <filename>debug__consumer__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="event__consumer__interfaces_8h" name="event_consumer_interfaces.h" local="yes">../event_consumer_interfaces.h</includes>
    <includes id="debug__event__class_8h" name="debug_event_class.h" local="yes">Include/debug_event_class.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>handler</name>
      <anchor>a2</anchor>
      <arglist>(context_t context UNUSED, uint32_t level, const wchar_t *module_name, const wchar_t *function_name, uint32_t line, const wchar_t *message)</arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>debug_consumer_init</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>debug_event_class.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Events/</path>
    <filename>debug__event__class_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="debug__event__class_8h" name="debug_event_class.h" local="yes">Include/debug_event_class.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>debug_description_register</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>supplier_handler_wrapper</name>
      <anchor>a4</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>debug_supplier_interface_register</name>
      <anchor>a5</anchor>
      <arglist>(uint32_t type, p_debug_supplier_handler_t handler, cpu_reference_t cpu)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>consumer_handler_wrapper</name>
      <anchor>a6</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in)</arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>debug_consumer_interface_register</name>
      <anchor>a7</anchor>
      <arglist>(uint32_t type, p_debug_consumer_handler_t handler, cpu_reference_t cpu)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>debug_description</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>debug_event_class.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Events/Include/</path>
    <filename>debug__event__class_8h</filename>
    <member kind="function">
      <type>description_reference_t</type>
      <name>debug_description_register</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>debug_supplier_interface_register</name>
      <anchor>a1</anchor>
      <arglist>(uint32_t type, p_debug_supplier_handler_t handler, cpu_reference_t cpu)</arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>debug_consumer_interface_register</name>
      <anchor>a2</anchor>
      <arglist>(uint32_t type, p_debug_consumer_handler_t handler, cpu_reference_t cpu)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>defines.h</name>
    <path>/root/Chaos/Sources/StormG4/storm/storm/</path>
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
    <name>destroy.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/</path>
    <filename>destroy_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="page_8h" name="page.h" local="yes">Include/page.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_destroy</name>
      <anchor>a2</anchor>
      <arglist>(p_virtual_memory_t virtual_memory)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/Dma/dma.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Dma/</path>
    <filename>Hardware_2Dma_2dma_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="controller_8h" name="controller.h" local="yes">Include/controller.h</includes>
    <class kind="struct">dma_channel_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_init</name>
      <anchor>a2</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_register</name>
      <anchor>a3</anchor>
      <arglist>(int dma_channel, void **buffer)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_unregister</name>
      <anchor>a4</anchor>
      <arglist>(int dma_channel)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>dma_transfer</name>
      <anchor>a5</anchor>
      <arglist>(unsigned int channel, unsigned int length, unsigned int operation, unsigned int transfer_mode, bool autoinit)</arglist>
    </member>
    <member kind="variable">
      <type>dma_channel_t</type>
      <name>dma_channels</name>
      <anchor>a1</anchor>
      <arglist>[7]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Kernel/Computer/dma.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Computer/</path>
    <filename>Repository_2Kernel_2Computer_2dma_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <class kind="struct">object_dma_aregister_method_t</class>
    <class kind="struct">object_dma_unregister_method_t</class>
    <class kind="struct">object_dma_transfer_method_t</class>
    <member kind="define">
      <type>#define</type>
      <name>number_of_methods</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>object_dma_init</name>
      <anchor>a6</anchor>
      <arglist>(interface_id_t *interface_id)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>object_dma_aregister_method_t</type>
      <name>object_dma_aregister_method</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>object_dma_unregister_method_t</type>
      <name>object_dma_unregister_method</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>object_dma_transfer_method_t</type>
      <name>object_dma_transfer_method</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_t *</type>
      <name>methods</name>
      <anchor>a4</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>dma_interface_t</type>
      <name>object_dma_interface</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>elf.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Elf/</path>
    <filename>elf_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ELF_SECTION_TYPE_PROGRAM</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>storm_elf_t</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_ELF_NONE</name>
      <anchor>a17a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_ELF_UNKNOWN</name>
      <anchor>a17a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_ELF_MODULE</name>
      <anchor>a17a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STORM_ELF_PROGRAM</name>
      <anchor>a17a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>enum storm_elf_t</type>
      <name>elf_identify</name>
      <anchor>a7</anchor>
      <arglist>(elf_header_t *elf_header)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_parse</name>
      <anchor>a8</anchor>
      <arglist>(elf_header_t *elf_header, elf_parsed_t *elf_parsed)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_resolve</name>
      <anchor>a9</anchor>
      <arglist>(elf_parsed_t *elf_parsed, function_info_t *function)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_relocate</name>
      <anchor>a10</anchor>
      <arglist>(elf_parsed_t *elf_parsed)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_symbol_find_by_index</name>
      <anchor>a11</anchor>
      <arglist>(elf_parsed_t *elf_parsed, unsigned int index, uint32_t *address)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_symbol_find_by_name</name>
      <anchor>a12</anchor>
      <arglist>(elf_parsed_t *elf_parsed, const char *name, address_t *address)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_load_module</name>
      <anchor>a13</anchor>
      <arglist>(elf_parsed_t *elf_parsed)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_parse_program</name>
      <anchor>a14</anchor>
      <arglist>(elf_header_t *elf_header, elf_parsed_program_t *elf_parsed)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_load_program</name>
      <anchor>a15</anchor>
      <arglist>(elf_parsed_program_t *elf_parsed, p_virtual_memory_t virtual_memory)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>elf_get_entry_point</name>
      <anchor>a16</anchor>
      <arglist>(elf_parsed_program_t *elf_parsed, address_t *address)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>enviroment.h</name>
    <path>/root/Chaos/Sources/StormG4/storm/storm/</path>
    <filename>enviroment_8h</filename>
  </compound>
  <compound kind="file">
    <name>event_class.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>event__class_8h</filename>
  </compound>
  <compound kind="file">
    <name>event_consumer_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>event__consumer__interface_8h</filename>
    <includes id="Repository_2EventConsumerInterface_2Include_2internal_8h" name="Repository/EventConsumerInterface/Include/internal.h" local="yes">../EventConsumerInterface/Include/internal.h</includes>
  </compound>
  <compound kind="file">
    <name>event_consumer_interfaces.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/</path>
    <filename>event__consumer__interfaces_8h</filename>
    <class kind="struct">kernel_event_consumer_interface_info_t</class>
    <member kind="typedef">
      <type>event_consumer_reference_t(</type>
      <name>kernel_event_consumer_init_function_t</name>
      <anchor>a0</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>kernel_event_consumer_init_function_t *</type>
      <name>p_kernel_event_consumer_init_function_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_EVENT_CONSUMER_INTERFACE_DEBUG_INDEX</name>
      <anchor>a5a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_event_consumer_interface_info_t</type>
      <name>kernel_event_consumers_interface_info</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>kernel_event_consumer_init_function_t</type>
      <name>debug_consumer_init</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event_supplier_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>event__supplier__interface_8h</filename>
    <includes id="Repository_2EventSupplierInterface_2Include_2internal_8h" name="Repository/EventSupplierInterface/Include/internal.h" local="yes">../EventSupplierInterface/Include/internal.h</includes>
  </compound>
  <compound kind="file">
    <name>event_supplier_interfaces.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/</path>
    <filename>event__supplier__interfaces_8h</filename>
    <class kind="struct">kernel_event_supplier_interface_info_t</class>
    <member kind="typedef">
      <type>event_supplier_reference_t(</type>
      <name>kernel_event_supplier_init_function_t</name>
      <anchor>a0</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>kernel_event_supplier_init_function_t *</type>
      <name>p_kernel_event_supplier_init_function_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_EVENT_SUPPLIER_INTERFACE_IRQ_INDEX</name>
      <anchor>a5a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_event_supplier_interface_info_t</type>
      <name>kernel_event_supplier_interfaces_info</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>kernel_event_supplier_init_function_t</type>
      <name>irq_supplier_init</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>exception.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Exception/Include/</path>
    <filename>exception_8h</filename>
    <member kind="variable">
      <type>bool</type>
      <name>output_enabled</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>flat_namespace.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>flat__namespace_8h</filename>
    <class kind="struct">flat_name_t</class>
    <class kind="struct">flat_namespace_t</class>
    <member kind="typedef">
      <type>flat_name_t *</type>
      <name>p_flat_name_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>flat_namespace_t *</type>
      <name>p_flat_namespace_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>flat_namespace_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>flat_namespace_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>flat__namespace__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="flat__namespace_8h" name="flat_namespace.h" local="yes">flat_namespace.h</includes>
    <includes id="flat__namespace__interface_8h" name="flat_namespace_interface.h" local="yes">flat_namespace_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>flat_namespace_add_entry</name>
      <anchor>a3</anchor>
      <arglist>(context_t context, wchar_t *name, reference_t reference, uint32_t type)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>reference_t</type>
      <name>flat_namespace_get_entry</name>
      <anchor>a4</anchor>
      <arglist>(context_t context, wchar_t *name, p_uint32_t type)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>flat_namespace_delete_entry</name>
      <anchor>a5</anchor>
      <arglist>(context_t context, wchar_t *name)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint32_t</type>
      <name>flat_namespace_list_entries</name>
      <anchor>a6</anchor>
      <arglist>(context_t context, sequence_t names, uint32_t start)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>flat_namespace_init</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>flat_namespace_interface_table_t</type>
      <name>table</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>flat_namespace_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>flat__namespace__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="flat__namespace__interface_8h" name="flat_namespace_interface.h" local="yes">flat_namespace_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>add_entry_wrapper</name>
      <anchor>a9</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>get_entry_wrapper</name>
      <anchor>a10</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>delete_entry_wrapper</name>
      <anchor>a11</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>list_entries_wrapper</name>
      <anchor>a12</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>flat_namespace_interface_register</name>
      <anchor>a13</anchor>
      <arglist>(p_flat_namespace_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_add_entry</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_get_entry</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_delete_entry</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_list_entries</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a6</anchor>
      <arglist>[METHOD_FLAT_NAMESPACE_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>flat_namespace_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>flat__namespace__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>flat_namespace_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_flat_namespace_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>flat_namespace_object.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>flat__namespace__object_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="classes_8h" name="classes.h" local="yes">../classes.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="flat__namespace_8h" name="flat_namespace.h" local="yes">flat_namespace.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>flat_namespace_class_init</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>class_description</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>flat_namespace_object_factory.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>flat__namespace__object__factory_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="flat__namespace_8h" name="flat_namespace.h" local="yes">../Classes/flat_namespace.h</includes>
    <includes id="flat__namespace__object__factory__interface_8h" name="flat_namespace_object_factory_interface.h" local="yes">flat_namespace_object_factory_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>key_string_compare</name>
      <anchor>a3</anchor>
      <arglist>(void *key1, void *key2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>unsigned int</type>
      <name>key_to_hash</name>
      <anchor>a4</anchor>
      <arglist>(void *key)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint64_t</type>
      <name>flat_namespace_object_create</name>
      <anchor>a5</anchor>
      <arglist>(context_t context UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>flat_namespace_object_destroy</name>
      <anchor>a6</anchor>
      <arglist>(context_t context UNUSED, uint64_t data)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>flat_namespace_object_factory_init</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>flat_namespace_object_factory_interface_table_t</type>
      <name>table</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>flat_namespace_object_factory_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>flat__namespace__object__factory__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="flat__namespace__object__factory__interface_8h" name="flat_namespace_object_factory_interface.h" local="yes">flat_namespace_object_factory_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>create_wrapper</name>
      <anchor>a7</anchor>
      <arglist>(uint64_t function, context_t context, class_reference_t class UNUSED, object_reference_t object, sequence_t parameters_in UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>destroy_wrapper</name>
      <anchor>a8</anchor>
      <arglist>(uint64_t function, context_t context, class_reference_t class UNUSED, object_reference_t object)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>flat_namespace_object_factory_interface_register</name>
      <anchor>a9</anchor>
      <arglist>(p_flat_namespace_object_factory_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_create</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_destroy</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a4</anchor>
      <arglist>[METHOD_OBJECT_FACTORY_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>flat_namespace_object_factory_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>flat__namespace__object__factory__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>flat_namespace_object_factory_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_flat_namespace_object_factory_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>gdb.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/SystemDebug/</path>
    <filename>gdb_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="gdb_8h" name="gdb.h" local="yes">Include/gdb.h</includes>
  </compound>
  <compound kind="file">
    <name>gdb.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/SystemDebug/Include/</path>
    <filename>gdb_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>BREAKPOINT</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gdb_serial_init</name>
      <anchor>a1</anchor>
      <arglist>(unsigned short port, unsigned int speed)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gdb_set_debug_traps</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>group.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>group_8h</filename>
    <member kind="function">
      <type>p_group_t</type>
      <name>group_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_group_t group)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>group_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_group_t group)</arglist>
    </member>
    <member kind="function">
      <type>p_group_t</type>
      <name>group_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(sequence_t group_objects)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>group_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_group_t group)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>halt.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/</path>
    <filename>halt_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>cpu_halt</name>
      <anchor>a2</anchor>
      <arglist>(enum halt_t type)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>handle.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>handle_8h</filename>
    <includes id="Repository_2Handle_2Include_2internal_8h" name="Repository/Handle/Include/internal.h" local="yes">../Handle/Include/internal.h</includes>
  </compound>
  <compound kind="file">
    <name>handlers.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Exception/</path>
    <filename>handlers_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="exception_8h" name="exception.h" local="yes">Include/exception.h</includes>
    <includes id="Exception_2Include_2handlers_8h" name="Exception/Include/handlers.h" local="yes">Include/handlers.h</includes>
    <member kind="variable">
      <type>exception_hardware_description_t</type>
      <name>exception_hardware_descriptions</name>
      <anchor>a0</anchor>
      <arglist>[NUMBER_OF_EXCEPTIONS]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Exception/Include/handlers.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Exception/Include/</path>
    <filename>Exception_2Include_2handlers_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_DIVIDE_ERROR_LOWLEVEL</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_DEBUG_LOWLEVEL</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_NONMASKABLE_INTERRUPT_LOWLEVEL</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_BREAKPOINT_LOWLEVEL</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_OVERFLOW_LOWLEVEL</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_BOUND_RANGE_EXCEEDED_LOWLEVEL</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_INVALID_OPCODE_LOWLEVEL</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_DEVICE_NOT_AVAILABLE_LOWLEVEL</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_DOUBLE_FAULT_LOWLEVEL</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_COPROCESSOR_SEGMENT_OVERRUN_LOWLEVEL</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_INVALID_TSS_LOWLEVEL</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_SEGMENT_NOT_PRESENT_LOWLEVEL</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_STACK_FAULT_LOWLEVEL</name>
      <anchor>a12</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_GENERAL_PROTECTION_LOWLEVEL</name>
      <anchor>a13</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_PAGE_FAULT_LOWLEVEL</name>
      <anchor>a14</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_DUMMY_LOWLEVEL</name>
      <anchor>a15</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_FLOATING_POINT_ERROR_LOWLEVEL</name>
      <anchor>a16</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_ALIGNMENT_CHECK_LOWLEVEL</name>
      <anchor>a17</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_MACHINE_CHECK_LOWLEVEL</name>
      <anchor>a18</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EXCEPTION_HANDLER_STREAMING_SIMD_EXTENSIONS_LOWLEVEL</name>
      <anchor>a19</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Irq/Include/handlers.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Irq/Include/</path>
    <filename>Irq_2Include_2handlers_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>irq0_handler</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq1_handler</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq3_handler</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq4_handler</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq5_handler</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq6_handler</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq7_handler</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq8_handler</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq9_handler</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq10_handler</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq11_handler</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq12_handler</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq13_handler</name>
      <anchor>a12</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq14_handler</name>
      <anchor>a13</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>irq15_handler</name>
      <anchor>a14</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Exception/handlers_lowlevel.S</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Exception/</path>
    <filename>Exception_2handlers__lowlevel_8S</filename>
    <member kind="define">
      <type>#define</type>
      <name>_ASM</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_HANDLER_WITH_ERROR_CODE</name>
      <anchor>a1</anchor>
      <arglist>(NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a2</anchor>
      <arglist>(NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE</name>
      <anchor>a3</anchor>
      <arglist>(NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXCEPTION_HANDLER_WITH_PAGE_ERROR_CODE</name>
      <anchor>a4</anchor>
      <arglist>(NAME)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a5</anchor>
      <arglist>(DIVIDE_ERROR)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a6</anchor>
      <arglist>(DEBUG)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a7</anchor>
      <arglist>(NONMASKABLE_INTERRUPT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a8</anchor>
      <arglist>(BREAKPOINT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a9</anchor>
      <arglist>(OVERFLOW)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a10</anchor>
      <arglist>(BOUND_RANGE_EXCEEDED)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a11</anchor>
      <arglist>(INVALID_OPCODE)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a12</anchor>
      <arglist>(DEVICE_NOT_AVAILABLE)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WITH_ERROR_CODE</name>
      <anchor>a13</anchor>
      <arglist>(DOUBLE_FAULT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a14</anchor>
      <arglist>(COPROCESSOR_SEGMENT_OVERRUN)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE</name>
      <anchor>a15</anchor>
      <arglist>(INVALID_TSS)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE</name>
      <anchor>a16</anchor>
      <arglist>(SEGMENT_NOT_PRESENT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE</name>
      <anchor>a17</anchor>
      <arglist>(STACK_FAULT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE</name>
      <anchor>a18</anchor>
      <arglist>(GENERAL_PROTECTION)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WITH_PAGE_ERROR_CODE</name>
      <anchor>a19</anchor>
      <arglist>(PAGE_FAULT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a20</anchor>
      <arglist>(DUMMY)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a21</anchor>
      <arglist>(FLOATING_POINT_ERROR)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WITH_ERROR_CODE</name>
      <anchor>a22</anchor>
      <arglist>(ALIGNMENT_CHECK)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a23</anchor>
      <arglist>(MACHINE_CHECK)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EXCEPTION_HANDLER_WO_ERROR_CODE</name>
      <anchor>a24</anchor>
      <arglist>(STREAMING_SIMD_EXTENSIONS)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Irq/handlers_lowlevel.S</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Irq/</path>
    <filename>Irq_2handlers__lowlevel_8S</filename>
    <member kind="define">
      <type>#define</type>
      <name>IRQ_HANDLER</name>
      <anchor>a0</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRQ_HANDLER</name>
      <anchor>a1</anchor>
      <arglist>(0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRQ_HANDLER</name>
      <anchor>a2</anchor>
      <arglist>(1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRQ_HANDLER</name>
      <anchor>a3</anchor>
      <arglist>(3)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRQ_HANDLER</name>
      <anchor>a4</anchor>
      <arglist>(4)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRQ_HANDLER</name>
      <anchor>a5</anchor>
      <arglist>(5)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRQ_HANDLER</name>
      <anchor>a6</anchor>
      <arglist>(6)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRQ_HANDLER</name>
      <anchor>a7</anchor>
      <arglist>(7)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRQ_HANDLER</name>
      <anchor>a8</anchor>
      <arglist>(8)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IRQ_HANDLER</name>
      <anchor>a9</anchor>
      <arglist>(9)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>SystemCall/handlers_lowlevel.S</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/SystemCall/</path>
    <filename>SystemCall_2handlers__lowlevel_8S</filename>
    <member kind="variable">
      <type>globl system_call_lowlevel</type>
      <name>system_call_lowlevel</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>globl system_call_lowlevel esp popl edi popl esi popl ebp</type>
      <name>addl</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>identification.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/</path>
    <filename>identification_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="cpu__id_8h" name="cpu_id.h" local="yes">Include/cpu_id.h</includes>
    <includes id="cpuid-internal_8h" name="cpuid-internal.h" local="yes">Include/cpuid-internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>sizeof_vendor_records</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>sizeof_cpu_sub_records</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>cpu_id_process_vendor</name>
      <anchor>a15</anchor>
      <arglist>(cpu_info_t *cpu_info, char *vendor)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>cpu_id_response</name>
      <anchor>a16</anchor>
      <arglist>(cpu_info_t *cpu_info, uint32_t signature)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>cpu_id_response_sub_type</name>
      <anchor>a17</anchor>
      <arglist>(cpu_info_t *cpu_info)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>cpu_id_process_features</name>
      <anchor>a18</anchor>
      <arglist>(cpu_info_t *cpu_info, uint32_t features)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>cpu_id_process_amd_features</name>
      <anchor>a19</anchor>
      <arglist>(cpu_info_t *cpu_info, uint32_t features)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>cpu_id_process</name>
      <anchor>a20</anchor>
      <arglist>(cpu_info_t *cpu_info)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_id_detect</name>
      <anchor>a21</anchor>
      <arglist>(cpu_info_t *cpu_info)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>vendor_record_t</type>
      <name>vendor_records</name>
      <anchor>a4</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>cpu_family_record</type>
      <name>family0</name>
      <anchor>a5</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>cpu_family_record</type>
      <name>family1</name>
      <anchor>a6</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>cpu_family_record</type>
      <name>family2</name>
      <anchor>a7</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>cpu_family_record</type>
      <name>family3</name>
      <anchor>a8</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>cpu_family_record</type>
      <name>family4</name>
      <anchor>a9</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>cpu_family_record</type>
      <name>family5</name>
      <anchor>a10</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>cpu_family_record</type>
      <name>family6</name>
      <anchor>a11</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>cpu_family_record</type>
      <name>family7</name>
      <anchor>a12</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>family_t</type>
      <name>cpu_families</name>
      <anchor>a13</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>cpu_sub_record_t</type>
      <name>cpu_sub_records</name>
      <anchor>a14</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/Boot/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Boot/</path>
    <filename>Hardware_2Boot_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="parse_8h" name="parse.h" local="yes">Include/parse.h</includes>
    <includes id="multiboot_8h" name="multiboot.h" local="yes">Include/multiboot.h</includes>
    <includes id="main_8h" name="main.h" local="yes">Include/main.h</includes>
    <class kind="struct">descriptors_table_register_t</class>
    <member kind="function">
      <type>descriptor_t gdt[GDT_ENTRIES]</type>
      <name>__attribute__</name>
      <anchor>a6</anchor>
      <arglist>((section(&quot;.gdt&quot;)))</arglist>
    </member>
    <member kind="function">
      <type>descriptor_t idt[IDT_ENTRIES]</type>
      <name>__attribute__</name>
      <anchor>a7</anchor>
      <arglist>((section(&quot;.idt&quot;)))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>kernel_entry</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_start</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>char *</type>
      <name>array_of_pointers</name>
      <anchor>a0</anchor>
      <arglist>[COMMAND_LINE_SIZE]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>unsigned int</type>
      <name>number_of_arguments</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>kernel_stack</name>
      <anchor>a2</anchor>
      <arglist>[KERNEL_STACK_SIZE]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>uint64_t</type>
      <name>temporary_gdt</name>
      <anchor>a3</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>descriptors_table_register_t</type>
      <name>idtr</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>descriptors_table_register_t</type>
      <name>gdtr</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/Cpu/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/</path>
    <filename>Hardware_2Cpu_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="cpu__id_8h" name="cpu_id.h" local="yes">Include/cpu_id.h</includes>
    <includes id="bugs_8h" name="bugs.h" local="yes">Include/bugs.h</includes>
    <includes id="speed_8h" name="speed.h" local="yes">Include/speed.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>cpu_get_info</name>
      <anchor>a3</anchor>
      <arglist>(cpu_info_t *cpu_info)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>cpu_init</name>
      <anchor>a4</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>cpu_info_t</type>
      <name>global_cpu_info</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/Exception/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Exception/</path>
    <filename>Hardware_2Exception_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="exception_8h" name="exception.h" local="yes">Include/exception.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>exception_print_page_screen</name>
      <anchor>a5</anchor>
      <arglist>(exception_hardware_page_info_t *exception_info)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>exception_print_segment_screen</name>
      <anchor>a6</anchor>
      <arglist>(exception_hardware_segment_info_t *exception_info)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>dump_registers</name>
      <anchor>a7</anchor>
      <arglist>(exception_hardware_info_t *registers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_print_screen</name>
      <anchor>a8</anchor>
      <arglist>(uint32_t class_id, const char *description, const char *reason, uint32_t error_code_type, exception_hardware_info_t *exception_info)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>exception_register</name>
      <anchor>a9</anchor>
      <arglist>(unsigned int exception_number, p_exception_handler_t function, p_void_t parameter)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>exception_unregister</name>
      <anchor>a10</anchor>
      <arglist>(unsigned int exception_number)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>dummy_handler</name>
      <anchor>a11</anchor>
      <arglist>(p_void_t data UNUSED, exception_hardware_info_t exception_info)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>exception_init</name>
      <anchor>a12</anchor>
      <arglist>(int argc, char *argv[], char **envp UNUSED)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>bool</type>
      <name>output_enabled</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_exception_handler_t</type>
      <name>exception_handlers</name>
      <anchor>a3</anchor>
      <arglist>[NUMBER_OF_EXCEPTIONS]</arglist>
    </member>
    <member kind="variable">
      <type>p_void_t</type>
      <name>exception_handlers_data</name>
      <anchor>a4</anchor>
      <arglist>[NUMBER_OF_EXCEPTIONS]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/PhysicalMemory/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/PhysicalMemory/</path>
    <filename>Hardware_2PhysicalMemory_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Hardware_2PhysicalMemory_2Include_2internal_8h" name="Hardware/PhysicalMemory/Include/internal.h" local="yes">Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>reserve_known_regions</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>physical_memory_get_total_pages</name>
      <anchor>a4</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>physical_memory_get_free_pages</name>
      <anchor>a5</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_init</name>
      <anchor>a6</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="variable">
      <type>physical_memory_t</type>
      <name>physical_memory_global</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/VirtualMemory/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/</path>
    <filename>Hardware_2VirtualMemory_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="page_8h" name="page.h" local="yes">Include/page.h</includes>
    <includes id="Hardware_2VirtualMemory_2Include_2internal_8h" name="Hardware/VirtualMemory/Include/internal.h" local="yes">Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_map</name>
      <anchor>a3</anchor>
      <arglist>(p_virtual_memory_t memory, page_number_t virtual_page, page_number_t physical_page, unsigned int pages, unsigned int flags)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_lookup</name>
      <anchor>a4</anchor>
      <arglist>(p_virtual_memory_t memory, page_number_t virtual_page, page_number_t *physical_page, unsigned int *flags)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_init</name>
      <anchor>a5</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="variable">
      <type>virtual_memory_t</type>
      <name>virtual_memory_global</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>init.c</name>
    <path>/root/Chaos/Sources/StormG4/</path>
    <filename>init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="subsystems_8h" name="subsystems.h" local="yes">subsystems.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>parse_enable_length</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>parse_disable_length</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>parse_parameters_length</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>arguments_parse</name>
      <anchor>a10</anchor>
      <arglist>(char *source, char **array_of_pointers)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>subsystem_set_enabled</name>
      <anchor>a11</anchor>
      <arglist>(char *name, bool enabled)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>subsystem_set_parameters</name>
      <anchor>a12</anchor>
      <arglist>(char *name, char *parameters)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>argument_analyse</name>
      <anchor>a13</anchor>
      <arglist>(char *argument)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>main_bootup</name>
      <anchor>a14</anchor>
      <arglist>(int argument_count, char *arguments[])</arglist>
    </member>
    <member kind="variable">
      <type>storm_info_t</type>
      <name>storm_info</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>subsystem_built_in_t</type>
      <name>subsystem_built_in</name>
      <anchor>a5</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>parse_enable</name>
      <anchor>a6</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>parse_disable</name>
      <anchor>a7</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>parse_parameters</name>
      <anchor>a8</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>char **</type>
      <name>storm_environment</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Class/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/</path>
    <filename>Repository_2Class_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="init_8h" name="init.h" local="yes">../Include/init.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_class_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Cpu/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Cpu/</path>
    <filename>Repository_2Cpu_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="init_8h" name="init.h" local="yes">../Include/init.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_cpu_init</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>cpu_t</type>
      <name>global_cpu</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Descriptions/Exception/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/</path>
    <filename>Repository_2Descriptions_2Exception_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="init_8h" name="init.h" local="yes">../../Include/init.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DESCRIPTION_EXCEPTION_HASH_TABLE_ENTRIES</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_description_exception_init</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>hash_table_t *</type>
      <name>exceptions_table</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/EventConsumerInterface/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/</path>
    <filename>Repository_2EventConsumerInterface_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_event_consumer_interface_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/EventSupplierInterface/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/</path>
    <filename>Repository_2EventSupplierInterface_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_event_supplier_interface_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Handle/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/</path>
    <filename>Repository_2Handle_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="init_8h" name="init.h" local="yes">../Include/init.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_handle_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Interface/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/</path>
    <filename>Repository_2Interface_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_interface_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Kernel/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/</path>
    <filename>Repository_2Kernel_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="kernel_8h" name="kernel.h" local="yes">../Include/kernel.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">interfaces.h</includes>
    <includes id="event__supplier__interfaces_8h" name="event_supplier_interfaces.h" local="yes">event_supplier_interfaces.h</includes>
    <includes id="event__consumer__interfaces_8h" name="event_consumer_interfaces.h" local="yes">event_consumer_interfaces.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_KERNEL_INTERFACES</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_KERNEL_EVENT_SUPPLIER_INTERFACES</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_KERNEL_EVENT_CONSUMER_INTERFACES</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>kernel_init</name>
      <anchor>a17</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>class_reference_t</type>
      <name>kernel_class</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>object_reference_t</type>
      <name>kernel_object</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_interface_info_t</type>
      <name>kernel_interfaces_info</name>
      <anchor>a7</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>interface_reference_t</type>
      <name>interfaces</name>
      <anchor>a8</anchor>
      <arglist>[NUMBER_OF_KERNEL_INTERFACES]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>int_seq</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_event_supplier_interface_info_t</type>
      <name>kernel_event_supplier_interfaces_info</name>
      <anchor>a10</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>event_supplier_interface_reference_t</type>
      <name>event_supplier_interfaces</name>
      <anchor>a11</anchor>
      <arglist>[NUMBER_OF_KERNEL_INTERFACES]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>event_sup_int_seq</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_event_consumer_interface_info_t</type>
      <name>kernel_event_consumer_interfaces_info</name>
      <anchor>a13</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>event_consumer_interface_reference_t</type>
      <name>event_consumer_interfaces</name>
      <anchor>a14</anchor>
      <arglist>[NUMBER_OF_KERNEL_INTERFACES]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>event_con_int_seq</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>class_description</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Method/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/</path>
    <filename>Repository_2Method_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_method_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Object/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/</path>
    <filename>Repository_2Object_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="init_8h" name="init.h" local="yes">../Include/init.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_object_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/tmp/CpuArray/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/CpuArray/</path>
    <filename>Repository_2tmp_2CpuArray_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>timer_handler</name>
      <anchor>a4</anchor>
      <arglist>(unsigned int timer_number UNUSED, p_void_t parameter UNUSED, p_irq_cpu_registers_t state UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_cpu_array_init</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>p_cpu_t</type>
      <name>cpu_array</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>cpu_array_t</type>
      <name>global_cpu_array</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/tmp/EventClass/init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/</path>
    <filename>Repository_2tmp_2EventClass_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_event_class_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm/storm/init.c</name>
    <path>/root/Chaos/Sources/StormG4/storm/storm/</path>
    <filename>storm_2storm_2init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="subsystems_8h" name="subsystems.h" local="yes">subsystems.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>parse_enable_length</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>parse_disable_length</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>parse_parameters_length</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>arguments_parse</name>
      <anchor>a11</anchor>
      <arglist>(char *source, char **array_of_pointers)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>subsystem_set_enabled</name>
      <anchor>a12</anchor>
      <arglist>(char *name, bool enabled)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>subsystem_set_parameters</name>
      <anchor>a13</anchor>
      <arglist>(char *name, char *parameters)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>argument_analyse</name>
      <anchor>a14</anchor>
      <arglist>(char *argument)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>main_bootup</name>
      <anchor>a15</anchor>
      <arglist>(int argument_count, char *arguments[])</arglist>
    </member>
    <member kind="variable">
      <type>storm_info_t</type>
      <name>storm_info</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>subsystem_built_in_t</type>
      <name>subsystem_built_in</name>
      <anchor>a6</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>parse_enable</name>
      <anchor>a7</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>parse_disable</name>
      <anchor>a8</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>parse_parameters</name>
      <anchor>a9</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>char **</type>
      <name>storm_environ</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>init.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>init_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>repository_method_init</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_interface_init</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_event_supplier_interface_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_event_consumer_interface_init</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_class_init</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_object_init</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_handle_init</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_event_supplier_init</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_event_consumer_init</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_cpu_init</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_memory_init</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_computer_init</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>init_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>init__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="classes_8h" name="classes.h" local="yes">../classes.h</includes>
    <includes id="storm__module_8h" name="storm_module.h" local="no">Classes/storm_module.h</includes>
    <includes id="init__interface_8h" name="init_interface.h" local="yes">init_interface.h</includes>
    <includes id="static__modules_8h" name="static_modules.h" local="yes">../static_modules.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_KERNEL_CLASSES</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_STATIC_MODULES</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>arguments_parse</name>
      <anchor>a13</anchor>
      <arglist>(char *source, char **array_of_pointers)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>init</name>
      <anchor>a14</anchor>
      <arglist>(context_t context)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>init_init</name>
      <anchor>a15</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>kernel_class_info_t</type>
      <name>kernel_classes_info</name>
      <anchor>a4</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>p_object_reference_t</type>
      <name>storm_module_objects</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>object_reference_t</type>
      <name>kernel_object_root_flat_namespace</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>kernel_handle_root_flat_namespace</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>kernel_handle_namespace</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>kernel_handle_timer</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>event_queue_reference_t</type>
      <name>kernel_debug_queue</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>static_module_info_t</type>
      <name>static_modules_info</name>
      <anchor>a11</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>init_interface_table_t</type>
      <name>table</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>init_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>init__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="init__interface_8h" name="init_interface.h" local="yes">init_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>init_wrapper</name>
      <anchor>a6</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, sequence_t parameters_out UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>init_interface_register</name>
      <anchor>a7</anchor>
      <arglist>(p_init_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_init</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a3</anchor>
      <arglist>[METHOD_INIT_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>init_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>init__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>init_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_init_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>integer.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Integer/</path>
    <filename>integer_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="integer__value__class_8h" name="integer_value_class.h" local="yes">integer_value_class.h</includes>
    <includes id="integer__control__interface_8h" name="integer_control_interface.h" local="yes">integer_control_interface.h</includes>
    <class kind="struct">integer_value_data_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>integer_value_data_t *</type>
      <name>p_integer_value_data_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_void_t</type>
      <name>integer_object_create</name>
      <anchor>a4</anchor>
      <arglist>(context_t context UNUSED, uint32_t value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>integer_object_destroy</name>
      <anchor>a5</anchor>
      <arglist>(context_t context UNUSED, p_void_t object_data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>integer_get</name>
      <anchor>a6</anchor>
      <arglist>(context_t context, p_uint32_t value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>integer_set</name>
      <anchor>a7</anchor>
      <arglist>(context_t context, uint32_t value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>integer_value_init</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>integer_control_interface_table_t</type>
      <name>integer_control_table</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>integer_interface_table_t</type>
      <name>integer_table</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>integer_control_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Integer/</path>
    <filename>integer__control__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="integer__control__interface_8h" name="integer_control_interface.h" local="yes">integer_control_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>integer_control_interface_register</name>
      <anchor>a6</anchor>
      <arglist>(p_integer_control_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_description_t</type>
      <name>method_create_description</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_description_t</type>
      <name>method_destroy_description</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a4</anchor>
      <arglist>[METHOD_CONTROL_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>interface_description_t</type>
      <name>interface_control_description</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>integer_control_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Integer/</path>
    <filename>integer__control__interface_8h</filename>
    <class kind="struct">integer_control_interface_table_t</class>
    <member kind="define">
      <type>#define</type>
      <name>INTERFACE_INTEGER_VALUE_CONTROL_ID</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>integer_control_interface_table_t *</type>
      <name>p_integer_control_interface_table_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_CONTROL_CREATE_ID</name>
      <anchor>a6a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_CONTROL_DESTROY_ID</name>
      <anchor>a6a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_CONTROL_NUMBER</name>
      <anchor>a6a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>integer_control_interface_register</name>
      <anchor>a5</anchor>
      <arglist>(p_integer_control_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>integer_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Integer/</path>
    <filename>integer__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="integer__interface_8h" name="integer_interface.h" local="yes">integer_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_INTEGER_GET_ID</name>
      <anchor>a10a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_INTEGER_SET_ID</name>
      <anchor>a10a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_INTEGER_NUMBER</name>
      <anchor>a10a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>integer_interface_register</name>
      <anchor>a9</anchor>
      <arglist>(p_integer_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_description_t</type>
      <name>method_get_description</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_description_t</type>
      <name>method_set_description</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a4</anchor>
      <arglist>[METHOD_INTEGER_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>interface_description_t</type>
      <name>interface_integer_description</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>integer_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Integer/</path>
    <filename>integer__interface_8h</filename>
    <class kind="struct">integer_interface_table_t</class>
    <member kind="typedef">
      <type>integer_interface_table_t *</type>
      <name>p_integer_interface_table_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>integer_interface_register</name>
      <anchor>a1</anchor>
      <arglist>(p_integer_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>integer_value_class.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Integer/</path>
    <filename>integer__value__class_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="integer__value__class_8h" name="integer_value_class.h" local="yes">integer_value_class.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>integer_value_class_register</name>
      <anchor>a4</anchor>
      <arglist>(object_reference_t class_repository, p_integer_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>interface_reference_t</type>
      <name>interfaces</name>
      <anchor>a2</anchor>
      <arglist>[NUMBER_OF_INTEGER_VALUE_INTERFACES]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>class_description_t</type>
      <name>integer_value_class_description</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>integer_value_class.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Integer/</path>
    <filename>integer__value__class_8h</filename>
    <includes id="integer__interface_8h" name="integer_interface.h" local="yes">integer_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>CLASS_INTEGER_VALUE_ID</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_INTEGER_VALUE_INTERFACES</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>integer_value_class_register</name>
      <anchor>a2</anchor>
      <arglist>(object_reference_t class_repository, p_integer_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>integer_value_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Integer/</path>
    <filename>integer__value__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="integer__control__interface_8h" name="integer_control_interface.h" local="yes">integer_control_interface.h</includes>
    <class kind="struct">integer_value_data_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>integer_value_data_t *</type>
      <name>p_integer_value_data_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_void_t</type>
      <name>integer_value_create</name>
      <anchor>a3</anchor>
      <arglist>(context_t context UNUSED, uint32_t value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>integer_value_destroy</name>
      <anchor>a4</anchor>
      <arglist>(context_t context UNUSED, p_void_t object_data)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>integer_value_init</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>integer_control_interface_table_t</type>
      <name>integer_control_table</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>interface_8h</filename>
    <includes id="Repository_2Interface_2Include_2internal_8h" name="Repository/Interface/Include/internal.h" local="yes">../Interface/Include/internal.h</includes>
  </compound>
  <compound kind="file">
    <name>interfaces.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/</path>
    <filename>interfaces_8h</filename>
    <class kind="struct">kernel_interface_info_t</class>
    <member kind="typedef">
      <type>interface_reference_t(</type>
      <name>kernel_interface_init_function_t</name>
      <anchor>a0</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>kernel_interface_init_function_t *</type>
      <name>p_kernel_interface_init_function_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_INTERFACE_INIT_INDEX</name>
      <anchor>a17a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_INTERFACE_FLAT_NAMESPACE_OBJECT_FACTORY_INDEX</name>
      <anchor>a17a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_INTERFACE_NAMESPACE_INDEX</name>
      <anchor>a17a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_INTERFACE_TIMER_INDEX</name>
      <anchor>a17a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_INTERFACE_STORM_MODULE_FACTORY_INDEX</name>
      <anchor>a17a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_INTERFACE_IRQ_SUPPLIER_FACTORY_INDEX</name>
      <anchor>a17a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KERNEL_INTERFACE_STORM_PROGRAM_FACTORY_INDEX</name>
      <anchor>a17a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_interface_info_t</type>
      <name>kernel_interfaces_info</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>kernel_interface_init_function_t</type>
      <name>init_init</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_interface_init_function_t</type>
      <name>flat_namespace_object_factory_init</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_interface_init_function_t</type>
      <name>namespace_init</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_interface_init_function_t</type>
      <name>timer_interface_init</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_interface_init_function_t</type>
      <name>storm_module_factory_interface_init</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_interface_init_function_t</type>
      <name>irq_supplier_factory_init</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>kernel_interface_init_function_t</type>
      <name>storm_program_factory_interface_init</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/PhysicalMemory/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/PhysicalMemory/</path>
    <filename>Hardware_2PhysicalMemory_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Hardware_2PhysicalMemory_2Include_2internal_8h" name="Hardware/PhysicalMemory/Include/internal.h" local="yes">Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_init</name>
      <anchor>a4</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_deinit</name>
      <anchor>a5</anchor>
      <arglist>(p_physical_memory_t memory UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>internal_memory_allocate</name>
      <anchor>a6</anchor>
      <arglist>(p_raw_memory_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_deallocate</name>
      <anchor>a7</anchor>
      <arglist>(p_raw_memory_t interface, void *pointer)</arglist>
    </member>
    <member kind="variable">
      <type>range_node_t</type>
      <name>node_pool_global</name>
      <anchor>a2</anchor>
      <arglist>[INTERNAL_MEMORY_SIZE]</arglist>
    </member>
    <member kind="variable">
      <type>static_pool_of_integers_t</type>
      <name>node_allocator_global</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/VirtualMemory/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/</path>
    <filename>Hardware_2VirtualMemory_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Hardware_2VirtualMemory_2Include_2internal_8h" name="Hardware/VirtualMemory/Include/internal.h" local="yes">Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_init2</name>
      <anchor>a2</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_deinit2</name>
      <anchor>a3</anchor>
      <arglist>(p_physical_memory_t memory UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>internal_memory_allocate2</name>
      <anchor>a4</anchor>
      <arglist>(p_raw_memory_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_deallocate2</name>
      <anchor>a5</anchor>
      <arglist>(p_raw_memory_t interface, void *pointer)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Class/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/</path>
    <filename>Repository_2Class_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Computer/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Computer/</path>
    <filename>Repository_2Computer_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <includes id="scheduler_8h" name="scheduler.h" local="yes">Include/scheduler.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_start</name>
      <anchor>a3</anchor>
      <arglist>(p_computer_t computer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_stop</name>
      <anchor>a4</anchor>
      <arglist>(p_computer_t computer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_schedule_prepare</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>iret_call</name>
      <anchor>a6</anchor>
      <arglist>(p_function_t function)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_invoke_internal</name>
      <anchor>a7</anchor>
      <arglist>(p_computer_t computer, p_handle_t handle, p_object_t object, p_class_t class, p_interface_t interface, p_method_t method, context_t context, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_invoke_async_internal</name>
      <anchor>a8</anchor>
      <arglist>(p_computer_t computer, p_handle_t handle, p_object_t object, p_class_t class, p_interface_t interface, p_method_t method, reference_t reference_base UNUSED, reference_t reference_new UNUSED, sequence_t parameters_in, sequence_t parameters_inout)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_begin</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_call_function</name>
      <anchor>a10</anchor>
      <arglist>(p_function_t function, uint32_t type, uint64_t data, context_t context, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
    <member kind="variable">
      <type>volatile list_t</type>
      <name>computers</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Cpu/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Cpu/</path>
    <filename>Repository_2Cpu_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>p_cpu_t</type>
      <name>cpu_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(uint32_t performance)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_cpu_t cpu)</arglist>
    </member>
    <member kind="function">
      <type>cpu_reference_t</type>
      <name>cpu_get_current</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_sleep_milli</name>
      <anchor>a5</anchor>
      <arglist>(cpu_reference_t cpu UNUSED, uint32_t milli)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Descriptions/Exception/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/</path>
    <filename>Repository_2Descriptions_2Exception_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Descriptions_2Exception_2Include_2internal_8h" name="Repository/Descriptions/Exception/Include/internal.h" local="yes">Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>p_exception_t</type>
      <name>exception_create_static_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_exception_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_exception_t exception UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>p_exception_t</type>
      <name>exception_create_internal</name>
      <anchor>a4</anchor>
      <arglist>(p_exception_description_t exception_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_internal</name>
      <anchor>a5</anchor>
      <arglist>(p_exception_t exception)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/EventConsumerInterface/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/</path>
    <filename>Repository_2EventConsumerInterface_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/EventSupplierInterface/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/</path>
    <filename>Repository_2EventSupplierInterface_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Handle/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/</path>
    <filename>Repository_2Handle_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Interface/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/</path>
    <filename>Repository_2Interface_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Method/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/</path>
    <filename>Repository_2Method_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Object/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/</path>
    <filename>Repository_2Object_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Security/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Security/</path>
    <filename>Repository_2Security_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>p_security_t</type>
      <name>security_create_static_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_security_t security)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_destroy_static_internal</name>
      <anchor>a4</anchor>
      <arglist>(p_security_t security)</arglist>
    </member>
    <member kind="function">
      <type>p_security_t</type>
      <name>security_create_internal</name>
      <anchor>a5</anchor>
      <arglist>(bool security_is_absolute, p_generic_acl_t generic_acl)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_destroy_internal</name>
      <anchor>a6</anchor>
      <arglist>(p_security_t security)</arglist>
    </member>
    <member kind="variable">
      <type>security_t</type>
      <name>security_absolute</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/tmp/CpuArray/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/CpuArray/</path>
    <filename>Repository_2tmp_2CpuArray_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_array_schedule_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_cpu_array_t cpu_array)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/tmp/EventClass/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/</path>
    <filename>Repository_2tmp_2EventClass_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/tmp/Group/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/Group/</path>
    <filename>Repository_2tmp_2Group_2internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>p_group_t</type>
      <name>group_create_static_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_group_t group)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>group_destroy_static_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_group_t group)</arglist>
    </member>
    <member kind="function">
      <type>p_group_t</type>
      <name>group_create_internal</name>
      <anchor>a4</anchor>
      <arglist>(sequence_t group_objects)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>group_destroy_internal</name>
      <anchor>a5</anchor>
      <arglist>(p_group_t group)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/tmp/VirtualCpu/internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/VirtualCpu/</path>
    <filename>Repository_2tmp_2VirtualCpu_2internal_8c</filename>
    <member kind="function">
      <type>virtual_cpu_reference_t</type>
      <name>virtual_cpu_create_internal</name>
      <anchor>a0</anchor>
      <arglist>(uint32_t cpu_policy, resource_usage_t cpu_usage)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>virtual_cpu_destroy_internal</name>
      <anchor>a1</anchor>
      <arglist>(virtual_cpu_reference_t virtual_cpu_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/PhysicalMemory/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/PhysicalMemory/Include/</path>
    <filename>Hardware_2PhysicalMemory_2Include_2internal_8h</filename>
    <class kind="union">static_pool_of_integers_t</class>
    <member kind="define">
      <type>#define</type>
      <name>INTERNAL_MEMORY_SIZE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_init</name>
      <anchor>a3</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_deinit</name>
      <anchor>a4</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>internal_memory_allocate</name>
      <anchor>a5</anchor>
      <arglist>(p_raw_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_deallocate</name>
      <anchor>a6</anchor>
      <arglist>(p_raw_memory_t memory, void *pointer)</arglist>
    </member>
    <member kind="variable">
      <type>range_node_t</type>
      <name>node_pool_global</name>
      <anchor>a1</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>static_pool_of_integers_t</type>
      <name>node_allocator_global</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/VirtualMemory/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/Include/</path>
    <filename>Hardware_2VirtualMemory_2Include_2internal_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>USER_MEMORY_START</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>USER_MEMORY_SIZE</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INTERNAL_MEMORY_SIZE</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INTERNAL_MEMORY_INIT</name>
      <anchor>a3</anchor>
      <arglist>(mdata)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_init2</name>
      <anchor>a4</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_deinit2</name>
      <anchor>a5</anchor>
      <arglist>(p_physical_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>internal_memory_allocate2</name>
      <anchor>a6</anchor>
      <arglist>(p_raw_memory_t memory)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>internal_memory_deallocate2</name>
      <anchor>a7</anchor>
      <arglist>(p_raw_memory_t memory, void *pointer)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Class/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/Include/</path>
    <filename>Repository_2Class_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>p_class_t</type>
      <name>class_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_class_t class)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>class_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_class_t class)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_class_t</type>
      <name>class_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_class_description_t class_description, sequence_t class_interfaces, sequence_t class_event_suppliers, sequence_t class_event_consumers, handle_reference_t class_object_factory, handle_reference_t class_handle_factory, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>class_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_class_t class)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>class_set_interfaces_internal</name>
      <anchor>a4</anchor>
      <arglist>(p_class_t class UNUSED, sequence_t class_interfaces UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>class_get_interfaces_internal</name>
      <anchor>a5</anchor>
      <arglist>(p_class_t class UNUSED, sequence_t class_interfaces UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_interface_t</type>
      <name>class_get_interface_by_id_internal</name>
      <anchor>a6</anchor>
      <arglist>(p_class_t class, interface_id_t interface_id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_event_supplier_interface_t</type>
      <name>class_get_event_supplier_interface_by_id_internal</name>
      <anchor>a7</anchor>
      <arglist>(p_class_t class, id_t event_id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_event_consumer_interface_t</type>
      <name>class_get_event_consumer_interface_by_id_internal</name>
      <anchor>a8</anchor>
      <arglist>(p_class_t class, id_t event_id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>class_create_object_internal</name>
      <anchor>a9</anchor>
      <arglist>(p_class_t class, object_reference_t object, sequence_t parameters)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>class_destroy_object_internal</name>
      <anchor>a10</anchor>
      <arglist>(p_class_t class UNUSED, object_reference_t object UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>class_create_event_supplier_internal</name>
      <anchor>a11</anchor>
      <arglist>(p_class_t class UNUSED, p_object_t object, p_event_supplier_t event_supplier, sequence_t parameters)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Computer/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Computer/Include/</path>
    <filename>Repository_2Computer_2Include_2internal_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>computer_invoke_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_computer_t computer, p_handle_t handle, p_object_t object, p_class_t class, p_interface_t interface, p_method_t method, context_t context, reference_t base_reference, reference_t new_reference, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_invoke_async_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_computer_t computer, p_handle_t handle, p_object_t object, p_class_t class, p_interface_t interface, p_method_t method, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_call_function</name>
      <anchor>a3</anchor>
      <arglist>(p_function_t function, uint32_t type, uint64_t data, context_t context, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_start</name>
      <anchor>a4</anchor>
      <arglist>(p_computer_t computer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_stop</name>
      <anchor>a5</anchor>
      <arglist>(p_computer_t computer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_schedule_prepare</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_begin</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>volatile list_t</type>
      <name>computers</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Descriptions/Exception/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/Include/</path>
    <filename>Repository_2Descriptions_2Exception_2Include_2internal_8h</filename>
    <member kind="function">
      <type>p_exception_t</type>
      <name>exception_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_exception_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_exception_t exception)</arglist>
    </member>
    <member kind="function">
      <type>p_exception_t</type>
      <name>exception_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_exception_description_t exception_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_exception_t exception)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Descriptions/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Include/</path>
    <filename>Repository_2Descriptions_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>description_reference_t</type>
      <name>description_reference_acquire_internal</name>
      <anchor>a0</anchor>
      <arglist>(description_reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>description_reference_release_internal</name>
      <anchor>a1</anchor>
      <arglist>(description_reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>id_t</type>
      <name>description_reference_get_id_internal</name>
      <anchor>a2</anchor>
      <arglist>(description_reference_t reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/EventConsumerInterface/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/Include/</path>
    <filename>Repository_2EventConsumerInterface_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>p_event_consumer_interface_t</type>
      <name>event_consumer_interface_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_event_consumer_interface_t event_consumer_interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_consumer_interface_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_event_consumer_interface_t event_consumer_interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_event_consumer_interface_t</type>
      <name>event_consumer_interface_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_event_description_t event_description, int type, method_reference_t handle, reference_t event_consumer_factory, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_consumer_interface_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_event_consumer_interface_t event_consumer_interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>id_t</type>
      <name>event_consumer_interface_get_id_internal</name>
      <anchor>a4</anchor>
      <arglist>(p_event_consumer_interface_t interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_consumer_interface_set_factory_internal</name>
      <anchor>a5</anchor>
      <arglist>(p_event_consumer_interface_t event_consumer_interface, reference_t event_consumer_factory)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_consumer_interface_create_event_consumer_internal</name>
      <anchor>a6</anchor>
      <arglist>(p_event_consumer_interface_t interface, p_object_t object, event_consumer_reference_t event_consumer, sequence_t parameters)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_consumer_interface_fire_async_internal</name>
      <anchor>a7</anchor>
      <arglist>(p_event_consumer_interface_t interface, sequence_t event_data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_consumer_interface_fire_sync_internal</name>
      <anchor>a8</anchor>
      <arglist>(p_event_consumer_interface_t interface, sequence_t event_data)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/EventQueue/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventQueue/Include/</path>
    <filename>Repository_2EventQueue_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_queue_fire_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_event_queue_t event_queue, sequence_t event_data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_queue_wait_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_event_queue_t event_queue, sequence_t event_data)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/EventSupplier/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplier/Include/</path>
    <filename>Repository_2EventSupplier_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>p_event_supplier_t</type>
      <name>event_supplier_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_event_supplier_t event_supplier, sequence_t parameters, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_supplier_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_event_supplier_t event_supplier)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_event_consumer_t</type>
      <name>event_consumer_create_static_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_event_consumer_t event_consumer, sequence_t parameters UNUSED, uint32_t options UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/EventSupplierInterface/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/Include/</path>
    <filename>Repository_2EventSupplierInterface_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>p_event_supplier_interface_t</type>
      <name>event_supplier_interface_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_event_supplier_interface_t event_supplier_interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_supplier_interface_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_event_supplier_interface_t event_supplier_interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_event_supplier_interface_t</type>
      <name>event_supplier_interface_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_event_description_t event_description, int type, method_reference_t handle, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_supplier_interface_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_event_supplier_interface_t event_supplier_interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>id_t</type>
      <name>event_supplier_interface_get_id_internal</name>
      <anchor>a4</anchor>
      <arglist>(p_event_supplier_interface_t interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_supplier_interface_set_factory_internal</name>
      <anchor>a5</anchor>
      <arglist>(p_event_supplier_interface_t event_supplier_interface, reference_t event_supplier_factory)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_supplier_interface_create_event_supplier_internal</name>
      <anchor>a6</anchor>
      <arglist>(p_event_supplier_interface_t interface, p_object_t object, event_supplier_reference_t event_supplier, sequence_t parameters)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_supplier_interface_wait_internal</name>
      <anchor>a7</anchor>
      <arglist>(p_event_supplier_interface_t interface UNUSED, sequence_t event_data UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Handle/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/Include/</path>
    <filename>Repository_2Handle_2Include_2internal_8h</filename>
    <includes id="Handle_2Include_2invoke__internal_8h" name="Handle/Include/invoke_internal.h" local="yes">invoke_internal.h</includes>
    <member kind="function" static="yes">
      <type>p_handle_t</type>
      <name>handle_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_handle_t handle, sequence_t parameters, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>handle_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_handle_t handle)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>handle_clone_static_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_handle_t handle, p_handle_t new_handle, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_handle_t</type>
      <name>handle_create_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_object_t object, interface_id_t interface_id, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>handle_destroy_internal</name>
      <anchor>a4</anchor>
      <arglist>(p_handle_t handle)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_handle_t</type>
      <name>handle_clone_internal</name>
      <anchor>a5</anchor>
      <arglist>(p_handle_t handle, uint32_t options)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>Repository_2Include_2internal_8h</filename>
    <includes id="init_8h" name="init.h" local="yes">init.h</includes>
    <includes id="reference_8h" name="reference.h" local="yes">reference.h</includes>
    <includes id="cpu_8h" name="cpu.h" local="yes">cpu.h</includes>
    <includes id="memory_8h" name="memory.h" local="yes">memory.h</includes>
    <includes id="computer_8h" name="computer.h" local="yes">computer.h</includes>
    <includes id="Repository_2Descriptions_2Include_2internal_8h" name="Repository/Descriptions/Include/internal.h" local="yes">../Descriptions/Include/internal.h</includes>
    <includes id="translate_8h" name="translate.h" local="yes">translate.h</includes>
    <includes id="invoke_8h" name="invoke.h" local="yes">invoke.h</includes>
    <includes id="method_8h" name="method.h" local="yes">method.h</includes>
    <includes id="interface_8h" name="interface.h" local="yes">interface.h</includes>
    <includes id="event__supplier__interface_8h" name="event_supplier_interface.h" local="yes">event_supplier_interface.h</includes>
    <includes id="event__consumer__interface_8h" name="event_consumer_interface.h" local="yes">event_consumer_interface.h</includes>
    <includes id="Repository_2EventQueue_2Include_2internal_8h" name="Repository/EventQueue/Include/internal.h" local="yes">../EventQueue/Include/internal.h</includes>
    <includes id="class_8h" name="class.h" local="yes">class.h</includes>
    <includes id="object_8h" name="object.h" local="yes">object.h</includes>
    <includes id="handle_8h" name="handle.h" local="yes">handle.h</includes>
    <includes id="Repository_2EventSupplier_2Include_2internal_8h" name="Repository/EventSupplier/Include/internal.h" local="yes">../EventSupplier/Include/internal.h</includes>
    <includes id="security_8h" name="security.h" local="yes">security.h</includes>
  </compound>
  <compound kind="file">
    <name>Repository/Interface/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/Include/</path>
    <filename>Repository_2Interface_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>p_interface_t</type>
      <name>interface_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_interface_t interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>interface_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_interface_t interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_interface_t</type>
      <name>interface_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_interface_description_t interface_description, sequence_t interface_methods, reference_t interface_factory, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>interface_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_interface_t interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>id_t</type>
      <name>interface_get_id_internal</name>
      <anchor>a4</anchor>
      <arglist>(p_interface_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Method/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/Include/</path>
    <filename>Repository_2Method_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>p_method_t</type>
      <name>method_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_method_t method)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>method_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_method_t method)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_method_t</type>
      <name>method_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(description_reference_t method_description, p_computer_t method_computer, p_memory_t method_memory, p_method_function_t method_function, uint64_t method_data, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>method_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_method_t method)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_method_function_t</type>
      <name>method_get_function_internal</name>
      <anchor>a4</anchor>
      <arglist>(p_method_t method)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint32_t</type>
      <name>method_get_type_internal</name>
      <anchor>a5</anchor>
      <arglist>(p_method_t method)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint64_t</type>
      <name>method_get_data_internal</name>
      <anchor>a6</anchor>
      <arglist>(p_method_t method)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Object/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/Include/</path>
    <filename>Repository_2Object_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>p_object_t</type>
      <name>object_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_object_t object, sequence_t parameters, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_object_t object)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_object_t</type>
      <name>object_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_class_t object_class, p_security_t object_security, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_object_t object)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint64_t</type>
      <name>object_get_data_internal</name>
      <anchor>a4</anchor>
      <arglist>(p_object_t object)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_class_t</type>
      <name>object_get_class_internal</name>
      <anchor>a5</anchor>
      <arglist>(p_object_t object)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_interface_t</type>
      <name>object_get_interface_by_id_internal</name>
      <anchor>a6</anchor>
      <arglist>(p_object_t object, interface_id_t interface_id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_event_supplier_interface_t</type>
      <name>object_get_event_supplier_interface_by_id_internal</name>
      <anchor>a7</anchor>
      <arglist>(p_object_t object, id_t event_class_id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_event_consumer_interface_t</type>
      <name>object_get_event_consumer_interface_by_id_internal</name>
      <anchor>a8</anchor>
      <arglist>(p_object_t object, id_t event_class_id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_security_t</type>
      <name>object_get_security_internal</name>
      <anchor>a9</anchor>
      <arglist>(p_object_t object)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_set_security_internal</name>
      <anchor>a10</anchor>
      <arglist>(p_object_t object, p_security_t security)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_create_handle_internal</name>
      <anchor>a11</anchor>
      <arglist>(p_object_t object UNUSED, handle_reference_t handle UNUSED, sequence_t parameters UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_destroy_handle_internal</name>
      <anchor>a12</anchor>
      <arglist>(p_object_t object UNUSED, handle_reference_t handle UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_create_event_supplier_internal</name>
      <anchor>a13</anchor>
      <arglist>(p_object_t object, p_event_supplier_t event_supplier, sequence_t parameters)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_destroy_event_supplier_internal</name>
      <anchor>a14</anchor>
      <arglist>(p_object_t object UNUSED, event_supplier_reference_t event_supplier UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_create_event_consumer_internal</name>
      <anchor>a15</anchor>
      <arglist>(p_object_t object UNUSED, p_event_consumer_t event_consumer UNUSED, sequence_t parameters UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Reference/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Reference/Include/</path>
    <filename>Repository_2Reference_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>reference_t</type>
      <name>reference_create_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_reference_struct_t reference_struct, unsigned int reference_type)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>reference_destroy_internal</name>
      <anchor>a2</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>reference_t</type>
      <name>reference_acquire_internal</name>
      <anchor>a3</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>reference_release_internal</name>
      <anchor>a4</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint32_t</type>
      <name>reference_get_type_internal</name>
      <anchor>a5</anchor>
      <arglist>(reference_t reference UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>object_reference_t</type>
      <name>reference_get_owner_internal</name>
      <anchor>a6</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint32_t</type>
      <name>reference_get_number_of_references_internal</name>
      <anchor>a7</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>reference_is_nill_internal</name>
      <anchor>a8</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>reference_is_exists_internal</name>
      <anchor>a9</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>reference_equals_internal</name>
      <anchor>a10</anchor>
      <arglist>(reference_t reference, reference_t reference2)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>magic_number_table</name>
      <anchor>a0</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/tmp/EventClass/Include/internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/Include/</path>
    <filename>Repository_2tmp_2EventClass_2Include_2internal_8h</filename>
    <member kind="function" static="yes">
      <type>p_event_class_t</type>
      <name>event_class_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_event_class_t event_class)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_class_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_event_class_t event_class)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_event_class_t</type>
      <name>event_class_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_event_class_description_t event_class_description)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_class_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_event_class_t event_class)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>invoke.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>invoke_8h</filename>
    <includes id="Method_2Include_2invoke__internal_8h" name="Method/Include/invoke_internal.h" local="yes">../Method/Include/invoke_internal.h</includes>
    <includes id="Interface_2Include_2invoke__internal_8h" name="Interface/Include/invoke_internal.h" local="yes">../Interface/Include/invoke_internal.h</includes>
    <includes id="Class_2Include_2invoke__internal_8h" name="Class/Include/invoke_internal.h" local="yes">../Class/Include/invoke_internal.h</includes>
    <includes id="Object_2Include_2invoke__internal_8h" name="Object/Include/invoke_internal.h" local="yes">../Object/Include/invoke_internal.h</includes>
    <includes id="Handle_2Include_2invoke__internal_8h" name="Handle/Include/invoke_internal.h" local="yes">../Handle/Include/invoke_internal.h</includes>
  </compound>
  <compound kind="file">
    <name>Class/Include/invoke_internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/Include/</path>
    <filename>Class_2Include_2invoke__internal_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>class_invoke_method_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_class_t class, p_handle_t handle, p_object_t object, p_interface_t interface, method_id_t method_id, p_computer_t computer, context_t context, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Handle/Include/invoke_internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/Include/</path>
    <filename>Handle_2Include_2invoke__internal_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>handle_invoke_method_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_handle_t handle, method_id_t method_id, p_computer_t computer, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Interface/Include/invoke_internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/Include/</path>
    <filename>Interface_2Include_2invoke__internal_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>interface_invoke_method_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_interface_t interface, p_handle_t handle, p_object_t object, p_class_t class, method_id_t method_id, p_computer_t computer, context_t context, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/Include/invoke_internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/Include/</path>
    <filename>Method_2Include_2invoke__internal_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>method_invoke_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_method_t method, p_handle_t handle, p_object_t object, p_class_t class, p_interface_t interface, p_computer_t computer, context_t context, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>method_invoke_async_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_method_t method, p_handle_t handle, p_object_t object, p_class_t class, p_interface_t interface, p_computer_t computer, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Object/Include/invoke_internal.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/Include/</path>
    <filename>Object_2Include_2invoke__internal_8h</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_invoke_method_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_object_t object, p_handle_t handle, p_interface_t interface, method_id_t method_id, p_computer_t computer, uint64_t handle_data, reference_t reference_base, reference_t reference_new, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>io_apic.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>io__apic_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>io_apic_assign_pci_irqs</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hardware/Irq/irq.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Irq/</path>
    <filename>Hardware_2Irq_2irq_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="pic_8h" name="pic.h" local="yes">Include/pic.h</includes>
    <includes id="irq_8h" name="irq.h" local="yes">Include/irq.h</includes>
    <includes id="Irq_2Include_2handlers_8h" name="Irq/Include/handlers.h" local="yes">Include/handlers.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>irq_init</name>
      <anchor>a5</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>irq_register</name>
      <anchor>a6</anchor>
      <arglist>(unsigned int irq_number, p_irq_handler_t function, p_void_t parameter)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>irq_unregister</name>
      <anchor>a7</anchor>
      <arglist>(unsigned int irq_number)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>irq_set_post_handler</name>
      <anchor>a8</anchor>
      <arglist>(unsigned int irq_number, p_function_t handler)</arglist>
    </member>
    <member kind="variable">
      <type>p_irq_handler_t</type>
      <name>irq_handlers</name>
      <anchor>a1</anchor>
      <arglist>[NUMBER_OF_IRQ_CHANNELS]</arglist>
    </member>
    <member kind="variable">
      <type>p_void_t</type>
      <name>irq_handlers_data</name>
      <anchor>a2</anchor>
      <arglist>[NUMBER_OF_IRQ_CHANNELS]</arglist>
    </member>
    <member kind="variable">
      <type>p_function_t</type>
      <name>irq_post_handlers</name>
      <anchor>a3</anchor>
      <arglist>[NUMBER_OF_IRQ_CHANNELS]</arglist>
    </member>
    <member kind="variable">
      <type>p_function_t</type>
      <name>irq_tmp_post_handler</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Repository/Kernel/Computer/irq.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Computer/</path>
    <filename>Repository_2Kernel_2Computer_2irq_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <class kind="struct">object_irq_aregister_method_t</class>
    <class kind="struct">object_irq_unregister_method_t</class>
    <member kind="define">
      <type>#define</type>
      <name>number_of_methods</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>object_irq_init</name>
      <anchor>a5</anchor>
      <arglist>(interface_id_t *interface_id)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>object_irq_aregister_method_t</type>
      <name>object_irq_aregister_method</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>object_irq_unregister_method_t</type>
      <name>object_irq_unregister_method</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_t *</type>
      <name>methods</name>
      <anchor>a3</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>irq_interface_t</type>
      <name>object_irq_interface</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>irq.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Irq/Include/</path>
    <filename>irq_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>irq_handler</name>
      <anchor>a1</anchor>
      <arglist>(unsigned int irq_number, irq_cpu_registers_t registers)</arglist>
    </member>
    <member kind="variable">
      <type>irq_handler_t *</type>
      <name>irq_handlers</name>
      <anchor>a0</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>irq_event_class.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Events/</path>
    <filename>irq__event__class_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="irq__event__class_8h" name="irq_event_class.h" local="yes">Include/irq_event_class.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>irq_description_register</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>supplier_handler_wrapper</name>
      <anchor>a4</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_out UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>irq_supplier_interface_register</name>
      <anchor>a5</anchor>
      <arglist>(uint32_t type, p_irq_supplier_handler_t handler, cpu_reference_t cpu)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>consumer_handler_wrapper</name>
      <anchor>a6</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>irq_consumer_interface_register</name>
      <anchor>a7</anchor>
      <arglist>(uint32_t type, p_irq_consumer_handler_t handler, cpu_reference_t cpu)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>irq_description</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>irq_event_class.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Events/Include/</path>
    <filename>irq__event__class_8h</filename>
    <member kind="function">
      <type>description_reference_t</type>
      <name>irq_description_register</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>irq_supplier_interface_register</name>
      <anchor>a1</anchor>
      <arglist>(uint32_t type, p_irq_supplier_handler_t handler, cpu_reference_t cpu)</arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>irq_consumer_interface_register</name>
      <anchor>a2</anchor>
      <arglist>(uint32_t type, p_irq_consumer_handler_t handler, cpu_reference_t cpu)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>irq_supplier_factory_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>irq__supplier__factory__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="irq__supplier__factory__interface_8h" name="irq_supplier_factory_interface.h" local="yes">irq_supplier_factory_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>event_irq_handler</name>
      <anchor>a3</anchor>
      <arglist>(unsigned int irq_number UNUSED, p_void_t parameter, irq_cpu_registers_t registers UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>create</name>
      <anchor>a4</anchor>
      <arglist>(context_t context UNUSED, event_supplier_reference_t irq_supplier, uint32_t irq_number)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>destroy</name>
      <anchor>a5</anchor>
      <arglist>(context_t context UNUSED, event_supplier_reference_t irq_supplier)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>irq_supplier_factory_init</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>irq_supplier_factory_interface_table_t</type>
      <name>table</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>irq_supplier_factory_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>irq__supplier__factory__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="irq__supplier__factory__interface_8h" name="irq_supplier_factory_interface.h" local="yes">irq_supplier_factory_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>create_wrapper</name>
      <anchor>a7</anchor>
      <arglist>(uint64_t function, context_t context, object_reference_t object UNUSED, event_supplier_reference_t event_supplier, sequence_t parameters_in)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>destroy_wrapper</name>
      <anchor>a8</anchor>
      <arglist>(uint64_t function, context_t context, object_reference_t object UNUSED, event_supplier_reference_t event_supplier)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>irq_supplier_factory_interface_register</name>
      <anchor>a9</anchor>
      <arglist>(p_irq_supplier_factory_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_create</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_destroy</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a4</anchor>
      <arglist>[METHOD_EVENT_SUPPLIER_FACTORY_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>irq_supplier_factory_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>irq__supplier__factory__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>irq_supplier_factory_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_irq_supplier_factory_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>irq_supplier_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Events/</path>
    <filename>irq__supplier__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="event__supplier__interfaces_8h" name="event_supplier_interfaces.h" local="yes">../event_supplier_interfaces.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="irq__event__class_8h" name="irq_event_class.h" local="yes">Include/irq_event_class.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>irq_supplier_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>jump_lowlevel.S</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Computer/</path>
    <filename>jump__lowlevel_8S</filename>
    <member kind="function">
      <type>globl jump_lowlevel eax movl</type>
      <name>x04</name>
      <anchor>a3</anchor>
      <arglist>(%eax)</arglist>
    </member>
    <member kind="function">
      <type>globl jump_lowlevel eax movl ebx movl esp movl</type>
      <name>x08</name>
      <anchor>a4</anchor>
      <arglist>(%eax)</arglist>
    </member>
    <member kind="function">
      <type>globl jump_lowlevel eax movl ebx movl esp movl ebx push ebx movl</type>
      <name>x0C</name>
      <anchor>a5</anchor>
      <arglist>(%eax)</arglist>
    </member>
    <member kind="function">
      <type>globl jump_lowlevel eax movl ebx movl esp movl ebx push ebx movl edi movl</type>
      <name>x10</name>
      <anchor>a6</anchor>
      <arglist>(%eax)</arglist>
    </member>
    <member kind="function">
      <type>globl jump_lowlevel eax movl ebx movl esp movl ebx push ebx movl edi movl esi movl</type>
      <name>x14</name>
      <anchor>a7</anchor>
      <arglist>(%eax)</arglist>
    </member>
    <member kind="function">
      <type>globl jump_lowlevel eax movl ebx movl esp movl ebx push ebx movl edi movl esi movl ebp movl</type>
      <name>x18</name>
      <anchor>a8</anchor>
      <arglist>(%eax)</arglist>
    </member>
    <member kind="function">
      <type>globl jump_lowlevel eax movl ebx movl esp movl ebx push ebx movl edi movl esi movl ebp movl ebx movl</type>
      <name>x1C</name>
      <anchor>a9</anchor>
      <arglist>(%eax)</arglist>
    </member>
    <member kind="function">
      <type>globl jump_lowlevel eax movl ebx movl esp movl ebx push ebx movl edi movl esi movl ebp movl ebx movl edx movl</type>
      <name>x20</name>
      <anchor>a10</anchor>
      <arglist>(%eax)</arglist>
    </member>
    <member kind="function">
      <type>globl jump_lowlevel eax movl ebx movl esp movl ebx push ebx movl edi movl esi movl ebp movl ebx movl edx movl ecx push ebx movl ebx movl</type>
      <name>x24</name>
      <anchor>a11</anchor>
      <arglist>(%ebx)</arglist>
    </member>
    <member kind="variable">
      <type>globl jump_lowlevel</type>
      <name>jump_lowlevel</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>globl jump_lowlevel eax movl ebx movl</type>
      <name>ebx</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>globl jump_lowlevel eax movl ebx movl esp movl ebx push ebx movl edi movl esi movl ebp movl ebx movl edx movl ecx push ebx movl</type>
      <name>eax</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>kernel.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>kernel_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>kernel_init</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>kernel_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Module/</path>
    <filename>kernel__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="storm__module_8h" name="storm_module.h" local="no">Classes/storm_module.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>storm_module_init</name>
      <anchor>a3</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED)</arglist>
    </member>
    <member kind="variable">
      <type>p_storm_module_info_t</type>
      <name>storm_modules</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>kernel_module_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Module/</path>
    <filename>kernel__module__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="storm__module_8h" name="storm_module.h" local="no">Classes/storm_module.h</includes>
    <class kind="struct">module_info_t</class>
    <class kind="struct">storm_module_data_t</class>
    <class kind="struct">storm_module_info_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME_LENGTH</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_VERSION_LENGTH</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>return_t(</type>
      <name>module_start_function_t</name>
      <anchor>a4</anchor>
      <arglist>)(int argc, char *argv[])</arglist>
    </member>
    <member kind="typedef">
      <type>return_t(</type>
      <name>module_stop_function_t</name>
      <anchor>a5</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>return_t</type>
      <name>storm_module_create</name>
      <anchor>a10</anchor>
      <arglist>(context_t *context, void *parameter)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>return_t</type>
      <name>storm_module_destroy</name>
      <anchor>a11</anchor>
      <arglist>(context_t *context)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>return_t</type>
      <name>storm_module_start</name>
      <anchor>a12</anchor>
      <arglist>(context_t *context, uint32_t argc, char *argv[])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>return_t</type>
      <name>storm_module_stop</name>
      <anchor>a13</anchor>
      <arglist>(context_t *context)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>storm_module_init</name>
      <anchor>a14</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>function_info_t</type>
      <name>function</name>
      <anchor>a3</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>storm_module_info_t *</type>
      <name>storm_modules</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>interface_id_t</type>
      <name>storm_module_repository_id</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>interface_id_t</type>
      <name>storm_module_interface_id</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>class_id_t</type>
      <name>storm_module_class_id</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>lock.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/</path>
    <filename>lock_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
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
  </compound>
  <compound kind="file">
    <name>main.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Boot/Include/</path>
    <filename>main_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>main_bootup</name>
      <anchor>a0</anchor>
      <arglist>(int argument_count, char *arguments[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>mc146818.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Clock/Include/</path>
    <filename>mc146818_8h</filename>
    <class kind="struct">rtc_time_t</class>
    <member kind="define">
      <type>#define</type>
      <name>RTC_PORT</name>
      <anchor>a0</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_ALWAYS_BCD</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_SECONDS</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_SECONDS_ALARM</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_MINUTES</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_MINUTES_ALARM</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_HOURS</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_HOURS_ALARM</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_ALARM_DONT_CARE</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_DAY_OF_WEEK</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_DAY_OF_MONTH</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_MONTH</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_YEAR</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_REG_A</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_REG_B</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_REG_C</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_REG_D</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_FREQ_SELECT</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_UIP</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_DIV_CTL</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_REF_CLCK_4MHZ</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_REF_CLCK_1MHZ</name>
      <anchor>a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_REF_CLCK_32KHZ</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_DIV_RESET1</name>
      <anchor>a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_DIV_RESET2</name>
      <anchor>a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_RATE_SELECT</name>
      <anchor>a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_CONTROL</name>
      <anchor>a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_SET</name>
      <anchor>a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_PIE</name>
      <anchor>a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_AIE</name>
      <anchor>a29</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_UIE</name>
      <anchor>a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_SQWE</name>
      <anchor>a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_DM_BINARY</name>
      <anchor>a32</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_24H</name>
      <anchor>a33</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_DST_EN</name>
      <anchor>a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_INTR_FLAGS</name>
      <anchor>a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_IRQF</name>
      <anchor>a36</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_PF</name>
      <anchor>a37</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_AF</name>
      <anchor>a38</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_UF</name>
      <anchor>a39</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_VALID</name>
      <anchor>a40</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RTC_VRT</name>
      <anchor>a41</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BCD_TO_BIN</name>
      <anchor>a42</anchor>
      <arglist>(val)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BIN_TO_BCD</name>
      <anchor>a43</anchor>
      <arglist>(val)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint8_t</type>
      <name>cmos_read</name>
      <anchor>a44</anchor>
      <arglist>(uint8_t offset)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>cmos_write</name>
      <anchor>a45</anchor>
      <arglist>(uint8_t addr, uint8_t value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint8_t</type>
      <name>convert_bcd_to_bin</name>
      <anchor>a46</anchor>
      <arglist>(uint8_t value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Kernel/Computer/memory.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Computer/</path>
    <filename>Kernel_2Computer_2memory_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <class kind="struct">object_memory_allocate_method_t</class>
    <class kind="struct">object_memory_deallocate_method_t</class>
    <member kind="define">
      <type>#define</type>
      <name>number_of_methods</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>object_memory_init</name>
      <anchor>a5</anchor>
      <arglist>(interface_id_t *interface_id)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>object_memory_allocate_method_t</type>
      <name>object_memory_allocate_method</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>object_memory_deallocate_method_t</type>
      <name>object_memory_deallocate_method</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_t *</type>
      <name>methods</name>
      <anchor>a3</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>memory_interface_t</type>
      <name>object_memory_interface</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Memory/memory.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Memory/</path>
    <filename>Memory_2memory_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="slab_8h" name="slab.h" local="yes">slab.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>memory_allocate</name>
      <anchor>a2</anchor>
      <arglist>(void **pointer, unsigned int bytes)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>memory_deallocate</name>
      <anchor>a3</anchor>
      <arglist>(void *pointer UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>memory.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>memory_8h</filename>
  </compound>
  <compound kind="file">
    <name>method.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>method_8h</filename>
    <includes id="Repository_2Method_2Include_2internal_8h" name="Repository/Method/Include/internal.h" local="yes">../Method/Include/internal.h</includes>
  </compound>
  <compound kind="file">
    <name>module.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Module/</path>
    <filename>module_8h</filename>
    <class kind="struct">module_info_t</class>
    <class kind="struct">storm_module_data_t</class>
    <class kind="struct">storm_module_info_t</class>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME_LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_VERSION_LENGTH</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>return_t(</type>
      <name>module_start_t</name>
      <anchor>a3</anchor>
      <arglist>)(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="typedef">
      <type>module_start_t *</type>
      <name>p_module_start_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>return_t(</type>
      <name>module_stop_t</name>
      <anchor>a5</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>module_stop_t *</type>
      <name>p_module_stop_t</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>storm_module_data_t *</type>
      <name>p_storm_module_data_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>storm_module_info_t *</type>
      <name>p_storm_module_info_t</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>function_info_t</type>
      <name>functions_table</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>p_storm_module_info_t</type>
      <name>storm_modules</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>multiboot.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Boot/</path>
    <filename>multiboot_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="multiboot_8h" name="multiboot.h" local="yes">Include/multiboot.h</includes>
    <member kind="function">
      <type>void</type>
      <name>multiboot_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t multiboot_header[]</type>
      <name>MULTIBOOT_HEADER_ATTR</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>multiboot_info_t</type>
      <name>multiboot_info</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>multiboot.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Boot/Include/</path>
    <filename>multiboot_8h</filename>
    <class kind="struct">multiboot_info_t</class>
    <class kind="struct">multiboot_module_info_t</class>
    <class kind="struct">multiboot_memory_map_t</class>
    <member kind="define">
      <type>#define</type>
      <name>MULTIBOOT_MAGIC</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MULTIBOOT_FLAGS</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME_SIZE</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MEMORY_MAP_SIZE</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMMAND_LINE_SIZE</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MULTIBOOT_PAGE_ALIGN</name>
      <anchor>a12a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MULTIBOOT_GET_MEMORY</name>
      <anchor>a12a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MULTIBOOT_GET_VIDEO_MODE</name>
      <anchor>a12a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>multiboot_init</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>multiboot_info_t</type>
      <name>multiboot_info</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>multiboot_module_info_t</type>
      <name>multiboot_module_info</name>
      <anchor>a6</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>multiboot_memory_map_t</type>
      <name>multiboot_memory_map</name>
      <anchor>a7</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>namespace_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>namespace__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="classes_8h" name="classes.h" local="yes">../classes.h</includes>
    <includes id="namespace__interface_8h" name="namespace_interface.h" local="yes">namespace_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FORCE_CREATE</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>is_char_illegal</name>
      <anchor>a6</anchor>
      <arglist>(wchar_t c)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>bool</type>
      <name>get_element</name>
      <anchor>a7</anchor>
      <arglist>(wchar_t *full_name, wchar_t *element_name, wchar_t **next_name)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>bind</name>
      <anchor>a8</anchor>
      <arglist>(context_t context, wchar_t *name, reference_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>rebind</name>
      <anchor>a9</anchor>
      <arglist>(context_t context UNUSED, wchar_t *old_name UNUSED, wchar_t *new_name UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>reference_t</type>
      <name>resolve</name>
      <anchor>a10</anchor>
      <arglist>(context_t context, wchar_t *name)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>unbind</name>
      <anchor>a11</anchor>
      <arglist>(context_t context UNUSED, wchar_t *name)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>namespace_init</name>
      <anchor>a12</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>kernel_handle_root_flat_namespace</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>char_illegals</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>namespace_interface_table_t</type>
      <name>table</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>namespace_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>namespace__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="namespace__interface_8h" name="namespace_interface.h" local="yes">namespace_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>bind_wrapper</name>
      <anchor>a9</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>rebind_wrapper</name>
      <anchor>a10</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out UNUSED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>resolve_wrapper</name>
      <anchor>a11</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>unbind_wrapper</name>
      <anchor>a12</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>namespace_interface_register</name>
      <anchor>a13</anchor>
      <arglist>(p_namespace_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_bind</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_rebind</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_resolve</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_unbind</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a6</anchor>
      <arglist>[METHOD_NAMESPACE_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>namespace_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>namespace__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>namespace_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_namespace_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>object.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>object_8h</filename>
    <includes id="Repository_2Object_2Include_2internal_8h" name="Repository/Object/Include/internal.h" local="yes">../Object/Include/internal.h</includes>
  </compound>
  <compound kind="file">
    <name>page.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/</path>
    <filename>page_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="page_8h" name="page.h" local="yes">Include/page.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>page_lookup</name>
      <anchor>a2</anchor>
      <arglist>(p_page_directory_t page_directory, page_number_t virtual_page, page_number_t *physical_page, unsigned int *flags)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>page_map</name>
      <anchor>a3</anchor>
      <arglist>(page_directory_t *page_directory, page_number_t virtual_page, page_number_t physical_page, unsigned int pages, unsigned int flags)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>page_init</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>p_page_directory_t</type>
      <name>page_directory_global</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>page.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/Include/</path>
    <filename>page_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>page_init</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>page_map</name>
      <anchor>a2</anchor>
      <arglist>(p_page_directory_t page_directory, page_number_t virtual_page, page_number_t physical_page, unsigned int pages, unsigned int flags)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>page_lookup</name>
      <anchor>a3</anchor>
      <arglist>(p_page_directory_t page_directory, page_number_t virtual_page, p_page_number_t physical_page, unsigned int *flags)</arglist>
    </member>
    <member kind="variable">
      <type>p_page_directory_t</type>
      <name>page_directory_global</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Class/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/</path>
    <filename>Class_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Class_2Include_2parameters__check_8h" name="Class/Include/parameters_check.h" local="yes">Include/parameters_check.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Exception/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/</path>
    <filename>Descriptions_2Exception_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventConsumerInterface/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/</path>
    <filename>EventConsumerInterface_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="EventConsumerInterface_2Include_2parameters__check_8h" name="EventConsumerInterface/Include/parameters_check.h" local="yes">Include/parameters_check.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventSupplierInterface/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/</path>
    <filename>EventSupplierInterface_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="EventSupplierInterface_2Include_2parameters__check_8h" name="EventSupplierInterface/Include/parameters_check.h" local="yes">Include/parameters_check.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Handle/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/</path>
    <filename>Handle_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Interface/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/</path>
    <filename>Interface_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Interface_2Include_2parameters__check_8h" name="Interface/Include/parameters_check.h" local="yes">Include/parameters_check.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/</path>
    <filename>Method_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Object/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/</path>
    <filename>Object_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Security/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Security/</path>
    <filename>Security_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Security_2Include_2parameters__check_8h" name="Security/Include/parameters_check.h" local="yes">Include/parameters_check.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/EventClass/parameters_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/</path>
    <filename>tmp_2EventClass_2parameters__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="tmp_2EventClass_2Include_2parameters__check_8h" name="tmp/EventClass/Include/parameters_check.h" local="yes">Include/parameters_check.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Class/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/Include/</path>
    <filename>Class_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(p_class_description_t class_description, sequence_t class_interfaces, object_reference_t class_repository)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(class_reference_t class)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Exception/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/Include/</path>
    <filename>Descriptions_2Exception_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(p_class_description_t class_description, sequence_t class_interfaces, object_reference_t class_repository)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(class_reference_t class)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventConsumerInterface/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/Include/</path>
    <filename>EventConsumerInterface_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>interface_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(p_interface_description_t interface_description, sequence_t interface_methods)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventSupplierInterface/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/Include/</path>
    <filename>EventSupplierInterface_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>interface_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(p_interface_description_t interface_description, sequence_t interface_methods)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Handle/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/Include/</path>
    <filename>Handle_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(p_class_description_t class_description, sequence_t class_interfaces, object_reference_t class_repository)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(class_reference_t class)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Interface/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/Include/</path>
    <filename>Interface_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>interface_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(p_interface_description_t interface_description, sequence_t interface_methods)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/Include/</path>
    <filename>Method_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(p_class_description_t class_description, sequence_t class_interfaces, object_reference_t class_repository)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(class_reference_t class)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Object/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/Include/</path>
    <filename>Object_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(p_class_description_t class_description, sequence_t class_interfaces, object_reference_t class_repository)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(class_reference_t class)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Security/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Security/Include/</path>
    <filename>Security_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>security_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(bool security_is_absolute, p_generic_acl_t generic_acl)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(p_security_t security)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/EventClass/Include/parameters_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/Include/</path>
    <filename>tmp_2EventClass_2Include_2parameters__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_parameters</name>
      <anchor>a0</anchor>
      <arglist>(p_class_description_t class_description, sequence_t class_interfaces, object_reference_t class_repository)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_parameters</name>
      <anchor>a1</anchor>
      <arglist>(class_reference_t class)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>parse.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Boot/</path>
    <filename>parse_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="parse_8h" name="parse.h" local="yes">Include/parse.h</includes>
    <member kind="function">
      <type>unsigned int</type>
      <name>arguments_parse</name>
      <anchor>a0</anchor>
      <arglist>(char *source, char **array_of_pointers)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>parse.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Boot/Include/</path>
    <filename>parse_8h</filename>
    <member kind="function">
      <type>unsigned int</type>
      <name>arguments_parse</name>
      <anchor>a0</anchor>
      <arglist>(char *source, char **array_of_pointers)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pic.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Irq/</path>
    <filename>pic_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="pic_8h" name="pic.h" local="yes">Include/pic.h</includes>
    <member kind="function">
      <type>void</type>
      <name>pic_remap_irq</name>
      <anchor>a0</anchor>
      <arglist>(unsigned int start)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_enable_irq</name>
      <anchor>a1</anchor>
      <arglist>(unsigned int irq_number)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_disable_irq</name>
      <anchor>a2</anchor>
      <arglist>(unsigned int irq_number)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_enable_all_irq</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_disable_all_irq</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_init</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_acknowledge</name>
      <anchor>a6</anchor>
      <arglist>(unsigned int irq_number)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pic.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Irq/Include/</path>
    <filename>pic_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>PIC_MASTER</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIC_SLAVE</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_remap_irq</name>
      <anchor>a2</anchor>
      <arglist>(unsigned int start)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_enable_irq</name>
      <anchor>a3</anchor>
      <arglist>(unsigned int irq_channel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_disable_irq</name>
      <anchor>a4</anchor>
      <arglist>(unsigned int irq_channel)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_enable_all_irq</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_disable_all_irq</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_init</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pic_acknowledge</name>
      <anchor>a8</anchor>
      <arglist>(unsigned int irq_channel)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pit.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Timer/</path>
    <filename>pit_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="pit_8h" name="pit.h" local="yes">Include/pit.h</includes>
    <includes id="timer_8h" name="timer.h" local="yes">Include/timer.h</includes>
    <member kind="function">
      <type>void</type>
      <name>pit_init</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pit_mode_set</name>
      <anchor>a3</anchor>
      <arglist>(int channel, unsigned int digits UNUSED, unsigned int mode)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pit_frequency_set</name>
      <anchor>a4</anchor>
      <arglist>(int channel, unsigned int frequency)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pit_counter_read</name>
      <anchor>a5</anchor>
      <arglist>(int channel, uint16_t *counter)</arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>pit_mode</name>
      <anchor>a0</anchor>
      <arglist>[NUMBER_OF_PIT_CHANNELS]</arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>pit_divisor</name>
      <anchor>a1</anchor>
      <arglist>[NUMBER_OF_PIT_CHANNELS]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pit.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Timer/Include/</path>
    <filename>pit_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_PIT_CHANNELS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_0_DEFAULT_FREQUENCY</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_2_DEFAULT_FREQUENCY</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_BASE</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_COUNTER_REGISTER</name>
      <anchor>a4</anchor>
      <arglist>(channel)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_MODE_REGISTER</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COUNTER_LATCH_COMMAND</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ACCESS_LOW_COUNTER_UINT8</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ACCESS_HIGH_COUNTER_UINT8</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_MODE_0</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_MODE_1</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_MODE_2</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_MODE_3</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_MODE_4</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_MODE_5</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_COUNTER_MODE_BINARY</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_COUNTER_MODE_BCD</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_BASE_FREQUENCY</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FREQUENCY_TO_COUNTER_DIVISOR</name>
      <anchor>a18</anchor>
      <arglist>(hz)</arglist>
    </member>
    <member kind="enumeration">
      <name>pit_mode</name>
      <anchor>a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_MODE_ZERO_DETECTION_INTERRUPT</name>
      <anchor>a34a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_MODE_PROGRAMMABLE_ONE_SHORT</name>
      <anchor>a34a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_MODE_RATE_GENERATOR</name>
      <anchor>a34a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_MODE_SQUARE_WAVE_GENERATOR</name>
      <anchor>a34a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_MODE_SOFTWARE_TRIGGERED_STROBE</name>
      <anchor>a34a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_MODE_HARDWARE_TRIGGERED_STROBE</name>
      <anchor>a34a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>pit_channel</name>
      <anchor>a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_CHANNEL_0</name>
      <anchor>a35a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_CHANNEL_1</name>
      <anchor>a35a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_CHANNEL_2</name>
      <anchor>a35a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PIT_CHANNEL_MEMORY_REFRESH</name>
      <anchor>a35a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pit_init</name>
      <anchor>a29</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pit_mode_set</name>
      <anchor>a30</anchor>
      <arglist>(int channel, unsigned int digits, unsigned int mode)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pit_counter_read</name>
      <anchor>a31</anchor>
      <arglist>(int channel, uint16_t *counter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pit_frequency_set</name>
      <anchor>a32</anchor>
      <arglist>(int channel, unsigned int frequency)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pit_wait_for_count</name>
      <anchor>a33</anchor>
      <arglist>(int channel, uint16_t wait_count)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pm.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>pm_8c</filename>
    <member kind="function" static="yes">
      <type>void</type>
      <name>apic_pm_suspend</name>
      <anchor>a15</anchor>
      <arglist>(void *data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>apic_pm_resume</name>
      <anchor>a16</anchor>
      <arglist>(void *data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>apic_pm_callback</name>
      <anchor>a17</anchor>
      <arglist>(struct pm_dev *dev, pm_request_t rqst, void *data)</arglist>
    </member>
    <member kind="function">
      <type>pm_dev *</type>
      <name>apic_pm_register</name>
      <anchor>a18</anchor>
      <arglist>(pm_dev_t type, unsigned long id, pm_callback callback)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apic_pm_unregister</name>
      <anchor>a19</anchor>
      <arglist>(struct pm_dev *dev)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>apic_pm_init1</name>
      <anchor>a20</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>apic_pm_init2</name>
      <anchor>a21</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>@1</type>
      <name>apic_pm_state</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>active</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>pm_dev *</type>
      <name>perfctr_pmdev</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_id</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_taskpri</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_ldr</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_dfr</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_spiv</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_lvtt</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_lvtpc</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_lvt0</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_lvt1</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_lvterr</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_tmict</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>apic_tdcr</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>port.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/IoPort/</path>
    <filename>port_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="function">
      <type>return_t</type>
      <name>io_port_init</name>
      <anchor>a0</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>io_port_register</name>
      <anchor>a1</anchor>
      <arglist>(unsigned int start UNUSED, size_t ports UNUSED, const char *description UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>io_port_unregister</name>
      <anchor>a2</anchor>
      <arglist>(unsigned int start UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>reallocate.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/PhysicalMemory/</path>
    <filename>reallocate_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_reallocate</name>
      <anchor>a2</anchor>
      <arglist>(p_physical_memory_t memory UNUSED, page_number_t *start_page UNUSED, unsigned int pages UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>reference.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>reference_8h</filename>
    <includes id="Repository_2Reference_2Include_2internal_8h" name="Repository/Reference/Include/internal.h" local="yes">../Reference/Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_add_child_internal</name>
      <anchor>a2</anchor>
      <arglist>(p_object_t object, p_reference_struct_t reference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>object_remove_child_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_object_t object, p_reference_struct_t reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>repository.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/</path>
    <filename>repository_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="init_8h" name="init.h" local="yes">Include/init.h</includes>
    <includes id="kernel_8h" name="kernel.h" local="yes">Include/kernel.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>repository_init</name>
      <anchor>a5</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="variable">
      <type>class_reference_t</type>
      <name>kernel_class</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>object_reference_t</type>
      <name>kernel_object</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>handle_reference_t</type>
      <name>kernel_handle_init</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Class/Include/repository_external.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/Include/</path>
    <filename>Class_2Include_2repository__external_8h</filename>
    <member kind="variable">
      <type>pool_of_integers_t *</type>
      <name>class_ids_pool</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>hash_table_t *</type>
      <name>classes_table</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Exception/Include/repository_external.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/Include/</path>
    <filename>Descriptions_2Exception_2Include_2repository__external_8h</filename>
    <member kind="variable">
      <type>pool_of_integers_t *</type>
      <name>exception_ids_pool</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>hash_table_t *</type>
      <name>exceptions_table</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Handle/Include/repository_external.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/Include/</path>
    <filename>Handle_2Include_2repository__external_8h</filename>
    <member kind="variable">
      <type>pool_of_integers_t *</type>
      <name>handle_ids_pool</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>hash_table_t *</type>
      <name>handles_table</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/Include/repository_external.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/Include/</path>
    <filename>Method_2Include_2repository__external_8h</filename>
    <member kind="variable">
      <type>pool_of_integers_t *</type>
      <name>method_ids_pool</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>hash_table_t *</type>
      <name>methods_table</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Object/Include/repository_external.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/Include/</path>
    <filename>Object_2Include_2repository__external_8h</filename>
    <member kind="variable">
      <type>pool_of_integers_t *</type>
      <name>object_ids_pool</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>hash_table_t *</type>
      <name>objects_table</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/EventClass/Include/repository_external.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/Include/</path>
    <filename>tmp_2EventClass_2Include_2repository__external_8h</filename>
    <member kind="variable">
      <type>pool_of_integers_t *</type>
      <name>class_ids_pool</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>hash_table_t *</type>
      <name>classes_table</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>PhysicalMemory/reserve.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/PhysicalMemory/</path>
    <filename>PhysicalMemory_2reserve_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>physical_memory_reserve</name>
      <anchor>a2</anchor>
      <arglist>(p_physical_memory_t memory, page_number_t start_page, unsigned int pages)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>VirtualMemory/reserve.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/VirtualMemory/</path>
    <filename>VirtualMemory_2reserve_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="page_8h" name="page.h" local="yes">Include/page.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>virtual_memory_reserve</name>
      <anchor>a2</anchor>
      <arglist>(p_virtual_memory_t virtual_memory, page_number_t start_virtual_page, uint32_t pages, p_page_number_t start_physical_page, unsigned int options)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>return_value.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/Include/</path>
    <filename>return__value_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>RETURN_TYPE_VOID</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RETURN_TYPE_32</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RETURN_TYPE_64</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RETURN_TYPE_FLOAT</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RETURN_TYPE_ARRAY</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>scheduler.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Computer/</path>
    <filename>scheduler_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="scheduler_8h" name="scheduler.h" local="yes">Include/scheduler.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>p_computer_t</type>
      <name>scheduler_get_next_computer</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>volatile list_t</type>
      <name>computers</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>scheduler.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Computer/Include/</path>
    <filename>scheduler_8h</filename>
    <member kind="function">
      <type>p_computer_t</type>
      <name>scheduler_get_next_computer</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>security.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>security_8h</filename>
    <member kind="function">
      <type>p_security_t</type>
      <name>security_create_static_internal</name>
      <anchor>a0</anchor>
      <arglist>(p_security_t security)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_destroy_static_internal</name>
      <anchor>a1</anchor>
      <arglist>(p_security_t security)</arglist>
    </member>
    <member kind="function">
      <type>p_security_t</type>
      <name>security_create_internal</name>
      <anchor>a2</anchor>
      <arglist>(bool security_is_absolute, p_generic_acl_t generic_acl)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_destroy_internal</name>
      <anchor>a3</anchor>
      <arglist>(p_security_t security)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Class/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/</path>
    <filename>Class_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Exception/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/</path>
    <filename>Descriptions_2Exception_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventConsumerInterface/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/</path>
    <filename>EventConsumerInterface_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="EventConsumerInterface_2Include_2security__check_8h" name="EventConsumerInterface/Include/security_check.h" local="yes">Include/security_check.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventSupplierInterface/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/</path>
    <filename>EventSupplierInterface_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="EventSupplierInterface_2Include_2security__check_8h" name="EventSupplierInterface/Include/security_check.h" local="yes">Include/security_check.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Handle/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/</path>
    <filename>Handle_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Interface/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/</path>
    <filename>Interface_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Interface_2Include_2security__check_8h" name="Interface/Include/security_check.h" local="yes">Include/security_check.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/</path>
    <filename>Method_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Object/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/</path>
    <filename>Object_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Security/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Security/</path>
    <filename>Security_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/EventClass/security_check.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/</path>
    <filename>tmp_2EventClass_2security__check_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Class/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/Include/</path>
    <filename>Class_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_set_interfaces_check_security</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interfaces_check_security</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interface_check_security</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Exception/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/Include/</path>
    <filename>Descriptions_2Exception_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_set_interfaces_check_security</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interfaces_check_security</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interface_check_security</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventConsumerInterface/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/Include/</path>
    <filename>EventConsumerInterface_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>interface_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventSupplierInterface/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/Include/</path>
    <filename>EventSupplierInterface_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>interface_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Handle/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/Include/</path>
    <filename>Handle_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_set_interfaces_check_security</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interfaces_check_security</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interface_check_security</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Interface/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/Include/</path>
    <filename>Interface_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>interface_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/Include/</path>
    <filename>Method_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_set_interfaces_check_security</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interfaces_check_security</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interface_check_security</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Object/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/Include/</path>
    <filename>Object_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_set_interfaces_check_security</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interfaces_check_security</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interface_check_security</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Security/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Security/Include/</path>
    <filename>Security_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_set_interfaces_check_security</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interfaces_check_security</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interface_check_security</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/EventClass/Include/security_check.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/Include/</path>
    <filename>tmp_2EventClass_2Include_2security__check_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>class_create_check_security</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_check_security</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_set_interfaces_check_security</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interfaces_check_security</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_get_interface_check_security</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>slab.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Memory/</path>
    <filename>slab_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="slab_8h" name="slab.h" local="yes">slab.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>slab_heap_index</name>
      <anchor>a2</anchor>
      <arglist>(unsigned int buffer_size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>slab_heap_init</name>
      <anchor>a3</anchor>
      <arglist>(slab_heap_t *heap)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>slab_superblock_init</name>
      <anchor>a4</anchor>
      <arglist>(slab_superblock_t *superblock, slab_heap_t *heap, int index)</arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>slab_block_size</name>
      <anchor>a1</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>slab.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Memory/</path>
    <filename>slab_8h</filename>
    <class kind="struct">slab_heap_t</class>
    <class kind="struct">slab_superblock_header_t</class>
    <class kind="struct">slab_block_t</class>
    <class kind="struct">slab_superblock_t</class>
    <member kind="define">
      <type>#define</type>
      <name>SLAB_MAGIC_COOKIE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>slab_heap_init</name>
      <anchor>a2</anchor>
      <arglist>(slab_heap_t *heap)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>slab_superblock_init</name>
      <anchor>a3</anchor>
      <arglist>(slab_superblock_t *superblock, slab_heap_t *heap, int index)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>slab_heap_index</name>
      <anchor>a4</anchor>
      <arglist>(unsigned int buffer_size)</arglist>
    </member>
    <member kind="variable">
      <type>const int</type>
      <name>slab_block_size</name>
      <anchor>a1</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>smp.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>smp_8c</filename>
    <class kind="struct">call_data_struct</class>
    <member kind="define">
      <type>#define</type>
      <name>FLUSH_ALL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>__prepare_ICR</name>
      <anchor>a9</anchor>
      <arglist>(unsigned int shortcut, int vector)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>__prepare_ICR2</name>
      <anchor>a10</anchor>
      <arglist>(unsigned int mask)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>__send_IPI_shortcut</name>
      <anchor>a11</anchor>
      <arglist>(unsigned int shortcut, int vector)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>send_IPI_self</name>
      <anchor>a12</anchor>
      <arglist>(int vector)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>send_IPI_mask_bitmask</name>
      <anchor>a13</anchor>
      <arglist>(int mask, int vector)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>send_IPI_mask_sequence</name>
      <anchor>a14</anchor>
      <arglist>(int mask, int vector)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>send_IPI_mask</name>
      <anchor>a15</anchor>
      <arglist>(int mask, int vector)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>send_IPI_allbutself</name>
      <anchor>a16</anchor>
      <arglist>(int vector)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>send_IPI_all</name>
      <anchor>a17</anchor>
      <arglist>(int vector)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>leave_mm</name>
      <anchor>a18</anchor>
      <arglist>(unsigned long cpu)</arglist>
    </member>
    <member kind="function">
      <type>asmlinkage void</type>
      <name>smp_invalidate_interrupt</name>
      <anchor>a19</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>flush_tlb_others</name>
      <anchor>a20</anchor>
      <arglist>(unsigned long cpumask, struct mm_struct *mm, unsigned long va)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>flush_tlb_current_task</name>
      <anchor>a21</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>flush_tlb_mm</name>
      <anchor>a22</anchor>
      <arglist>(struct mm_struct *mm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>flush_tlb_page</name>
      <anchor>a23</anchor>
      <arglist>(struct vm_area_struct *vma, unsigned long va)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>do_flush_tlb_all_local</name>
      <anchor>a24</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>flush_tlb_all_ipi</name>
      <anchor>a25</anchor>
      <arglist>(void *info)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>flush_tlb_all</name>
      <anchor>a26</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>smp_send_reschedule</name>
      <anchor>a27</anchor>
      <arglist>(int cpu)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>smp_call_function</name>
      <anchor>a28</anchor>
      <arglist>(void(*func)(void *info), void *info, int nonatomic, int wait)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>stop_this_cpu</name>
      <anchor>a29</anchor>
      <arglist>(void *dummy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>smp_send_stop</name>
      <anchor>a30</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>asmlinkage void</type>
      <name>smp_reschedule_interrupt</name>
      <anchor>a31</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>asmlinkage void</type>
      <name>smp_call_function_interrupt</name>
      <anchor>a32</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>spinlock_t</type>
      <name>kernel_flag</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>tlb_state</type>
      <name>cpu_tlbstate</name>
      <anchor>a2</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>volatile unsigned long</type>
      <name>flush_cpumask</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>mm_struct *</type>
      <name>flush_mm</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>unsigned long</type>
      <name>flush_va</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>spinlock_t</type>
      <name>tlbstate_lock</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>spinlock_t</type>
      <name>call_lock</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>call_data_struct *</type>
      <name>call_data</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>smp.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>smp_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>INT_DELIVERY_MODE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TARGET_CPUS</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>clustered_apic_mode</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>esr_disable</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>smpboot.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>smpboot_8c</filename>
    <member kind="define">
      <type>#define</type>
      <name>NR_LOOPS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>int __init</type>
      <name>nosmp</name>
      <anchor>a34</anchor>
      <arglist>(char *str)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>__setup</name>
      <anchor>a35</anchor>
      <arglist>(&quot;nosmp&quot;, nosmp)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int __init</type>
      <name>maxcpus</name>
      <anchor>a36</anchor>
      <arglist>(char *str)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>__setup</name>
      <anchor>a37</anchor>
      <arglist>(&quot;maxcpus=&quot;, maxcpus)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>unsigned long __init</type>
      <name>setup_trampoline</name>
      <anchor>a38</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void __init</type>
      <name>smp_alloc_memory</name>
      <anchor>a39</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void __init</type>
      <name>smp_store_cpu_info</name>
      <anchor>a40</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="function">
      <type>void __init</type>
      <name>smp_commence</name>
      <anchor>a41</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>unsigned long long</type>
      <name>div64</name>
      <anchor>a42</anchor>
      <arglist>(unsigned long long a, unsigned long b0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void __init</type>
      <name>synchronize_tsc_bp</name>
      <anchor>a43</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void __init</type>
      <name>synchronize_tsc_ap</name>
      <anchor>a44</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calibrate_delay</name>
      <anchor>a45</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void __init</type>
      <name>smp_callin</name>
      <anchor>a46</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>cpu_idle</name>
      <anchor>a47</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int __init</type>
      <name>start_secondary</name>
      <anchor>a48</anchor>
      <arglist>(void *unused)</arglist>
    </member>
    <member kind="function">
      <type>void __init</type>
      <name>initialize_secondary</name>
      <anchor>a49</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int __init</type>
      <name>fork_by_hand</name>
      <anchor>a50</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>init_cpu_to_apicid</name>
      <anchor>a51</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>map_cpu_to_boot_apicid</name>
      <anchor>a52</anchor>
      <arglist>(int cpu, int apicid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>unmap_cpu_to_boot_apicid</name>
      <anchor>a53</anchor>
      <arglist>(int cpu, int apicid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>wakeup_secondary_via_NMI</name>
      <anchor>a54</anchor>
      <arglist>(int logical_apicid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int</type>
      <name>wakeup_secondary_via_INIT</name>
      <anchor>a55</anchor>
      <arglist>(int phys_apicid, unsigned long start_eip)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void __init</type>
      <name>do_boot_cpu</name>
      <anchor>a56</anchor>
      <arglist>(int apicid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>smp_tune_scheduling</name>
      <anchor>a57</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void __init</type>
      <name>smp_boot_cpus</name>
      <anchor>a58</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>int</type>
      <name>smp_b_stepping</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>int</type>
      <name>max_cpus</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>smp_num_cpus</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned long</type>
      <name>cpu_online_map</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>volatile unsigned long</type>
      <name>cpu_callin_map</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>volatile unsigned long</type>
      <name>cpu_callout_map</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cpuinfo_x86 cpu_data[NR_CPUS]</type>
      <name>__cacheline_aligned</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>smp_threads_ready</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char</type>
      <name>trampoline_data</name>
      <anchor>a9</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>unsigned char</type>
      <name>trampoline_end</name>
      <anchor>a10</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>unsigned char *</type>
      <name>trampoline_base</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>atomic_t</type>
      <name>smp_commenced</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>atomic_t</type>
      <name>tsc_start_flag</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>atomic_t</type>
      <name>tsc_count_start</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>atomic_t</type>
      <name>tsc_count_stop</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>unsigned long long</type>
      <name>tsc_values</name>
      <anchor>a16</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable">
      <type>unsigned long</type>
      <name>fast_gettimeoffset_quotient</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>atomic_t</type>
      <name>init_deasserted</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>cpucount</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>@2</type>
      <name>stack_start</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>esp</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>ss</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile int</type>
      <name>physical_apicid_2_cpu</name>
      <anchor>a23</anchor>
      <arglist>[MAX_APICID]</arglist>
    </member>
    <member kind="variable">
      <type>volatile int</type>
      <name>cpu_2_physical_apicid</name>
      <anchor>a24</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable">
      <type>volatile int</type>
      <name>logical_apicid_2_cpu</name>
      <anchor>a25</anchor>
      <arglist>[MAX_APICID]</arglist>
    </member>
    <member kind="variable">
      <type>volatile int</type>
      <name>cpu_2_logical_apicid</name>
      <anchor>a26</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable">
      <type>unsigned long</type>
      <name>cpu_initialized</name>
      <anchor>a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cycles_t</type>
      <name>cacheflush_time</name>
      <anchor>a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>prof_multiplier</name>
      <anchor>a29</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>prof_old_multiplier</name>
      <anchor>a30</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>prof_counter</name>
      <anchor>a31</anchor>
      <arglist>[NR_CPUS]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>int</type>
      <name>boot_cpu_logical_apicid</name>
      <anchor>a32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>xquad_portio</name>
      <anchor>a33</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>smpboot.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>smpboot_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>clustered_apic_mode</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRAMPOLINE_LOW</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRAMPOLINE_HIGH</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>boot_cpu_apicid</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>cpu_present_to_apicid</name>
      <anchor>a4</anchor>
      <arglist>(apicid)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>logical_apicid_to_cpu</name>
      <anchor>a5</anchor>
      <arglist>(apicid)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>cpu_to_logical_apicid</name>
      <anchor>a6</anchor>
      <arglist>(cpu)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>physical_apicid_to_cpu</name>
      <anchor>a7</anchor>
      <arglist>(apicid)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>cpu_to_physical_apicid</name>
      <anchor>a8</anchor>
      <arglist>(cpu)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>boot_apicid_to_cpu</name>
      <anchor>a9</anchor>
      <arglist>(apicid)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>cpu_to_boot_apicid</name>
      <anchor>a10</anchor>
      <arglist>(cpu)</arglist>
    </member>
    <member kind="variable">
      <type>volatile int</type>
      <name>logical_apicid_2_cpu</name>
      <anchor>a11</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>volatile int</type>
      <name>cpu_2_logical_apicid</name>
      <anchor>a12</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>volatile int</type>
      <name>physical_apicid_2_cpu</name>
      <anchor>a13</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>volatile int</type>
      <name>cpu_2_physical_apicid</name>
      <anchor>a14</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>smplock.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/APIC/</path>
    <filename>smplock_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>kernel_locked</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>release_kernel_lock</name>
      <anchor>a1</anchor>
      <arglist>(task, cpu)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>reacquire_kernel_lock</name>
      <anchor>a2</anchor>
      <arglist>(task)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>__inline__ void</type>
      <name>lock_kernel</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>__inline__ void</type>
      <name>unlock_kernel</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>spinlock_t</type>
      <name>kernel_flag</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>speed.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/</path>
    <filename>speed_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="speed_8h" name="speed.h" local="yes">Include/speed.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PIT_BASE_FREQUENCY</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LATCH</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CALIBRATE_LATCH</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CALIBRATE_TIME</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint32_t</type>
      <name>calibrate_tsc</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>cpu_speed_get</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>unsigned int</type>
      <name>hz</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>speed.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Cpu/Include/</path>
    <filename>speed_8h</filename>
    <member kind="function">
      <type>uint64_t</type>
      <name>cpu_speed_get</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Class/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/</path>
    <filename>Class_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>class_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_class_t class)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(class_reference_t class_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Exception/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/</path>
    <filename>Descriptions_2Exception_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Descriptions_2Exception_2Include_2internal_8h" name="Repository/Descriptions/Exception/Include/internal.h" local="yes">Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>exception_reference_t</type>
      <name>exception_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_exception_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(exception_reference_t exception_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventConsumerInterface/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/</path>
    <filename>EventConsumerInterface_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>event_consumer_interface_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_event_consumer_interface_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_interface_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(event_consumer_interface_reference_t interface_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventSupplierInterface/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/</path>
    <filename>EventSupplierInterface_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>event_supplier_interface_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_event_supplier_interface_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_interface_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(event_supplier_interface_reference_t interface_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Handle/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/</path>
    <filename>Handle_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>handle_reference_t</type>
      <name>handle_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_handle_t handle, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(handle_reference_t handle_reference)</arglist>
    </member>
    <member kind="function">
      <type>handle_reference_t</type>
      <name>handle_clone_static</name>
      <anchor>a4</anchor>
      <arglist>(handle_reference_t handle_reference, p_handle_t new_handle, uint32_t options)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Interface/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/</path>
    <filename>Interface_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>interface_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_interface_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(interface_reference_t interface_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/</path>
    <filename>Method_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>method_reference_t</type>
      <name>method_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_method_t method)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(method_reference_t method_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Object/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/</path>
    <filename>Object_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>object_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_object_t object, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Security/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Security/</path>
    <filename>Security_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>security_reference_t</type>
      <name>security_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_security_t security)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(security_reference_t security_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/EventClass/static.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/</path>
    <filename>tmp_2EventClass_2static_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_class_reference_t</type>
      <name>event_class_create_static</name>
      <anchor>a2</anchor>
      <arglist>(p_event_class_t event_class)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_class_destroy_static</name>
      <anchor>a3</anchor>
      <arglist>(event_class_reference_t event_class_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>static_modules.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/</path>
    <filename>static__modules_8h</filename>
    <class kind="struct">static_module_info_t</class>
    <member kind="define">
      <type>#define</type>
      <name>STATIC_MODULE_KEYBOARD</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STATIC_MODULE_MOUSE</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STATIC_MODULE_VGA</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STATIC_MODULE_CONSOLE</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>return_t(</type>
      <name>module_main_t</name>
      <anchor>a4</anchor>
      <arglist>)(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="typedef">
      <type>module_main_t *</type>
      <name>p_module_main_t</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>pci_main</name>
      <anchor>a7</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>pcnet32_main</name>
      <anchor>a8</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>ata_main</name>
      <anchor>a9</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>partition_main</name>
      <anchor>a10</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>vfat_main</name>
      <anchor>a11</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>keyboard_main</name>
      <anchor>a12</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>mouse_main</name>
      <anchor>a13</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>vga_main</name>
      <anchor>a14</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>console_main</name>
      <anchor>a15</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="variable">
      <type>static_module_info_t</type>
      <name>static_modules</name>
      <anchor>a6</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_module.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__module_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="classes_8h" name="classes.h" local="yes">../classes.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="storm__module_8h" name="storm_module.h" local="no">Classes/storm_module.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>storm_module_class_init</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>class_description</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_module.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__module_8h</filename>
    <class kind="struct">module_info_t</class>
    <class kind="struct">storm_module_data_t</class>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME_LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_VERSION_LENGTH</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>return_t(</type>
      <name>module_start_t</name>
      <anchor>a3</anchor>
      <arglist>)(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="typedef">
      <type>module_start_t *</type>
      <name>p_module_start_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>return_t(</type>
      <name>module_stop_t</name>
      <anchor>a5</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>module_stop_t *</type>
      <name>p_module_stop_t</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>storm_module_data_t *</type>
      <name>p_storm_module_data_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_module_control_init</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>function_info_t</type>
      <name>functions_table</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_module_control_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__module__control__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="storm__module_8h" name="storm_module.h" local="yes">storm_module.h</includes>
    <includes id="storm__module__control__interface_8h" name="storm_module_control_interface.h" local="yes">storm_module_control_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>return_t</type>
      <name>start</name>
      <anchor>a3</anchor>
      <arglist>(context_t context, uint32_t argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>return_t</type>
      <name>stop</name>
      <anchor>a4</anchor>
      <arglist>(context_t context)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_module_control_init</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>storm_module_control_interface_table_t</type>
      <name>table</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_module_control_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__module__control__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="storm__module__control__interface_8h" name="storm_module_control_interface.h" local="yes">storm_module_control_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>start_wrapper</name>
      <anchor>a7</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>stop_wrapper</name>
      <anchor>a8</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_module_control_interface_register</name>
      <anchor>a9</anchor>
      <arglist>(p_storm_module_control_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_start</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_stop</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a4</anchor>
      <arglist>[METHOD_STORM_MODULE_CONTROL_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_module_control_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__module__control__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_module_control_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_storm_module_control_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_module_factory.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>storm__module__factory_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="storm__module_8h" name="storm_module.h" local="yes">../Classes/storm_module.h</includes>
    <includes id="storm__module__factory__interface_8h" name="storm_module_factory_interface.h" local="yes">storm_module_factory_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>dummy</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint64_t</type>
      <name>storm_module_create</name>
      <anchor>a5</anchor>
      <arglist>(context_t context UNUSED, elf_header_t *elf_header)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>storm_module_destroy</name>
      <anchor>a6</anchor>
      <arglist>(context_t context UNUSED, uint64_t data)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_module_factory_interface_init</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>function_info_t</type>
      <name>functions_table</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>storm_module_factory_interface_table_t</type>
      <name>table</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_module_factory_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>storm__module__factory__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="storm__module__factory__interface_8h" name="storm_module_factory_interface.h" local="yes">storm_module_factory_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>create_wrapper</name>
      <anchor>a7</anchor>
      <arglist>(uint64_t function, context_t context, class_reference_t class UNUSED, object_reference_t object, sequence_t parameters_in)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>destroy_wrapper</name>
      <anchor>a8</anchor>
      <arglist>(uint64_t function, context_t context, class_reference_t class UNUSED, object_reference_t object)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_module_factory_interface_register</name>
      <anchor>a9</anchor>
      <arglist>(p_storm_module_factory_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_create</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_destroy</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a4</anchor>
      <arglist>[METHOD_OBJECT_FACTORY_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_module_factory_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>storm__module__factory__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_module_factory_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_storm_module_factory_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_program.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__program_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="classes_8h" name="classes.h" local="yes">../classes.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="storm__program_8h" name="storm_program.h" local="no">Classes/storm_program.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>storm_program_class_init</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>class_description</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_program.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__program_8h</filename>
    <class kind="struct">storm_program_data_t</class>
    <member kind="typedef">
      <type>return_t(</type>
      <name>main_function_t</name>
      <anchor>a0</anchor>
      <arglist>)(uint32_t argc, char **argv, char **envp)</arglist>
    </member>
    <member kind="typedef">
      <type>main_function_t *</type>
      <name>p_main_function_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>storm_program_data_t *</type>
      <name>p_storm_program_data_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_program_control_init</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_program_control_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__program__control__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="storm__program_8h" name="storm_program.h" local="yes">storm_program.h</includes>
    <includes id="storm__program__control__interface_8h" name="storm_program_control_interface.h" local="yes">storm_program_control_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_PROGRAM_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>return_t</type>
      <name>storm_main</name>
      <anchor>a3</anchor>
      <arglist>(context_t context, uint32_t argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_program_control_init</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>storm_program_control_interface_table_t</type>
      <name>table</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_program_control_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__program__control__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="storm__program__control__interface_8h" name="storm_program_control_interface.h" local="yes">storm_program_control_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>main_wrapper</name>
      <anchor>a6</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in, sequence_t parameters_inout UNUSED, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_program_control_interface_register</name>
      <anchor>a7</anchor>
      <arglist>(p_storm_program_control_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_main</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a3</anchor>
      <arglist>[METHOD_STORM_PROGRAM_CONTROL_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_program_control_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Classes/</path>
    <filename>storm__program__control__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_program_control_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_storm_program_control_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_program_factory.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>storm__program__factory_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="storm__program_8h" name="storm_program.h" local="yes">../Classes/storm_program.h</includes>
    <includes id="storm__program__factory__interface_8h" name="storm_program_factory_interface.h" local="yes">storm_program_factory_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint64_t</type>
      <name>storm_program_create</name>
      <anchor>a3</anchor>
      <arglist>(context_t context UNUSED, elf_header_t *elf_header)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>storm_program_destroy</name>
      <anchor>a4</anchor>
      <arglist>(context_t context UNUSED, uint64_t data)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_program_factory_interface_init</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>storm_program_factory_interface_table_t</type>
      <name>table</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_program_factory_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>storm__program__factory__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="storm__program__factory__interface_8h" name="storm_program_factory_interface.h" local="yes">storm_program_factory_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>create_wrapper</name>
      <anchor>a7</anchor>
      <arglist>(uint64_t function, context_t context, class_reference_t class UNUSED, object_reference_t object, sequence_t parameters_in)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>destroy_wrapper</name>
      <anchor>a8</anchor>
      <arglist>(uint64_t function, context_t context, class_reference_t class UNUSED, object_reference_t object)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_program_factory_interface_register</name>
      <anchor>a9</anchor>
      <arglist>(p_storm_program_factory_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_create</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_destroy</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a4</anchor>
      <arglist>[METHOD_OBJECT_FACTORY_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storm_program_factory_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>storm__program__factory__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>storm_program_factory_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_storm_program_factory_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>subsystems.h</name>
    <path>/root/Chaos/Sources/StormG4/</path>
    <filename>subsystems_8h</filename>
    <class kind="struct">subsystem_built_in_t</class>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_BUILT_IN</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>return_t(</type>
      <name>main_function_t</name>
      <anchor>a1</anchor>
      <arglist>)(int argc, char *argv[], char **envp)</arglist>
    </member>
    <member kind="typedef">
      <type>main_function_t *</type>
      <name>p_main_function_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>subsystem_built_in_t</type>
      <name>subsystem_built_in</name>
      <anchor>a3</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Class/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/</path>
    <filename>Class_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>class_create</name>
      <anchor>a2</anchor>
      <arglist>(description_reference_t class_description, sequence_t class_interfaces, sequence_t class_event_suppliers, sequence_t class_event_consumers, handle_reference_t class_object_factory, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy</name>
      <anchor>a3</anchor>
      <arglist>(class_reference_t class_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_set_interfaces</name>
      <anchor>a4</anchor>
      <arglist>(class_reference_t class_reference, sequence_t class_interfaces)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>class_get_interface_by_id</name>
      <anchor>a5</anchor>
      <arglist>(class_reference_t class_reference, interface_id_t interface_id)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Computer/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Computer/</path>
    <filename>Computer_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>computer_reference_t</type>
      <name>computer_create</name>
      <anchor>a5</anchor>
      <arglist>(cpu_reference_t cpu, memory_reference_t memory, security_reference_t security)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_destroy</name>
      <anchor>a6</anchor>
      <arglist>(computer_reference_t computer_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_reset</name>
      <anchor>a7</anchor>
      <arglist>(computer_reference_t computer_reference)</arglist>
    </member>
    <member kind="function">
      <type>computer_reference_t</type>
      <name>computer_get_current</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_add_exception_context</name>
      <anchor>a9</anchor>
      <arglist>(computer_reference_t computer_reference, p_exception_context_t context)</arglist>
    </member>
    <member kind="function">
      <type>p_exception_context_t</type>
      <name>computer_remove_exception_context</name>
      <anchor>a10</anchor>
      <arglist>(computer_reference_t computer_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jump_lowlevel</name>
      <anchor>a11</anchor>
      <arglist>(void *, void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_fire_exception</name>
      <anchor>a12</anchor>
      <arglist>(computer_reference_t computer_reference UNUSED, p_exception_info_t exception_info)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_computer_init</name>
      <anchor>a13</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>bool</type>
      <name>lock</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>computer_t</type>
      <name>computer_kernel</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile p_computer_t</type>
      <name>computer_current</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Cpu/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Cpu/</path>
    <filename>Cpu_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>cpu_reference_t</type>
      <name>cpu_create</name>
      <anchor>a3</anchor>
      <arglist>(uint32_t performance)</arglist>
    </member>
    <member kind="variable">
      <type>cpu_t</type>
      <name>cpu_kernel</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Class/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Class/</path>
    <filename>Descriptions_2Class_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Descriptions_2Include_2internal_8h" name="Repository/Descriptions/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>class_description_register</name>
      <anchor>a2</anchor>
      <arglist>(id_t id, const wchar_t *name, uint32_t type, uint32_t number_of_interfaces, uint32_t number_of_event_suppliers, uint32_t number_of_event_consumers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_description_unregister</name>
      <anchor>a3</anchor>
      <arglist>(description_reference_t description_reference UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Event/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Event/</path>
    <filename>Descriptions_2Event_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Descriptions_2Include_2internal_8h" name="Repository/Descriptions/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>event_description_register</name>
      <anchor>a2</anchor>
      <arglist>(id_t id, const wchar_t *name, uint32_t data_length)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_description_unregister</name>
      <anchor>a3</anchor>
      <arglist>(description_reference_t description_reference UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Exception/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/</path>
    <filename>Descriptions_2Exception_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Descriptions_2Exception_2Include_2internal_8h" name="Repository/Descriptions/Exception/Include/internal.h" local="yes">Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>exception_reference_t</type>
      <name>exception_create</name>
      <anchor>a2</anchor>
      <arglist>(p_exception_description_t exception_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy</name>
      <anchor>a3</anchor>
      <arglist>(exception_reference_t exception_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Interface/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Interface/</path>
    <filename>Descriptions_2Interface_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Descriptions_2Include_2internal_8h" name="Repository/Descriptions/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>interface_description_register</name>
      <anchor>a2</anchor>
      <arglist>(id_t id, const wchar_t *name, uint32_t type, sequence_t method_descriptions UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_description_unregister</name>
      <anchor>a3</anchor>
      <arglist>(description_reference_t description_reference UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Method/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Method/</path>
    <filename>Descriptions_2Method_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Descriptions_2Include_2internal_8h" name="Repository/Descriptions/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>method_description_register</name>
      <anchor>a2</anchor>
      <arglist>(id_t id, const wchar_t *name, uint32_t type, p_void_t return_type UNUSED, sequence_t parameter_descriptions UNUSED, sequence_t exception_descriptions UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_description_unregister</name>
      <anchor>a3</anchor>
      <arglist>(description_reference_t description_reference UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventConsumerInterface/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/</path>
    <filename>EventConsumerInterface_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>event_consumer_interface_create</name>
      <anchor>a2</anchor>
      <arglist>(description_reference_t event_description, int type, method_reference_t handler, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_interface_destroy</name>
      <anchor>a3</anchor>
      <arglist>(event_consumer_interface_reference_t event_consumer_interface_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_interface_set_factory</name>
      <anchor>a4</anchor>
      <arglist>(event_consumer_interface_reference_t event_consumer_interface_reference, reference_t factory)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventQueue/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventQueue/</path>
    <filename>EventQueue_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_queue_reference_t</type>
      <name>event_queue_create</name>
      <anchor>a2</anchor>
      <arglist>(description_reference_t event_description, uint32_t type, uint32_t capacity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_queue_destroy</name>
      <anchor>a3</anchor>
      <arglist>(event_queue_reference_t event_queue_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventSupplier/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplier/</path>
    <filename>EventSupplier_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_supplier_reference_t</type>
      <name>event_supplier_create</name>
      <anchor>a1</anchor>
      <arglist>(object_reference_t object_reference, event_id_t event_class_id, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_destroy</name>
      <anchor>a2</anchor>
      <arglist>(event_supplier_reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_fire_event</name>
      <anchor>a3</anchor>
      <arglist>(event_supplier_reference_t reference, sequence_t event_data, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_set_data</name>
      <anchor>a4</anchor>
      <arglist>(event_supplier_reference_t reference, uint64_t data)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>event_supplier_get_data</name>
      <anchor>a5</anchor>
      <arglist>(event_supplier_reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_set_queue</name>
      <anchor>a6</anchor>
      <arglist>(event_supplier_reference_t reference, event_queue_reference_t event_queue)</arglist>
    </member>
    <member kind="function">
      <type>event_consumer_reference_t</type>
      <name>event_consumer_create</name>
      <anchor>a7</anchor>
      <arglist>(object_reference_t object_reference, event_id_t event_class_id, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_destroy</name>
      <anchor>a8</anchor>
      <arglist>(event_consumer_reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_wait_event</name>
      <anchor>a9</anchor>
      <arglist>(event_consumer_reference_t reference, sequence_t event_data, uint32_t options UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_set_queue</name>
      <anchor>a10</anchor>
      <arglist>(event_consumer_reference_t reference, event_queue_reference_t event_queue UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_event_supplier_init</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_event_consumer_init</name>
      <anchor>a12</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventSupplierInterface/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/</path>
    <filename>EventSupplierInterface_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>event_supplier_interface_create</name>
      <anchor>a2</anchor>
      <arglist>(description_reference_t event_description, int type, method_reference_t handler, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_interface_destroy</name>
      <anchor>a3</anchor>
      <arglist>(event_supplier_interface_reference_t event_supplier_interface_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_interface_set_factory</name>
      <anchor>a4</anchor>
      <arglist>(event_supplier_interface_reference_t event_supplier_interface_reference, reference_t factory)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Handle/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Handle/</path>
    <filename>Handle_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>handle_reference_t</type>
      <name>handle_create</name>
      <anchor>a2</anchor>
      <arglist>(object_reference_t object_reference, interface_id_t interface_id, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_destroy</name>
      <anchor>a3</anchor>
      <arglist>(handle_reference_t handle_reference)</arglist>
    </member>
    <member kind="function">
      <type>handle_reference_t</type>
      <name>handle_clone</name>
      <anchor>a4</anchor>
      <arglist>(handle_reference_t handle_reference, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_invoke_method</name>
      <anchor>a5</anchor>
      <arglist>(handle_reference_t handle_reference, method_id_t method_id, computer_reference_t computer, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out, uint32_t options UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Interface/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/</path>
    <filename>Interface_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>interface_create</name>
      <anchor>a2</anchor>
      <arglist>(description_reference_t interface_description, sequence_t interface_methods, reference_t interface_factory, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy</name>
      <anchor>a3</anchor>
      <arglist>(interface_reference_t interface_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Memory/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Memory/</path>
    <filename>Memory_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>repository_memory_init</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>memory_t</type>
      <name>memory_global</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/</path>
    <filename>Method_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>method_reference_t</type>
      <name>method_create</name>
      <anchor>a2</anchor>
      <arglist>(description_reference_t method_description, computer_reference_t method_computer, memory_reference_t method_memory, p_method_function_t method_function, uint64_t method_data, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_destroy</name>
      <anchor>a3</anchor>
      <arglist>(method_reference_t method_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Object/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/</path>
    <filename>Object_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>object_create</name>
      <anchor>a2</anchor>
      <arglist>(class_reference_t class_reference, security_reference_t security_reference, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_destroy</name>
      <anchor>a3</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>object_get_current</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>object_get_kernel</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>object_get_data</name>
      <anchor>a6</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_set_data</name>
      <anchor>a7</anchor>
      <arglist>(object_reference_t object_reference, uint64_t object_data)</arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>object_get_class</name>
      <anchor>a8</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>object_get_interface_by_id</name>
      <anchor>a9</anchor>
      <arglist>(object_reference_t object_reference, interface_id_t interface_id)</arglist>
    </member>
    <member kind="function">
      <type>security_reference_t</type>
      <name>object_get_security</name>
      <anchor>a10</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_set_security</name>
      <anchor>a11</anchor>
      <arglist>(object_reference_t object_reference, security_reference_t security_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Quality/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Quality/</path>
    <filename>Quality_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>quality_set</name>
      <anchor>a2</anchor>
      <arglist>(quality_reference_t quality_reference UNUSED, uint32_t delay UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>quality_reset</name>
      <anchor>a3</anchor>
      <arglist>(quality_reference_t quality_reference UNUSED)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Reference/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Reference/</path>
    <filename>Reference_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>reference_t</type>
      <name>reference_acquire</name>
      <anchor>a3</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reference_release</name>
      <anchor>a4</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>reference_get_type</name>
      <anchor>a5</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>reference_get_owner</name>
      <anchor>a6</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>reference_get_number_of_references</name>
      <anchor>a7</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>reference_is_nill</name>
      <anchor>a8</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>reference_is_exists</name>
      <anchor>a9</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>reference_equals</name>
      <anchor>a10</anchor>
      <arglist>(reference_t reference, reference_t reference2)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>magic_number_table</name>
      <anchor>a2</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Security/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Security/</path>
    <filename>Security_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Repository_2Include_2internal_8h" name="Repository/Include/internal.h" local="yes">../Include/internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>security_reference_t</type>
      <name>security_create</name>
      <anchor>a2</anchor>
      <arglist>(bool security_is_absolute, p_generic_acl_t generic_acl)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_destroy</name>
      <anchor>a3</anchor>
      <arglist>(security_reference_t security_reference)</arglist>
    </member>
    <member kind="function">
      <type>security_reference_t</type>
      <name>security_get_current</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/CpuArray/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/CpuArray/</path>
    <filename>tmp_2CpuArray_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_array_schedule</name>
      <anchor>a2</anchor>
      <arglist>(p_cpu_array_t cpu_array)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/EventClass/system.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/</path>
    <filename>tmp_2EventClass_2system_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_class_reference_t</type>
      <name>event_class_create</name>
      <anchor>a2</anchor>
      <arglist>(p_event_class_description_t event_class_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_class_destroy</name>
      <anchor>a3</anchor>
      <arglist>(event_class_reference_t event_class_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>system_call.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/SystemCall/</path>
    <filename>system__call_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="system__call_8h" name="system_call.h" local="yes">Include/system_call.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>system_call_init</name>
      <anchor>a2</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>system_call</name>
      <anchor>a3</anchor>
      <arglist>(uint32_t *stack)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>system_call.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/SystemCall/Include/</path>
    <filename>system__call_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_CALL_NUMBER</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_CALL_ARGUMENTS</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_CALL_ARGUMENT_0</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_CALL_ARGUMENT_1</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_CALL_ARGUMENT_2</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_CALL_ARGUMENT_3</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SYSTEM_CALL_ARGUMENT_4</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>system_call_lowlevel</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>system_call</name>
      <anchor>a8</anchor>
      <arglist>(uint32_t *stack)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>task_state.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/TaskState/</path>
    <filename>task__state_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="tss_8h" name="tss.h" local="yes">Include/tss.h</includes>
    <includes id="task__state_8h" name="task_state.h" local="yes">Include/task_state.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_create</name>
      <anchor>a2</anchor>
      <arglist>(p_task_state_t task_state, p_void_t virtual_memory UNUSED, p_function_t instruction_pointer, p_uint8_t stack_pointer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_destroy</name>
      <anchor>a3</anchor>
      <arglist>(p_task_state_t task_state UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_switch_prepare</name>
      <anchor>a4</anchor>
      <arglist>(p_task_state_t task_state)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_state_switch_finish_internal</name>
      <anchor>a5</anchor>
      <arglist>(irq_cpu_registers_t reg UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>task_state_init</name>
      <anchor>a6</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="variable">
      <type>task_state_t</type>
      <name>task_state_kernel</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>task_state.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/TaskState/Include/</path>
    <filename>task__state_8h</filename>
  </compound>
  <compound kind="file">
    <name>task_state_lowlevel.S</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/TaskState/</path>
    <filename>task__state__lowlevel_8S</filename>
  </compound>
  <compound kind="file">
    <name>time.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Clock/</path>
    <filename>time_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="mc146818_8h" name="mc146818.h" local="yes">Include/mc146818.h</includes>
    <includes id="time_8h" name="time.h" local="yes">Include/time.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CMOS_BASE</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint64_t</type>
      <name>time_t</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>rtc_read</name>
      <anchor>a5</anchor>
      <arglist>(rtc_time_t *rtc_time)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>time_t</type>
      <name>gregorian_to_chaos</name>
      <anchor>a6</anchor>
      <arglist>(unsigned int year, unsigned int month, unsigned int day, unsigned int hours, unsigned int minutes, unsigned int seconds)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>clock_init</name>
      <anchor>a7</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>time_t</type>
      <name>system_time</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>time.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Clock/Include/</path>
    <filename>time_8h</filename>
    <member kind="enumeration">
      <name>month_t</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_January</name>
      <anchor>a19a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_February</name>
      <anchor>a19a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_March</name>
      <anchor>a19a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_April</name>
      <anchor>a19a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_May</name>
      <anchor>a19a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_June</name>
      <anchor>a19a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_July</name>
      <anchor>a19a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_August</name>
      <anchor>a19a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_September</name>
      <anchor>a19a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_October</name>
      <anchor>a19a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_November</name>
      <anchor>a19a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MONTH_December</name>
      <anchor>a19a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>day_of_week_t</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DAY_OF_WEEK_Monday</name>
      <anchor>a20a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DAY_OF_WEEK_Tuesday</name>
      <anchor>a20a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DAY_OF_WEEK_Wendsday</name>
      <anchor>a20a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DAY_OF_WEEK_Thursaday</name>
      <anchor>a20a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DAY_OF_WEEK_Friday</name>
      <anchor>a20a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DAY_OF_WEEK_Saturday</name>
      <anchor>a20a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DAY_OF_WEEK_Sunday</name>
      <anchor>a20a18</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>timer.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Timer/</path>
    <filename>timer_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="pit_8h" name="pit.h" local="yes">Include/pit.h</includes>
    <includes id="timer_8h" name="timer.h" local="yes">Include/timer.h</includes>
    <class kind="struct">timer_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>timer_handler</name>
      <anchor>a2</anchor>
      <arglist>(unsigned int irq_number UNUSED, p_void_t parameter UNUSED, irq_cpu_registers_t irq_cpu_registers UNUSED)</arglist>
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
    <member kind="function">
      <type>return_t</type>
      <name>timer_init</name>
      <anchor>a11</anchor>
      <arglist>(int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>timer_t</type>
      <name>timers</name>
      <anchor>a1</anchor>
      <arglist>[NUMBER_OF_TIMERS]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>timer.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/Timer/Include/</path>
    <filename>timer_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>NUMBER_OF_TIMERS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TIMER_IRQ</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>timer_state_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TIMER_STATE_COUNTED</name>
      <anchor>a4a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TIMER_STATE_STOPED</name>
      <anchor>a4a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>timer_interface.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>timer__interface_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="timer__interface_8h" name="timer_interface.h" local="yes">timer_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>read_milli_wrapper</name>
      <anchor>a6</anchor>
      <arglist>(uint64_t function, context_t context, sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, sequence_t parameters_out)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>timer_interface_register</name>
      <anchor>a7</anchor>
      <arglist>(p_timer_interface_table_t table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>method_description_read_milli</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>method_reference_t</type>
      <name>methods</name>
      <anchor>a3</anchor>
      <arglist>[METHOD_TIMER_NUMBER]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>sequence_t</type>
      <name>method_seq</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>description_reference_t</type>
      <name>interface_description</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>timer_interface.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>timer__interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>timer_interface_register</name>
      <anchor>a0</anchor>
      <arglist>(p_timer_interface_table_t table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>timer_interface_init.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Kernel/Interfaces/</path>
    <filename>timer__interface__init_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="interfaces_8h" name="interfaces.h" local="yes">../interfaces.h</includes>
    <includes id="classes_8h" name="classes.h" local="yes">../classes.h</includes>
    <includes id="timer__interface_8h" name="timer_interface.h" local="yes">timer_interface.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>uint32_t</type>
      <name>read_milli</name>
      <anchor>a3</anchor>
      <arglist>(context_t context UNUSED)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>timer_interface_init</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>timer_interface_table_t</type>
      <name>table</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Class/transaction.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/</path>
    <filename>Class_2transaction_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Class_2Include_2transaction_8h" name="Class/Include/transaction.h" local="yes">Include/transaction.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Exception/transaction.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/</path>
    <filename>Descriptions_2Exception_2transaction_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Descriptions_2Exception_2Include_2transaction_8h" name="Descriptions/Exception/Include/transaction.h" local="yes">Include/transaction.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventConsumerInterface/transaction.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/</path>
    <filename>EventConsumerInterface_2transaction_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="EventConsumerInterface_2Include_2transaction_8h" name="EventConsumerInterface/Include/transaction.h" local="yes">Include/transaction.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventSupplierInterface/transaction.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/</path>
    <filename>EventSupplierInterface_2transaction_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="EventSupplierInterface_2Include_2transaction_8h" name="EventSupplierInterface/Include/transaction.h" local="yes">Include/transaction.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Interface/transaction.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/</path>
    <filename>Interface_2transaction_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Interface_2Include_2transaction_8h" name="Interface/Include/transaction.h" local="yes">Include/transaction.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/transaction.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/</path>
    <filename>Method_2transaction_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="Method_2Include_2transaction_8h" name="Method/Include/transaction.h" local="yes">Include/transaction.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Object/transaction.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Object/</path>
    <filename>Object_2transaction_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/EventClass/transaction.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/</path>
    <filename>tmp_2EventClass_2transaction_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="tmp_2EventClass_2Include_2transaction_8h" name="tmp/EventClass/Include/transaction.h" local="yes">Include/transaction.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Class/Include/transaction.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Class/Include/</path>
    <filename>Class_2Include_2transaction_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>exception_create_static_commit</name>
      <anchor>a0</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_commit</name>
      <anchor>a1</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_static_rollback</name>
      <anchor>a2</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_rollback</name>
      <anchor>a3</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_commit</name>
      <anchor>a4</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_commit</name>
      <anchor>a5</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_rollback</name>
      <anchor>a6</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_rollback</name>
      <anchor>a7</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/Exception/Include/transaction.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Descriptions/Exception/Include/</path>
    <filename>Descriptions_2Exception_2Include_2transaction_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>exception_create_static_commit</name>
      <anchor>a0</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_commit</name>
      <anchor>a1</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_static_rollback</name>
      <anchor>a2</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_rollback</name>
      <anchor>a3</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_commit</name>
      <anchor>a4</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_commit</name>
      <anchor>a5</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_rollback</name>
      <anchor>a6</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_rollback</name>
      <anchor>a7</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventConsumerInterface/Include/transaction.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventConsumerInterface/Include/</path>
    <filename>EventConsumerInterface_2Include_2transaction_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>interface_create_static_commit</name>
      <anchor>a0</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_static_commit</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_create_static_rollback</name>
      <anchor>a2</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_static_rollback</name>
      <anchor>a3</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_create_commit</name>
      <anchor>a4</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_commit</name>
      <anchor>a5</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_create_rollback</name>
      <anchor>a6</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_rollback</name>
      <anchor>a7</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EventSupplierInterface/Include/transaction.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/EventSupplierInterface/Include/</path>
    <filename>EventSupplierInterface_2Include_2transaction_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>interface_create_static_commit</name>
      <anchor>a0</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_static_commit</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_create_static_rollback</name>
      <anchor>a2</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_static_rollback</name>
      <anchor>a3</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_create_commit</name>
      <anchor>a4</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_commit</name>
      <anchor>a5</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_create_rollback</name>
      <anchor>a6</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_rollback</name>
      <anchor>a7</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Interface/Include/transaction.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Interface/Include/</path>
    <filename>Interface_2Include_2transaction_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>interface_create_static_commit</name>
      <anchor>a0</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_static_commit</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_create_static_rollback</name>
      <anchor>a2</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_static_rollback</name>
      <anchor>a3</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_create_commit</name>
      <anchor>a4</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_commit</name>
      <anchor>a5</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_create_rollback</name>
      <anchor>a6</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy_rollback</name>
      <anchor>a7</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Method/Include/transaction.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Method/Include/</path>
    <filename>Method_2Include_2transaction_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>exception_create_static_commit</name>
      <anchor>a0</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_commit</name>
      <anchor>a1</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_static_rollback</name>
      <anchor>a2</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_rollback</name>
      <anchor>a3</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_commit</name>
      <anchor>a4</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_commit</name>
      <anchor>a5</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_rollback</name>
      <anchor>a6</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_rollback</name>
      <anchor>a7</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tmp/EventClass/Include/transaction.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/EventClass/Include/</path>
    <filename>tmp_2EventClass_2Include_2transaction_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>exception_create_static_commit</name>
      <anchor>a0</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_commit</name>
      <anchor>a1</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_static_rollback</name>
      <anchor>a2</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_static_rollback</name>
      <anchor>a3</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_commit</name>
      <anchor>a4</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_commit</name>
      <anchor>a5</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_create_rollback</name>
      <anchor>a6</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>exception_destroy_rollback</name>
      <anchor>a7</anchor>
      <arglist>(exception_reference_t exception)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>transaction_internal.c</name>
    <path>/root/Chaos/Sources/StormG4/Repository/tmp/Transaction/</path>
    <filename>transaction__internal_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_LEVEL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>transaction_reference_t</type>
      <name>transaction_create_static_internal</name>
      <anchor>a11</anchor>
      <arglist>(p_transaction_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_destroy_static_internal</name>
      <anchor>a12</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>transaction_reference_t</type>
      <name>transaction_create_internal</name>
      <anchor>a13</anchor>
      <arglist>(sequence_t filtered_objects, sequence_t ignored_objects, uint32_t history_depth, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_destroy_internal</name>
      <anchor>a14</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_begin_internal</name>
      <anchor>a15</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_commit_internal</name>
      <anchor>a16</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_rollback_internal</name>
      <anchor>a17</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_add_operation_internal</name>
      <anchor>a18</anchor>
      <arglist>(transaction_reference_t transaction, handle_reference_t handle, method_id_t method_id)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>add_operation</name>
      <anchor>a19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>rollback</name>
      <anchor>a20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>transaction_add_slot</name>
      <anchor>a21</anchor>
      <arglist>(transaction_reference_t transaction, reference_t reference, uint32_t operation)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>transaction_clear_slot</name>
      <anchor>a22</anchor>
      <arglist>(transaction_reference_t transaction, uint32_t slot_index)</arglist>
    </member>
    <member kind="variable">
      <type>operations</type>
      <name>__pad0__</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>operations</type>
      <name>OPERATION_CLASS_CREATE_STATIC</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>operations</type>
      <name>OPERATION_CLASS_CREATE</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>operations</type>
      <name>OPERATION_CLASS_DESTROY_STATIC</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>operations</type>
      <name>OPERATION_CLASS_DESTROY</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>operations</type>
      <name>OPERATION_OBJECT_CREATE_STATIC</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>operations</type>
      <name>OPERATION_OBJECT_CREATE</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>operations</type>
      <name>OPERATION_OBJECT_DESTROY_STATIC</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>operations</type>
      <name>OPERATION_OBJECT_DESTROY</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>translate.h</name>
    <path>/root/Chaos/Sources/StormG4/Repository/Include/</path>
    <filename>translate_8h</filename>
    <member kind="function" static="yes">
      <type>p_method_t</type>
      <name>method_translate_reference</name>
      <anchor>a0</anchor>
      <arglist>(method_reference_t method)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_interface_t</type>
      <name>interface_translate_reference</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_class_t</type>
      <name>class_translate_reference</name>
      <anchor>a2</anchor>
      <arglist>(class_reference_t class)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_security_t</type>
      <name>security_translate_reference</name>
      <anchor>a3</anchor>
      <arglist>(security_reference_t security)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_object_t</type>
      <name>object_translate_reference</name>
      <anchor>a4</anchor>
      <arglist>(object_reference_t object)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>p_handle_t</type>
      <name>handle_translate_reference</name>
      <anchor>a5</anchor>
      <arglist>(handle_reference_t handle)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tss.c</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/TaskState/</path>
    <filename>tss_8c</filename>
    <includes id="enviroment_8h" name="enviroment.h" local="no">enviroment.h</includes>
    <includes id="tss_8h" name="tss.h" local="yes">Include/tss.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_MODULE_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tss_create</name>
      <anchor>a3</anchor>
      <arglist>(p_tss_t tss, p_page_directory_t page_directory, uint16_t selector_code, uint16_t selector_data, uint32_t instruction_pointer, uint32_t kernel_stack_pointer, uint32_t user_stack_pointer, uint32_t eflags)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tss_switch_prepare</name>
      <anchor>a4</anchor>
      <arglist>(p_tss_t tss)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>volatile unsigned int</type>
      <name>dispatch_flag</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>jump_data</name>
      <anchor>a2</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tss.h</name>
    <path>/root/Chaos/Sources/StormG4/Hardware/TaskState/Include/</path>
    <filename>tss_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>tss_create</name>
      <anchor>a1</anchor>
      <arglist>(p_tss_t tss, p_page_directory_t page_directory, uint16_t selector_code, uint16_t selector_data, uint32_t instruction_pointer, uint32_t kernel_stack_pointer, uint32_t user_stack_pointer, uint32_t eflags)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tss_switch_prepare</name>
      <anchor>a2</anchor>
      <arglist>(p_tss_t tss)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>jump_data</name>
      <anchor>a0</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>call_data_struct</name>
    <filename>structcall__data__struct.html</filename>
    <member kind="variable">
      <type>void(*</type>
      <name>func</name>
      <anchor>o0</anchor>
      <arglist>)(void *info)</arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>info</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>atomic_t</type>
      <name>started</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>atomic_t</type>
      <name>finished</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>wait</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_family_record</name>
    <filename>structcpu__family__record.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>from_model</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>to_model</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>vendor_id</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>cpu_type_id</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_record_t</name>
    <filename>structcpu__record__t.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>family</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>from_model</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>to_model</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>vendor_id</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>cpu_type_id</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_sub_record_t</name>
    <filename>structcpu__sub__record__t.html</filename>
    <member kind="variable">
      <type>uint16_t</type>
      <name>cpu_type_id</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>model</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>stepping</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>cpu_sub_type_id</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_sub_type_record_t</name>
    <filename>structcpu__sub__type__record__t.html</filename>
    <member kind="variable">
      <type>uint16_t</type>
      <name>sub_type_id</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>name</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_type_record_t</name>
    <filename>structcpu__type__record__t.html</filename>
    <member kind="variable">
      <type>uint16_t</type>
      <name>type_id</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>name</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>debug_screen_t</name>
    <filename>structdebug__screen__t.html</filename>
    <member kind="variable">
      <type>char</type>
      <name>character</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>attribute</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>descriptors_table_register_t</name>
    <filename>structdescriptors__table__register__t.html</filename>
    <member kind="variable">
      <type>uint16_t</type>
      <name>size</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>descriptor_t *base</type>
      <name>PACKED</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>dma_channel_t</name>
    <filename>structdma__channel__t.html</filename>
    <member kind="variable">
      <type>unsigned int</type>
      <name>channel</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>is_used</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>physical_buffer</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>dma_command_register_t</name>
    <filename>structdma__command__register__t.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>memory_to_memory_enable</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>__pad0__</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>__pad1__</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>__pad2__</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>__pad3__</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>__pad4__</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>__pad5__</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>__pad6__</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>dma_mode_register_t</name>
    <filename>structdma__mode__register__t.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>channel</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>mode</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>autoinit</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>decrement</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>transfer_mode</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>family_t</name>
    <filename>structfamily__t.html</filename>
    <member kind="variable">
      <type>cpu_family_record *</type>
      <name>family</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>size_of_family</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>flat_name_t</name>
    <filename>structflat__name__t.html</filename>
    <member kind="variable">
      <type></type>
      <name>HASH_ELEMENT_PART</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>wchar_t</type>
      <name>name</name>
      <anchor>o1</anchor>
      <arglist>[WSTRING_MAX_LENGTH]</arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>type</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>reference_t</type>
      <name>reference</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>flat_namespace_t</name>
    <filename>structflat__namespace__t.html</filename>
    <member kind="variable">
      <type>hash_table_t *</type>
      <name>names_table</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fpu_type_record_t</name>
    <filename>structfpu__type__record__t.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>type_id</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>name</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>integer_control_interface_table_t</name>
    <filename>structinteger__control__interface__table__t.html</filename>
    <member kind="variable">
      <type>p_void_t(*</type>
      <name>create</name>
      <anchor>o0</anchor>
      <arglist>)(context_t context, uint32_t value)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>destroy</name>
      <anchor>o1</anchor>
      <arglist>)(context_t context, p_void_t object_data)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>integer_interface_table_t</name>
    <filename>structinteger__interface__table__t.html</filename>
    <member kind="variable">
      <type>void(*</type>
      <name>get</name>
      <anchor>o0</anchor>
      <arglist>)(context_t context, p_uint32_t value)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>set</name>
      <anchor>o1</anchor>
      <arglist>)(context_t context, uint32_t value)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>integer_value_data_t</name>
    <filename>structinteger__value__data__t.html</filename>
    <member kind="variable">
      <type>atomic_uint32_t</type>
      <name>value</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>kernel_class_info_t</name>
    <filename>structkernel__class__info__t.html</filename>
    <member kind="variable">
      <type>const wchar_t *</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_kernel_class_init_function_t</type>
      <name>init</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>class_reference_t</type>
      <name>class</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>enabled</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>kernel_event_consumer_interface_info_t</name>
    <filename>structkernel__event__consumer__interface__info__t.html</filename>
    <member kind="variable">
      <type>const wchar_t *</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_kernel_event_consumer_init_function_t</type>
      <name>init</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>enabled</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>kernel_event_supplier_interface_info_t</name>
    <filename>structkernel__event__supplier__interface__info__t.html</filename>
    <member kind="variable">
      <type>const wchar_t *</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_kernel_event_supplier_init_function_t</type>
      <name>init</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>enabled</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>kernel_interface_info_t</name>
    <filename>structkernel__interface__info__t.html</filename>
    <member kind="variable">
      <type>const wchar_t *</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_kernel_interface_init_function_t</type>
      <name>init</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>interface_reference_t</type>
      <name>interface</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>enabled</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>local_apic</name>
    <filename>structlocal__apic.html</filename>
    <member kind="variable">
      <type>local_apic::@9</type>
      <name>__reserved_01</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@10</type>
      <name>__reserved_02</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@11</type>
      <name>id</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>phys_apic_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o3</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>const struct local_apic::@12</type>
      <name>version</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>version</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>max_lvt</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o4</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@13</type>
      <name>__reserved_03</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@14</type>
      <name>__reserved_04</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@15</type>
      <name>__reserved_05</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@16</type>
      <name>__reserved_06</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@17</type>
      <name>tpr</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>priority</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o2</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>const struct local_apic::@18</type>
      <name>apr</name>
      <anchor>o18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>u32</type>
      <name>priority</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>u32</type>
      <name>__reserved_1</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o2</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>const struct local_apic::@19</type>
      <name>ppr</name>
      <anchor>o19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>priority</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o2</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@20</type>
      <name>eoi</name>
      <anchor>o21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>eoi</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o1</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@21</type>
      <name>__reserved_07</name>
      <anchor>o22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@22</type>
      <name>ldr</name>
      <anchor>o24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>logical_dest</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o2</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@23</type>
      <name>dfr</name>
      <anchor>o26</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>model</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o2</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@24</type>
      <name>svr</name>
      <anchor>o31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>spurious_vector</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>apic_enabled</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>focus_cpu</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o4</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@25</type>
      <name>isr</name>
      <anchor>o33</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>bitfield</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o1</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@26</type>
      <name>tmr</name>
      <anchor>o34</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>bitfield</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o1</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@27</type>
      <name>irr</name>
      <anchor>o35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>bitfield</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o1</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@28</type>
      <name>esr</name>
      <anchor>o46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@28::@52</type>
      <name>error_bits</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>send_cs_error</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>receive_cs_error</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>send_accept_error</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>receive_accept_error</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>send_illegal_vector</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>receive_illegal_vector</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>illegal_register_address</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o9</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@28::@53</type>
      <name>all_errors</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>errors</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o1</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@29</type>
      <name>__reserved_08</name>
      <anchor>o47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@30</type>
      <name>__reserved_09</name>
      <anchor>o48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@31</type>
      <name>__reserved_10</name>
      <anchor>o49</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@32</type>
      <name>__reserved_11</name>
      <anchor>o50</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@33</type>
      <name>__reserved_12</name>
      <anchor>o51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@34</type>
      <name>__reserved_13</name>
      <anchor>o52</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@35</type>
      <name>__reserved_14</name>
      <anchor>o53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@36</type>
      <name>icr1</name>
      <anchor>o62</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>vector</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_mode</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>destination_mode</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_status</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>level</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>trigger</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>shorthand</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_4</name>
      <anchor>o10</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@37</type>
      <name>icr2</name>
      <anchor>o65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@37::@54</type>
      <name>dest</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>phys_dest</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>logical_dest</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_4</name>
      <anchor>o1</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@38</type>
      <name>lvt_timer</name>
      <anchor>o68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>vector</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_status</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>mask</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>timer_mode</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_4</name>
      <anchor>o7</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@39</type>
      <name>__reserved_15</name>
      <anchor>o69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@40</type>
      <name>lvt_pc</name>
      <anchor>o70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>vector</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_mode</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_status</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>mask</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_4</name>
      <anchor>o7</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@41</type>
      <name>lvt_lint0</name>
      <anchor>o73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>vector</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_mode</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_status</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>polarity</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>remote_irr</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>trigger</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>mask</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o9</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@42</type>
      <name>lvt_lint1</name>
      <anchor>o74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>vector</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_mode</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_status</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>polarity</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>remote_irr</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>trigger</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>mask</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o9</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@43</type>
      <name>lvt_error</name>
      <anchor>o75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>vector</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>delivery_status</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>mask</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_3</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_4</name>
      <anchor>o6</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@44</type>
      <name>timer_icr</name>
      <anchor>o77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>initial_count</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o1</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>const struct local_apic::@45</type>
      <name>timer_ccr</name>
      <anchor>o79</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>curr_count</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o1</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@46</type>
      <name>__reserved_16</name>
      <anchor>o80</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@47</type>
      <name>__reserved_17</name>
      <anchor>o81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@48</type>
      <name>__reserved_18</name>
      <anchor>o82</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@49</type>
      <name>__reserved_19</name>
      <anchor>o83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@50</type>
      <name>timer_dcr</name>
      <anchor>o85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>divisor</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_1</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved_2</name>
      <anchor>o2</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>local_apic::@51</type>
      <name>__reserved_20</name>
      <anchor>o86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__reserved</name>
      <anchor>o0</anchor>
      <arglist>[4]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>module_info_t</name>
    <filename>structmodule__info__t.html</filename>
    <member kind="variable">
      <type>char</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist>[MODULE_NAME_LENGTH]</arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>version</name>
      <anchor>o1</anchor>
      <arglist>[MODULE_VERSION_LENGTH]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiboot_info_t</name>
    <filename>structmultiboot__info__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_memory_info</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_boot_device_info</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_command_line</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_module_info</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_aout_info</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_elf_info</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_memory_map</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_drives_info</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_ROM_config</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_boot_loader_name</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_APM_info</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>has_video_mode_info</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>__pad0__</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>memory_lower</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>memory_upper</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>boot_device</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>command_line</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_modules</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>module_base</name>
      <anchor>o18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>section_header_num</name>
      <anchor>o19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>section_header_size</name>
      <anchor>o20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>section_header_address</name>
      <anchor>o21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>section_header_string_index</name>
      <anchor>o22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>memory_map_length</name>
      <anchor>o23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>memory_map_address</name>
      <anchor>o24</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>multiboot_memory_map_t</name>
    <filename>structmultiboot__memory__map__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>size</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>base_address</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
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
    <name>multiboot_module_info_t</name>
    <filename>structmultiboot__module__info__t.html</filename>
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
      <type>char *</type>
      <name>name</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>reserved</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_debug_print_method_t</name>
    <filename>structobject__debug__print__method__t.html</filename>
    <member kind="variable">
      <type>debug_print_function_t *</type>
      <name>function</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>method_id_t</type>
      <name>method_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>parameters_size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_parameters</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parameter_t</type>
      <name>parameters</name>
      <anchor>o4</anchor>
      <arglist>[5]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_dma_aregister_method_t</name>
    <filename>structobject__dma__aregister__method__t.html</filename>
    <member kind="variable">
      <type>dma_aregister_function_t *</type>
      <name>function</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>method_id_t</type>
      <name>method_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>parameters_size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_parameters</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parameter_t</type>
      <name>parameters</name>
      <anchor>o4</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_dma_transfer_method_t</name>
    <filename>structobject__dma__transfer__method__t.html</filename>
    <member kind="variable">
      <type>dma_transfer_function_t *</type>
      <name>function</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>method_id_t</type>
      <name>method_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>parameters_size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_parameters</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parameter_t</type>
      <name>parameters</name>
      <anchor>o4</anchor>
      <arglist>[5]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_dma_unregister_method_t</name>
    <filename>structobject__dma__unregister__method__t.html</filename>
    <member kind="variable">
      <type>dma_unregister_function_t *</type>
      <name>function</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>method_id_t</type>
      <name>method_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>parameters_size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_parameters</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parameter_t</type>
      <name>parameters</name>
      <anchor>o4</anchor>
      <arglist>[1]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_irq_aregister_method_t</name>
    <filename>structobject__irq__aregister__method__t.html</filename>
    <member kind="variable">
      <type>irq_aregister_function_t *</type>
      <name>function</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>method_id_t</type>
      <name>method_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>parameters_size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_parameters</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parameter_t</type>
      <name>parameters</name>
      <anchor>o4</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_irq_unregister_method_t</name>
    <filename>structobject__irq__unregister__method__t.html</filename>
    <member kind="variable">
      <type>irq_unregister_function_t *</type>
      <name>function</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>method_id_t</type>
      <name>method_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>parameters_size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_parameters</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parameter_t</type>
      <name>parameters</name>
      <anchor>o4</anchor>
      <arglist>[1]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_memory_allocate_method_t</name>
    <filename>structobject__memory__allocate__method__t.html</filename>
    <member kind="variable">
      <type>memory_allocate_function_t *</type>
      <name>function</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>method_id_t</type>
      <name>method_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>parameters_size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_parameters</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parameter_t</type>
      <name>parameters</name>
      <anchor>o4</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_memory_deallocate_method_t</name>
    <filename>structobject__memory__deallocate__method__t.html</filename>
    <member kind="variable">
      <type>memory_deallocate_function_t *</type>
      <name>function</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>method_id_t</type>
      <name>method_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>parameters_size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_parameters</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parameter_t</type>
      <name>parameters</name>
      <anchor>o4</anchor>
      <arglist>[1]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>rtc_time_t</name>
    <filename>structrtc__time__t.html</filename>
    <member kind="variable">
      <type>unsigned char</type>
      <name>seconds</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char</type>
      <name>minutes</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char</type>
      <name>hours</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char</type>
      <name>day_of_week</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char</type>
      <name>day_of_month</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned char</type>
      <name>month</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>year</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>slab_block_t</name>
    <filename>structslab__block__t.html</filename>
    <member kind="variable">
      <type>void *</type>
      <name>previous</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>next</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>slab_heap_t</name>
    <filename>structslab__heap__t.html</filename>
    <member kind="variable">
      <type>void *</type>
      <name>block</name>
      <anchor>o0</anchor>
      <arglist>[0]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>slab_superblock_header_t</name>
    <filename>structslab__superblock__header__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>magic_number</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>buffer_size</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>previous_superblock</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>next_superblock</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>free_list</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>free_blocks</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>total_blocks</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>slab_superblock_t</name>
    <filename>structslab__superblock__t.html</filename>
    <member kind="variable">
      <type>slab_superblock_header_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>buffer</name>
      <anchor>o1</anchor>
      <arglist>[0]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>static_module_info_t</name>
    <filename>structstatic__module__info__t.html</filename>
    <member kind="variable">
      <type>const wchar_t *</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_module_main_t</type>
      <name>main</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>enabled</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="union">
    <name>static_pool_of_integers_t</name>
    <filename>unionstatic__pool__of__integers__t.html</filename>
    <member kind="variable">
      <type>pool_of_integers_t</type>
      <name>pool</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>data</name>
      <anchor>o1</anchor>
      <arglist>[INTERNAL_MEMORY_SIZE]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>storm_module_data_t</name>
    <filename>structstorm__module__data__t.html</filename>
    <member kind="variable">
      <type>elf_parsed_t</type>
      <name>elf_parsed</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_module_start_t</type>
      <name>start</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_module_stop_t</type>
      <name>stop</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>module_start_function_t *</type>
      <name>start</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>module_stop_function_t *</type>
      <name>stop</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>storm_program_data_t</name>
    <filename>structstorm__program__data__t.html</filename>
    <member kind="variable">
      <type>elf_parsed_program_t</type>
      <name>elf_parsed</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>virtual_memory_t</type>
      <name>virtual_memory</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_main_function_t</type>
      <name>main</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>subsystem_built_in_t</name>
    <filename>structsubsystem__built__in__t.html</filename>
    <member kind="variable">
      <type>char</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist>[STRING_MAX_LENGTH]</arglist>
    </member>
    <member kind="variable">
      <type>p_main_function_t</type>
      <name>init</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>enabled</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>parameters</name>
      <anchor>o3</anchor>
      <arglist>[STRING_MAX_LENGTH]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>timer_t</name>
    <filename>structtimer__t.html</filename>
    <member kind="variable">
      <type>p_timer_handler_t</type>
      <name>handler</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_void_t</type>
      <name>data</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>state</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>ticks</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>period</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mode</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>vendor_record_t</name>
    <filename>structvendor__record__t.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>vendor_id</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>vendor_string</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
