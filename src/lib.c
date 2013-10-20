#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "lib.h"

static int DEFAULT_STAR_FILE_PERMS = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

int star_create_archive(const char* star_file_name, char** files) {
  int star_file;
  if( ( star_file = open(star_file_name, O_WRONLY | O_CREAT, DEFAULT_STAR_FILE_PERMS) ) == -1 ) {
    fprintf(stderr, "Could not open %s\n", star_file_name);
    return -1;
  }

  close(star_file);
  return 0;
}
