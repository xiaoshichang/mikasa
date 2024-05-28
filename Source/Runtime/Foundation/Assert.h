#pragma once

// assert implemetation
#if MIKASA_TARGET_PLATFORM_Window64
#include <crtdbg.h>
#define ASSERT_IMPL(EXPR)		_ASSERTE(EXPR)
#elif TARGET_PLATFORM_MACOS
#include <cassert>
#define ASSERT_IMPL(EXPR)		assert(EXPR)
#else
#pragma error
#endif

// assert switch
#if MIKASA_BUILDTYPE_DEBUG
#define MIKASA_ASSERT(EXPR)		ASSERT_IMPL(EXPR)
#else
#define MIKASA_ASSERT(EXPR)		    ((void)0)
#endif