#include <functional>

#include "internal.hpp"
#include "public_api.h"
#include <experimental/propagate_const>

template <typename TFunc> int Wrap(TFunc &&func) {
  try {
    std::invoke(std::move(func));
    return SUCCESS;
  } catch (const OutOfMemoryException &oome) {
    return OUT_OF_MEMORY;
  } catch (const BasicException &be) {
    return GENERAL_ERROR;
  } catch (...) {
    return UNEXPECTED_ERROR;
  }
}

template <typename TType, typename... TArgs> TType *allocate(TArgs &&...args) {
  return new TType(std::forward<TArgs...>(args)...);
}

// This must be const because of the std::memory_resource
template <typename TType> void deallocate(TType *obj) { delete obj; }

int foo_create(struct Foo **foo) {
  return Wrap([&] { *foo = allocate<Foo>(); });
}

int foo_get_value(const struct Foo *foo, int *value) {
  return Wrap([&] { *value = foo->getValue(); });
}

int foo_set_value(struct Foo *foo, const int value) {
  return Wrap([&] { foo->setValue(value); });
}

int foo_get_bar_mut(struct Foo *foo, struct Bar **bar) {
  return Wrap([&] { *bar = &foo->getBar(); });
}

int foo_get_bar(const struct Foo *foo, const struct Bar **bar) {
  return Wrap([&] { *bar = &foo->getBar(); });
}

int foo_get_bar_by_copy(const struct Foo *foo, struct Bar **bar) {
  return Wrap([&] { *bar = allocate<Bar>(foo->getBar()); });
}

void foo_destroy(struct Foo *foo) { deallocate(foo); }

int bar_get_value(const struct Bar *bar, int *value) {
  return Wrap([&] { *value = bar->getValue(); });
}

int bar_set_value(struct Bar *bar, const int value) {
  return Wrap([&] { bar->setValue(value); });
}

void bar_destroy(struct Bar *bar) { deallocate(bar); }
