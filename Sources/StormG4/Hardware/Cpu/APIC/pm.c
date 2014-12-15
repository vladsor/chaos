
static struct {
	/* 'active' is true if the local APIC was enabled by us and
	   not the BIOS; this signifies that we are also responsible
	   for disabling it before entering apm/acpi suspend */
	int active;
	/* 'perfctr_pmdev' is here because the current (2.4.1) PM
	   callback system doesn't handle hierarchical dependencies */
	struct pm_dev *perfctr_pmdev;
	/* r/w apic fields */
	unsigned int apic_id;
	unsigned int apic_taskpri;
	unsigned int apic_ldr;
	unsigned int apic_dfr;
	unsigned int apic_spiv;
	unsigned int apic_lvtt;
	unsigned int apic_lvtpc;
	unsigned int apic_lvt0;
	unsigned int apic_lvt1;
	unsigned int apic_lvterr;
	unsigned int apic_tmict;
	unsigned int apic_tdcr;
} apic_pm_state;

static void apic_pm_suspend(void *data)
{
	unsigned int l, h;
	unsigned long flags;

	if (apic_pm_state.perfctr_pmdev)
		pm_send(apic_pm_state.perfctr_pmdev, PM_SUSPEND, data);
	apic_pm_state.apic_id = apic_read(APIC_ID);
	apic_pm_state.apic_taskpri = apic_read(APIC_TASKPRI);
	apic_pm_state.apic_ldr = apic_read(APIC_LDR);
	apic_pm_state.apic_dfr = apic_read(APIC_DFR);
	apic_pm_state.apic_spiv = apic_read(APIC_SPIV);
	apic_pm_state.apic_lvtt = apic_read(APIC_LVTT);
	apic_pm_state.apic_lvtpc = apic_read(APIC_LVTPC);
	apic_pm_state.apic_lvt0 = apic_read(APIC_LVT0);
	apic_pm_state.apic_lvt1 = apic_read(APIC_LVT1);
	apic_pm_state.apic_lvterr = apic_read(APIC_LVTERR);
	apic_pm_state.apic_tmict = apic_read(APIC_TMICT);
	apic_pm_state.apic_tdcr = apic_read(APIC_TDCR);
	__save_flags(flags);
	__cli();
	disable_local_APIC();
	rdmsr(MSR_IA32_APICBASE, l, h);
	l &= ~MSR_IA32_APICBASE_ENABLE;
	wrmsr(MSR_IA32_APICBASE, l, h);
	__restore_flags(flags);
}

static void apic_pm_resume(void *data)
{
	unsigned int l, h;
	unsigned long flags;

	__save_flags(flags);
	__cli();
	rdmsr(MSR_IA32_APICBASE, l, h);
	l &= ~MSR_IA32_APICBASE_BASE;
	l |= MSR_IA32_APICBASE_ENABLE | APIC_DEFAULT_PHYS_BASE;
	wrmsr(MSR_IA32_APICBASE, l, h);
	apic_write(APIC_ID, apic_pm_state.apic_id);
	apic_write(APIC_DFR, apic_pm_state.apic_dfr);
	apic_write(APIC_LDR, apic_pm_state.apic_ldr);
	apic_write(APIC_TASKPRI, apic_pm_state.apic_taskpri);
	apic_write(APIC_SPIV, apic_pm_state.apic_spiv);
	apic_write(APIC_LVT0, apic_pm_state.apic_lvt0);
	apic_write(APIC_LVT1, apic_pm_state.apic_lvt1);
	apic_write(APIC_ESR, 0);
	apic_read(APIC_ESR);
	apic_write(APIC_LVTERR, apic_pm_state.apic_lvterr);
	apic_write(APIC_ESR, 0);
	apic_read(APIC_ESR);
	apic_write(APIC_LVTPC, apic_pm_state.apic_lvtpc);
	apic_write(APIC_LVTT, apic_pm_state.apic_lvtt);
	apic_write(APIC_TDCR, apic_pm_state.apic_tdcr);
	apic_write(APIC_TMICT, apic_pm_state.apic_tmict);
	__restore_flags(flags);
	if (apic_pm_state.perfctr_pmdev)
		pm_send(apic_pm_state.perfctr_pmdev, PM_RESUME, data);
}

static int apic_pm_callback(struct pm_dev *dev, pm_request_t rqst, void *data)
{
	switch (rqst) {
	case PM_SUSPEND:
		apic_pm_suspend(data);
		break;
	case PM_RESUME:
		apic_pm_resume(data);
		break;
	}
	return 0;
}

/* perfctr driver should call this instead of pm_register() */
struct pm_dev *apic_pm_register(pm_dev_t type,
				unsigned long id,
				pm_callback callback)
{
	struct pm_dev *dev;

	if (!apic_pm_state.active)
		return pm_register(type, id, callback);
	if (apic_pm_state.perfctr_pmdev)
		return NULL;	/* we're busy */
	dev = kmalloc(sizeof(struct pm_dev), GFP_KERNEL);
	if (dev) {
		memset(dev, 0, sizeof(*dev));
		dev->type = type;
		dev->id = id;
		dev->callback = callback;
		apic_pm_state.perfctr_pmdev = dev;
	}
	return dev;
}

/* perfctr driver should call this instead of pm_unregister() */
void apic_pm_unregister(struct pm_dev *dev)
{
	if (!apic_pm_state.active) {
		pm_unregister(dev);
	} else if (dev == apic_pm_state.perfctr_pmdev) {
		apic_pm_state.perfctr_pmdev = NULL;
		kfree(dev);
	}
}

static void apic_pm_init1(void)
{
	/* can't pm_register() at this early stage in the boot process
	   (causes an immediate reboot), so just set the flag */
	apic_pm_state.active = 1;
}

static void apic_pm_init2(void)
{
	if (apic_pm_state.active)
		pm_register(PM_SYS_DEV, 0, apic_pm_callback);
}

