/********************************************************************\
 * app.h -- UUID GUI application class                              *
 *                                                                  *
 * Copyright (C) 2009 Kenneth Laskoski                              *
 *                                                                  *
\********************************************************************/
/** @file app.h
    @brief graphical user interface to UUIDs defined by RFC 4122
    @author Copyright (C) 2009 Kenneth Laskoski

    Use, modification, and distribution are subject
    to the Boost Software License, Version 1.0.  (See accompanying file
    LICENSE_1_0.txt or a copy at <http://www.boost.org/LICENSE_1_0.txt>.)
*/

#include "../kashmir/devrandom.h"

#include <wx/wx.h>

class App : public wxApp
{
    kashmir::system::DevRandom devrandom;

public:
    virtual bool OnInit();

    kashmir::system::DevRandom& DevRandom()
    {
        return devrandom;
    }
};

DECLARE_APP(App)
