// md5.h -- hash algorithm described in IETF RFC 1321

// Copyright (C) 2010 Kenneth Laskoski

/** @file md5.h
    @brief hash algorithm described in IETF RFC 1321
    @author Copyright (C) 2010 Kenneth Laskoski

    Use, modification, and distribution are subject to the
    Boost Software License, Version 1.0. See accompanying file
    LICENSE_1_0.txt or <http://www.boost.org/LICENSE_1_0.txt>.
*/
/*
    Relevant copyright information is provided below and may not be removed from this file. 
    Derived from the RSA Data Security, Inc. MD5 Message-Digest Algorithm.

    MD5C.C - RSA Data Security, Inc., MD5 message-digest algorithm

    Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All rights 
    reserved.

    License to copy and use this software is granted provided that it is 
    identified as the "RSA Data Security, Inc. MD5 Message-Digest Algorithm" in 
    all material mentioning or referencing this software or this function. 

    License is also granted to make and use derivative works provided that such 
    works are identified as "derived from the RSA Data Security, Inc. MD5 
    Message-Digest Algorithm" in all material mentioning or referencing the 
    derived work. 

    RSA Data Security, Inc. makes no representations concerning either the 
    merchantability of this software or the suitability of this software for 
    any particular purpose. It is provided "as is" without express or implied 
    warranty of any kind. 

    These notices must be retained in any copies of any part of this 
    documentation and/or software. 
*/

#ifndef KL_MD5_H
#define KL_MD5_H 

#include "array.h"

#include <istream>
#include <ostream>
#include <sstream>

#include <cstddef>

#include <stdexcept>
#include <algorithm>

#include "iostate.h"

namespace kashmir {
namespace md5 {

// F, G, H and I are basic MD5 functions.
template<class T> T F(T x, T y, T z) { return (x & y) | (~x & z); } 
template<class T> T G(T x, T y, T z) { return (x & z) | (y & ~z); }
template<class T> T H(T x, T y, T z) { return x ^ y ^ z; }
template<class T> T I(T x, T y, T z) { return y ^ (x | ~z); }

// left rotation
template<class T> T rotate_left(T x, T y) { return x << y | x >> (32 - y); }

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
template<class T>
void FF(T& a, T b, T c, T d, T x, T s, T ac){
    a += F(b, c, d) + x + ac;
    a = rotate_left(a, s) +b;
}

template<class T>
void GG(T& a, T b, T c, T d, T x, T s, T ac){
    a += G(b, c, d) + x + ac;
    a = rotate_left(a, s) +b;
}

template<class T>
void HH(T& a, T b, T c, T d, T x, T s, T ac){
    a += H(b, c, d) + x + ac;
    a = rotate_left(a, s) +b;
}

template<class T>
void II(T& a, T b, T c, T d, T x, T s, T ac){
    a += I(b, c, d) + x + ac;
    a = rotate_left(a, s) +b;
}


/** @class md5_t
    @brief This class implements the hash algorithm described in
    
    - IETF RFC 1321 - available at http://tools.ietf.org/html/rfc1321

    This document documents the code below.
*/

class md5_t
{
    // an MD5 is a string of 16 octets (128 bits)
    // we use an unpacked representation, value_type may be larger than 8 bits,
    // in which case every input operation must assert data[i] < 256 for i < 16
    // note even char may be more than 8 bits in some particular platform
    typedef unsigned char value_type;
    typedef std::size_t size_type;

    enum { size = 16, string_size = 32 };

    typedef array<value_type, size> data_type;
    data_type data;

public:
    // uninitialized memory
    md5_t() {}
    ~md5_t() {}

    // copy and assignment
    md5_t(const md5_t& rhs) : data(rhs.data) {}

    md5_t& operator=(const md5_t& rhs)
    {
        data = rhs.data;
        return *this;
    }

    // initialization from C string
    explicit md5_t(const char* string)
    {
        std::stringstream stream(string);
        get(stream);
    }

    // test for nil value
    bool is_nil() const
    {
        for (size_type i = 0; i < size; ++i)
            if (data[i])
                return false;
        return true;
    }

    // safe bool idiom
    typedef data_type md5_t::*bool_type; 

    operator bool_type() const
    {
        return is_nil() ? 0 : &md5_t::data;
    }

    friend bool operator==(const md5_t& lhs, const md5_t& rhs);
    friend bool operator<(const md5_t& lhs, const md5_t& rhs);

    // stream operators
    template<class char_t, class char_traits>
    std::basic_ostream<char_t, char_traits>& put(std::basic_ostream<char_t, char_traits>& os) const;

