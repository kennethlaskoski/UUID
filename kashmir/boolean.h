// boolean.h -- safe bool idiom

// Copyright (C) 2009 Kenneth Laskoski

/** @file boolean.h
    @brief safe bool idiom
    @author Copyright (C) 2009 Kenneth Laskoski
    
    see <http://www.artima.com/cppsource/safebool3.html>

    Use, modification, and distribution are subject
    to the Boost Software License, Version 1.0.  (See accompanying file
    LICENSE_1_0.txt or a copy at <http://www.boost.org/LICENSE_1_0.txt>.)
*/

#ifndef KL_BOOLEAN_H
#define KL_BOOLEAN_H 

namespace kashmir {
namespace boolean_ADL_fence {

template<class T = void>
class boolean
{
    typedef T* const boolean<T>::*bool_type;

    T* const self;

protected:
    boolean() : self(static_cast<T*>(this)) {}
    ~boolean() {}

public:
    operator bool_type() const
    {
        return self->operator!() ? 0 : &boolean<T>::self;
    }
};

template<>
class boolean<void>
{
    typedef bool (boolean<void>::*bool_type)() const;

protected:
    virtual bool predicate() const = 0;
    virtual ~boolean() {}

public:
    operator bool_type() const
    {
        return predicate() ? &boolean<void>::predicate : 0;
    }
};

} // namespace kashmir::boolean_ADL_fence

using namespace boolean_ADL_fence;

} // namespace kashmir

#endif
