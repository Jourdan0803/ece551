#ifndef __EXPR_H___
#define __EXPR_H___
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream s;
    s << number;
    return s.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * l;
  Expression * r;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << l->toString() << " + " << r->toString() << ")";
    return ss.str();
  }
  virtual ~PlusExpression() {
    delete l;
    delete r;
  }
};

#endif
