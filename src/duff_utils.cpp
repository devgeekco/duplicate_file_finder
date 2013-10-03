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
  
  MD5((unsigned char*) file_buffer, fsize, (unsigned char*) &digest);
  char mdString[33];
  
  for(int i = 0; i < 16; i++)
    sprintf(&mdString[i*2], "%02x", (unsigned int) digest[i]);
  
  printf("md5 digest of %s: %s\n", file_name_char, mdString);
  munmap(file_buffer, fsize);
  return 0;
}

unsigned long duff_utils::get_size_by_fd(int fd) {
    struct stat statbuf;
    if(fstat(fd, &statbuf) < 0) exit(-1);
    return statbuf.st_size;
}
