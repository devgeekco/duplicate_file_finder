/* ----------------------------------------------------------------------------------
* Various Utils like hash functions, type conversions etc. will contain in this 
* class.
*
* @Author Ankit Singh (iankits) 
*
*
-----------------------------------------------------------------------------------*/

#include "duff_utils.h"

// get the hash value of the files
int duff_utils::get_hash(string file) {
  int fd;
  unsigned long fsize;
  char* file_buffer;
  unsigned char digest[MD5_DIGEST_LENGTH];
  char *file_name_char = string_to_charstr(file); 
  //char *file_name_char = new char[file.length() + 1];  
  //strcpy(file_name_char,file.c_str()); // conversion from string to char *
  
  fd = open(file_name_char, O_RDONLY);
  if(fd < 0) exit(-1);
  
  fsize = get_size_by_fd(fd);
  //  printf("file size:\t%lu\n", fsize);
  file_buffer = (char *) mmap(0, fsize, PROT_READ, MAP_SHARED, fd, 0);  
  
  do_md5(file_name_char, fsize);

  munmap(file_buffer, fsize);
  return 0;
}

// get the hash value of the files name i.e strings only
int duff_utils::get_hash_filename(string file) {
  int fd;
  char *file_name_char = new char[file.length() + 1];  
  strcpy(file_name_char,file.c_str()); // conversion from string to char *
  
  fd = open(file_name_char, O_RDONLY);
  if(fd < 0) exit(-1);
  
  cout << "MD5 of Strings ONLY: ";
  do_md5(file_name_char, strlen(file_name_char));

  return 0;
}

unsigned long duff_utils::get_size_by_fd(int fd) {
    struct stat statbuf;
    if(fstat(fd, &statbuf) < 0) exit(-1);
    return statbuf.st_size;
}

// Get MD5 of the given input for filename
char* duff_utils::do_md5(char * file_name, int fsize) {
  unsigned char digest[MD5_DIGEST_LENGTH];
  MD5((unsigned char*) file_name, fsize, (unsigned char*) &digest);
  
 for(int i = 0; i < 16; i++)
   sprintf(&mdString[i*2], "%02x", (unsigned int) digest[i]);
 
 printf("md5 digest of %s: %s\n", file_name, mdString);
 return mdString;
}

// converts string to char
char* duff_utils::string_to_charstr(string input_to_convert) {
  char * to_char = new char[input_to_convert.length() + 1];  
  strcpy(to_char,input_to_convert.c_str()); // conversion from string to char *
  return to_char;
} 

// Callback function for sqlite3 executions
int sqldb_utils::callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

// try to open database else throw error 
int  sqldb_utils::sqlite_open_db(char * db_name) {
  int status = 1;

   /* Open database */
   rc = sqlite3_open(db_name, &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      //exit(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
      status = 0; // SUCCESS
   }

  return status;
}

/* Create SQL Example statement 
   sql = "CREATE TABLE SCANRESULT("  \
         "FILE VARCHAR(255) PRIMARY KEY     NOT NULL," \
         "SIZE_HASH           CHAR(32)    NOT NULL," \
         "NAME_HASH           CHAR(32)    NOT NULL," \
         "SIZE                INT," \
	  "FILE_TYPE          CHAR(10)," \
         "DUP_COUNT           INT );";
 */
// creates new sqlite3 db
int sqldb_utils::sqlite_create_db(char * sql_create_table, char * table_name) {
  int status = 1;
  char *zErrMsg = 0;

  sqlite_open_db(table_name); // open db

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);

  if( rc != SQLITE_OK ){
     fprintf(stderr, "SQL error: %s\n", zErrMsg);
     sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Table created successfully\n");
    status = 0;
   }
  sqlite3_close(db);

  return status;
}

// SQL statement for inserting data into table
int sqldb_utils::sqlite_insert_db(char *sql_insert, char * table_name) {
  int status = 1;
  char *zErrMsg = 0;

  sqlite_open_db(table_name); // open db

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
     fprintf(stdout, "Records created successfully\n");
     status = 0;
   }
   sqlite3_close(db);
   return status;
}
