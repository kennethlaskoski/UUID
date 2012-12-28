// uuid_gen.cpp -- universally unique ID - as defined by ISO/IEC 9834-8:2005

// Copyright (C) 2012 Kenneth Laskoski

/** @file uuid_gen.cpp
    @brief universally unique ID - as defined by ISO/IEC 9834-8:2005
    @author Copyright (C) 2012 Kenneth Laskoski
*/

#include "uuid_gen.h"

namespace kashmir {
namespace uuid {

void cast_md5(uuid_t& uuid)
{
    unsigned char *const data = reinterpret_cast<unsigned char *const>(&uuid);

    // set variant
    // should be 0b10xxxxxx
    data[8] &= 0xbf;   // 0b10111111
    data[8] |= 0x80;   // 0b10000000

    // set version
    // should be 0b0011xxxx
    data[6] &= 0x3f;   // 0b00111111
    data[6] |= 0x30;   // 0b00110000
}

void cast_sha1(uuid_t& uuid)
{
    unsigned char *const data = reinterpret_cast<unsigned char *const>(&uuid);

    // set variant
    // should be 0b10xxxxxx
    data[8] &= 0xbf;   // 0b10111111
    data[8] |= 0x80;   // 0b10000000

    // set version
    // should be 0b0101xxxx
    data[6] &= 0x5f;   // 0b01011111
    data[6] |= 0x50;   // 0b01010000
}

} // namespace kashmir::uuid
} // namespace kashmir
