#include "public_api.h"

int test() {
  struct Foo *foo;
  if (foo_create(&foo) != SUCCESS) {
    return -1;
  };
  if (foo_set_value(foo, 42) != SUCCESS) {
    return -2;
  }
  int value = 0;
  if (foo_get_value(foo, &value) != SUCCESS) {
    return -3;
  }

  const struct Bar *const_bar;
  // This is just warning
  if (foo_get_bar_mut(foo, &const_bar) != SUCCESS) {
    return -4;
  }

  struct Bar *bar;
  // This is just warning
  if (foo_get_bar(foo, &bar) != SUCCESS) {
    return -4;
  }

  return value;
}
