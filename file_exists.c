/* 
  Hassan Khan <hassan.khan@uoguelph.ca>
  University of Guelph
  Buffer Overflow Lab

  Program that verifies that the argument file exists
  Note: This is a buggy program and will only run on the distributed VM
  (C) Hassan Khan, Do not distribute
*/ 
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  
  char command[256] = "/bin/ls ";
  FILE *file = NULL;
  char line[1024];
  char TEMP_FILE_NAME[8] = "temp_op";
  int rv = 0;

  //Verify the number of arguments
  if (argc != 2) {
    printf("Usage: %s <file-to-test>\n", argv[0]);
    return;
  }

  //use ls command to write to temp_op whether the file exists
  strncat(command, argv[1], 128);
  strncat(command, " > ", 3);
  strncat(command, TEMP_FILE_NAME, 8);
  strncat(command, " 2> /dev/null", 13);
  rv = system(command);
  if (rv == -1) {
     printf("Error running system command\n");
     return 0;
  }
  
  //read output of the above command
  if ((file = fopen("temp_op", "r")) == NULL) {
     printf("File read error\n");
     return 0;
  }

  fscanf(file, "%[^\n]", line);
  fclose(file);

  //cleanup
  if (system("rm temp_op") == -1) {
    printf("File delete error: temp_op\n");
  }

  //check the output to confirm file existance
  if (strncmp(line, argv[1], strlen(argv[1])) == 0)
    return 1;
  else
    return 0;
}   
