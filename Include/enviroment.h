
#include "../Enviroments/Common/common_enviroment.h"

#if defined (__STORM_KERNEL__)
#    include "../Enviroments/System/system_enviroment.h"
#    include "storm.h"
#elif defined (__STORM_KERNEL_MODULE__)
#    include "../Enviroments/System/system_enviroment.h"
#    include "modules.h"
#else
//#    include "../Libraries/system_enviroment/user_enviroment.h"
//#    include "system_call.h"
#error "Unknown object target"
#endif
