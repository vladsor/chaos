/**
 * @file                float.c
 * @brief               Functions for working with float.
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2000-2003
 */

#include <enviroment.h>
#include "string.h"

unsigned int float_is_special (double float_number)
{
  /* IEEE standard number rapresentation */
  register struct IEEEdp
  {
    unsigned manl : 32;
    unsigned manh : 20;
    unsigned exp  : 11;
    unsigned sign : 1;
  } *ip = (struct IEEEdp *) &float_number;

  if (ip->exp != 0x7ff)
  {
    return FLOAT_NORMAL;
  }
  
  if (ip->manh || ip->manl)
  {
    return FLOAT_NAN;
  }
  else if (ip->sign)
  {
    return FLOAT_PLUS_INFINITE;
  } 

  return FLOAT_MINUS_INFINITE;
}
