/* 
  Hassan Khan <hassan.khan@uoguelph.ca>
  University of Guelph
  Buffer Overflow Lab

  Program that verifies that the argument is a valid log file

*/ 
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verify(char *buffer) {
  char local_buf[32];
  //printf("%p\n", local_buf);
  char VALID_SIGNATURE[23] = "LOG_FILE VERSION_CODE=";
  int rv = 0;

  //valid log file should contain VALID_SIGNATURE
  strcpy(local_buf, buffer);
  rv = strncmp(VALID_SIGNATURE, local_buf, strlen(VALID_SIGNATURE));
  if ( rv == 0)
    return 1;
  return 0;
}

int main(int argc, char ** argv) {

  char command[256] = "./file_exists ";
  char buffer[1024];
  FILE *file = NULL;
  int rv = 0;

  //Verify the number of arguments
  if (argc != 2) {
    printf("Usage: %s <file-to-test>\n", argv[0]);
    return 0;
  }

  //Verify the supplied file exists
  strncat(command, argv[1], 244);
  rv = system(command);
  if (rv <= 0) {
    printf("%s does not exist\n", argv[1]);
    return 0;
  }
  
  //read file
  if ((file = fopen(argv[1], "r")) == NULL) {
    printf("File read error\n");
    return 0;
  }
  fscanf(file,"%[^\n]", buffer);
  fclose(file);
 
  if (verify(buffer) == 1)
    printf("Valid!!!\n");
  else
    printf("Invalid!!!\n");
  
}   
