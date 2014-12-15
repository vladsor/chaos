
#define spin_lock_irqsave(x, flags) \
	do { cpu_flags_save (flags); cpu_interrupts_disable (); (*x) = SPIN_LOCKED;} while (0)

#define spin_unlock_irqrestore(x, flags) \
	do { (*x) = SPIN_UNLOCKED; cpu_flags_load (flags); } while (0)
