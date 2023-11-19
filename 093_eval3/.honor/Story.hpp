#ifndef _STORY_HPP_
#define _STORY_HPP_

#include "Page.hpp"  // Include your Page classes
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class Story {
private:
    std::vector<Page*> pages;

public:
    Story(){}
    // Destructor
    ~Story() {
        for (size_t i = 0; i< pages.size();i++) {
            delete pages[i];
        }
    }

    // Copy constructor
    Story(const Story& rhs) {
        for (size_t i = 0; i< rhs.pages.size();i++) {
                
                pages.push_back(rhs.pages[i]->clone());
            } 
        }
    
    // Copy assignment operator
    Story& operator=(const Story& rhs) {
        if (this != &rhs) {
            std::vector<Page*> temp;
            for (size_t i = 0; i< pages.size();i++) {
                pages.push_back(rhs.pages[i]->clone());
                delete pages[i];
            }
            pages.clear();
            pages = temp;
        }
        return *this;
    }

    void loadStory(const std::string &directory) {
        std::ifstream storyFile(directory + "/story.txt");
        std::string line;

        if (!storyFile) {
            std::cerr << "Failed to open story.txt in " << directory << std::endl;
            exit(EXIT_FAILURE);
        }

        while (getline(storyFile, line)) {
            std::istringstream iss(line);
            size_t pageNum;
            char dummyString;
            std::string filename;
            //check if tyoe is number@type:filename(0@N:page0.txt)
            if (line.find('@') != std::string::npos) {
                char type;
                iss >> pageNum >> dummyString >> type >> dummyString >> filename;
                std::ifstream pageFile(directory + "/" + filename);
                std::string pageText((std::istreambuf_iterator<char>(pageFile)),
                                     std::istreambuf_iterator<char>());
                
                if (pageNum >= pages.size()) {
                    Page * newPage;
                    switch (type) {
                        case 'N':
                            newPage = new Npage(pageNum, pageText);
                            break;
                        case 'W':
                            newPage = new Wpage(pageNum, pageText);
                            break;
                        case 'L':
                            newPage = new Lpage(pageNum, pageText);
                            break;
                        }
                    pages.push_back(newPage);
                }else{
                    exit(EXIT_FAILURE);
                }
            }
            else if (line.find(':') != std::string::npos) {
                // Process choice line 2:1:Something
                size_t destPage;
                std::string choiceText;
                iss >> pageNum >> dummyString >> destPage >> dummyString >>std::ws;
                getline(iss,choiceText);
                if (pageNum < pages.size()) {
                    Npage* npage = dynamic_cast<Npage*>(pages[pageNum]);
                    npage->addChoice(destPage, choiceText);
                }else{
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    void displayStory() const {
        for (size_t i = 0; i< pages.size();i++) {
                pages[i]->displayPage();
        }
    }
};

#endif
