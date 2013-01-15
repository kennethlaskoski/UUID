// uuid_gen.h -- universally unique ID - as defined by ISO/IEC 9834-8:2005

// Copyright (C) 2008 Kenneth Laskoski

/** @file uuid_gen.h
    @brief universally unique ID - as defined by ISO/IEC 9834-8:2005
    @author Copyright (C) 2008 Kenneth Laskoski
*/

#ifndef KL_UUID_GEN_H
#define KL_UUID_GEN_H

#include "uuid.h"
#include "randomstream.h"

namespace kashmir {
namespace uuid {

template<class crtp_impl>
randomstream<crtp_impl>& operator>>(randomstream<crtp_impl>& is, uuid_t& uuid)
{
    // get random bytes
    // we take advantage of our representation
    char *data = reinterpret_cast<char*>(&uuid);
    is.read(data, size);

    // a more general solution would be
//    input_iterator<is> it;
//    std::copy(it, it+size, data.begin());

    // if uuid_t::value_type is larger than 8 bits, we need
    // to maintain the invariant data[i] < 256 for i < 16
    // Example (which may impact randomness):
//    for (size_t i = 0; i < size; ++i)
//        data[i] &= 0xff;

    // set variant
    // should be 0b10xxxxxx
    data[8] &= 0xbf;   // 0b10111111
    data[8] |= 0x80;   // 0b10000000

    // set version
    // should be 0b0100xxxx
    data[6] &= 0x4f;   // 0b01001111
    data[6] |= 0x40;   // 0b01000000

    return is;
}

void cast_md5(uuid_t& uuid);
void cast_sha1(uuid_t& uuid);

} // namespace kashmir::uuid
} // namespace kashmir

#endif
