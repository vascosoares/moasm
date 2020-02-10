#pragma once
#include <cassert>
#include <functional>

template <typename T>
class prop {
public:
  using Getter = std::function<T()>;
  using Setter = std::function<void(T)>;

private:
  T __val__;
  Getter __getter__;
  Setter __setter__;

  void initialize() {
    __getter__ = [&]() { return __val__; }; 
    __setter__ = [&](T value) { __val__ = value; };
  }

  prop(const prop<T>&) = delete;
  prop(prop<T>&&) = delete;

public:
  prop() { initialize(); }
  prop(T o) : __val__(o) { initialize(); }

  prop(Getter getter, Setter setter) :
    __getter__(getter), __setter__(setter) {}

  virtual prop<T>& operator=(T o)
  { __setter__(o); return *this; }

  virtual operator T() const
  { return __getter__(); }

  virtual T operator++(int)
  { T t = __getter__(); __setter__(__getter__() + 1); return t; }

  virtual T operator--(int)
  { T t = __getter__(); __setter__(__getter__() - 1); return t; }

  virtual prop<T>& operator++()
  { __setter__(__getter__() + 1); return *this; }

  virtual prop<T>& operator--()
  { __setter__(__getter__() - 1); return *this; }

  #define COMPOUND_ASSIGNMENT(OP)                   \
    virtual prop<T>& operator OP##=(T o)         \
    { __setter__(__getter__() OP o); return *this; }

  COMPOUND_ASSIGNMENT(+)
  COMPOUND_ASSIGNMENT(-)
  COMPOUND_ASSIGNMENT(*)
  COMPOUND_ASSIGNMENT(/)
  COMPOUND_ASSIGNMENT(%)
  COMPOUND_ASSIGNMENT(>>)
  COMPOUND_ASSIGNMENT(<<)
  COMPOUND_ASSIGNMENT(&)
  COMPOUND_ASSIGNMENT(^)
  COMPOUND_ASSIGNMENT(|)

  #undef COMPOUND_ASSIGNMENT
};

template <typename T>
class prop<const T> {
public:
  using Getter = std::function<T()>;

private:
  Getter __getter__;

  prop(const prop<T>&) = delete;
  prop(prop<T>&&) = delete;

public:
  prop(Getter getter) : __getter__(getter) {}

  virtual operator T() const
  { return __getter__(); }
};

#define __get__() [&]()
#define __set__(T) , [&](T value)
