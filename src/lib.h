#ifndef __lib_h__
#define __lib_h__

#include <sys/stat.h>

int star_create_archive(const char* star_file_name, char** files, const int fileCount);

void create_star_file_header(const int star_file, char** files, const int fileCount);

ssize_t append_to_star_file(const int star_file, const int file);

#endif
