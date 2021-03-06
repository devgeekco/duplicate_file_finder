/*-------------------------------------------------------------------
Duff and sql Utils header class

@Author Ankit Singh (ankit@devgeek.co)
@Copyright 2013 devgeek.co
--------------------------------------------------------------------*/

#ifndef __DUFF_UTIL_H_INCLUDED__
#define __DUFF_UTIL_H_INCLUDED__

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <boost/filesystem/convenience.hpp>
#include <sqlite3.h> 

#include "md5.h"

using namespace std;
namespace bf = boost::filesystem;

// Class specific to utils required for the operations
class duff_utils {
 private:
  char * mdString;
 public:
  char * get_hash(string);
  char * get_hash_filename(string);
  int do_md5(char *, int);
  char* string_to_charstr(string);
};

// Class specific to db operations
class sqldb_utils {
 private:
  sqlite3 *db;
  int rc; // result of sql execution
  static int callback(void *, int, char**, char**);
  int sqlite3_exec_statement(char *, char *, const char*);
 public:
  int sqlite_open_db(char *); // try to open db else throw error
  int sqlite_create_db(char *, char *); // create new default DB
  int sqlite_insert_db(char *, char *); // (statement, table name)
  int sqlite_update_db(char *, char *); 
  int sqlite_delete_db(char *, char *); 
  int sqlite_select_db(char *, char *); // (select query, table name)
};

#endif __DUFF_UTIL_H_INCLUDED__
