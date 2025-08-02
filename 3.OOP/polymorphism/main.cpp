#include "compiletime/complex.h"
#include "runtime/baseclass.h"
#include "runtime/derivedclass.h"
#include "virtualfunction/employee.h"

int main(){

  // /*
  //   compile-time polymorphism include function overloading and operator overloading
  //     +) function overloading is multiple functions with same name, functions can be 
  //     overloaded by changing the number of arguments or changing the type of arguments 
  //     +) provide the operatos with a special meaning for a data type.
  // */
  // Complex a(12, 23, 23), b(5, 23, 21), c(102, 2, 45);
  // auto d = a+b; auto D = a*b;
  // auto e = b+c; auto E = b*c;
  // a.print();
  // b.print();
  // c.print();
  // std::cout << "a+b: ";  
  // d.print();
  // std::cout << "b+c: ";
  // e.print();
  // std::cout << "a*b: ";
  // D.print();
  // std::cout << "b*c: ";
  // E.print();
  // // above operate "*" and "+" is overloaded by operate that defined in class

  // a.func(10);
  // a.func(10, 10);
  // a.func(10, 10, 10);



  /*
  RUNTIME POLYMORPHISM
  */

  Baseclass *some_parent;
  Derived_1 child_1;
  Derived_2 child_2;
  Derived_3 child_3;
  Derived_4 child_4;
  
  some_parent = &child_1;
  some_parent->function1();
  some_parent->function2();
  some_parent = &child_2;
  some_parent->function1();
  some_parent->function2();
  some_parent = &child_3;
  some_parent->function1();
  some_parent->function2();
  some_parent = &child_4;
  some_parent->function1();
  some_parent->function2();
  std::cout << std::endl;

  child_4.function1(); // function overriding
  child_3.function1();
  std::cout << std::endl;

  child_1.Baseclass::function1();
  std::cout << std::endl;

  Shape *shape, other;
  Circle circle(4);
  Rectangle rectangle(20, 30);
  Tritangle triangle(30, 15);
  shape = &other;
  shape->get_area();
  shape = &circle;
  shape->get_area();
  shape = &rectangle;
  shape->get_area();
  shape = &triangle;
  shape->get_area();
  std::cout << std::endl;

  Employee *employee;
  Manager A;
  employee = &A;
  employee->raise_salary(0.2);
  std::cout << employee->get_salary() << std::endl;


}