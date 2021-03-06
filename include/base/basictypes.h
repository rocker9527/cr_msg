// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file contains definitions of our old basic integral types
// ((u)int{8,16,32,64}) and further includes. I recommend that you use the C99
// standard types instead, and include <stdint.h>/<stddef.h>/etc. as needed.
// Note that the macros and macro-like constructs that were formerly defined in
// this file are now available separately in base/macros.h.

#ifndef BASE_BASICTYPES_H_
#define BASE_BASICTYPES_H_

#include <limits.h>  // So we can set the bounds of our types.
#include <stddef.h>  // For size_t.
#include <stdint.h>  // For intptr_t.

#include "base/macros.h"
//#include "base/port.h"  // Types that only need exist on certain systems.

// DEPRECATED: Please use (u)int{8,16,32,64}_t instead (and include <stdint.h>).
typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef int32_t int32;
typedef uint16_t uint16;
typedef uint32_t uint32;

// TODO(vtl): Figure what's up with the 64-bit types. Can we just define them as
// |int64_t|/|uint64_t|?
// The NSPR system headers define 64-bit as |long| when possible, except on
// Mac OS X.  In order to not have typedef mismatches, we do the same on LP64.
//
// On Mac OS X, |long long| is used for 64-bit types for compatibility with
// <inttypes.h> format macros even in the LP64 model.
#if defined(__LP64__) && !defined(OS_MACOSX) && !defined(OS_OPENBSD)
typedef long int64;
typedef unsigned long uint64;
#else
typedef long long int64;
typedef unsigned long long uint64;
#endif

// DEPRECATED: Please use std::numeric_limits (from <limits>) instead.
const uint8  kuint8max  =  0xFF;
const uint16 kuint16max =  0xFFFF;
const uint32 kuint32max =  0xFFFFFFFF;
const uint64 kuint64max =  0xFFFFFFFFFFFFFFFFULL;
const  int8  kint8min   = -0x7F - 1;
const  int8  kint8max   =  0x7F;
const  int16 kint16min  = -0x7FFF - 1;
const  int16 kint16max  =  0x7FFF;
const  int32 kint32min  = -0x7FFFFFFF - 1;
const  int32 kint32max  =  0x7FFFFFFF;
const  int64 kint64min  = -0x7FFFFFFFFFFFFFFFLL - 1;
const  int64 kint64max  =  0x7FFFFFFFFFFFFFFFLL;


#include <stdarg.h>
#include "base/build_config.h"

// DEPRECATED: Use ...LL and ...ULL suffixes.
// TODO(viettrungluu): Delete these. These are only here until |GG_(U)INT64_C|
// are deleted (some other header files (re)define |GG_(U)INT64_C|, so our
// definitions of them must exactly match theirs).
#ifdef COMPILER_MSVC
#define GG_LONGLONG(x) x##I64
#define GG_ULONGLONG(x) x##UI64
#else
#define GG_LONGLONG(x) x##LL
#define GG_ULONGLONG(x) x##ULL
#endif

// DEPRECATED: In Chromium, we force-define __STDC_CONSTANT_MACROS, so you can
// just use the regular (U)INTn_C macros from <stdint.h>.
// TODO(viettrungluu): Remove the remaining GG_(U)INTn_C macros.
#define GG_INT64_C(x)   GG_LONGLONG(x)
#define GG_UINT64_C(x)  GG_ULONGLONG(x)

// It's possible for functions that use a va_list, such as StringPrintf, to
// invalidate the data in it upon use.  The fix is to make a copy of the
// structure before using it and use that copy instead.  va_copy is provided
// for this purpose.  MSVC does not provide va_copy, so define an
// implementation here.  It is not guaranteed that assignment is a copy, so the
// StringUtil.VariableArgsFunc unit test tests this capability.
#if defined(COMPILER_GCC)
#define GG_VA_COPY(a, b) (va_copy(a, b))
#elif defined(COMPILER_MSVC)
#define GG_VA_COPY(a, b) (a = b)
#endif

// Define an OS-neutral wrapper for shared library entry points
#if defined(OS_WIN)
#define API_CALL __stdcall
#else
#define API_CALL
#endif


#endif  // BASE_BASICTYPES_H_
