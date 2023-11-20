// Story.cpp
#include "Story.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>

Story::Story() {
}
// Destructor
Story::~Story() {
  for (size_t i = 0; i < pages.size(); i++) {
    delete pages[i];
  }
}

// Copy constructor
Story::Story(const Story & rhs) {
  for (size_t i = 0; i < rhs.pages.size(); i++) {
    pages.push_back(rhs.pages[i]->clone());
  }
}

// Copy assignment operator
Story & Story::operator=(const Story & rhs) {
  if (this != &rhs) {
    std::vector<Page *> temp;
    for (size_t i = 0; i < pages.size(); i++) {
      pages.push_back(rhs.pages[i]->clone());
      delete pages[i];
    }
    pages.clear();
    pages = temp;
  }
  return *this;
}

void Story::loadStory(const std::string & directory) {
  std::ifstream storyFile((directory + "/story.txt").c_str());
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
      std::ifstream pageFile((directory + "/" + filename).c_str());
      std::string pageText;
      std::getline(pageFile, pageText, '\0');

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
      }
      else {
        std::cerr << "Page appears not in right order " << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    else if (line.find(':') != std::string::npos) {
      // Process choice line 2:1:Something
      size_t destPage;
      std::string choiceText;
      iss >> pageNum >> dummyString >> destPage >> dummyString;
      getline(iss, choiceText);
      if (pageNum < pages.size()) {
        Npage * npage = dynamic_cast<Npage *>(pages[pageNum]);
        npage->addChoice(destPage, choiceText);
      }
      else {
        std::cerr << "Page not being declared" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
}

void Story::displayStory() const {
  for (size_t i = 0; i < pages.size(); i++) {
    pages[i]->displayPage();
  }
}
