#include "polynomial.h"

polynomial::polynomial() : head(NULL)
{
}

polynomial::polynomial(const polynomial &that) : head(NULL)
{
  term* that_last_item = that.head;
  if(that.head != NULL) {
    term* top_item = new term;
    top_item->power = that_last_item->power;
    top_item->coeff = that_last_item->coeff;
    top_item->next = NULL;
    head = top_item;
    that_last_item = that_last_item->next;
    while(that_last_item != NULL)
    {
      term* new_term = new term;
      new_term->power = that_last_item->power;
      new_term->coeff = that_last_item->coeff;
      new_term->next = NULL;
      top_item->next = new_term;
      top_item = new_term;
      that_last_item = that_last_item->next;
    }
  }
}

polynomial::~polynomial()
{
  while(head != NULL)
  {
    term* copy_pointer = head;
    head = copy_pointer->next;
    delete copy_pointer;
  }
}

int polynomial::degree()
{
  if(head == NULL)
  {
    return -1;
  }
  return head->power;
}


double polynomial::coefficient(int power)
{
  term* last_item = head;
  while(last_item != NULL && last_item->power != power)
  {
    last_item = last_item->next;
  }
  if(last_item == NULL) {
    return 0;
  }
  return last_item->coeff;
}

double polynomial::value(double x)
{
  double result = 0;
  term* last_item = head;
  while(last_item != NULL)
  {
    result += coefficient(last_item->power) * std::pow(x, last_item->power);
    last_item = last_item->next;
  }
  return result;
}

void polynomial::change_coeff(double new_coeff, int power)
{
  term* last_item = head;
  if(power > degree())
  {
    term* new_term = new term;
    new_term->coeff = new_coeff;
    new_term->power = power;
    new_term->next = head;
    head = new_term;
  }
  else if(power == degree())
  {
    if(new_coeff == 0)
    {
      head = head->next;
      delete last_item;
    }
    else
    {
      last_item->coeff = new_coeff;
    }
  }
  else {
    while(last_item->next != NULL && last_item->next->power > power)
    {
      last_item = last_item->next;
    }
    term* target_item = last_item->next;
    if(target_item == NULL || target_item->power < power)
    {
      term* new_term = new term;
      new_term->coeff = new_coeff;
      new_term->power = power;
      new_term->next = target_item;
      last_item->next = new_term;
    }
    else if(target_item->power == power)
    {
      if(new_coeff == 0)
      {
        last_item->next = target_item->next;
        delete target_item;
      }
      else
      {
        target_item->coeff = new_coeff;
      }
    }
  }
}

void polynomial::add(polynomial &that)
{
  term* that_head = that.head;
  while(that_head != NULL)
  {
    double current_coeff = coefficient(that_head->power);
    change_coeff(current_coeff + that_head->coeff, that_head->power);
    that_head = that_head->next;
  }
}

void polynomial::mult1(polynomial &that)
{
  term* last_item = head;
  while(last_item != NULL)
  {
    last_item->coeff *= that.head->coeff;
    last_item->power += that.head->power;
    last_item = last_item->next;
  }
}

void polynomial::mult(polynomial &that)
{
  polynomial* condenser = new polynomial(*this);
  condenser->mult1(that);
  term* that_last_item = that.head->next;
  while(that_last_item != NULL)
  {
    polynomial* summand = new polynomial(*this);
    polynomial* multiplier = new polynomial();
    multiplier->head = that_last_item;
    summand->mult1(*multiplier);
    condenser->add(*summand);
    that_last_item = that_last_item->next;
  }
  head = condenser->head;
}

void polynomial::print()
{
  term* last_item = head;
  while(last_item != NULL)
  {
    cout << last_item->coeff << " *x^" << last_item->power << (last_item->next == NULL ? "" : " + ");
    last_item = last_item->next;
  }
  cout << endl;
}
