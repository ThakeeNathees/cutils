//------------------------------------------------------------------------------
// MIT License
//------------------------------------------------------------------------------
// 
// Copyright (c) 2020 Thakee Nathees
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

#ifndef VARHCORE_H
#define VARHCORE_H

#include <assert.h>
#include <cstring>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <type_traits>
#include <typeinfo>

#define _USE_MATH_DEFINES
#include <map>
#include <math.h>
#include <vector>

#define STRCAT2(m_a, m_b) m_a##m_b
#define STRCAT3(m_a, m_b, m_c) m_a##m_b##m_c
#define STRCAT4(m_a, m_b, m_c, m_d) m_a##m_b##m_c##m_d

#define STR(m_mac) #m_mac
#define STRINGIFY(m_mac) STR(m_mac)

#define PLACE_HOLDER_MACRO

#define newptr(T1, ...) std::make_shared<T1>(__VA_ARGS__)
#define newptr2(T1, T2, ...) std::make_shared<T1, T2>(__VA_ARGS__)
#define ptr_cast(T, m_ptr)    std::static_pointer_cast<T>(m_ptr)
template<typename T>
using Ptr = std::shared_ptr<T>;

#define VSNPRINTF_BUFF_SIZE 8192

#if defined(DOUBLE_AS_REAL)
typedef double real_t;
#else
typedef float real_t;
#endif

#ifdef _MSC_VER
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK() __builtin_trap()
#endif

#define DEBUG_PRINT(m_msg, ...) \
	printf("DEBUG: %s\n\tat: %s(%s:%li)", m_msg, __FUNCTION__, __FILE__, __LINE__)

#if defined(_DEBUG)
#define VAR_ASSERT(m_cond, m_msg)  \
	if (!(m_cond))                 \
		VAR_ERR(m_msg)
#else
#define VAR_ASSERT
#endif

namespace varh {
class VarError : public std::exception {
public:
	enum Type {
		OK,
		NULL_POINTER,
		INVALID_INDEX,
		INVALID_CASTING,
		NOT_IMPLEMENTED,
		ZERO_DIVISION,
	};

	const char* what() const noexcept override { return msg.c_str(); }
	Type get_Type() const { return type; }

	VarError() {}
	VarError(Type p_type) { type = p_type; }
	VarError(Type p_type, const std::string& p_msg) {
		type = p_type;
		msg = p_msg;
	}

private:
	Type type = OK;
	std::string msg;
};
}

#endif // VARHCORE_H