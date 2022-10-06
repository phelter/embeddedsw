/******************************************************************************
* Copyright (c) 2009 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/* The errno variable is stored in the reentrancy structure.  This
   function returns its address for use by the macro errno defined in
   errno.h.  */

#include <errno.h>
#include "xil_types.h"

__attribute__((weak)) sint32 * __errno (void);

__attribute__((weak)) sint32 *__errno (void)
{
  return NULL;
}
