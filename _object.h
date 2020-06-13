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

#ifndef OBJECT_H
#define OBJECT_H

#include "varhcore.h"

namespace varh {

class Object
{
private:
	friend class var;

public:

	// operators
	virtual String to_string() const { return operator String(); }
	virtual operator String() const { return String("[Object:") + String((int)this) + String("]"); }
	virtual Object& operator=(const Object& p_copy) = default;

	virtual bool operator==(const Object& p_other) { return &p_other == this; }
	virtual bool operator!=(const Object& p_other) { return !operator == (p_other); }
	virtual bool operator<=(const Object& p_other) { return this <= &p_other; }
	virtual bool operator>=(const Object& p_other) { return this >= &p_other; }
	virtual bool operator<(const Object& p_other) { return this < &p_other; }
	virtual bool operator>(const Object& p_other) { return this > &p_other; }


	// methods
	virtual bool get(const String& p_name, var& r_val) const = 0;
	virtual bool set(const String& p_name, const var& p_val) = 0;
	virtual bool has(const String& p_name) const = 0;

	virtual void copy(Object* r_ret, bool p_deep) const = 0;
	String get_class_name() const { return "Object"; }

	template <typename T>
	T* cast() const { 
		return dynamic_cast<T*>(this); 
	}

};

}


#endif //OBJECT_H