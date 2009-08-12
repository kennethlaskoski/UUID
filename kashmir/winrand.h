/********************************************************************\
 * winrand.h -- Windows random number generator                     *
 *                                                                  *
 * Copyright (C) 2008 Kenneth Laskoski                              *
 *                                                                  *
\********************************************************************/
/** @file winrand.h
    @brief Windows random number generator
    Uses the ADVAPI32!RtlGenRandom function, which doesn't require a CSP context
    see <http://blogs.msdn.com/michael_howard/archive/2005/01/14/353379.aspx>
    and <http://msdn.microsoft.com/en-us/library/aa387694%28VS.85%29.aspx>
    @author Copyright (C) 2008 Kenneth Laskoski
    based on work by
    @author Copyright (C) 1996, 1997, 1998 Theodore Ts'o
    @author Copyright (C) 2004-2008 Ralf S. Engelschall <rse@engelschall.com>

    Use, modification, and distribution are subject
    to the Boost Software License, Version 1.0.  (See accompanying file
    LICENSE_1_0.txt or a copy at <http://www.boost.org/LICENSE_1_0.txt>.)
*/

#ifndef KL_WINRAND_H
#define KL_WINRAND_H

#include "randomstream.h"
#include "noncopyable.h"

#include <stdexcept>

#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <windows.h>

namespace kashmir {
namespace system {

class WinRand : public user::randomstream<WinRand>, noncopyable
{
public:
    WinRand() : hLib(LoadLibrary("ADVAPI32.DLL"))
    {
        if (!hLib)
            throw std::runtime_error("failed to load ADVAPI32.DLL.");

        RtlGenRandom = (BOOLEAN (APIENTRY *)(void*,ULONG)) GetProcAddress(hLib,"SystemFunction036");
        if (!RtlGenRandom)
        {
            FreeLibrary(hLib);
            throw std::runtime_error("failed to get ADVAPI32!RtlGenRandom address.");
        }
    }

    ~WinRand()
    {
        FreeLibrary(hLib);
    }

    void read(char* buffer, std::size_t count)
    {
        if (!RtlGenRandom(buffer, count))
            throw std::runtime_error("system failed to generate random data.");
    }

private:
    HMODULE hLib;
    BOOLEAN (APIENTRY *RtlGenRandom)(void*, ULONG);
};

}}

#endif
