/*
  (c) Copyright 2017 Michael R. Neilly
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  * Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  * Neither the names of the copyright holders nor the names of their
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include <math.h>
#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/fegetenv.html
 * Referred to as 'fegetenv.html below.
 *
 * "The fegetenv() function shall attempt to store the current
 * floating-point environment in the object pointed to by envp.
 *
 * The fesetenv() function shall attempt to establish the
 * floating-point environment represented by the object pointed to by
 * envp. The argument envp shall point to an object set by a call to
 * fegetenv() or feholdexcept(), or equal a floating-point environment
 * macro. The fesetenv() function does not raise floating-point
 * exceptions, but only installs the state of the floating-point
 * status flags represented through its argument."
 */

#if __RISCV_HARD_FLOAT

int fesetenv(const fenv_t *envp)
{

  /* Set environment (FCSR) */

  fenv_t fcsr = *envp;
  __asm__ volatile("fscsr %0" : : "r"(fcsr));

  /* Per 'fegetenv.html:
   *
   * "If the environment was successfully established, fesetenv()
   * shall return zero. Otherwise, it shall return a non-zero value.
   */

  return 0;
}
#else
#include "../../fenv/fesetenv.c"
#endif
