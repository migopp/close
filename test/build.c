// Experiementing with native build systems...
//
// Yes, I know that done as is, this is sorta stupid, but the idea is
// that this file can be compiled with `cc -o build build.c` and then
// it builds the test file.
//
// Perhaps a similar idea would be idea for building everything, as
// then the only dependency for building is `cc` itself...

#include <stdio.h>
#include <stdlib.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

int main(void) {
  printf(YELLOW "NOTE: " RESET "Building `close` test files\n");

  printf(BLUE "1: " RESET "Building `close` library files\n");
  const char *cmd_build_close = "cd .. && make clean && make";
  int rc = system(cmd_build_close);
  if (rc < 0) {
    fprintf(stderr,
            RED "FAILURE: " RESET "Build of `close` failed, aborting...");
    exit(-1);
  }

  printf(BLUE "2: " RESET "Building test infra and linking in `close` lib\n");
  const char *cmd_build_test = "gcc -Werror -Wall -O0 -g -std=c99 -o "
                               "./bin/test test.c ../target/close.o";
  rc = system(cmd_build_test);
  if (rc < 0) {
    fprintf(stderr,
            RED "FAILURE: " RESET "Build of `test` failed, aborting...");
    exit(-1);
  }

  printf(BLUE "3: " RESET "Running `test`\n");
  const char *cmd_run_test = "./bin/test";
  rc = system(cmd_run_test);
  if (rc != 0) {
    fprintf(stderr, RED "FAILURE: " RESET "Run of `test` failed, aborting...");
    exit(-1);
  }

  printf(GREEN "SUCCESS: " RESET "Build complete!\n");
  return 0;
}
