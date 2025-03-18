#include "../close.h"
#include <stdio.h>

void fn_1(void) { printf("HELLO FN!\n"); }

int main(void) {
  closure_t c = init_closure(fn_1, 0);
  call_closure(c);
  return 0;
}
