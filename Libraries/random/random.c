/* $Id: random.c,v 1.1.1.1 2000/09/26 19:08:08 plundis Exp $ */
/* Abstract: Library for calculating random numbers. */
/* Authors: Per Lundberg <plundis@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include "random.h"

/* The algorithm is pretty pathetic right now, but it's better than
   nothing... */

static volatile int random_seed = 0;

/* Initialise the random seed. */

return_t random_init (int seed)
{
  random_seed = seed;

  return RANDOM_RETURN_SUCCESS;
}

/* Get a random number with max size max in *output. */

int random (int max)
{
  random_seed = (random_seed * 12345 + 67892);
  //  random_seed &= 0xFFFF;

  max++;

  return random_seed;
}
