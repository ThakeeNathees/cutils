//------------------------------------------------------------------------------
// MIT License
//------------------------------------------------------------------------------
// 
// Copyright (c) 2020-2021 Thakee Nathees
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//------------------------------------------------------------------------------

#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __cplusplus

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>
#include <bitset>

#include <vector>
#include <cstring>
#include <string>
#include <stack>
#include <map>
#include <unordered_map>

#include <chrono>
#include <iostream>
#include <ostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <new>
#include <thread>
#include <mutex>

#endif // __cplusplus

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
#define PLATFORM_IOS_SIMULATOR
#elif TARGET_OS_IPHONE
#define PLATFORM_IOS
#elif TARGET_OS_MAC
#define PLATFORM_APPLE
#else
#error "Unknown Apple platform"
#endif
#elif defined(__linux__)
#define PLATFORM_LINUX
#elif defined(__unix__)
#define PLATFORM_UNIX
#elif defined(_POSIX_VERSION)
#define PLATFORM_POSIX
#else
#error "Unknown Platform"
#endif

#if defined(CARBON_DLL)
#if defined(CARBON_DLL_EXPORT)
#define CARBON_API __declspec(dllexport)
#else
#define CARBON_API __declspec(dllimport)
#endif
#else
#define CARBON_API
#endif

// https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
#ifdef _MSC_VER // Microsoft compilers
#define GET_ARG_COUNT(...)  INTERNAL_EXPAND_ARGS_PRIVATE(INTERNAL_ARGS_AUGMENTER(__VA_ARGS__))

#define INTERNAL_ARGS_AUGMENTER(...) unused, __VA_ARGS__
#define INTERNAL_EXPAND(x) x
#define INTERNAL_EXPAND_ARGS_PRIVATE(...) INTERNAL_EXPAND(INTERNAL_GET_ARG_COUNT_PRIVATE(__VA_ARGS__, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define INTERNAL_GET_ARG_COUNT_PRIVATE(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count	
#else // Non-Microsoft compilers
#define GET_ARG_COUNT(...) INTERNAL_GET_ARG_COUNT_PRIVATE(0, ## __VA_ARGS__, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define INTERNAL_GET_ARG_COUNT_PRIVATE(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count
#endif

#ifndef DEBUG_BUILD
#if defined(_DEBUG) || defined(DEBUG)
#define DEBUG_BUILD
#endif
#endif

#ifdef DEBUG_BUILD
#ifdef _MSC_VER
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK() __builtin_trap()
#endif
#define DEBUG_BREAK_COND(m_cond) if (m_cond) DEBUG_BREAK()
#else 
#define DEBUG_BREAK()
#define DEBUG_BREAK_COND(m_cond)
#endif

#define _CRASH()                \
do {                            \
	char* CRASH_HERE = nullptr; \
	*CRASH_HERE = '\0';         \
} while(false)

#ifdef DEBUG_BUILD
#define DEBUG_PRINT(m_msg)                                                                                        \
	do {                                                                                                              \
		printf("DEBUG_PRINT: \"%s\" at %s (%s:%i)\n", String("" m_msg).c_str(), __FUNCTION__, __FILE__, __LINE__);    \
	} while (false)
#define DEBUG_PRINT_COND(m_cond, m_msg) do { if (m_cond) DEBUG_PRINT(m_msg); } while (false)

#ifdef __cplusplus
#define ASSERT(m_cond)                                                                                            \
		do {                                                                                                          \
			if (!(m_cond)) {                                                                                          \
				DEBUG_BREAK();                                                                                        \
				THROW_ERROR(Error::BUG, String::format("ASSERTION FAILED: at %s (%s:%i)\n%s is false", __FUNCTION__, __FILE__, __LINE__, STR(m_cond)));  \
			}                                                                                                         \
		} while (false)
#endif // __cplusplus

#else
#define DEBUG_PRINT(m_msg)
#define DEBUG_PRINT_COND(m_cond, m_msg)
#define ASSERT(m_cond)
#endif

#ifdef __cplusplus
#define MISSED_ENUM_CHECK(m_max_enum, m_max_value)                                                               \
    static_assert((int)m_max_enum == m_max_value, "MissedEnum: " STRINGIFY(m_max_enum) " != " STRINGIFY(m_value) \
        "\n\tat: " __FILE__ "(" STRINGIFY(__LINE__) ")")
#endif // __cplusplus


#define STR(m_) #m_
#define STRINGIFY(m_) STR(m_)
#define PLACE_HOLDER_MACRO
#define NO_ERRECT_MACRO(m) m
#define VSNPRINTF_BUFF_SIZE 8192

#ifdef __cplusplus
namespace varh {
	typedef unsigned char byte_t;

	unsigned constexpr __const_hash(char const* input) {
		return *input ? static_cast<unsigned int>(*input) + 33 * __const_hash(input + 1) : 5381;
	}

	std::size_t constexpr operator "" _hash(const char* s, size_t) {
		return __const_hash(s);
	}

	// custom free operator for malloc in shared ptr
	struct _mem_free_t {
		void operator()(void* _mem) { free(_mem); }
	};

	// custom destructor for malloc in shared ptr
	struct _mem_delete_t {
		typedef void (*_clean_f)(void*);
		_mem_delete_t(_clean_f fp) : fp(fp) {}
		_clean_f fp;
		void operator()(void* _mem) {
			fp(_mem);
		}
	};

	template<typename T>
	using ptr = std::shared_ptr<T>;

	template<typename T>
	using stdvec = std::vector<T>;

	template<typename T1, typename T2>
	using stdmap = std::map<T1, T2>;

	template<typename T1, typename T2>
	using stdhashtable = std::unordered_map<T1, T2>;

	template<typename T, typename... Targs>
	inline ptr<T> newptr(Targs... p_args) {
		return std::make_shared<T>(p_args...);
	}

	template<typename T1, typename T2>
	inline ptr<T1> ptrcast(T2 p_ptr) {
		return std::static_pointer_cast<T1>(p_ptr);
	}

	template<typename T, typename... Targs>
	stdvec<T> make_stdvec(Targs... p_args) { return { p_args... }; }

} // namespace varh
#endif // __cplusplus

#endif // CORE_INTERNAL_H