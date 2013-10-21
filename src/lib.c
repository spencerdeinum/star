#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "lib.h"

static int DEFAULT_STAR_FILE_PERMS = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

static const size_t BUFFER_SIZE = 1024;

int star_create_archive(const char* star_file_name, char** files, int file_count) {
  int star_file;
  if( (star_file = open(star_file_name, O_WRONLY | O_CREAT, DEFAULT_STAR_FILE_PERMS)) == -1 ) {
    fprintf(stderr, "Could not create %s\n", star_file_name);
    return -1;
  }

  create_star_file_header(star_file, files, file_count);

  int file_to_archive;
  for(int i = 0; i < file_count; ++i) {
    if( (file_to_archive = open(files[i], O_RDONLY)) == -1 ) {
      fprintf(stderr, "Could not open %s, skipping\n", files[i]);
      break;
    }

    printf("Adding %s\n", files[i]);
    ssize_t bytes_written = append_to_star_file(star_file, file_to_archive);
    if( bytes_written < 0 ) {
      fprintf(stderr, "IO encountered while processing %s, exiting\n", files[i]);
      close(file_to_archive);
      close(star_file);
      return -1;
    }
    close(file_to_archive);
  }

  close(star_file);
  return 0;
}

void create_star_file_header(const int star_file, char** files, const int file_count) {
  write(star_file, &file_count, sizeof(file_count));
}

ssize_t append_to_star_file(const int star_file, const int file_to_append) {
  ssize_t total_bytes_written = 0;
  ssize_t bytes_read;
  ssize_t bytes_written;
  char buffer[BUFFER_SIZE];

  while( (bytes_read = read(file_to_append, buffer, BUFFER_SIZE)) > 0 ) {
    if( bytes_read == -1 ) {
      return -1;
    }
    bytes_written = write(star_file, buffer, (size_t)bytes_read);
    if(bytes_written == -1) {
      return -1;
    }
    total_bytes_written += bytes_written;
  }

  return total_bytes_written;
}
