#include "../close.h"
#include <stdint.h>
#include <stdio.h>

void fn_no_args(void) { printf("| fn_no_args\n"); }

void fn_1_u32(uint32_t n) { printf("| fn_1_u32: %d\n", n); }

void fn_1_u8(uint8_t n) { printf("| fn_1_u8: %d\n", n); }

void fn_2_u32(uint32_t n, uint32_t m) { printf("| fn_2_u32: %d %d\n", n, m); }

int main(void) {
  // `fn_no_args`
  printf("| t0:\n");
  closure_t c = init_closure(fn_no_args, 0);
  call_closure(c);
  deinit_closure(c);

  // `fn_1_u32`
  printf("| t1:\n");
  uint32_t n_u32 = 1337;
  capture_t c_n = init_capture(UINT32, &n_u32);
  c = init_closure((func_t)fn_1_u32, 1, c_n);
  call_closure(c);
  deinit_closure(c);

  // `fn_1_u8`
  printf("| t2:\n");
  uint8_t n_u8 = 255;
  c_n = init_capture(UINT8, &n_u8);
  c = init_closure((func_t)fn_1_u8, 1, c_n);
  call_closure(c);
  deinit_closure(c);

  // `fn_2_u32`
  printf("| t3:\n");
  n_u32 = 420;
  uint32_t m_u32 = 6969;
  c_n = init_capture(UINT32, &n_u32);
  capture_t c_m = init_capture(UINT32, &m_u32);
  c = init_closure((func_t)fn_2_u32, 2, c_n, c_m);
  call_closure(c);
  deinit_closure(c);

  return 0;
}
