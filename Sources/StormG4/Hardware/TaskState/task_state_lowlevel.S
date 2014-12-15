.globl task_state_switch_finish
.globl task_state_switch_finish2
.globl task_state_switch_finish_internal
.extern jump_data

task_state_switch_finish:
	ljmp *jump_data

task_state_switch_finish2:
	pushal
	call task_state_switch_finish_internal
	popal
	iret
