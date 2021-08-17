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

struct BarReference {
  struct Bar *bar;
};

int foo_create(struct Foo **foo);

int foo_get_value(const struct Foo *foo, int *value);
int foo_set_value(struct Foo *foo, const int value);

// This is similar to iterators, where the vertex/edge/property is contained by
// the iterators, therefore a non const pointer is necessary to retreive a non
// const member
// This means the ownership cannot be represented by the constness of objects,
// because the iterators must be able to return non const objects that shouldn't
// be freed by the user. Alternatively to the current approach the mutable
// functions could return a copy, but I don't think that it would the API
// better, but worse.
int foo_get_bar(struct Foo *foo, struct BarReference *bar);

// This is similar to getting a vertex, because the returned value is newly
// contruscted
int foo_get_bar_by_copy(const struct Foo *foo, struct Bar **bar);

// This must receive the object by non const pointer, because the memory
// resource cannot free the allocated memory via a const pointer
// Therefore we cannot create a proper const correct API: for returning a vertex
// from a graph the returned vertex must be mutable in order to be freed by the
// user.
// We can say we provide a const correct API when it is possible (e.g.:
// iterators), but I am not sure if that is helpful, because mixing the styles
// can be confusing.
void foo_destroy(struct Foo *foo);

int bar_get_value(const struct Bar *bar, int *value);
// For setters the objects has to be passed as non const pointer, therefore if
// we keep the constness for signaling the ownership and start to receive
// objects by non const pointer, then it will confuse everybody not just the
// users.
int bar_set_value(struct Bar *bar, const int value);

void bar_destroy(struct Bar *bar);

#ifdef __cplusplus
}
#endif
