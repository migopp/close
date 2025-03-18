#include "close.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static size_t closure_id = 0;

capture_t init_capture(capture_tn type, void *c) {
  capture_t n_capture;
  if (type == UINT32) {
    n_capture.cap_typename = UINT32;
    n_capture.cap_thing.u32 = *(uint32_t *)c;
  }
  return n_capture;
}

void deinit_capture() {}

closure_t init_closure(func_t fn, size_t caps, ...) {
  va_list args;
  va_start(args, caps);
  closure_t closure;
  closure.clo_id = closure_id++;
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

void call_closure(closure_t c) {
  printf("*** Calling closure %zu\n", c.clo_id);
  if (c.clo_captures_n > 0) {
    printf("*** With capture: %d\n", c.clo_captures[0].cap_thing.u32);
    __asm__ volatile("mov %0, %%rdi;"
                     :
                     : "r"(c.clo_captures[0].cap_thing)
                     : "%rdi");
  }
  c.clo_fn();
}
