/*
 * Copyright (c) 2019 BayLibre SAS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_TOOLCHAIN_ZEPHYR_STDINT_H_
#define ZEPHYR_INCLUDE_TOOLCHAIN_ZEPHYR_STDINT_H_

/*
 * Some gcc versions and/or configurations as found in the Zephyr SDK
 * (questionably) define __INT32_TYPE__ and derivatives as a long int
 * which makes the printf format checker to complain about long vs int
 * mismatch when %u is given a uint32_t argument, and uint32_t pointers not
 * being compatible with int pointers. Let's redefine them to follow
 * common expectations and usage.
 */

/*
 * If the compiler does not define __SIZEOF_INT__ deduce it from __INT_MAX__
 * or INT_MAX.
 */
#ifndef __SIZEOF_LONG__
#define __SIZEOF_LONG__ 4
#endif
#ifndef __SIZEOF_LONG_LONG__
#define __SIZEOF_LONG_LONG__ 8
#endif
#ifndef __SIZEOF_SHORT__
#define __SIZEOF_SHORT__ 2
#endif
#ifndef __SIZEOF_POINTER__
#define __SIZEOF_POINTER__ 4
#endif

#if !defined(__SIZEOF_INT__)

#if defined(__INT_MAX__)
/* GCC >= 3.3.0 has __<val>__ implicitly defined. */
#define __Z_INT_MAX __INT_MAX__
#else
/* Fall back to POSIX versions from <limits.h> */
#define __Z_INT_MAX INT_MAX
#include <limits.h>
#endif

#if __Z_INT_MAX == 0x7fff
#define __SIZEOF_INT__ 2
#elif __Z_INT_MAX == 0x7fffffffL
#define __SIZEOF_INT__ 4
#elif __Z_INT_MAX > 0x7fffffffL
#define __SIZEOF_INT__ 8
#endif

#undef __Z_INT_MAX

#endif

#if __SIZEOF_INT__ != 4
#error "unexpected int width"
#endif

#ifndef __INT8_TYPE__
#define __INT8_TYPE__ signed char
#define __UINT8_TYPE__ unsigned char
#define __INT_FAST8_TYPE__ __INT8_TYPE__
#define __UINT_FAST8_TYPE__ __UINT8_TYPE__
#define __INT_LEAST8_TYPE__ __INT8_TYPE__
#define __UINT_LEAST8_TYPE__ __UINT8_TYPE__
#endif

#ifndef __INT16_TYPE__
#define __INT16_TYPE__ short int
#define __UINT16_TYPE__ unsigned short int
#define __INT_FAST16_TYPE__ __INT16_TYPE__
#define __UINT_FAST16_TYPE__ __UINT16_TYPE__
#define __INT_LEAST16_TYPE__ __INT16_TYPE__
#define __UINT_LEAST16_TYPE__ __UINT16_TYPE__
#endif

#ifndef __INT8_MAX__
#define __INT8_MAX__ 127
#define __INT16_MAX__ 32767
#define __INT32_MAX__ 2147483647
#define __INT64_MAX__ 9223372036854775807LL

#define __UINT8_MAX__ 255
#define __UINT16_MAX__ 65535
#define __UINT32_MAX__ 4294967295U
#define __UINT64_MAX__ 18446744073709551615ULL

#define __INT_FAST8_MAX__ __INT8_MAX__
#define __INT_FAST16_MAX__ __INT16_MAX__
#define __INT_FAST32_MAX__ __INT32_MAX__
#define __INT_FAST64_MAX__ __INT64_MAX__

#define __UINT_FAST8_MAX__ __UINT8_MAX__
#define __UINT_FAST16_MAX__ __UINT16_MAX__
#define __UINT_FAST32_MAX__ __UINT32_MAX__
#define __UINT_FAST64_MAX__ __UINT64_MAX__

#define __INT_LEAST8_MAX__ __INT8_MAX__
#define __INT_LEAST16_MAX__ __INT16_MAX__
#define __INT_LEAST32_MAX__ __INT32_MAX__
#define __INT_LEAST64_MAX__ __INT64_MAX__

#define __UINT_LEAST8_MAX__ __UINT8_MAX__
#define __UINT_LEAST16_MAX__ __UINT16_MAX__
#define __UINT_LEAST32_MAX__ __UINT32_MAX__
#define __UINT_LEAST64_MAX__ __UINT64_MAX__

#define __INTPTR_MAX__ __INT32_MAX__
#define __UINTPTR_MAX__ __UINT32_MAX__
#define __PTRDIFF_MAX__ __INT32_MAX__
#define __SIZE_MAX__ __UINT32_MAX__
#endif

#undef __INT32_TYPE__
#undef __UINT32_TYPE__
#undef __INT_FAST32_TYPE__
#undef __UINT_FAST32_TYPE__
#undef __INT_LEAST32_TYPE__
#undef __UINT_LEAST32_TYPE__
#undef __INT64_TYPE__
#undef __UINT64_TYPE__
#undef __INT_FAST64_TYPE__
#undef __UINT_FAST64_TYPE__
#undef __INT_LEAST64_TYPE__
#undef __UINT_LEAST64_TYPE__

#define __INT32_TYPE__ int
#define __UINT32_TYPE__ unsigned int
#define __INT_FAST32_TYPE__ __INT32_TYPE__
#define __UINT_FAST32_TYPE__ __UINT32_TYPE__
#define __INT_LEAST32_TYPE__ __INT32_TYPE__
#define __UINT_LEAST32_TYPE__ __UINT32_TYPE__
#define __INT64_TYPE__ long long int
#define __UINT64_TYPE__ unsigned long long int
#define __INT_FAST64_TYPE__ __INT64_TYPE__
#define __UINT_FAST64_TYPE__ __UINT64_TYPE__
#define __INT_LEAST64_TYPE__ __INT64_TYPE__
#define __UINT_LEAST64_TYPE__ __UINT64_TYPE__

/*
 * The confusion also exists with __INTPTR_TYPE__ which is either an int
 * (even when __INT32_TYPE__ is a long int) or a long int. Let's redefine
 * it to a long int to get some uniformity. Doing so also makes it compatible
 * with LP64 (64-bit) targets where a long is always 64-bit wide.
 */

#if __SIZEOF_POINTER__ != __SIZEOF_LONG__
#error "unexpected size difference between pointers and long ints"
#endif

#undef __INTPTR_TYPE__
#undef __UINTPTR_TYPE__
#define __INTPTR_TYPE__ long int
#define __UINTPTR_TYPE__ long unsigned int

/*
 * Re-define the INTN_C(value) integer constant expression macros to match the
 * integer types re-defined above.
 */

#undef __INT32_C
#undef __UINT32_C
#undef __INT64_C
#undef __UINT64_C
#define __INT32_C(c) c
#define __UINT32_C(c) c ## U
#define __INT64_C(c) c ## LL
#define __UINT64_C(c) c ## ULL

#endif /* ZEPHYR_INCLUDE_TOOLCHAIN_ZEPHYR_STDINT_H_ */
