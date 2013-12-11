/*********************************************************************
* This module is for scanning the system and sync all MD5 of the files 
* to the database.
*
* @Author Ankit Singh (ankit@devgeek.co)
* @Copyright 2013 devgeek.co
**********************************************************************/

#include "sys_scan.h"

//possible files to be excluded from duplicate finder list
boost::regex pattern("(.*)(.rvm)(.*)|(.*)(.Trash)(.*)|(.*)(.DS_Store)(.*)|(.*)(.android)(.*)|(.*)(.bunclde)(.*)|(.*)(.macports)(.*)|(.*)(.gradle)(.*)|(.*)(.heroku)(.*)|(.*)(.config)(.*)|(.*)(CMakeFiles)(.*)|(.*)(.git)(.*)|(.*)(.~)") ;
int thread = 0;
duff_utils dutils;
magic_t myt;
sqldb_utils sqlu;

// Recognises each file type
// take MD5 of the file and save it to the database with absolute path
// if directory and then create a new thread 'sscan_dir' to scan it
int sys_scan::sscan(string folder_path) {
  int filesize;
  char sql[520] ;
  char tablename[] = "SCANRESULT";
  char * folderp_cstr = dutils.string_to_charstr(folder_path);
  char* hash_file = (char *) malloc(33);  
  char* hash_filename = (char *) malloc(33);  
  try {
    if (bf::exists(folder_path)) {
      if(!boost::regex_match (folder_path, pattern)) {
	if (is_regular_file((bf::path) folder_path)) {// is p a regular file? 
	  filesize = file_size((bf::path) folder_path);
	  cout << "\n"<< folder_path << " size is " << filesize << '\n';
	  
	  myt = magic_open(MAGIC_CONTINUE|MAGIC_ERROR/*|MAGIC_DEBUG*/|MAGIC_MIME);
	  magic_load(myt,NULL);
	  //printf("magic output: '%s'\n",magic_file(myt,folderp_cstr));
	  strcpy(hash_file, dutils.get_hash(folder_path));
	  strcpy(hash_filename, dutils.get_hash_filename(folder_path));
	  
	  sprintf( sql, "INSERT INTO %s (FILE, FILE_HASH, NAME_HASH, SIZE, FILE_TYPE, DUP_COUNT) VALUES ('%s','%s','%s',%d,'%s',0);", tablename, folderp_cstr, hash_file, hash_filename, filesize, magic_file(myt,folderp_cstr));
	  magic_close(myt);
	  // sprintf( sql, "SELECT * FROM %s",tablename);
	  printf("Full SQL INSERT STATEMENT::: %s ", sql);
	  sqlu.sqlite_insert_db(sql, tablename); // insert file data into table
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
