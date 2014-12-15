
#include "ia32/cpu_common.h"
#include "ia32/system_registers.h"

#ifdef FPU_ENABLED
# include "ia32/fpu.h"
#endif

#include "ia32/descriptor.h"
#include "ia32/selectors.h"
#include "ia32/page.h"
#include "ia32/limits.h"
#include "ia32/exceptions.h"
#include "ia32/locks.h"

#include "limits.h"
