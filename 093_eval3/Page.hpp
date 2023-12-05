// Page.hpp
#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Page {
 protected:
  size_t pageNumber;
  std::string text;

 public:
  Page();
  Page(size_t num, std::string t);
  virtual void displayPage() const = 0;
  virtual Page * clone() const = 0;
  virtual ~Page();
  virtual char getType() const = 0;
  virtual size_t getPageNum() const = 0;
};

class Npage : public Page {
  std::vector<std::pair<size_t, std::string> > choices;
  

 public:
  std::map<std::string, long int> pageVariables;
  std::vector<std::pair<std::string, long int> > conditions; 
  Npage(size_t num, std::string t);
  void addChoice(size_t destPage, const std::string & choiceText);
  void addVariable(const std::string & variable,size_t value);
  virtual Npage * clone() const;
  virtual void displayPage() const;
  virtual char getType() const;
  virtual size_t getPageNum() const;
  const std::vector<std::pair<size_t, std::string> > & getChoices() const;
  bool isConditionMet(const std::pair<std::string, long int> & condition, const std::map<std::string, long int>& vars);
  void updateVariables(const std::map<std::string, long int>& vars);
};

class Wpage : public Page {
 public:
  Wpage(size_t num, std::string t);
  virtual Wpage * clone() const;
  virtual void displayPage() const;
  virtual char getType() const;
  virtual size_t getPageNum() const;
};

class Lpage : public Page {
 public:
  Lpage(size_t num, std::string t);
  virtual Lpage * clone() const;
  virtual void displayPage() const;
  virtual char getType() const;
  virtual size_t getPageNum() const;
};

#endif
