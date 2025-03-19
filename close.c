#include "close.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static size_t closure_id = 0;

// TODO: Support of custom types
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

// TODO: More arguments; tc3
void call_closure(closure_t c) {
  if (c.clo_captures_n > 0) {
    __asm__ volatile("mov %0, %%rdi;"
                     :
                     : "r"(c.clo_captures[0].cap_thing)
                     : "%rdi");
  }
  c.clo_fn();
}
