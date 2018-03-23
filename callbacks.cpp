#include <iostream>
#include <functional> // C++11
//#include <boost/function.hpp>
//#include <boost/bind.hpp>

struct A{
  std::function<void(int)> callback;
  void invoke(){ callback(42); }
};

struct B{
  void foo(int data){ std::cout << data * 2 << "\n"; }
};

struct C{
  void bar(int data){ std::cout << data / 2 << "\n"; }
};

int main(){
  using namespace std::placeholders; // namespace for argument placeholders for std::bind
                                     // not needed for Boost.Bind
  A a;
  B b;
  a.callback = std::bind(&B::foo, &b, _1);
  a.invoke();
  C c;
  a.callback = std::bind(&C::bar, &c, _1);
  a.invoke();
};