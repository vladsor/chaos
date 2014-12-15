
#include "../Enviroments/Common/common_enviroment.h"

#if defined (__STORM_KERNEL__)
#    include "../Sources/configuration.h"
#    include "../Enviroments/System/system_enviroment.h"
#    include "../Enviroments/Kernel/kernel.h"
#    include "../Enviroments/Repository/repository.h"
#elif defined (__STORM_KERNEL_MODULE__)
#    include "../Enviroments/System/system_enviroment.h"
/**
 * @todo remove kernel enviroment from this
 */
#    include "../Enviroments/Kernel/kernel.h"
#    include "../Enviroments/Repository/repository.h"
#    include "modules.h"
#elif defined (__STORM_PROGRAM__)
//#    include "../Libraries/system_enviroment/user_enviroment.h"
//#    include "system_call.h"
//#    include "../Enviroments/Repository/repository.h"
#else
#error "Unknown object target"
#endif

