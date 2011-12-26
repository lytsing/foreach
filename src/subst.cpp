/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   Tue April 15 2008
   Copyright (C) 2008 deli <hlqing@gmail.com>
   $Id: subst.cpp 94 2008-04-16 02:36:35Z deli $

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

#include <iostream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

static bool space(char c)
{
    return isspace(c);
}

static bool not_space(char c)
{
    return !isspace(c);
}

static vector<string> split(const string& str)
{
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = str.begin();
    while (i != str.end()) {
        // ignore leading blanks
        i = find_if(i, str.end(), not_space);
        // find end of next word
        iter j = find_if(i, str.end(), space);

        // copy the characters in [i, j)
        if (i != str.end())
            ret.push_back(string(i, j));
        i = j;
    }
    return ret;
}

static int stoi(const string& str)
{
    int ret;
    // NOTE: You should probably do some checks to ensure that
    // this string contains only numbers. If the string is not
    // a valid integer, zero will be returned.
    ret = atoi(str.c_str());

    return ret;
}

string subst(const string& in, const string& out)
{
    typedef vector<string>::const_iterator iter;
    vector<string> vecs1 = split(in);
    vector<string> vecs2 = split(out);
    string ret;
    string tmp;

    vector<string>::size_type i;
    vector<string>::size_type j;

    for (i = 0; i != vecs1.size(); ++i) {
        for (j = 0; j != vecs2.size(); ++j) {
            if ((vecs2[j])[0] == '#' 
                && i == (vector<string>::size_type)stoi(tmp.assign(
                        vecs2[j], 1, (vecs2[i]).size() -1)) -1) {
                vecs2[j] = vecs1[i];
            }
        }
    }

    for (iter k = vecs2.begin(); k != vecs2.end(); ++k) {
        ret += *k + " ";
    }

    return ret;
}

#if 0
int main(int argc, char *argv[])
{
    string str1("210.34.0.222 43 bbs.xmu.edu.cn");
    string str2("echo #3 #1 #2");
    
    string str3 = subst(str1, str2);

    cout << str3 << endl;

    return 0;
}

#endif

