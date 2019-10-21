CC=gcc
CFLAGS= -z execstack -fno-stack-protector

all: file_exists is_log_file 

file_exists: file_exists.c
	$(CC) -o file_exists file_exists.c $(CFLAGS)

is_log_file: is_log_file.c
	$(CC) -o is_log_file is_log_file.c $(CFLAGS)

clean:
	rm file_exists is_log_file
