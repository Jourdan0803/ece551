#ifndef __EXPR_H___
#define __EXPR_H___
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const { return number; }
  virtual ~NumExpression() {}
};

class OperateExpression : public Expression {
 protected:
  Expression * l;
  Expression * r;
  std::string o;

 public:
  OperateExpression(Expression * lhs, Expression * rhs, std::string operate) :
      l(lhs), r(rhs), o(operate) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << l->toString() << o << r->toString() << ")";
    return ss.str();
  }
  virtual ~OperateExpression() {
    delete l;
    delete r;
  }
};

class PlusExpression : public OperateExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) :
      OperateExpression(lhs, rhs, " + ") {}
  virtual long evaluate() const { return l->evaluate() + r->evaluate(); }
};

class MinusExpression : public OperateExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) :
      OperateExpression(lhs, rhs, " - ") {}
  virtual long evaluate() const { return l->evaluate() - r->evaluate(); }
};
class TimesExpression : public OperateExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) :
      OperateExpression(lhs, rhs, " * ") {}
  virtual long evaluate() const { return l->evaluate() * r->evaluate(); }
};
class DivExpression : public OperateExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) :
      OperateExpression(lhs, rhs, " / ") {}
  virtual long evaluate() const { return l->evaluate() / r->evaluate(); }
};

#endif
