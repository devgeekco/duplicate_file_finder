/*------------------------------------------------------------------------------
This is the main class which runs the duplicate file finder

@Author Ankit Singh (ankit@devgeek.co)
@copyright 2013 devgeek.co
 -------------------------------------------------------------------------------*/

#include "run_duff.h"

int main(int argc, char** argv) {
  
  if(argc<2){
    cout << "Syntax Error!" << endl;
    cout << "Usage:" << endl;
    cout << "\t" << argv[0] << " <Path to Folder to be scanned>\n" << endl;
    return -1;
  }
  
  cout << "\n\tScanning directory \"" << argv[1] << "\" \n\n";
  
  sys_scan ss;
  sqldb_utils sql_utils;
  char * sql = "CREATE TABLE SCANRESULT("	     \
    "FILE VARCHAR(255) PRIMARY KEY     NOT NULL,"    \
    "FILE_HASH           CHAR(32)    NOT NULL,"	     \
    "NAME_HASH           CHAR(32)    NOT NULL,"	     \
    "SIZE                INT,"			     \
    "FILE_TYPE          CHAR(10),"		     \
    "DUP_COUNT           INT );";

  sql_utils.sqlite_create_db(sql, "SCANRESULT");


  ss.sscan(argv[1]);

  return 0;
}
