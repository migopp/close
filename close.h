#ifndef CLOSE
#define CLOSE

#include <stddef.h>
#include <stdint.h>

// Typename of a captured variable
//
// NOTE: Right now this is rather limited for simplicity of implementation,
// however it could be expanded if needed
typedef enum capture_tn {
  UINT8,
  UINT16,
  UINT32,
  UINT64,
  VOIDPTR,
  CHARPTR
} capture_tn;

typedef struct capture_t {
  capture_tn cap_typename;
  union {
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    void *v;
    char *c;
  } cap_thing;
} capture_t;

typedef void (*func_t)(void);
typedef struct closure_t {
  size_t clo_id;
  func_t clo_fn;
  size_t clo_captures_n;
  capture_t *clo_captures;
} closure_t;

capture_t init_capture(capture_tn, void *);
void deinit_capture();
closure_t init_closure(func_t, size_t, ...);
void deinit_closure(closure_t);
void call_closure(closure_t);

#endif // !CLOSE
