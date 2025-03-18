#include "close.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static size_t closure_id = 0;

capture_t init_capture(capture_tn type, void *c) {
  capture_t capture = {.cap_typename = type, .cap_thing.v = c};
  return capture;
}

void deinit_capture() {}

closure_t init_closure(func_t fn, size_t caps, ...) {
  va_list args;
  va_start(args, caps);
  closure_t closure;
  closure.clo_id = closure_id++;
  closure.clo_fn = fn;
  capture_t *capture_space = malloc(caps * sizeof(capture_t));
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
  // Place captures here with inline assembly
  //
  // So that they appear to be in the first args
  c.clo_fn();
}
