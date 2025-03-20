#include "../close.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define assert(exp)                                                            \
  if (!(exp)) {                                                                \
    fprintf(stderr, "ASSERTION FAILED: %s, FILE: %s, LINE: %d\n", #exp,        \
            __FILE__, __LINE__);                                               \
    exit(-1);                                                                  \
  }

void fn_no_caps(void) { assert(true); }

void fn_1_u32(uint32_t n) { assert(n == 1337); }

void fn_1_u8(uint8_t n) { assert(n == 255); }

void fn_2_u32(uint32_t n, uint32_t m) { assert(n == 420 && m == 6969); }

void fn_6_u32(uint32_t n, uint32_t m, uint32_t o, uint32_t p, uint32_t q,
              uint32_t r) {
  assert(n == 420 && m == 6969 && o == 1337 && p == 8008135 && q == 43110 &&
         r == 42);
}

void fn_7_u32(uint32_t n, uint32_t m, uint32_t o, uint32_t p, uint32_t q,
              uint32_t r, uint32_t s) {
  assert(n == 420 && m == 6969 && o == 1337 && p == 8008135 && q == 43110 &&
         r == 42 && s == 27);
}

int main(void) {
  // `fn_no_args`
  printf("| testing fn w/ no captures\n");
  closure_t c = init_closure(fn_no_caps, 0);
  call_closure(c);
  deinit_closure(c);

  // `fn_1_u32`
  printf("| testing fn w/ 1 uint32_t capture\n");
  uint32_t n_u32 = 1337;
  capture_t c_n = init_capture(UINT32, &n_u32);
  c = init_closure((func_t)fn_1_u32, 1, c_n);
  call_closure(c);
  deinit_closure(c);

  // `fn_1_u8`
  printf("| testing fn w/ 1 uint8_t capture\n");
  uint8_t n_u8 = 255;
  c_n = init_capture(UINT8, &n_u8);
  c = init_closure((func_t)fn_1_u8, 1, c_n);
  call_closure(c);
  deinit_closure(c);

  // `fn_2_u32`
  printf("| testing fn w/ 2 uint32_t captures\n");
  n_u32 = 420;
  uint32_t m_u32 = 6969;
  c_n = init_capture(UINT32, &n_u32);
  capture_t c_m = init_capture(UINT32, &m_u32);
  c = init_closure((func_t)fn_2_u32, 2, c_n, c_m);
  call_closure(c);
  deinit_closure(c);

  // `fn_6_u32`
  printf("| testing fn w/ 6 uint32_t captures\n");
  n_u32 = 420;
  m_u32 = 6969;
  uint32_t o_u32 = 1337;
  uint32_t p_u32 = 8008135;
  uint32_t q_u32 = 43110;
  uint32_t r_u32 = 42;
  c_n = init_capture(UINT32, &n_u32);
  c_m = init_capture(UINT32, &m_u32);
  capture_t c_o = init_capture(UINT32, &o_u32);
  capture_t c_p = init_capture(UINT32, &p_u32);
  capture_t c_q = init_capture(UINT32, &q_u32);
  capture_t c_r = init_capture(UINT32, &r_u32);
  c = init_closure((func_t)fn_6_u32, 6, c_n, c_m, c_o, c_p, c_q, c_r);
  call_closure(c);
  deinit_closure(c);

  // `fn_7_u32`
  printf("| testing fn w/ 7 uint32_t captures\n");
  n_u32 = 420;
  m_u32 = 6969;
  o_u32 = 1337;
  p_u32 = 8008135;
  q_u32 = 43110;
  r_u32 = 42;
  uint32_t s_u32 = 27;
  c_n = init_capture(UINT32, &n_u32);
  c_m = init_capture(UINT32, &m_u32);
  c_o = init_capture(UINT32, &o_u32);
  c_p = init_capture(UINT32, &p_u32);
  c_q = init_capture(UINT32, &q_u32);
  c_r = init_capture(UINT32, &r_u32);
  capture_t c_s = init_capture(UINT32, &s_u32);
  c = init_closure((func_t)fn_7_u32, 7, c_n, c_m, c_o, c_p, c_q, c_r, c_s);
  call_closure(c);
  deinit_closure(c);

  return 0;
}
