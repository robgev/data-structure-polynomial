#pragma once

#include <cstddef>
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

class polynomial
{
public:
  polynomial();
  polynomial(const polynomial &that);
  ~polynomial();

  int degree();
  double coefficient(int power);
  double value(double x);
  void change_coeff(double new_coeff, int power);
  void add(polynomial &that);
  void mult1(polynomial &that);
  void mult(polynomial &that);
  void print();

private:
  struct term
  {
    int power;
    double coeff;
    term* next;
  };
  term* head;
};
