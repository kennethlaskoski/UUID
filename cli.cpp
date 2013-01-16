/********************************************************************\
 * cli.cpp -- UNIX command line interface                           *
 *                                                                  *
 * Copyright (C) 2009 Kenneth Laskoski                              *
 *                                                                  *
\********************************************************************/
/** @file cli.cpp
    @brief UNIX command line interface
    @author Copyright (C) 2009 Kenneth Laskoski
    based on work by
    @author Copyright (C) 2004-2008 Ralf S. Engelschall <rse@engelschall.com>

    Use, modification, and distribution are subject
    to the Boost Software License, Version 1.0.  (See accompanying file
    LICENSE_1_0.txt or a copy at <http://www.boost.org/LICENSE_1_0.txt>.)
*/

#include "kashmir/md5.h"
#include "kashmir/uuid_gen.h"
#include "kashmir/system/devrand.h"

#include <iostream>
#include <fstream>

#include <unistd.h>

namespace
{
    using std::ostream;
    using std::ofstream;

    int n = 1;
    int v = 4;

    ostream* outp = &std::cout;
    ofstream ofile;

    void parse_cmd_line(int argc, char *argv[])
    {
        int ch;
        char *p;

        while ((ch = getopt(argc, argv, "n:o:v:")) != -1) {
            switch (ch) {
                case 'n':
                    n = strtoul(optarg, &p, 10);
                    if (*p != '\0' || n < 1)
                        std::cerr << "invalid argument for option 'n'\n";
                    break;
                case 'o':
                    ofile.open(optarg);
                    outp = &ofile;
                    break;
                case 'v':
                    v = strtoul(optarg, &p, 10);
                    if (*p == '\0' && (3 <= v && v <= 5))
                        break;
                    std::cerr << "invalid argument for option 'v'\n";
                    // fall through
                default:
                    exit(1);
            }
        }
        argv += optind;
        argc -= optind;
    }
}

int main(int argc, char *argv[])
{
    using kashmir::md5_t;

    using kashmir::uuid::uuid_gen;
    using kashmir::system::DevRand;

    parse_cmd_line(argc, argv);
    ostream& out = *outp;

    if (v == 3)
    {
        out << md5_t() << '\n';
        return 0;
    }

    DevRand devrand;
    for (int i = 0; i < n; i++)
        out << *uuid_gen(devrand) << '\n';

    return 0;
}
