/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   Tue April 15 2008
   Copyright (C) 2008 deli <huangliqing@broncho.org>
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

// http://school.21tx.com/2005/03/13/18210.html

#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

using namespace std;

static int my_system(const char* pCmd, char* pResult, int size)
{
    int fd[2];
    int pid;
    int count;
    int left;
    char* p = 0;
    int maxlen = size -1;

    memset(pResult, 0, size);

    if (pipe(fd)) {
        fprintf(stderr, "pipe error\n");
        return -1;
    }

    if ((pid = fork()) == 0) {
        // child process
        int fd2[2];
        if (pipe(fd2)) {
            fprintf(stderr, "pipe2 error");
                return -1;
        }
        close (1);
        dup2(fd2[1], 1);
        close(fd2[1]);
        system(pCmd);
        read(fd2[0], pResult, maxlen);
        
        pResult[strlen(pResult)-1] = 0;
        write(fd[1], pResult, strlen(pResult));
        close(fd2[0]);
        exit (0);
    }

    // parent process
    close(fd[1]);
    p = pResult;
    left = maxlen;

    while ((count = read(fd[0], p, left))) {
        p += count;
        left -= count;
        if (left == 0)
            break;
    }

    close(fd[0]);

    return 0;
}

int main(int argc, char* argv[])
{
    char result[1024];

    my_system("/sbin/ifconfig", result, 1024);

    printf("the result is \n\n%s\n", result);

    return 0;
}
