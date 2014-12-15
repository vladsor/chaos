/**
 * @file                Common/ia32/Cpu/bugs.h 
 * @brief               Definitions of cpu bugs.
 * @author              Vladimir Sorokin
 * @version             1.3
 * @date                2000-2004
 */

/* Copyright: chaos development. */

/** 
 * @addtogroup group_cpu
 *
 * @{
 */

#ifndef __ENVIROMENT_COMMON_IA32_CPU_BUGS_H_
#define __ENVIROMENT_COMMON_IA32_CPU_BUGS_H_

/**
 * @brief               Bugs founded in CPU.
 */
enum cpu_bug_t
{
    CPU_BUG_POPAD,
    CPU_BUG_F0_0F,

    CPU_BUG_LAST,
};

/**
 * @brief               Total number of bugs.
 */
#define NUMBER_OF_BUGS		(CPU_BUG_LAST)

#endif /* !__ENVIROMENT_COMMON_IA32_CPU_BUGS_H_ */

/**
 * }@ // end of group group_cpu
 */

