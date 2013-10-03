/*-------------------------------------------------------------------
Duff Util header class

@Author Ankit Singh
@Copyright 2013
--------------------------------------------------------------------*/

#ifndef __DUFF_UTIL_H_INCLUDED__
#define __DUFF_UTIL_H_INCLUDED__

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <openssl/md5.h>
#include <iostream>
#include <boost/filesystem/convenience.hpp>
#include <sys/mman.h>
#include <sys/stat.h>

using namespace std;

namespace bf = boost::filesystem;

class duff_utils {
 public:
  int get_hash(string);
 private:
  unsigned long get_size_by_fd(int);
};

#endif __DUFF_UTIL_H_INCLUDED__
