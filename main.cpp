#include <iostream>
#include "polynomial.h"

using std::cout;
using std::endl;



int main() {
  polynomial test1, test2, test3, test4, test5;
  test3.change_coeff(3, 2);
  test4.change_coeff(3, 0);
  test4.change_coeff(4, 2);
  test5.change_coeff(5, 0);
  test5.change_coeff(1, 2);
  test5.change_coeff(2, 3);
  int max_power = 5;
  for (int power = 1; power < max_power; power++)
  {
    if(power != 3) {
		  test1.change_coeff(power,power);
    }
	}
  for (int power = 1; power < max_power+1; power++)
  {
    if(power != 2) {
		  test2.change_coeff(power*2,power);
    }
	}
  test1.print();
  cout << "Degree of the polynomial is " << test1.degree() << endl;
  test1.change_coeff(5.0, 3);
  test1.print();
  test1.change_coeff(0.0, 3);
  test1.print();
  test2.print();
  test1.add(test2);
  test1.print();
  test3.print();
  test1.mult1(test3);
  test1.print();
  test4.print();
  test5.print();
  cout << endl << endl;
  test4.mult(test5);
  cout << "Test 4 after mult is ";
  test4.print();
  cout << "Coefficient is " << test1.coefficient(3) << endl
      << "Value at 1 is " << test1.value(1.0) << endl;
  return 0;
}
