#pragma once

#include <stdexcept>
#include <vector>

class Bar {
public:
  Bar(int value) : m_value(value){};

  int getValue() const { return m_value; }
  void setValue(const int value) { m_value = value; }

private:
  int m_value;
};

class Foo {
public:
  Bar &getBar() { return m_bar; }
  const Bar &getBar() const { return m_bar; }

  int getValue() const { return m_value; }
  void setValue(const int value) { m_value = value; }

private:
  Bar m_bar{42};
  int m_value{2};
};

struct BasicException : public std::runtime_error {};
struct OutOfMemoryException : BasicException {};