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
  char *file_name_char = new char[file.length() + 1];  
  strcpy(file_name_char,file.c_str()); // conversion from string to char *
  
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
