/****************************************************
System scan header class

@Author Ankit Singh (ankit@devgeek.co)  
@Copyright 2013 devgeek.co
******************************************************/

#ifndef __SYSSCAN_H_INCLUDED__
#define __SYSSCAN_H_INCLUDED__

#include <boost/filesystem/convenience.hpp>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <magic.h>

#include "duff_utils.h"

using namespace std;
namespace bf = boost::filesystem; 

int sscan_dir(bf::path);

class sys_scan {
 public:
  int sscan(string);
};

#endif __SYSSCAN_H_INCLUDED__
