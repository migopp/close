#include "../close.h"
#include <stdint.h>
#include <stdio.h>

void fn_1(void) { printf("HELLO FN!\n"); }

void fn_2(uint32_t n) { printf("HELLO FN 2! %d\n", n); }

int main(void) {
  closure_t c = init_closure(fn_1, 0);
  call_closure(c);
  deinit_closure(c);

  uint32_t n = 56;
  printf("*** n thing: %d\n", n);
  capture_t c_n = init_capture(UINT32, &n);
  printf("*** c_n typename: %d\n", c_n.cap_typename);
  printf("*** c_n thing: %d\n", c_n.cap_thing.u32);
  c = init_closure((func_t)fn_2, 1, c_n);
  call_closure(c);
  deinit_closure(c);
  return 0;
}
