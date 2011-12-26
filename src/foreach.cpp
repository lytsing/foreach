/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   Tue April 15 2008
   Copyright (C) 2008 deli <hlqing@gmail.com>
   $Id: foreach.cpp 94 2008-04-16 02:36:35Z deli $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/*
     __                          _     
    / _|                        | |    
   | |_ ___  _ __ ___  __ _  ___| |__  
   |  _/ _ \| '__/ _ \/ _` |/ __| '_ \
   | || (_) | | |  __/ (_| | (__| | | |
   |_| \___/|_|  \___|\__,_|\___|_| |_|

   Don't Repeat Yourself
                     -- Dave Thomas */

#include <iostream>
#include <string>
#include <getopt.h>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <unistd.h>
#include "subst.h"

using namespace std;

/*  ------------------- DEFINITIONS -------------------------- */

#define BUFSZ PIPE_BUF
#define MAX_CONCURRENCY 20000

static void print_help(const char* progname);

/* simple little function to write an error string and exit */
static void err(const char* s) {
    fprintf(stderr, "%s\n", s);
    exit(EXIT_FAILURE);
}

const struct option long_options[] = {
    { "count", 1, NULL, 'c' },
    { "number", 1, NULL, 'n' },
    { "help", 0, NULL, 'h' },
    { "timeout", 1, NULL, 't' },
    { "version", 0, NULL, 'v' },
    { NULL, 0, NULL, 0 }
};

const char short_options[] = "c:n:t:hv";

const char* VERSION = "0.0.1";  // Version of foreach

/*  --------------------- GLOBALS ---------------------------- */
int requests = 1;       // Number of requests to make
int concurrency = 1;    // Number of multiple requests to make

int main(int argc, char *argv[]) {
    int ret;
    char* cmd = NULL;
    char buf[BUFSZ];
    int fd;
    int len;

    if (argc == 1) {
        cout << "foreach: missing command operand\n";
        cout << "Try `foreach --help' for more information." << endl;
        return -1;
    }

    while (true) {
        int option_index = 0;

        ret = getopt_long(argc, argv, short_options,
                          long_options, &option_index);

        if (ret == -1) break;

        switch (ret) {
            case 'n':
                requests = atoi(optarg);
                if (requests <= 0) {
                    err("Invalid number of requests\n");
                }
                break;
            case 'c':
                concurrency = atoi(optarg);
                break;
            case 'v':
                cout << "foreach " << VERSION << endl;
                return 0;
            case '?':
            default:
                print_help(argv[0]);
        }
    }

    if (optind >= argc) {
        print_help(argv[0]);
    }

    if ((concurrency < 0) || (concurrency > MAX_CONCURRENCY)) {
        fprintf(stderr, "%s: Invalid Concurrency [Range 0..%d]\n",
                argv[0], MAX_CONCURRENCY);
        print_help(argv[0]);
    }

    if (concurrency > requests) {
        fprintf(stderr, "%s: Cannot use concurrency level greater than "
                "total number of requests\n", argv[0]);
        print_help(argv[0]);
    }

    fd = dup(STDIN_FILENO);
    len = read(fd, buf, BUFSZ);
    // cout << "len == " << len << endl;

    while (optind < argc) {
        cmd = argv[optind++];

        if (requests >= 1) {
            int retval = 0;
            for (int i = 0; i < requests; ++i) {
                if (len == 0) {
                    retval = system(cmd);
                } else {
                    string in(buf);
                    // XXX: name have problem.
                    string out(cmd);
                    string command = subst(in, out);
                    ret = system(command.c_str());
                }

                if (retval == 127)
                    cerr << "/bin/sh is not available\n";
                else if (retval == -1)
                    cerr << "system\n";
                else if (retval != 0)
                    cerr << "no cmd input\n";
            }
        }
    }

    close(fd);

    return 0;
}

static void print_help(const char* progname) {
    cout << "Usage: " << progname << " [options] [CMD]\n";
    cout << "Options are:\n";
    cout << "  -n,  --requests=n    Number of requests to perform\n";
    cout << "  -c,  --concurrency=n Number of multiple requests to make\n";
    cout << "  -v,  --version       Show the version of the foreach and exit\n";
    cout << "  -h,  --help          Display usage information (this message)" << endl;

    exit(EXIT_FAILURE);
}

