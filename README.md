# close

Simulated closures in C.

## Closures

Closures are an incredibly useful language feature, even in the context of lower-level programming.
Consider, for example, the threading mechanism of a rudimentary kernel.
If it were implemented with off-level threads, there may be some work the main thread wanted executed after switching:

```c
void off_level_handler_work(void) {
    closure_t *to_do = poll(work_queue);
    call_closure(to_do);
    // ...
    context_switch(me, to);
}
```

Then, it's convenient to provide this work in the form of a closure, so that no other context is needed for the executing thread.

If we were writing C++, we could use the built-in features of the language (lambda expressions), but alas the simplicity of C is enticing.

## Usage

The general interface is available in [`cheap.h`](https://github.com/migopp/close/blob/main/close.h).
But, here I'll provide a small use example:

```c
#include "close.h"
#include <stdio.h>

// A sample user-defined type.
typedef struct thing_t {
    unsigned a;
    unsigned b;
    struct thing_t *next;
} thing_t;

// This is the chunk of code we want to run when our closure is called.
//
// The variables to be captured must be the first arguments to the function.
// If a user-defined type is desired to be captured, it must be passed as a pointer.
void func(uint8_t m, uint64_t n, thing_t *t) {
    printf("| m = %c, n = %llu, t->a = %u, t->b = %u, t->next = %p\n", m, n, t->a, t->b, t->next);
}

int main(void) {
    // Init the variables we would like to capture.
    uint8_t m = 27;
    uint64_t n = 0x4242424242424242;
    thing_t t = {.a = 1337, .b = 2027, .next = NULL};

    // Now we manually capture them.
    //
    // This is with `init_capture(capture_tn type, void *c)`,
    // so `type` is the type to be captured (enum defined in `close.h`)
    // and `c` is a pointer to the captured value.
    capture_t c_m = init_capture(UINT8, &m);
    capture_t c_n = init_capture(UINT64, &n);
    // For user-defined types, we say that this is `VOIDPTR`,
    // meaning that the capture is of the pointer to the user-defined type
    // passed in.
    //
    // And thus, `t` must live longer than `c_t`!
    //
    // As this fact is rather finnicky and error-prone, I may revise it in
    // the future through a macro or something of that nature.
    capture_t c_t = init_capture(VOIDPTR, &t);

    // We can init the closure by specifying what to capture.
    //
    // This is done with `init_closure(func_t fn, size_t caps, ...)`
    // where the variadic arguments are the `capture_t` variables produced above.
    closure_t c = init_closure((func_t)func, 3, c_m, c_n, c_t);

    // Now we can use the closure wherever we want!
    call_closure(c);
    return 0;
}
```

Note that you should also clean up with `deinit_capture` and `deinit_closure` wherever possible.
At this time `init_closure` actually makes an allocation for the captured variables, so this should be cleaned up.

## Building

Clone this repository,

```
git clone git@github.com:migopp/close.git
```

then use make or manually compile:

```
make
```

(I do actually hope to get off of `make` at some point and integrate with a custom build system, but for now...)

> [!WARNING]
> This library is experimental and not quite polished. Breaking changes may occur at any time.
