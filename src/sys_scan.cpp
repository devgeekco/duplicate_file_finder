/*********************************************************************
* This module is for scan the system and sync all MD5 of the files 
* to the database.
*
* @Author Ankit Singh (ankit@devgeek.co)
* @Copyright 2013 devgeek.co
*
**********************************************************************/

#include "sys_scan.h"

// Scans each folder and its sub-directory
int sys_scan::sscan(string folder_path) {
  //possible files to be excluded from duplicate finder list
  boost::regex pattern("(.*)(.git)(.*)|(.*)(.~)") ;

  BOOST_FOREACH(bf::path folder_path,
                boost::make_iterator_range(
                                           bf::recursive_directory_iterator(bf::path(folder_path)),
                                           bf::recursive_directory_iterator())) {
    if(!boost::regex_match (folder_path.string(), pattern))
      cout << folder_path.string() << endl;
  }
  return 0;
}
