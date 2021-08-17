#pragma once

#define SUCCESS 0
#define OUT_OF_MEMORY 10
#define GENERAL_ERROR 100
#define UNEXPECTED_ERROR 1000

#ifdef __cplusplus
extern "C" {
#endif

struct Foo;
struct Bar;

int foo_create(struct Foo **foo);

int foo_get_value(const struct Foo *foo, int *value);
int foo_set_value(struct Foo *foo, const int value);

// This is similar to iterators, where the vertex/edge/property is contained by
// the iterators, therefore a non const pointer is necessary to retreive a non
// const member
int foo_get_bar_mut(struct Foo *foo, struct Bar **bar);
int foo_get_bar(const struct Foo *foo, const struct Bar **bar);

// This is similar to getting a vertex, because the returned value is newly
// contruscted
int foo_get_bar_by_copy(const struct Foo *foo, struct Bar **bar);

// This must receive the object by non const pointer, because the memory
// resource cannot free the allocated memory via a const pointer
void foo_destroy(struct Foo *foo);

int bar_get_value(const struct Bar *bar, int *value);
int bar_set_value(struct Bar *bar, const int value);

void bar_destroy(struct Bar *bar);

#ifdef __cplusplus
}
#endif
