// Page.cpp
#include "Page.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


Page::Page():pageNumber(-1),text(""){}
Page::Page(size_t num,std::string t):pageNumber(num),text(t){}
Page::~Page(){}

Npage::Npage(size_t num,std::string t):Page(num,t){}
void Npage::addChoice(int destPage, const std::string& choiceText) {
    choices.push_back(std::make_pair(destPage, choiceText));
}
Npage* Npage::clone() const{
    return new Npage(*this);
}
void Npage::displayPage() const {
    std::cout << "Page " << pageNumber << "\n" << "==========" << std::endl;
    std::cout << text << std::endl << std::endl;
    std::cout << "\nWhat would you like to do?\n" << std::endl;
    for(size_t i = 0;i< choices.size();i++){
        std::cout << " " << i+1 << ". " << choices[i].second << std::endl;
    }
}


Wpage::Wpage(size_t num,std::string t):Page(num,t){}
Wpage* Wpage::clone() const{
    return new Wpage(*this);
}
void Wpage::displayPage() const {
    std::cout << "Page " << pageNumber << "\n" << "==========" << std::endl;
    std::cout << text << std::endl;
    std::cout << "\nCongratulations! You have won. Hooray!" << std::endl;
}


Lpage::Lpage(size_t num,std::string t):Page(num,t){}
Lpage* Lpage::clone() const {
    return new Lpage(*this);
}
void Lpage::displayPage() const {
    std::cout << "Page " << pageNumber << "\n" << "==========" << std::endl;
    std::cout << text << std::endl;
    std::cout << "\nSorry, you have lost. Better luck next time!" << std::endl;
}
