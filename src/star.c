#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "lib.h"

static char* OPTSTRING = "c:h";

void print_help(void);

int main(int argc, char** argv)
{
  if( argc < 2 ) {
    print_help();
    return 0;
  }

  int option = getopt(argc, argv, OPTSTRING);

  if(option == 'c') {
    int fileCount = argc - optind;
    char** files = malloc(sizeof(char*) * (unsigned long)fileCount);

    for(int i = 0; i < fileCount; ++i) {
      files[i] = argv[optind + i];
    }

    int success = star_create_archive(optarg, files, fileCount);

    free(files);
    return success;
  }
  else if(option == 'h') {
    print_help();
    return 0;
  }
  else {
    print_help();
    return 0;
  }
}

void print_help(void) {
  puts("Available commands:");
  puts("star -c <star_file> <files_to_star>   - Create a new star file.");
}
