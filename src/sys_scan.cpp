/*********************************************************************
* This module is for scanning the system and sync all MD5 of the files 
* to the database.
*
* @Author Ankit Singh (ankit@devgeek.co)
* @Copyright 2013 devgeek.co
**********************************************************************/

#include "sys_scan.h"

//possible files to be excluded from duplicate finder list
boost::regex pattern("(.*)(.rvm)(.*)|(.*)(.config)(.*)|(.*)(CMakeFiles)(.*)|(.*)(.git)(.*)|(.*)(.~)") ;
int thread = 0;
duff_utils dutils;
magic_t myt;

// Recognises each file type
// take MD5 of the file and save it to the database with absolute path
// if directory and then create a new thread 'sscan_dir' to scan it
int sys_scan::sscan(string folder_path) {
  int filesize;
  try {
    if (bf::exists(folder_path)) {
      if(!boost::regex_match (folder_path, pattern)) {
	if (is_regular_file((bf::path) folder_path)) {// is p a regular file? 
	  filesize = file_size((bf::path) folder_path);
	  cout << "\n"<< folder_path << " size is " << filesize << '\n';
	  
	  myt = magic_open(MAGIC_CONTINUE|MAGIC_ERROR/*|MAGIC_DEBUG*/|MAGIC_MIME);
	  magic_load(myt,NULL);
	  printf("magic output: '%s'\n",magic_file(myt,dutils.string_to_charstr(folder_path)));
	  magic_close(myt);
	  
	  dutils.get_hash(folder_path);
	  dutils.get_hash_filename(folder_path);
	} else if (is_directory((bf::path) folder_path)) {     // is p a directory?
	  cout <<  "\n#### " << folder_path << " is a directory containing:\n\n";
	  boost::thread ss_thread(&sscan_dir,(bf::path) folder_path);
	  ss_thread.join();
	}
	else
	  cout << folder_path << " exists, but is neither a regular file nor a directory\n";	    
      }
    } else
      cout << "\tOoops! "<< folder_path << " does not exist\n";
  } catch (const bf::filesystem_error& ex) {
    cout << ex.what() << "\n";
  }
  return 0;
}

// Thread function Scans each folder
int sscan_dir(bf::path folder_path) {
  cout << "## New Thread No:: " << thread++ << " for directory " << folder_path.string() << " ##\n";  
  sys_scan ss;
  bf::directory_iterator end_iter;
  for (bf::directory_iterator dir_itr(folder_path); dir_itr != end_iter; ++dir_itr) {
      if(!boost::regex_match (dir_itr->path().string(), pattern)) {
      	ss.sscan(dir_itr->path().string());
      }
    }

  return 0; 
} 
