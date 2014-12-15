<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="file">
    <name>class.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>class_8h</filename>
    <member kind="function">
      <type>class_reference_t</type>
      <name>class_create</name>
      <anchor>a0</anchor>
      <arglist>(description_reference_t class_description, sequence_t class_interfaces, sequence_t event_supplier_interfaces, sequence_t event_consumer_interfaces, handle_reference_t object_factory, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy</name>
      <anchor>a1</anchor>
      <arglist>(class_reference_t class_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_invoke_method</name>
      <anchor>a2</anchor>
      <arglist>(class_reference_t class_reference, interface_reference_t interface_reference, method_id_t method_id, context_t context, computer_reference_t computer, sequence_t parameters, sequence_t return_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_fire_event</name>
      <anchor>a3</anchor>
      <arglist>(class_reference_t class_reference, event_supplier_interface_reference_t interface_reference, context_t context, event_queue_reference_t event_queue, sequence_t event_data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_wait_event</name>
      <anchor>a4</anchor>
      <arglist>(class_reference_t class_reference, event_consumer_interface_reference_t interface_reference, context_t context, event_queue_reference_t event_queue, sequence_t event_data)</arglist>
    </member>
    <member kind="function">
      <type>sequence_t</type>
      <name>class_get_interfaces</name>
      <anchor>a5</anchor>
      <arglist>(class_reference_t class_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_set_interfaces</name>
      <anchor>a6</anchor>
      <arglist>(class_reference_t class_reference, sequence_t class_interfaces)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>class_get_interface_by_index</name>
      <anchor>a7</anchor>
      <arglist>(class_reference_t class_reference, uint32_t index)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>class_get_interface_by_id</name>
      <anchor>a8</anchor>
      <arglist>(class_reference_t class_reference, interface_id_t interface_id)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/class.h</name>
    <path>/root/Chaos/Enviroments/Repository/Descriptions/</path>
    <filename>Descriptions_2class_8h</filename>
    <class kind="struct">class_description_t</class>
    <member kind="typedef">
      <type>id_t</type>
      <name>class_id_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>class_id_t *</type>
      <name>p_class_id_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>class_description_t *</type>
      <name>p_class_description_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>class_type_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CLASS_TYPE_STATIC</name>
      <anchor>a7a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CLASS_TYPE_DYNAMIC</name>
      <anchor>a7a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>class_description_register</name>
      <anchor>a5</anchor>
      <arglist>(id_t id, const wchar_t *name, uint32_t type, uint32_t number_of_interfaces, uint32_t number_of_event_suppliers, uint32_t number_of_event_consumers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_description_unregister</name>
      <anchor>a6</anchor>
      <arglist>(description_reference_t description_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/class.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2class_8h</filename>
    <class kind="struct">class_t</class>
    <member kind="typedef">
      <type>class_t *</type>
      <name>p_class_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_class_t *</type>
      <name>p_p_class_t</name>
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
    <name>System/Descriptions/class.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Descriptions/</path>
    <filename>System_2Descriptions_2class_8h</filename>
    <class kind="struct">class_description_t</class>
    <member kind="typedef">
      <type>class_description_t *</type>
      <name>p_class_description_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>class_type_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CLASS_TYPE_STATIC</name>
      <anchor>a7a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CLASS_TYPE_DYNAMIC</name>
      <anchor>a7a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>class_description_register_static</name>
      <anchor>a3</anchor>
      <arglist>(p_class_description_t class_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_description_unregister_static</name>
      <anchor>a4</anchor>
      <arglist>(description_reference_t description)</arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>class_description_register</name>
      <anchor>a5</anchor>
      <arglist>(p_class_description_t class_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_description_unregister</name>
      <anchor>a6</anchor>
      <arglist>(description_reference_t description)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/Static/class.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Static/</path>
    <filename>System_2Static_2class_8h</filename>
    <member kind="function">
      <type>class_reference_t</type>
      <name>class_create_static</name>
      <anchor>a0</anchor>
      <arglist>(p_class_t class)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>class_destroy_static</name>
      <anchor>a1</anchor>
      <arglist>(class_reference_t class_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>computer.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>computer_8h</filename>
    <class kind="struct">invoke_record_t</class>
    <class kind="struct">computer_node_t</class>
    <class kind="struct">computer_t</class>
    <member kind="define">
      <type>#define</type>
      <name>COMPUTER_KERNEL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COMPUTER_CURRENT</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_CURRENT</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MEMORY_CURRENT</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SECURITY_CURRENT</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>METHOD_CURRENT</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>METHOD_CURRENT_INVOKER</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INTERFACE_CURRENT</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INTERFACE_CURRENT_INVOKER</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CLASS_CURRENT</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CLASS_CURRENT_INVOKER</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>OBJECT_CURRENT</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>OBJECT_CURRENT_INVOKER</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HANDLE_CURRENT</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>HANDLE_CURRENT_INVOKER</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>computer_node_t *</type>
      <name>p_computer_node_t</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>computer_t *</type>
      <name>p_computer_t</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>computer_t</type>
      <name>computer_kernel</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile p_computer_t</type>
      <name>computer_current</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/computer.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2computer_8h</filename>
    <member kind="enumvalue">
      <name>COMPUTER_STATE_STOPPED</name>
      <anchor>a10a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>COMPUTER_STATE_RUNNING</name>
      <anchor>a10a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>COMPUTER_STATE_WAITING</name>
      <anchor>a10a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>computer_reference_t</type>
      <name>computer_create</name>
      <anchor>a3</anchor>
      <arglist>(cpu_reference_t cpu, memory_reference_t memory, security_reference_t security)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_destroy</name>
      <anchor>a4</anchor>
      <arglist>(computer_reference_t computer_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_reset</name>
      <anchor>a5</anchor>
      <arglist>(computer_reference_t computer_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_fire_exception</name>
      <anchor>a6</anchor>
      <arglist>(computer_reference_t computer_reference, p_exception_info_t exception_info)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computer_add_exception_context</name>
      <anchor>a7</anchor>
      <arglist>(computer_reference_t computer_reference, p_exception_context_t context)</arglist>
    </member>
    <member kind="function">
      <type>p_exception_context_t</type>
      <name>computer_remove_exception_context</name>
      <anchor>a8</anchor>
      <arglist>(computer_reference_t computer_reference)</arglist>
    </member>
    <member kind="function">
      <type>computer_reference_t</type>
      <name>computer_get_current</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>constraint.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>constraint_8h</filename>
    <class kind="struct">constraint_t</class>
    <member kind="define">
      <type>#define</type>
      <name>CONSTRAINT_CURRENT</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>constraint_t *</type>
      <name>p_constraint</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constraint_reference_t</type>
      <name>constraint_create</name>
      <anchor>a2</anchor>
      <arglist>(constraint_reference_t parent)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>constraint_destroy</name>
      <anchor>a3</anchor>
      <arglist>(constraint_reference_t constraint_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>context.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>context_8h</filename>
    <class kind="struct">context_t</class>
    <member kind="typedef">
      <type>context_t *</type>
      <name>p_context_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cpu.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>cpu_8h</filename>
    <class kind="struct">cpu_t</class>
    <member kind="define">
      <type>#define</type>
      <name>CPU_KERNEL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>cpu_t *</type>
      <name>p_cpu_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_cpu_t *</type>
      <name>p_p_cpu_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>cpu_reference_t</type>
      <name>cpu_create</name>
      <anchor>a4</anchor>
      <arglist>(uint32_t performance)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_destroy</name>
      <anchor>a5</anchor>
      <arglist>(cpu_reference_t cpu_reference)</arglist>
    </member>
    <member kind="function">
      <type>cpu_reference_t</type>
      <name>cpu_get_current</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_schedule</name>
      <anchor>a7</anchor>
      <arglist>(p_cpu_t cpu)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_sleep_milli</name>
      <anchor>a8</anchor>
      <arglist>(cpu_reference_t cpu, uint32_t milli)</arglist>
    </member>
    <member kind="variable">
      <type>cpu_t</type>
      <name>cpu_kernel</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>cpu_array.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>cpu__array_8h</filename>
    <class kind="struct">cpu_array_t</class>
    <member kind="define">
      <type>#define</type>
      <name>CPU_ARRAY_GLOBAL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>cpu_array_t *</type>
      <name>p_cpu_array_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cpu_array_schedule</name>
      <anchor>a3</anchor>
      <arglist>(p_cpu_array_t cpu_array)</arglist>
    </member>
    <member kind="variable">
      <type>cpu_array_t</type>
      <name>global_cpu_array</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>data.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>data_8h</filename>
  </compound>
  <compound kind="file">
    <name>Descriptions/data.h</name>
    <path>/root/Chaos/Enviroments/Repository/Descriptions/</path>
    <filename>Descriptions_2data_8h</filename>
    <class kind="struct">type_sequence_info_t</class>
    <class kind="struct">parameter_description_t</class>
    <member kind="typedef">
      <type>parameter_description_t *</type>
      <name>p_parameter_description_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>parameter_attribute_t</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PARAMETER_ATTRIBUTE_IN</name>
      <anchor>a22a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PARAMETER_ATTRIBUTE_OUT</name>
      <anchor>a22a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PARAMETER_ATTRIBUTE_INOUT</name>
      <anchor>a22a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>data_type_t</name>
      <anchor>a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_SHORT_INT</name>
      <anchor>a23a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_LONG_INT</name>
      <anchor>a23a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_LONG_LONG_INT</name>
      <anchor>a23a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_SHORT_UINT</name>
      <anchor>a23a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_LONG_UINT</name>
      <anchor>a23a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_LONG_LONG_UINT</name>
      <anchor>a23a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_CHAR</name>
      <anchor>a23a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_WCHAR</name>
      <anchor>a23a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_BOOLEAN</name>
      <anchor>a23a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_OCTET</name>
      <anchor>a23a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_FLOAT</name>
      <anchor>a23a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_DOUBLE</name>
      <anchor>a23a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_SEQUENCE</name>
      <anchor>a23a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_STRING</name>
      <anchor>a23a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_STRUCT</name>
      <anchor>a23a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_ANY</name>
      <anchor>a23a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_OBJECT</name>
      <anchor>a23a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DATA_TYPE_INTERFACE</name>
      <anchor>a23a21</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/Descriptions/data.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Descriptions/</path>
    <filename>System_2Descriptions_2data_8h</filename>
    <class kind="struct">data_description_t</class>
    <member kind="typedef">
      <type>data_description_t *</type>
      <name>p_data_description_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>parameter_type_t</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PARAMETER_TYPE_BASE</name>
      <anchor>a10a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PARAMETER_TYPE_SEQUENCE</name>
      <anchor>a10a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PARAMETER_TYPE_STRUCT</name>
      <anchor>a10a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PARAMETER_TYPE_OBJECT</name>
      <anchor>a10a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PARAMETER_TYPE_INTERFACE</name>
      <anchor>a10a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>data_description_register_static</name>
      <anchor>a6</anchor>
      <arglist>(p_data_description_t data_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>data_description_unregister_static</name>
      <anchor>a7</anchor>
      <arglist>(description_reference_t description)</arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>data_description_register</name>
      <anchor>a8</anchor>
      <arglist>(p_data_description_t data_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>data_description_unregister</name>
      <anchor>a9</anchor>
      <arglist>(description_reference_t description)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event.h</name>
    <path>/root/Chaos/Enviroments/Repository/Descriptions/</path>
    <filename>event_8h</filename>
    <class kind="struct">event_description_t</class>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>event_id_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>event_description_t *</type>
      <name>p_event_description_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>event_description_register_static</name>
      <anchor>a2</anchor>
      <arglist>(p_event_description_t event_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_description_unregister_static</name>
      <anchor>a3</anchor>
      <arglist>(description_reference_t description_reference)</arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>event_description_register</name>
      <anchor>a4</anchor>
      <arglist>(id_t id, const wchar_t *name, uint32_t data_length)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_description_unregister</name>
      <anchor>a5</anchor>
      <arglist>(description_reference_t description_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event_class.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/tmp/</path>
    <filename>event__class_8h</filename>
    <class kind="struct">event_class_t</class>
    <member kind="typedef">
      <type>event_class_t *</type>
      <name>p_event_class_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_event_class_t *</type>
      <name>p_p_event_class_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event_consumer.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>event__consumer_8h</filename>
    <member kind="function">
      <type>event_consumer_reference_t</type>
      <name>event_consumer_create</name>
      <anchor>a0</anchor>
      <arglist>(object_reference_t object_reference, event_id_t event_class_id, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_destroy</name>
      <anchor>a1</anchor>
      <arglist>(event_consumer_reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_wait_event</name>
      <anchor>a2</anchor>
      <arglist>(event_consumer_reference_t reference, sequence_t event_data, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_set_queue</name>
      <anchor>a3</anchor>
      <arglist>(event_consumer_reference_t event_consumer_reference, event_queue_reference_t event_queue_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/event_consumer.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2event__consumer_8h</filename>
    <class kind="struct">event_consumer_t</class>
    <member kind="typedef">
      <type>event_consumer_t *</type>
      <name>p_event_consumer_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_event_consumer_t *</type>
      <name>p_p_event_consumer_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event_consumer_factory.h</name>
    <path>/root/Chaos/Enviroments/Repository/Interfaces/</path>
    <filename>event__consumer__factory_8h</filename>
    <member kind="enumvalue">
      <name>METHOD_EVENT_CONSUMER_FACTORY_CREATE_ID</name>
      <anchor>a3a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_EVENT_CONSUMER_FACTORY_DESTROY_ID</name>
      <anchor>a3a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_EVENT_CONSUMER_FACTORY_NUMBER</name>
      <anchor>a3a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event_consumer_interface.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>event__consumer__interface_8h</filename>
    <member kind="enumvalue">
      <name>EVENT_CONSUMER_TYPE_NONE</name>
      <anchor>a10a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EVENT_CONSUMER_TYPE_PUSH</name>
      <anchor>a10a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EVENT_CONSUMER_TYPE_PULL</name>
      <anchor>a10a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_EVENT_CONSUMER_HANDLER_ID</name>
      <anchor>a11a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>event_consumer_interface_create_static</name>
      <anchor>a4</anchor>
      <arglist>(p_event_consumer_interface_t event_consumer_interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_interface_destroy_static</name>
      <anchor>a5</anchor>
      <arglist>(event_consumer_interface_reference_t event_consumer_interface)</arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>event_consumer_interface_create</name>
      <anchor>a6</anchor>
      <arglist>(event_class_reference_t event_class, int type, method_reference_t handle, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_interface_destroy</name>
      <anchor>a7</anchor>
      <arglist>(event_consumer_interface_reference_t event_consumer_interface_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_interface_wait</name>
      <anchor>a8</anchor>
      <arglist>(event_consumer_interface_reference_t event_consumer_interface_reference, context_t context, event_queue_reference_t event_queue, sequence_t event_data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_consumer_interface_set_factory</name>
      <anchor>a9</anchor>
      <arglist>(event_consumer_interface_reference_t event_consumer_interface_reference, reference_t factory)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/event_consumer_interface.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2event__consumer__interface_8h</filename>
    <class kind="struct">event_consumer_interface_t</class>
    <member kind="typedef">
      <type>event_consumer_interface_t *</type>
      <name>p_event_consumer_interface_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_event_consumer_interface_t *</type>
      <name>p_p_event_consumer_interface_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event_queue.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>event__queue_8h</filename>
    <member kind="enumvalue">
      <name>EVENT_QUEUE_TYPE_ASYNCHRONOUS</name>
      <anchor>a5a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EVENT_QUEUE_TYPE_SYNCHRONOUS</name>
      <anchor>a5a1</anchor>
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
      <arglist>(event_queue_reference_t event_queue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_queue_flush</name>
      <anchor>a4</anchor>
      <arglist>(event_queue_reference_t event_queue)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/event_queue.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2event__queue_8h</filename>
    <class kind="struct">event_queue_t</class>
    <member kind="typedef">
      <type>event_queue_t *</type>
      <name>p_event_queue_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event_supplier.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>event__supplier_8h</filename>
    <member kind="function">
      <type>event_supplier_reference_t</type>
      <name>event_supplier_create</name>
      <anchor>a0</anchor>
      <arglist>(object_reference_t object_reference, event_id_t event_class_id, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_destroy</name>
      <anchor>a1</anchor>
      <arglist>(event_supplier_reference_t event_supplier_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_fire_event</name>
      <anchor>a2</anchor>
      <arglist>(event_supplier_reference_t event_supplier_reference, sequence_t event_data, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>event_supplier_get_data</name>
      <anchor>a3</anchor>
      <arglist>(event_supplier_reference_t event_supplier_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_set_data</name>
      <anchor>a4</anchor>
      <arglist>(event_supplier_reference_t event_supplier_reference, uint64_t data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_set_queue</name>
      <anchor>a5</anchor>
      <arglist>(event_supplier_reference_t event_supplier_reference, event_queue_reference_t event_queue_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/event_supplier.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2event__supplier_8h</filename>
    <class kind="struct">event_supplier_t</class>
    <member kind="typedef">
      <type>event_supplier_t *</type>
      <name>p_event_supplier_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_event_supplier_t *</type>
      <name>p_p_event_supplier_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/Static/event_supplier.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Static/</path>
    <filename>System_2Static_2event__supplier_8h</filename>
    <member kind="function">
      <type>event_supplier_reference_t</type>
      <name>event_supplier_create_static</name>
      <anchor>a0</anchor>
      <arglist>(p_event_supplier_t event_supplier, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_destroy_static</name>
      <anchor>a1</anchor>
      <arglist>(event_supplier_reference_t reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event_supplier_factory.h</name>
    <path>/root/Chaos/Enviroments/Repository/Interfaces/</path>
    <filename>event__supplier__factory_8h</filename>
    <class kind="struct">event_supplier_factory_interface_table_t</class>
    <member kind="define">
      <type>#define</type>
      <name>INTERFACE_EVENT_SUPPLIER_FACTORY_ID</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>event_supplier_factory_create_t</name>
      <anchor>a1</anchor>
      <arglist>)(context_t context, event_supplier_reference_t event_supplier)</arglist>
    </member>
    <member kind="typedef">
      <type>event_supplier_factory_create_t *</type>
      <name>p_event_supplier_factory_create_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>event_supplier_factory_destroy_t</name>
      <anchor>a3</anchor>
      <arglist>)(context_t context, event_supplier_reference_t event_supplier)</arglist>
    </member>
    <member kind="typedef">
      <type>event_supplier_factory_destroy_t *</type>
      <name>p_event_supplier_factory_destroy_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>event_supplier_factory_interface_table_t *</type>
      <name>p_event_supplier_factory_interface_table_t</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_EVENT_SUPPLIER_FACTORY_CREATE_ID</name>
      <anchor>a9a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_EVENT_SUPPLIER_FACTORY_DESTROY_ID</name>
      <anchor>a9a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_EVENT_SUPPLIER_FACTORY_NUMBER</name>
      <anchor>a9a8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>event_supplier_interface.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>event__supplier__interface_8h</filename>
    <member kind="enumvalue">
      <name>EVENT_SUPPLIER_TYPE_NONE</name>
      <anchor>a11a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EVENT_SUPPLIER_TYPE_PUSH</name>
      <anchor>a11a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EVENT_SUPPLIER_TYPE_PULL</name>
      <anchor>a11a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_EVENT_SUPPLIER_HANDLER_ID</name>
      <anchor>a12a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>event_supplier_interface_create_static</name>
      <anchor>a4</anchor>
      <arglist>(p_event_supplier_interface_t event_supplier_interface)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_interface_destroy_static</name>
      <anchor>a5</anchor>
      <arglist>(event_supplier_interface_reference_t event_supplier_interface)</arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>event_supplier_interface_create</name>
      <anchor>a6</anchor>
      <arglist>(event_class_reference_t event_class, int type, method_reference_t handle, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_interface_destroy</name>
      <anchor>a7</anchor>
      <arglist>(event_supplier_interface_reference_t event_supplier_interface_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_interface_fire</name>
      <anchor>a8</anchor>
      <arglist>(event_supplier_interface_reference_t event_supplier_interface_reference, context_t context, event_queue_reference_t event_queue, sequence_t event_data)</arglist>
    </member>
    <member kind="function">
      <type>reference_t</type>
      <name>event_supplier_interface_get_factory</name>
      <anchor>a9</anchor>
      <arglist>(event_supplier_interface_reference_t event_supplier_interface_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_supplier_interface_set_factory</name>
      <anchor>a10</anchor>
      <arglist>(event_supplier_interface_reference_t event_supplier_interface_reference, reference_t factory)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/event_supplier_interface.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2event__supplier__interface_8h</filename>
    <class kind="struct">event_supplier_interface_t</class>
    <member kind="typedef">
      <type>event_supplier_interface_t *</type>
      <name>p_event_supplier_interface_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_event_supplier_interface_t *</type>
      <name>p_p_event_supplier_interface_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>exception.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Descriptions/</path>
    <filename>exception_8h</filename>
    <member kind="enumvalue">
      <name>EXCEPTION_INVALID_PARAMETERS</name>
      <anchor>a7a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXCEPTION_NOT_IMPLEMENTED</name>
      <anchor>a7a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXCEPTION_NOT_SUPPORTED</name>
      <anchor>a7a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXCEPTION_ACCESS_DENIED</name>
      <anchor>a7a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXCEPTION_IS_LOCKED</name>
      <anchor>a7a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXCEPTION_NOT_ENOUGH_RESOURCES</name>
      <anchor>a7a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXCEPTION_INTERNAL_FAULT</name>
      <anchor>a7a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>function.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>function_8h</filename>
    <member kind="typedef">
      <type>void(</type>
      <name>function_dynamic_t</name>
      <anchor>a0</anchor>
      <arglist>)(uint64_t key, context_t context, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
    <member kind="typedef">
      <type>function_dynamic_t *</type>
      <name>p_function_dynamic_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>function_static_t</name>
      <anchor>a2</anchor>
      <arglist>)(uint64_t key, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out)</arglist>
    </member>
    <member kind="typedef">
      <type>function_static_t *</type>
      <name>p_function_static_t</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>function_object_create_t</name>
      <anchor>a4</anchor>
      <arglist>)(uint64_t key, context_t context, class_reference_t class, object_reference_t object, sequence_t parameters_in)</arglist>
    </member>
    <member kind="typedef">
      <type>function_object_create_t *</type>
      <name>p_function_object_create_t</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>function_object_destroy_t</name>
      <anchor>a6</anchor>
      <arglist>)(uint64_t key, context_t context, class_reference_t class, object_reference_t object)</arglist>
    </member>
    <member kind="typedef">
      <type>function_object_destroy_t *</type>
      <name>p_function_object_destroy_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>function_event_supplier_create_t</name>
      <anchor>a8</anchor>
      <arglist>)(uint64_t key, context_t context, object_reference_t object, event_supplier_reference_t event_supplier, sequence_t parameters_in)</arglist>
    </member>
    <member kind="typedef">
      <type>function_event_supplier_create_t *</type>
      <name>p_function_event_supplier_create_t</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>function_event_supplier_destroy_t</name>
      <anchor>a10</anchor>
      <arglist>)(uint64_t key, context_t context, object_reference_t object, event_supplier_reference_t event_supplier)</arglist>
    </member>
    <member kind="typedef">
      <type>function_event_supplier_destroy_t *</type>
      <name>p_function_event_supplier_destroy_t</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bool(</type>
      <name>function_event_supplier_handler_t</name>
      <anchor>a12</anchor>
      <arglist>)(uint64_t key, context_t context, sequence_t parameters_out)</arglist>
    </member>
    <member kind="typedef">
      <type>function_event_supplier_handler_t *</type>
      <name>p_function_event_supplier_handler_t</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>function_event_consumer_handler_t</name>
      <anchor>a14</anchor>
      <arglist>)(uint64_t key, context_t context, sequence_t parameters_in)</arglist>
    </member>
    <member kind="typedef">
      <type>function_event_consumer_handler_t *</type>
      <name>p_function_event_consumer_handler_t</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>group.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>group_8h</filename>
    <class kind="struct">group_t</class>
    <member kind="typedef">
      <type>group_t *</type>
      <name>p_group</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>group_reference_t</type>
      <name>group_create_static</name>
      <anchor>a1</anchor>
      <arglist>(p_group_t group)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>group_destroy_static</name>
      <anchor>a2</anchor>
      <arglist>(group_reference_t group_reference)</arglist>
    </member>
    <member kind="function">
      <type>group_reference_t</type>
      <name>group_create</name>
      <anchor>a3</anchor>
      <arglist>(sequence_t objects)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>group_destroy</name>
      <anchor>a4</anchor>
      <arglist>(group_reference_t group_reference)</arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>group_get_object</name>
      <anchor>a5</anchor>
      <arglist>(interface_id_t interface_id)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>handle.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>handle_8h</filename>
    <member kind="function">
      <type>handle_reference_t</type>
      <name>handle_create</name>
      <anchor>a0</anchor>
      <arglist>(object_reference_t object_reference, interface_id_t interface_id, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_destroy</name>
      <anchor>a1</anchor>
      <arglist>(handle_reference_t handle_reference)</arglist>
    </member>
    <member kind="function">
      <type>handle_reference_t</type>
      <name>handle_clone</name>
      <anchor>a2</anchor>
      <arglist>(handle_reference_t handle_reference, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_invoke_method</name>
      <anchor>a3</anchor>
      <arglist>(handle_reference_t handle_reference, method_id_t method_id, computer_reference_t computer, sequence_t parameters_in, sequence_t parameters_inout, sequence_t parameters_out, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>handle_get_data</name>
      <anchor>a4</anchor>
      <arglist>(handle_reference_t handle_reference)</arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>handle_get_object</name>
      <anchor>a5</anchor>
      <arglist>(handle_reference_t handle_reference)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>handle_get_interface</name>
      <anchor>a6</anchor>
      <arglist>(handle_reference_t handle_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/handle.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2handle_8h</filename>
    <class kind="struct">handle_t</class>
    <member kind="typedef">
      <type>handle_t *</type>
      <name>p_handle_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_handle_t *</type>
      <name>p_p_handle_t</name>
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
      <arglist>(handle_reference_t handle_refernce, p_handle_t new_handle_reference, uint32_t options)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>handle_factory.h</name>
    <path>/root/Chaos/Enviroments/Repository/Interfaces/</path>
    <filename>handle__factory_8h</filename>
    <member kind="enumvalue">
      <name>METHOD_HANDLE_FACTORY_CREATE_ID</name>
      <anchor>a4a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_HANDLE_FACTORY_DESTROY_ID</name>
      <anchor>a4a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_HANDLE_FACTORY_CLONE_ID</name>
      <anchor>a4a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_HANDLE_FACTORY_NUMBER</name>
      <anchor>a4a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/interface.h</name>
    <path>/root/Chaos/Enviroments/Repository/Descriptions/</path>
    <filename>Descriptions_2interface_8h</filename>
    <class kind="struct">interface_description_t</class>
    <member kind="typedef">
      <type>id_t</type>
      <name>interface_id_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>interface_id_t *</type>
      <name>p_interface_id_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>interface_description_t *</type>
      <name>p_interface_description_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>interface_type_t</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_DYNAMIC</name>
      <anchor>a11a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_STATIC</name>
      <anchor>a11a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_OBJECT_FACTORY</name>
      <anchor>a11a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_HANDLE_FACTORY</name>
      <anchor>a11a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_EVENT_SUPPLIER_FACTORY</name>
      <anchor>a11a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_EVENT_CONSUMER_FACTORY</name>
      <anchor>a11a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>interface_description_register</name>
      <anchor>a9</anchor>
      <arglist>(id_t id, const wchar_t *name, uint32_t type, sequence_t method_descriptions)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_description_unregister</name>
      <anchor>a10</anchor>
      <arglist>(description_reference_t description_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>interface.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>interface_8h</filename>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>interface_create</name>
      <anchor>a0</anchor>
      <arglist>(description_reference_t interface_description, sequence_t interface_methods, reference_t interface_factory, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_destroy</name>
      <anchor>a1</anchor>
      <arglist>(interface_reference_t interface_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_invoke_method</name>
      <anchor>a2</anchor>
      <arglist>(interface_reference_t interface_reference, method_id_t method_id, context_t context, computer_reference_t computer, sequence_t parameters, sequence_t return_value)</arglist>
    </member>
    <member kind="function">
      <type>method_reference_t</type>
      <name>interface_get_method_by_index</name>
      <anchor>a3</anchor>
      <arglist>(interface_reference_t interface_reference, uint32_t index)</arglist>
    </member>
    <member kind="function">
      <type>method_reference_t</type>
      <name>interface_get_method_by_id</name>
      <anchor>a4</anchor>
      <arglist>(interface_reference_t interface_reference, method_id_t method_id)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/Descriptions/interface.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Descriptions/</path>
    <filename>System_2Descriptions_2interface_8h</filename>
    <class kind="struct">interface_description_t</class>
    <member kind="typedef">
      <type>interface_description_t *</type>
      <name>p_interface_description_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>interface_type_t</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_DYNAMIC</name>
      <anchor>a11a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_STATIC</name>
      <anchor>a11a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_OBJECT_FACTORY</name>
      <anchor>a11a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_HANDLE_FACTORY</name>
      <anchor>a11a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_EVENT_SUPPLIER_FACTORY</name>
      <anchor>a11a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INTERFACE_TYPE_EVENT_CONSUMER_FACTORY</name>
      <anchor>a11a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>interface_description_reference_t</type>
      <name>interface_description_register_static</name>
      <anchor>a7</anchor>
      <arglist>(p_interface_description_t interface_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_description_unregister_static</name>
      <anchor>a8</anchor>
      <arglist>(interface_description_reference_t description_reference)</arglist>
    </member>
    <member kind="function">
      <type>interface_description_reference_t</type>
      <name>interface_description_register</name>
      <anchor>a9</anchor>
      <arglist>(p_interface_description_t interface_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>interface_description_unregister</name>
      <anchor>a10</anchor>
      <arglist>(interface_description_reference_t description_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/interface.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2interface_8h</filename>
    <class kind="struct">interface_t</class>
    <member kind="typedef">
      <type>interface_t *</type>
      <name>p_interface_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_interface_t *</type>
      <name>p_p_interface_t</name>
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
    <name>System/Static/interface.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Static/</path>
    <filename>System_2Static_2interface_8h</filename>
  </compound>
  <compound kind="file">
    <name>memory.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>memory_8h</filename>
    <class kind="struct">memory_t</class>
    <member kind="define">
      <type>#define</type>
      <name>MEMORY_GLOBAL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>memory_t *</type>
      <name>p_memory_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>memory_t</type>
      <name>memory_global</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>memory_region.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>memory__region_8h</filename>
  </compound>
  <compound kind="file">
    <name>Descriptions/method.h</name>
    <path>/root/Chaos/Enviroments/Repository/Descriptions/</path>
    <filename>Descriptions_2method_8h</filename>
    <class kind="struct">method_description_t</class>
    <member kind="typedef">
      <type>id_t</type>
      <name>method_id_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>method_id_t *</type>
      <name>p_method_id_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>method_description_t *</type>
      <name>p_method_description_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>method_type_t</name>
      <anchor>a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_DYNAMIC</name>
      <anchor>a21a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_STATIC</name>
      <anchor>a21a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_DYNAMIC_ONEWAY</name>
      <anchor>a21a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_STATIC_ONEWAY</name>
      <anchor>a21a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_OBJECT_CREATE</name>
      <anchor>a21a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_OBJECT_DESTROY</name>
      <anchor>a21a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_HANDLE_CREATE</name>
      <anchor>a21a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_HANDLE_DESTROY</name>
      <anchor>a21a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_EVENT_SUPPLIER_CREATE</name>
      <anchor>a21a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_EVENT_SUPPLIER_DESTROY</name>
      <anchor>a21a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_EVENT_CONSUMER_CREATE</name>
      <anchor>a21a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_EVENT_CONSUMER_DESTROY</name>
      <anchor>a21a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_EVENT_SUPPLIER_HANDLER</name>
      <anchor>a21a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_EVENT_CONSUMER_HANDLER</name>
      <anchor>a21a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>method_description_register_static</name>
      <anchor>a17</anchor>
      <arglist>(p_method_description_t method_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_description_unregister_static</name>
      <anchor>a18</anchor>
      <arglist>(description_reference_t description_reference)</arglist>
    </member>
    <member kind="function">
      <type>description_reference_t</type>
      <name>method_description_register</name>
      <anchor>a19</anchor>
      <arglist>(id_t id, const wchar_t *name, uint32_t type, p_void_t return_type, sequence_t parameter_descriptions, sequence_t exception_descriptions)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_description_unregister</name>
      <anchor>a20</anchor>
      <arglist>(description_reference_t description_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>method.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>method_8h</filename>
    <member kind="function">
      <type>method_reference_t</type>
      <name>method_create</name>
      <anchor>a0</anchor>
      <arglist>(description_reference_t description, computer_reference_t computer, memory_reference_t memory, p_method_function_t function, uint64_t data, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_destroy</name>
      <anchor>a1</anchor>
      <arglist>(method_reference_t method_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_invoke</name>
      <anchor>a2</anchor>
      <arglist>(method_reference_t method, context_t context, computer_reference_t computer, sequence_t return_value, sequence_t parameters)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_invoke_async</name>
      <anchor>a3</anchor>
      <arglist>(method_reference_t method, context_t context, computer_reference_t computer, sequence_t parameters, event_queue_reference_t event_queue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>method_reference_t</type>
      <name>method_create_dynamic</name>
      <anchor>a4</anchor>
      <arglist>(description_reference_t description, computer_reference_t computer, memory_reference_t memory, p_function_dynamic_t function, uint64_t data, uint32_t options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>method_reference_t</type>
      <name>method_create_object_create</name>
      <anchor>a5</anchor>
      <arglist>(description_reference_t description, computer_reference_t computer, memory_reference_t memory, p_function_object_create_t function, uint64_t data, uint32_t options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>method_reference_t</type>
      <name>method_create_object_destroy</name>
      <anchor>a6</anchor>
      <arglist>(description_reference_t description, computer_reference_t computer, memory_reference_t memory, p_function_object_destroy_t function, uint64_t data, uint32_t options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>method_reference_t</type>
      <name>method_create_event_supplier_create</name>
      <anchor>a7</anchor>
      <arglist>(description_reference_t description, computer_reference_t computer, memory_reference_t memory, p_function_event_supplier_create_t function, uint64_t data, uint32_t options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>method_reference_t</type>
      <name>method_create_event_supplier_destroy</name>
      <anchor>a8</anchor>
      <arglist>(description_reference_t description, computer_reference_t computer, memory_reference_t memory, p_function_event_supplier_destroy_t function, uint64_t data, uint32_t options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>method_reference_t</type>
      <name>method_create_event_supplier_handler</name>
      <anchor>a9</anchor>
      <arglist>(description_reference_t description, computer_reference_t computer, memory_reference_t memory, p_function_event_supplier_handler_t function, uint64_t data, uint32_t options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>method_reference_t</type>
      <name>method_create_event_consumer_handler</name>
      <anchor>a10</anchor>
      <arglist>(description_reference_t description, computer_reference_t computer, memory_reference_t memory, p_function_event_consumer_handler_t function, uint64_t data, uint32_t options)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/Descriptions/method.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Descriptions/</path>
    <filename>System_2Descriptions_2method_8h</filename>
    <class kind="struct">method_description_t</class>
    <member kind="typedef">
      <type>method_description_t *</type>
      <name>p_method_description_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>method_type_t</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_DYNAMIC</name>
      <anchor>a9a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_STATIC</name>
      <anchor>a9a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_DYNAMIC_ONEWAY</name>
      <anchor>a9a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_TYPE_STATIC_ONEWAY</name>
      <anchor>a9a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>method_description_reference_t</type>
      <name>method_description_register_static</name>
      <anchor>a5</anchor>
      <arglist>(p_method_description_t method_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_description_unregister_static</name>
      <anchor>a6</anchor>
      <arglist>(method_description_reference_t description_reference)</arglist>
    </member>
    <member kind="function">
      <type>method_description_reference_t</type>
      <name>method_description_register</name>
      <anchor>a7</anchor>
      <arglist>(p_method_description_t method_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_description_unregister</name>
      <anchor>a8</anchor>
      <arglist>(method_description_reference_t description_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/method.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2method_8h</filename>
    <class kind="struct">method_t</class>
    <member kind="typedef">
      <type>void(</type>
      <name>method_function_t</name>
      <anchor>a0</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>method_function_t *</type>
      <name>p_method_function_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>method_t *</type>
      <name>p_method_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_method_t *</type>
      <name>p_p_method_t</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>method_reference_t</type>
      <name>method_create_static</name>
      <anchor>a4</anchor>
      <arglist>(p_method_t method)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>method_destroy_static</name>
      <anchor>a5</anchor>
      <arglist>(method_reference_t method_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>object.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>object_8h</filename>
    <member kind="function">
      <type>object_reference_t</type>
      <name>object_create</name>
      <anchor>a0</anchor>
      <arglist>(class_reference_t class_reference, security_reference_t security_reference, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_destroy</name>
      <anchor>a1</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>object_clone</name>
      <anchor>a2</anchor>
      <arglist>(object_reference_t object_reference, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_invoke_method</name>
      <anchor>a3</anchor>
      <arglist>(object_reference_t object_reference, interface_reference_t interface_reference, method_id_t method_id, uint64_t handle_data, computer_reference_t computer, sequence_t return_value, sequence_t parameters)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_fire_event</name>
      <anchor>a4</anchor>
      <arglist>(object_reference_t object_reference, event_supplier_interface_reference_t interface_reference, uint64_t event_supplier_data, event_queue_reference_t event_queue, sequence_t event_data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_wait_event</name>
      <anchor>a5</anchor>
      <arglist>(object_reference_t object_reference, event_consumer_interface_reference_t interface_reference, uint64_t event_consumer_data, event_queue_reference_t event_queue, sequence_t event_data)</arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>object_get_current</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>object_get_kernel</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>object_get_data</name>
      <anchor>a8</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_set_data</name>
      <anchor>a9</anchor>
      <arglist>(object_reference_t object_reference, uint64_t data)</arglist>
    </member>
    <member kind="function">
      <type>class_reference_t</type>
      <name>object_get_class</name>
      <anchor>a10</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>object_get_interface_by_id</name>
      <anchor>a11</anchor>
      <arglist>(object_reference_t object_reference, interface_id_t interface_id)</arglist>
    </member>
    <member kind="function">
      <type>interface_reference_t</type>
      <name>object_get_interface_by_index</name>
      <anchor>a12</anchor>
      <arglist>(object_reference_t object_reference, uint32_t index)</arglist>
    </member>
    <member kind="function">
      <type>event_supplier_interface_reference_t</type>
      <name>object_get_event_supplier_interface_by_id</name>
      <anchor>a13</anchor>
      <arglist>(object_reference_t object_reference, uint32_t event_class_id)</arglist>
    </member>
    <member kind="function">
      <type>event_consumer_interface_reference_t</type>
      <name>object_get_event_consumer_interface_by_id</name>
      <anchor>a14</anchor>
      <arglist>(object_reference_t object_reference, uint32_t event_class_id)</arglist>
    </member>
    <member kind="function">
      <type>security_reference_t</type>
      <name>object_get_security</name>
      <anchor>a15</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_set_security</name>
      <anchor>a16</anchor>
      <arglist>(object_reference_t object_reference, security_reference_t security_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/object.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2object_8h</filename>
    <class kind="struct">object_t</class>
    <member kind="define">
      <type>#define</type>
      <name>OBJECT_KERNEL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>object_t *</type>
      <name>p_object_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_object_t *</type>
      <name>p_p_object</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>object_reference_t</type>
      <name>kernel_object</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/Static/object.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Static/</path>
    <filename>System_2Static_2object_8h</filename>
    <member kind="function">
      <type>object_reference_t</type>
      <name>object_create_static</name>
      <anchor>a0</anchor>
      <arglist>(p_object_t object, sequence_t parameters, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object_destroy_static</name>
      <anchor>a1</anchor>
      <arglist>(object_reference_t object_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>object_factory.h</name>
    <path>/root/Chaos/Enviroments/Repository/Interfaces/</path>
    <filename>object__factory_8h</filename>
    <class kind="struct">object_factory_interface_table_t</class>
    <member kind="typedef">
      <type>uint64_t(</type>
      <name>object_factory_create_t</name>
      <anchor>a0</anchor>
      <arglist>)(context_t context)</arglist>
    </member>
    <member kind="typedef">
      <type>object_factory_create_t *</type>
      <name>p_object_factory_create_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(</type>
      <name>object_factory_destroy_t</name>
      <anchor>a2</anchor>
      <arglist>)(context_t context, uint64_t object_data)</arglist>
    </member>
    <member kind="typedef">
      <type>object_factory_destroy_t *</type>
      <name>p_object_factory_destroy_t</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint64_t(</type>
      <name>object_factory_clone_t</name>
      <anchor>a4</anchor>
      <arglist>)(context_t context, uint64_t object_data)</arglist>
    </member>
    <member kind="typedef">
      <type>object_factory_clone_t *</type>
      <name>p_object_factory_clone_t</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_OBJECT_FACTORY_CREATE_ID</name>
      <anchor>a12a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_OBJECT_FACTORY_DESTROY_ID</name>
      <anchor>a12a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_OBJECT_FACTORY_CLONE_ID</name>
      <anchor>a12a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>METHOD_OBJECT_FACTORY_NUMBER</name>
      <anchor>a12a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void object</type>
      <name>$create</name>
      <anchor>a10</anchor>
      <arglist>(object_reference_t object)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>object_reference_t object</type>
      <name>$clone</name>
      <anchor>a11</anchor>
      <arglist>(object_reference_t object)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>quality.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>quality_8h</filename>
    <class kind="struct">resource_usage_t</class>
    <class kind="struct">quality_t</class>
    <member kind="define">
      <type>#define</type>
      <name>QUALITY_CURRENT</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>policy_t</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>POLICY_UNSPECIFIED</name>
      <anchor>a8a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>POLICY_CONSTANT</name>
      <anchor>a8a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>POLICY_REALTIME_VARIABLE</name>
      <anchor>a8a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>POLICY_NON_REALTIME_VARIABLE</name>
      <anchor>a8a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>POLICY_AVAILABLE</name>
      <anchor>a8a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>quality_set</name>
      <anchor>a6</anchor>
      <arglist>(quality_reference_t quality_reference, uint32_t delay)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>quality_reset</name>
      <anchor>a7</anchor>
      <arglist>(quality_reference_t quality_reference)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Descriptions/reference.h</name>
    <path>/root/Chaos/Enviroments/Repository/Descriptions/</path>
    <filename>Descriptions_2reference_8h</filename>
    <class kind="struct">description_reference_struct_t</class>
    <member kind="typedef">
      <type>description_reference_struct_t *</type>
      <name>p_description_reference_struct_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>description_reference_type_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_DATA</name>
      <anchor>a7a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_EXCEPTION</name>
      <anchor>a7a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_EVENT</name>
      <anchor>a7a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_METHOD</name>
      <anchor>a7a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_INTERFACE</name>
      <anchor>a7a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_CLASS</name>
      <anchor>a7a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>reference.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>reference_8h</filename>
    <member kind="enumeration">
      <name>reference_type_t</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_METHOD</name>
      <anchor>a20a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_INTERFACE</name>
      <anchor>a20a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_CLASS</name>
      <anchor>a20a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_SECURITY</name>
      <anchor>a20a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_OBJECT</name>
      <anchor>a20a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_HANDLE</name>
      <anchor>a20a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_EVENT_SUPPLIER_INTERFACE</name>
      <anchor>a20a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_EVENT_SUPPLIER</name>
      <anchor>a20a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_EVENT_CONSUMER_INTERFACE</name>
      <anchor>a20a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_EVENT_CONSUMER</name>
      <anchor>a20a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>REFERENCE_TYPE_EVENT_QUEUE</name>
      <anchor>a20a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>reference_t</type>
      <name>reference_acquire</name>
      <anchor>a11</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reference_release</name>
      <anchor>a12</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>reference_get_type</name>
      <anchor>a13</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>object_reference_t</type>
      <name>reference_get_owner</name>
      <anchor>a14</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reference_set_owner</name>
      <anchor>a15</anchor>
      <arglist>(reference_t reference, object_reference_t object_reference)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>reference_get_number_of_references</name>
      <anchor>a16</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>reference_is_nill</name>
      <anchor>a17</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>reference_is_exists</name>
      <anchor>a18</anchor>
      <arglist>(reference_t reference)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>reference_equals</name>
      <anchor>a19</anchor>
      <arglist>(reference_t reference, reference_t reference2)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/Descriptions/reference.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/Descriptions/</path>
    <filename>System_2Descriptions_2reference_8h</filename>
    <class kind="struct">description_reference_struct_t</class>
    <member kind="typedef">
      <type>void *</type>
      <name>description_reference_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>description_reference_struct_t *</type>
      <name>p_description_reference_struct_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>description_reference_type_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_DATA</name>
      <anchor>a7a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_EXCEPTION</name>
      <anchor>a7a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_METHOD</name>
      <anchor>a7a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_INTERFACE</name>
      <anchor>a7a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DESCRIPTION_REFERENCE_TYPE_CLASS</name>
      <anchor>a7a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>System/reference.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>System_2reference_8h</filename>
    <class kind="struct">reference_struct_t</class>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_NULL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_METHOD</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_INTERFACE</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_CLASS</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_SECURITY</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_OBJECT</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_HANDLE</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_EVENT_SUPPLIER_INTERFACE</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_EVENT_CONSUMER_INTERFACE</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_EVENT_SUPPLIER</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_EVENT_CONSUMER</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_MAGIC_NUMBER_EVENT_QUEUE</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_struct_t *</type>
      <name>p_reference_struct_t</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>repository.h</name>
    <path>/root/Chaos/Enviroments/Repository/</path>
    <filename>repository_8h</filename>
    <includes id="System_2reference_8h" name="System/reference.h" local="yes">System/reference.h</includes>
    <includes id="reference_8h" name="reference.h" local="yes">reference.h</includes>
    <includes id="context_8h" name="context.h" local="yes">context.h</includes>
    <includes id="function_8h" name="function.h" local="yes">function.h</includes>
    <includes id="Descriptions_2reference_8h" name="Descriptions/reference.h" local="yes">Descriptions/reference.h</includes>
    <includes id="Descriptions_2data_8h" name="Descriptions/data.h" local="yes">Descriptions/data.h</includes>
    <includes id="exception_8h" name="exception.h" local="yes">System/Descriptions/exception.h</includes>
    <includes id="Descriptions_2method_8h" name="Descriptions/method.h" local="yes">Descriptions/method.h</includes>
    <includes id="event_8h" name="event.h" local="yes">Descriptions/event.h</includes>
    <includes id="Descriptions_2interface_8h" name="Descriptions/interface.h" local="yes">Descriptions/interface.h</includes>
    <includes id="Descriptions_2class_8h" name="Descriptions/class.h" local="yes">Descriptions/class.h</includes>
    <includes id="security_8h" name="security.h" local="yes">System/security.h</includes>
    <includes id="System_2method_8h" name="System/method.h" local="yes">System/method.h</includes>
    <includes id="method_8h" name="method.h" local="yes">method.h</includes>
    <includes id="System_2interface_8h" name="System/interface.h" local="yes">System/interface.h</includes>
    <includes id="interface_8h" name="interface.h" local="yes">interface.h</includes>
    <includes id="System_2class_8h" name="System/class.h" local="yes">System/class.h</includes>
    <includes id="class_8h" name="class.h" local="yes">class.h</includes>
    <includes id="System_2object_8h" name="System/object.h" local="yes">System/object.h</includes>
    <includes id="System_2Static_2object_8h" name="System/Static/object.h" local="yes">System/Static/object.h</includes>
    <includes id="object_8h" name="object.h" local="yes">object.h</includes>
    <includes id="System_2handle_8h" name="System/handle.h" local="yes">System/handle.h</includes>
    <includes id="handle_8h" name="handle.h" local="yes">handle.h</includes>
    <includes id="quality_8h" name="quality.h" local="yes">System/quality.h</includes>
    <includes id="cpu_8h" name="cpu.h" local="yes">System/cpu.h</includes>
    <includes id="memory_8h" name="memory.h" local="yes">System/memory.h</includes>
    <includes id="System_2computer_8h" name="System/computer.h" local="yes">System/computer.h</includes>
    <includes id="computer_8h" name="computer.h" local="yes">computer.h</includes>
    <includes id="System_2event__supplier__interface_8h" name="System/event_supplier_interface.h" local="yes">System/event_supplier_interface.h</includes>
    <includes id="event__supplier__interface_8h" name="event_supplier_interface.h" local="yes">event_supplier_interface.h</includes>
    <includes id="System_2event__consumer__interface_8h" name="System/event_consumer_interface.h" local="yes">System/event_consumer_interface.h</includes>
    <includes id="event__consumer__interface_8h" name="event_consumer_interface.h" local="yes">event_consumer_interface.h</includes>
    <includes id="System_2event__queue_8h" name="System/event_queue.h" local="yes">System/event_queue.h</includes>
    <includes id="event__queue_8h" name="event_queue.h" local="yes">event_queue.h</includes>
    <includes id="System_2event__supplier_8h" name="System/event_supplier.h" local="yes">System/event_supplier.h</includes>
    <includes id="System_2Static_2event__supplier_8h" name="System/Static/event_supplier.h" local="yes">System/Static/event_supplier.h</includes>
    <includes id="event__supplier_8h" name="event_supplier.h" local="yes">event_supplier.h</includes>
    <includes id="System_2event__consumer_8h" name="System/event_consumer.h" local="yes">System/event_consumer.h</includes>
    <includes id="event__consumer_8h" name="event_consumer.h" local="yes">event_consumer.h</includes>
    <includes id="object__factory_8h" name="object_factory.h" local="yes">Interfaces/object_factory.h</includes>
    <includes id="handle__factory_8h" name="handle_factory.h" local="yes">Interfaces/handle_factory.h</includes>
    <includes id="event__supplier__factory_8h" name="event_supplier_factory.h" local="yes">Interfaces/event_supplier_factory.h</includes>
    <includes id="event__consumer__factory_8h" name="event_consumer_factory.h" local="yes">Interfaces/event_consumer_factory.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>ID_NONE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>REFERENCE_NULL</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>id_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void *</type>
      <name>reference_t</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t *</type>
      <name>p_reference_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>description_reference_t</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>event_class_reference_t</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>event_class_reference_t *</type>
      <name>p_event_class_reference_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>event_supplier_interface_reference_t</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>event_supplier_interface_reference_t *</type>
      <name>p_event_supplier_interface_reference_t</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>event_consumer_interface_reference_t</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>event_consumer_interface_reference_t *</type>
      <name>p_event_consumer_interface_reference_t</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>class_reference_t</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>class_reference_t *</type>
      <name>p_class_reference_t</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>object_reference_t</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>object_reference_t *</type>
      <name>p_object_reference_t</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>handle_reference_t</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>handle_reference_t *</type>
      <name>p_handle_reference_t</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>event_supplier_reference_t</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>event_supplier_reference_t *</type>
      <name>p_event_supplier_reference_t</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>event_consumer_reference_t</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>event_consumer_reference_t *</type>
      <name>p_event_consumer_reference_t</name>
      <anchor>a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>event_queue_reference_t</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>event_queue_reference_t *</type>
      <name>p_event_queue_reference_t</name>
      <anchor>a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>quality_reference_t</name>
      <anchor>a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>exception_reference_t</name>
      <anchor>a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>method_reference_t</name>
      <anchor>a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>interface_reference_t</name>
      <anchor>a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>interface_reference_t *</type>
      <name>p_interface_reference_t</name>
      <anchor>a28</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>exception_reference_t *</type>
      <name>p_exception_reference_t</name>
      <anchor>a29</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>security_reference_t</name>
      <anchor>a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>security_reference_t *</type>
      <name>p_security_reference_t</name>
      <anchor>a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>cpu_reference_t</name>
      <anchor>a32</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>cpu_reference_t *</type>
      <name>p_cpu_reference_t</name>
      <anchor>a33</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>memory_reference_t</name>
      <anchor>a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>memory_reference_t *</type>
      <name>p_memory_reference_t</name>
      <anchor>a35</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>reference_t</type>
      <name>computer_reference_t</name>
      <anchor>a36</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>computer_reference_t *</type>
      <name>p_computer_reference_t</name>
      <anchor>a37</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>memory_allocate</name>
      <anchor>a38</anchor>
      <arglist>(void **pointer, unsigned int size)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>memory_deallocate</name>
      <anchor>a39</anchor>
      <arglist>(void *pointer)</arglist>
    </member>
    <member kind="function">
      <type>return_t</type>
      <name>repository_init</name>
      <anchor>a40</anchor>
      <arglist>(int argc, char *argv[], char **envp)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>security.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>security_8h</filename>
    <class kind="struct">generic_acl_t</class>
    <class kind="struct">method_acl_t</class>
    <class kind="struct">interface_acl_t</class>
    <class kind="struct">class_acl_t</class>
    <class kind="struct">object_acl_t</class>
    <class kind="struct">handle_acl_t</class>
    <class kind="struct">user_acl_t</class>
    <class kind="struct">security_t</class>
    <member kind="define">
      <type>#define</type>
      <name>SECURITY_ABSOLUTE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>generic_acl_t *</type>
      <name>p_generic_acl_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>method_acl_t *</type>
      <name>p_method_acl_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>interface_acl_t *</type>
      <name>p_interface_acl_t</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>class_acl_t *</type>
      <name>p_class_acl_t</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>object_acl_t *</type>
      <name>p_object_acl_t</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>handle_acl_t *</type>
      <name>p_handle_acl_t</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>security_t *</type>
      <name>p_security_t</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>security_reference_t</type>
      <name>security_create_static</name>
      <anchor>a9</anchor>
      <arglist>(p_security_t security)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_destroy_static</name>
      <anchor>a10</anchor>
      <arglist>(security_reference_t security)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_clone_static</name>
      <anchor>a11</anchor>
      <arglist>(security_reference_t security, security_reference_t new_security, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>security_reference_t</type>
      <name>security_create</name>
      <anchor>a12</anchor>
      <arglist>(bool security_is_absolute, p_generic_acl_t generic_acl)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>security_destroy</name>
      <anchor>a13</anchor>
      <arglist>(security_reference_t security)</arglist>
    </member>
    <member kind="function">
      <type>security_reference_t</type>
      <name>security_get_current</name>
      <anchor>a14</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>security_reference_t</type>
      <name>security_clone</name>
      <anchor>a15</anchor>
      <arglist>(security_reference_t security, uint32_t options)</arglist>
    </member>
    <member kind="variable">
      <type>security_t</type>
      <name>security_absolute</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>transaction.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>transaction_8h</filename>
    <class kind="struct">transaction_control_t</class>
    <class kind="struct">transaction_t</class>
    <member kind="typedef">
      <type>transaction_t *</type>
      <name>p_transaction_t</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CLASS_TYPE_STATIC</name>
      <anchor>a10a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CLASS_TYPE_DYNAMIC</name>
      <anchor>a10a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>transaction_reference_t</type>
      <name>transaction_create_static</name>
      <anchor>a3</anchor>
      <arglist>(p_transaction_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_destroy_static</name>
      <anchor>a4</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>transaction_reference_t</type>
      <name>transaction_create</name>
      <anchor>a5</anchor>
      <arglist>(sequence_t filtered_objects, sequence_t ignored_objects, uint32_t history_depth, uint32_t options)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_destroy</name>
      <anchor>a6</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_begin</name>
      <anchor>a7</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_commit</name>
      <anchor>a8</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transaction_rollback</name>
      <anchor>a9</anchor>
      <arglist>(transaction_reference_t transaction)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>virtual_cpu.h</name>
    <path>/root/Chaos/Enviroments/Repository/System/</path>
    <filename>virtual__cpu_8h</filename>
    <class kind="struct">virtual_cpu_t</class>
    <member kind="define">
      <type>#define</type>
      <name>VIRTUAL_CPU_CURRENT</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>virtual_cpu_t *</type>
      <name>p_virtual_cpu_t</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>p_virtual_cpu_t *</type>
      <name>p_p_virtual_cpu_t</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>virtual_cpu_reference_t</type>
      <name>virtual_cpu_create</name>
      <anchor>a3</anchor>
      <arglist>(uint32_t cpu_policy, resource_usage_t cpu_usage)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>virtual_cpu_destroy</name>
      <anchor>a4</anchor>
      <arglist>(virtual_cpu_reference_t virtual_cpu)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>virtual_cpu_sleep_milli</name>
      <anchor>a5</anchor>
      <arglist>(virtual_cpu_reference_t virtual_cpu, uint32_t milliseconds)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>virtual_cpu_sleep_micro</name>
      <anchor>a6</anchor>
      <arglist>(virtual_cpu_reference_t virtual_cpu, uint32_t microseconds)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>virtual_cpu_time_read_milli</name>
      <anchor>a7</anchor>
      <arglist>(virtual_cpu_reference_t virtual_cpu)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>class_acl_t</name>
    <filename>structclass__acl__t.html</filename>
    <member kind="variable">
      <type>class_reference_t</type>
      <name>reference</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>destroy</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>set_interfaces</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>get_interfaces</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>get_interface</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>__pad0__</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>class_description_t</name>
    <filename>structclass__description__t.html</filename>
    <member kind="variable">
      <type>description_reference_struct_t</type>
      <name>header</name>
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
      <type>uint32_t</type>
      <name>type</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_interfaces</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_event_suppliers</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_event_consumers</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>class_t</name>
    <filename>structclass__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_class_description_t</type>
      <name>description</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>interfaces</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>event_supplier_interfaces</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>event_consumer_interfaces</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>object_factory</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>handle_factory</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>state_monitor</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>security_monitor</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>quality_control</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>transaction_control</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>computer_node_t</name>
    <filename>structcomputer__node__t.html</filename>
    <member kind="variable">
      <type>list_node_t</type>
      <name>node</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_void_t</type>
      <name>computer</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>computer_t</name>
    <filename>structcomputer__t.html</filename>
    <member kind="variable">
      <type>volatile uint32_t</type>
      <name>state</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_cpu_t</type>
      <name>cpu</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_memory_t</type>
      <name>memory</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_security_t</type>
      <name>security</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_task_state_t</type>
      <name>task_state</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_uint8_t</type>
      <name>stack</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_method_t</type>
      <name>method</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_method_t</type>
      <name>method_invoker</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_interface_t</type>
      <name>interface</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_interface_t</type>
      <name>interface_invoker</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_class_t</type>
      <name>class</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_class_t</type>
      <name>class_invoker</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_object_t</type>
      <name>object</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_object_t</type>
      <name>object_invoker</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_handle_t</type>
      <name>handle</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_handle_t</type>
      <name>handle_invoker</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>list_t</type>
      <name>exception_context_stack</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>exception_top</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>computer_t *</type>
      <name>upper</name>
      <anchor>o18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>computer_t *</type>
      <name>nested</name>
      <anchor>o19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>computer_node_t</type>
      <name>node</name>
      <anchor>o20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>upper_is_sync</name>
      <anchor>o21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>nested_is_sync</name>
      <anchor>o22</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>constraint_t</name>
    <filename>structconstraint__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constraint_reference_t</type>
      <name>parent</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>list_t</type>
      <name>childs</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>context_t</name>
    <filename>structcontext__t.html</filename>
    <member kind="variable">
      <type>uint64_t</type>
      <name>object_data</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>handle_data</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_array_t</name>
    <filename>structcpu__array__t.html</filename>
    <member kind="variable">
      <type>sequence_t</type>
      <name>cpus</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cpu_t</name>
    <filename>structcpu__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>performance</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>resource_usage_t</type>
      <name>usage</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>list_t</type>
      <name>virtuals</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>data_description_t</name>
    <filename>structdata__description__t.html</filename>
    <member kind="variable">
      <type>description_reference_struct_t</type>
      <name>header</name>
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
      <name>size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>description_reference_struct_t</name>
    <filename>structdescription__reference__struct__t.html</filename>
    <member kind="variable">
      <type></type>
      <name>HASH_ELEMENT_PART</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>id_t</type>
      <name>id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>magic_number</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_references</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>is_static</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>event_class_t</name>
    <filename>structevent__class__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_class_description_t</type>
      <name>description</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>event_consumer_interface_t</name>
    <filename>structevent__consumer__interface__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_description_t</type>
      <name>event_description</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>type</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_method_t</type>
      <name>handle</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>reference_t</type>
      <name>factory</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>factory_type</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>event_consumer_t</name>
    <filename>structevent__consumer__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>data</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_object_t</type>
      <name>object</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_consumer_interface_t</type>
      <name>interface</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_queue_t</type>
      <name>queue</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>event_description_t</name>
    <filename>structevent__description__t.html</filename>
    <member kind="variable">
      <type>description_reference_struct_t</type>
      <name>header</name>
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
      <type>uint32_t</type>
      <name>data_length</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>event_queue_t</name>
    <filename>structevent__queue__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_description_t</type>
      <name>event_class</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>type</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>capacity</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_supplier_interface_t</type>
      <name>supplier</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_consumer_interface_t</type>
      <name>consumer</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>buffer_head</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>buffer_tail</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>countlock_t</type>
      <name>buffer_count</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_losted_events</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>last_lost_event_time</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>last_fired_event_time</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>event_supplier_factory_interface_table_t</name>
    <filename>structevent__supplier__factory__interface__table__t.html</filename>
    <member kind="variable">
      <type>p_event_supplier_factory_create_t</type>
      <name>create</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_supplier_factory_destroy_t</type>
      <name>destroy</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>event_supplier_interface_t</name>
    <filename>structevent__supplier__interface__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_description_t</type>
      <name>event_description</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>type</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_method_t</type>
      <name>handle</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>reference_t</type>
      <name>factory</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>factory_type</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>event_supplier_t</name>
    <filename>structevent__supplier__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>data</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_object_t</type>
      <name>object</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_supplier_interface_t</type>
      <name>interface</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_event_queue_t</type>
      <name>queue</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>generic_acl_t</name>
    <filename>structgeneric__acl__t.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>method_create</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>method_destroy</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>method_invoke</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>interface_create</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>interface_destroy</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>class_create</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>class_destroy</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>object_create</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>object_destroy</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>handle_create</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>handle_destroy</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>security_create</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>security_destroy</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>__pad0__</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>group_t</name>
    <filename>structgroup__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>objects</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>handle_acl_t</name>
    <filename>structhandle__acl__t.html</filename>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>handle</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>destroy</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>__pad0__</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>handle_t</name>
    <filename>structhandle__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>data</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_object_t</type>
      <name>object</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_interface_t</type>
      <name>interface</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>interface_acl_t</name>
    <filename>structinterface__acl__t.html</filename>
    <member kind="variable">
      <type>interface_reference_t</type>
      <name>reference</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>destroy</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>__pad0__</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>interface_description_t</name>
    <filename>structinterface__description__t.html</filename>
    <member kind="variable">
      <type>description_reference_struct_t</type>
      <name>header</name>
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
      <type>uint32_t</type>
      <name>type</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>method_descriptions</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>interface_t</name>
    <filename>structinterface__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_interface_description_t</type>
      <name>description</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>methods</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>reference_t</type>
      <name>factory</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>invoke_record_t</name>
    <filename>structinvoke__record__t.html</filename>
    <member kind="variable">
      <type>p_handle_t</type>
      <name>handle</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_object_t</type>
      <name>object</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_class_t</type>
      <name>class</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_interface_t</type>
      <name>interface</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_method_t</type>
      <name>method</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>parameters_in</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>parameters_inout</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>parameters_out</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>memory_t</name>
    <filename>structmemory__t.html</filename>
    <member kind="variable">
      <type>bool</type>
      <name>is_virtual</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>method_acl_t</name>
    <filename>structmethod__acl__t.html</filename>
    <member kind="variable">
      <type>method_reference_t</type>
      <name>reference</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>destroy</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>invoke</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>__pad0__</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>method_description_t</name>
    <filename>structmethod__description__t.html</filename>
    <member kind="variable">
      <type>description_reference_struct_t</type>
      <name>header</name>
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
      <type>uint32_t</type>
      <name>type</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_void_t</type>
      <name>return_type</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>parameter_descriptions</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>exception_descriptions</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_data_description_t</type>
      <name>return_type</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>method_t</name>
    <filename>structmethod__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_method_description_t</type>
      <name>description</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>computer_reference_t</type>
      <name>computer</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>memory_reference_t</type>
      <name>memory</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_method_function_t</type>
      <name>function</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>data</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_acl_t</name>
    <filename>structobject__acl__t.html</filename>
    <member kind="variable">
      <type>object_reference_t</type>
      <name>object</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>destroy</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>__pad0__</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_factory_interface_table_t</name>
    <filename>structobject__factory__interface__table__t.html</filename>
    <member kind="variable">
      <type>p_object_factory_create_t</type>
      <name>create</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_object_factory_destroy_t</type>
      <name>destroy</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_object_factory_clone_t</type>
      <name>clone</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>object_t</name>
    <filename>structobject__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>list_t</type>
      <name>childs</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>data</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_class_t</type>
      <name>class</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_security_t</type>
      <name>security</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>parameter_description_t</name>
    <filename>structparameter__description__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>attribute</name>
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
      <name>size</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>quality_t</name>
    <filename>structquality__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>lost_probability</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>time_delay</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>latency</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>reference_struct_t</name>
    <filename>structreference__struct__t.html</filename>
    <member kind="variable">
      <type>list_node_t</type>
      <name>node</name>
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
      <name>magic_number</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>object_reference_t</type>
      <name>owner</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>atomic_uint32_t</type>
      <name>number_of_references</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>spinlock_t</type>
      <name>lock</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>is_static</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>resource_usage_t</name>
    <filename>structresource__usage__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>max</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>average</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>min</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>max_burst</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>security_t</name>
    <filename>structsecurity__t.html</filename>
    <member kind="variable">
      <type>reference_struct_t</type>
      <name>header</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>is_absolute</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_generic_acl_t</type>
      <name>generic_acl</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>exception_acls</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>method_acls</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>interface_acls</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>class_acls</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>object_acls</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>handle_acls</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>user_acls</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>transaction_control_t</name>
    <filename>structtransaction__control__t.html</filename>
    <member kind="variable">
      <type>handle_reference_t</type>
      <name>handle</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_void_t</type>
      <name>data</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>transaction_t</name>
    <filename>structtransaction__t.html</filename>
    <member kind="variable">
      <type></type>
      <name>HASH_ELEMENT_PART</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>class_id_t</type>
      <name>id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>name</name>
      <anchor>o2</anchor>
      <arglist>[STRING_MAX_LENGTH]</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>number_of_references</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>is_static</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>is_active</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>filtered_objects</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>ignored_objects</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>transaction_controls</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>slot</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sequence_t</type>
      <name>history</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>type_sequence_info_t</name>
    <filename>structtype__sequence__info__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>max_count</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>element_size</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>user_acl_t</name>
    <filename>structuser__acl__t.html</filename>
    <member kind="variable">
      <type>object_reference_t</type>
      <name>object</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>interface_reference_t</type>
      <name>interface</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>method_reference_t</type>
      <name>method</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>data</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>virtual_cpu_t</name>
    <filename>structvirtual__cpu__t.html</filename>
    <member kind="variable">
      <type></type>
      <name>LIST_NODE_PART</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>p_cpu_t</type>
      <name>cpu</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>policy</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>resource_usage_t</type>
      <name>usage</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>first_tick</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>last_tick</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
