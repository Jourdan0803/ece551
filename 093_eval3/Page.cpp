// Page.cpp
#include "Page.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Page::Page() : pageNumber(-1), text("") {
}
Page::Page(size_t num, std::string t) : pageNumber(num), text(t) {
}
Page::~Page() {
}

Npage::Npage(size_t num, std::string t) : Page(num, t),conditions(std::vector<std::pair<std::string, long int> >()) {
}
//add choices to vector choice of nPage class
void Npage::addChoice(size_t destPage, const std::string & choiceText) {
  choices.push_back(std::make_pair(destPage, choiceText));
}
Npage * Npage::clone() const {
  return new Npage(*this);
}
void Npage::displayPage() const {
  std::cout << text << std::endl;
  std::cout << "What would you like to do?\n" << std::endl;
  for (size_t i = 0; i < choices.size(); i++) {
    std::cout << " " << i + 1 << ". " << choices[i].second << std::endl;
  }
}
char Npage::getType() const {
  return 'N';
}
const std::vector<std::pair<size_t, std::string> > & Npage::getChoices() const {
  return choices;
}
size_t Npage::getPageNum() const {
  return pageNumber;
}
void Npage::addVariable(const std::string & variable,size_t value){
  conditions.push_back(make_pair(variable, value));
   
}
bool Npage::isConditionMet(const std::pair<std::string, long int>& condition, const std::map<std::string, long int>& vars) {
    if(condition.first.empty()){
      return true;
    }
    std::map<std::string, long int>::const_iterator it = vars.find(condition.first);
    if (it != vars.end()) {
        return it->second == condition.second; // Check if variable value matches the condition
    } if(condition.second == 0){
      return true;
    }else{
      return false;
    }
}
void Npage::updateVariables(const std::map<std::string, long int>& vars) {
     for (size_t i = 0; i < choices.size();i++) {
      if(conditions.size()==0){
        return;
      }
        if (!isConditionMet(conditions[i], vars)) {
           choices[i].second = "<UNAVAILABLE>";
         }
     }
}

Wpage::Wpage(size_t num, std::string t) : Page(num, t) {
}
Wpage * Wpage::clone() const {
  return new Wpage(*this);
}
void Wpage::displayPage() const {
  std::cout << text << std::endl;
  std::cout << "Congratulations! You have won. Hooray!" << std::endl;
}

char Wpage::getType() const {
  return 'W';
}
size_t Wpage::getPageNum() const {
  return pageNumber;
}

Lpage::Lpage(size_t num, std::string t) : Page(num, t) {
}
Lpage * Lpage::clone() const {
  return new Lpage(*this);
}
void Lpage::displayPage() const {
  std::cout << text << std::endl;
  std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
}
char Lpage::getType() const {
  return 'L';
}
size_t Lpage::getPageNum() const {
  return pageNumber;
}
