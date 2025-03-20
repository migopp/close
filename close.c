#include "close.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

capture_t init_capture(capture_tn type, void *c) {
  capture_t capture;
  capture.cap_typename = type;
  switch (type) {
  case UINT8: {
    capture.cap_thing.u8 = *(uint8_t *)c;
    break;
  }
  case UINT16: {
    capture.cap_thing.u16 = *(uint16_t *)c;
    break;
  }
  case UINT32: {
    capture.cap_thing.u32 = *(uint32_t *)c;
    break;
  }
  case UINT64: {
    capture.cap_thing.u64 = *(uint64_t *)c;
    break;
  }
  case VOIDPTR: {
    capture.cap_thing.v = c;
    break;
  }
  case CHARPTR: {
    capture.cap_thing.c = (char *)c;
    break;
  }
  default:
    break;
  }
  return capture;
}

void deinit_capture() {}

closure_t init_closure(func_t fn, size_t caps, ...) {
  va_list args;
  va_start(args, caps);
  closure_t closure;
  closure.clo_fn = fn;
  closure.clo_captures_n = caps;
  capture_t *capture_space = NULL;
  if (caps > 0) {
    capture_space = malloc(caps * sizeof(capture_t));
  }
  closure.clo_captures = capture_space;
  for (size_t i = 0; i < caps; ++i) {
    closure.clo_captures[i] = va_arg(args, capture_t);
  }
  va_end(args);
  return closure;
}

void deinit_closure(closure_t c) { free(c.clo_captures); }

// TODO: More arguments; tc3
void call_closure(closure_t c) {
  if (c.clo_captures_n > 0) {
    __asm__ volatile("mov %0, %%rdi;"
                     :
                     : "r"(c.clo_captures[0].cap_thing)
                     : "%rdi");
  }
  if (c.clo_captures_n > 1) {
    __asm__ volatile("mov %0, %%rsi;"
                     :
                     : "r"(c.clo_captures[1].cap_thing)
                     : "%rsi");
  }
  if (c.clo_captures_n > 2) {
    __asm__ volatile("mov %0, %%rdx;"
                     :
                     : "r"(c.clo_captures[2].cap_thing)
                     : "%rdx");
  }
  if (c.clo_captures_n > 3) {
    __asm__ volatile("mov %0, %%rcx;"
                     :
                     : "r"(c.clo_captures[3].cap_thing)
                     : "%rcx");
  }
  if (c.clo_captures_n > 4) {
    __asm__ volatile("mov %0, %%r8;"
                     :
                     : "r"(c.clo_captures[4].cap_thing)
                     : "%r8");
  }
  if (c.clo_captures_n > 5) {
    __asm__ volatile("mov %0, %%r9;"
                     :
                     : "r"(c.clo_captures[5].cap_thing)
                     : "%r9");
  }
  if (c.clo_captures_n > 6) {
    for (size_t i = c.clo_captures_n - 1; i > 5; --i) {
      __asm__ volatile("push %0;" : : "r"(c.clo_captures[i].cap_thing) :);
    }
  }
  c.clo_fn();
}
