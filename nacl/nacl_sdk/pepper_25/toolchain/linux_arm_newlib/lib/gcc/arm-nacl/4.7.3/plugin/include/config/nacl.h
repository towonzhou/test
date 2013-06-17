/* Definitions for Native Client systems.
   Copyright (C) 2012 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/* TODO:
   glibc vs newlib options
 */

#define GNU_USER_TARGET_OS_CPP_BUILTINS()               \
  do {                                                  \
    builtin_define ("__native_client__");               \
    builtin_assert ("system=nacl");                     \
    builtin_assert ("system=posix");                    \
    builtin_define (BYTES_BIG_ENDIAN ? "__BIG_ENDIAN__" \
		    : "__LITTLE_ENDIAN__");             \
  } while (0)

/* This is the value for %(subtarget_cpp_spec).  It goes with gnu-user.opt.  */
#undef  SUBTARGET_CPP_SPEC
#define SUBTARGET_CPP_SPEC  "%{posix:-D_POSIX_SOURCE} %{pthread:-D_REENTRANT}"

/* Since non-instructions can never go into code sections,
   this is always false for Native Client targets.  */
#undef  JUMP_TABLES_IN_TEXT_SECTION
#define JUMP_TABLES_IN_TEXT_SECTION     0

/* Every Native Client platform has a va_list type of the same
   size and minimum alignment, even if it just contains unused
   padding space to reach that size.  */
#define VA_LIST_TYPE_SIZE               (16 * BITS_PER_UNIT)

#define NACL_MIN_ALIGN(condition, bundle_size)                          \
  do {                                                                  \
    if (condition)                                                      \
      {                                                                 \
	/* All functions and branch targets are aligned to at least the \
	   bundle size in native client. */                             \
	if (align_functions < bundle_size)                              \
	  align_functions = bundle_size;                                \
	if (align_jumps < bundle_size)                                  \
	  align_jumps = bundle_size;                                    \
	if (align_labels < bundle_size)                                 \
	  align_labels = bundle_size;                                   \
	if (align_loops < bundle_size)                                  \
	  align_loops = bundle_size;                                    \
      }                                                                 \
  } while (0)

/* Every Native Client platform has a 'long double' type that is just
   'double', which is always the IEEE754 64-bit type.  */
#undef LONG_DOUBLE_TYPE_SIZE
#define LONG_DOUBLE_TYPE_SIZE		DOUBLE_TYPE_SIZE
#undef LIBGCC2_HAS_TF_MODE
