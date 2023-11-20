// Page.hpp
#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <iostream>
#include <string>
#include <vector>

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
};

class Npage : public Page {
  std::vector<std::pair<int, std::string> > choices;

 public:
  Npage(size_t num, std::string t);
  void addChoice(int destPage, const std::string & choiceText);
  virtual Npage * clone() const;
  virtual void displayPage() const;
};

class Wpage : public Page {
 public:
  Wpage(size_t num, std::string t);
  virtual Wpage * clone() const;
  virtual void displayPage() const;
};

class Lpage : public Page {
 public:
  Lpage(size_t num, std::string t);
  virtual Lpage * clone() const;
  virtual void displayPage() const;
};

#endif
