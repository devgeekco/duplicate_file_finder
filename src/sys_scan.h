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
#include <iostream>
#include <boost/regex.hpp>

using namespace std;

namespace bf = boost::filesystem;

class sys_scan {
 public:
  int sscan(string); // TODO: get type to pass function
};

#endif __SYSSCAN_H_INCLUDED__
