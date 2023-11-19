#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Page{
    protected:
        size_t pageNumber;
        std::string text;
    public:
        Page():pageNumber(-1),text(""){}
        Page(size_t num,std::string t):pageNumber(num),text(t){}
        virtual void displayPage() const = 0;
        virtual Page* clone() const = 0;
        virtual ~Page(){}
};

class Npage : public Page{
    std::vector<std::pair<int,std::string> > choices;
    public:
        Npage(size_t num,std::string t):Page(num,t){}
        void addChoice(int destPage, const std::string& choiceText) {
            choices.push_back(std::make_pair(destPage, choiceText));
        }
        virtual Npage* clone() const{
            return new Npage(*this);
        }
        virtual void displayPage() const {
            std::cout << "Page " << pageNumber << "\n" << "==========" << std::endl;
            std::cout << text << std::endl << std::endl;
            std::cout << "\nWhat would you like to do?\n" << std::endl;
            for(size_t i = 0;i< choices.size();i++){
                std::cout << " " << i+1 << ". " << choices[i].second << std::endl;
            }
        }
};

class Wpage:public Page{
    public:
        Wpage(size_t num,std::string t):Page(num,t){}
        virtual Wpage* clone() const{
            return new Wpage(*this);
        }
        virtual void displayPage() const {
            std::cout << "Page " << pageNumber << "\n" << "==========" << std::endl;
            std::cout << text << std::endl;
            std::cout << "\nCongratulations! You have won. Hooray!" << std::endl;
        }
};

class Lpage:public Page{
    public:
        Lpage(size_t num,std::string t):Page(num,t){}
        virtual Lpage* clone() const {
            return new Lpage(*this);
        }
        virtual void displayPage() const {
            std::cout << "Page " << pageNumber << "\n" << "==========" << std::endl;
            std::cout << text << std::endl;
            std::cout << "\nSorry, you have lost. Better luck next time!" << std::endl;
        }
};

#endif