    template<class char_t, class char_traits>
    std::basic_istream<char_t, char_traits>& get(std::basic_istream<char_t, char_traits>& is);
};

// comparison operators define a total order
inline bool operator==(const md5_t& lhs, const md5_t& rhs)
{
    return lhs.data == rhs.data;
}

inline bool operator<(const md5_t& lhs, const md5_t& rhs)
{
    return lhs.data < rhs.data;
}

inline bool operator>(const md5_t& lhs, const md5_t& rhs) { return (rhs < lhs); }
inline bool operator<=(const md5_t& lhs, const md5_t& rhs) { return !(rhs < lhs); }
inline bool operator>=(const md5_t& lhs, const md5_t& rhs) { return !(lhs < rhs); }
inline bool operator!=(const md5_t& lhs, const md5_t& rhs) { return !(lhs == rhs); }

template<class char_t, class char_traits>
std::basic_ostream<char_t, char_traits>& md5_t::put(std::basic_ostream<char_t, char_traits>& os) const
{
    if (!os.good())
        return os;

    const typename std::basic_ostream<char_t, char_traits>::sentry ok(os);
    if (ok)
    {
        ios_flags_saver flags(os);
        basic_ios_fill_saver<char_t, char_traits> fill(os);

        const std::streamsize width = os.width(0);
        const std::streamsize mysize = string_size;

        // right padding
        if (flags.value() & (std::ios_base::right | std::ios_base::internal))
            for (std::streamsize i = width; i > mysize; --i)
                os << fill.value();

        os << std::hex;
        os.fill(os.widen('0'));

        for (size_t i = 0; i < 16; ++i)
        {
            os.width(2);
            os << static_cast<unsigned>(data[i]);
        }

        // left padding
        if (flags.value() & std::ios_base::left)
            for (std::streamsize i = width; i > mysize; --i)
                os << fill.value();
    }

    return os;
}

template<class char_t, class char_traits>
std::basic_istream<char_t, char_traits>& md5_t::get(std::basic_istream<char_t, char_traits>& is)
{
    if (!is.good())
        return is;

    const typename std::basic_istream<char_t, char_traits>::sentry ok(is);
    if (ok)
    {
        char_t hexdigits[16];
        char_t* const npos = hexdigits+16;

        typedef std::ctype<char_t> facet_t;
        const facet_t& facet = std::use_facet<facet_t>(is.getloc());

        const char* tmp = "0123456789abcdef";
        facet.widen(tmp, tmp+16, hexdigits);

        char_t c;
        char_t* f;
        for (size_t i = 0; i < size; ++i)
        {
            is >> c;
            c = facet.tolower(c);

            f = std::find(hexdigits, npos, c);
            if (f == npos)
            {
                is.setstate(std::ios_base::failbit);
                break;
            }

            data[i] = static_cast<value_type>(std::distance(hexdigits, f));

            is >> c;
            c = facet.tolower(c);

            f = std::find(hexdigits, npos, c);
            if (f == npos)
            {
                is.setstate(std::ios_base::failbit);
                break;
            }

            data[i] <<= 4;
            data[i] |= static_cast<value_type>(std::distance(hexdigits, f));
        }

        if (!is)
            throw std::runtime_error("failed to extract valid md5 from stream.");
    }

    return is;
}

template<class char_t, class char_traits>
inline std::basic_ostream<char_t, char_traits>& operator<<(std::basic_ostream<char_t, char_traits>& os, const md5_t& md5)
{
    return md5.put(os);
}

template<class char_t, class char_traits>
inline std::basic_istream<char_t, char_traits>& operator>>(std::basic_istream<char_t, char_traits>& is, md5_t& md5)
{
    return md5.get(is);
}

/*
void update (void *input, std::size_t input_length) {

    uint4 input_index, buffer_index;
    uint4 buffer_space;                // how much space is left in buffer

    if (finalized){  // so we can't update!
        cerr << "MD5::update:  Can't update a finalized digest!" << endl;
        return;
    }

    // Compute number of bytes mod 64
    buffer_index = (unsigned int)((count[0] >> 3) & 0x3F);

    // Update number of bits
    if (  (count[0] += ((uint4) input_length << 3))<((uint4) input_length << 3) )
        count[1]++;

    count[1] += ((uint4)input_length >> 29);


    buffer_space = 64 - buffer_index;  // how much space is left in buffer

    // Transform as many times as possible.
    if (input_length >= buffer_space) { // ie. we have enough to fill the buffer
        // fill the rest of the buffer and transform
        memcpy (buffer + buffer_index, input, buffer_space);
        transform (buffer);

        // now, transform each 64-byte piece of the input, bypassing the buffer
        for (input_index = buffer_space; input_index + 63 < input_length;
                input_index += 64)
            transform (input+input_index);

        buffer_index = 0;  // so we can buffer remaining
    }
    else
        input_index=0;     // so we can buffer the whole input


    // and here we do the buffering:
    memcpy(buffer+buffer_index, input+input_index, input_length-input_index);
}
*/

md5_t hash(const char *input, std::size_t input_length)
{
    md5_t val;
    return val;
}

md5_t hash(std::istream& s)
{
    md5_t val;
/*
    unsigned char buffer[1024];
    int len;

    while (stream.good()){
        stream.read(buffer, 1024); // note that return value of read is unusable.
        len=stream.gcount();
        update(buffer, len);
    }

*/
    return val;
}

} // namespace kashmir::md5

using md5::md5_t;

} // namespace kashmir

#endif
