// Story.cpp
#include "Story.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
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
/***************************************** step1 ****************************************/
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
    //check if type is number@type:filename(0@N:page0.txt)
    if (line.find('@') != std::string::npos) {
      char type;
      iss >> pageNum >> dummyString >> type >> dummyString >> filename;
      std::ifstream pageFile((directory + "/" + filename).c_str());
      std::string pageText;
      std::getline(pageFile, pageText, '\0');

      if (pageNum == pages.size()) {
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
    else if (line.find('$') != std::string::npos) {
      // step 4: Process pagenum$var=value
      std::string variable;
      long int value;
      iss >> pageNum >> dummyString;
      getline(iss, variable, '=');
      iss >> value;
      if (pageNum < pages.size()) {
        Npage * npage = dynamic_cast<Npage *>(pages[pageNum]);
        npage->pageVariables[variable] = value;
      }
      else {
        std::cerr << "Page not being declared" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    else if (line.find(':') != std::string::npos) {
      // Process choice line 2:1:Something and pagenum[var=value]:dest:text
      size_t destPage;
      std::string choiceText;
      // step 4: pagenum[var=value]:dest:text

      if (line.find('[') != std::string::npos) {
        std::string variable;
        long int value;
        char colon;
        iss >> pageNum >> dummyString;
        getline(iss, variable, '=');
        iss >> value >> dummyString >> colon >> destPage >> colon;
        getline(iss, choiceText);
        if (pageNum < pages.size()) {
          Npage * npage = dynamic_cast<Npage *>(pages[pageNum]);
          npage->addVariable(variable, value);
          npage->addChoice(destPage, choiceText);
        }
        else {
          std::cerr << "Page not being declared" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      else {
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
}

void Story::displayStory() const {
  for (size_t i = 0; i < pages.size(); i++) {
    std::cout << "Page " << pages[i]->getPageNum() << "\n"
              << "==========" << std::endl;
    pages[i]->displayPage();
  }
}

/*********************************** step2 ***************************************/
void Story::verifyPage() const {
  // verify existance of win and lose page
  bool WpageExist = false;
  bool LpageExist = false;
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i]->getType() == 'W') {
      WpageExist = true;
    }
    if (pages[i]->getType() == 'L') {
      LpageExist = true;
    }
  }
  if (LpageExist == false || WpageExist == false) {
    std::cerr << "At least one page must be a W/L page" << std::endl;
    exit(EXIT_FAILURE);
  }
  /* 1.verify all referenced pages exist
     2.Every page (except page 0) is referenced by at least one page's choices.
  */
  std::vector<bool> reference(pages.size(), false);
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i]->getType() == 'N') {
      const std::vector<std::pair<size_t, std::string> > & choice_i =
          dynamic_cast<const Npage *>(pages[i])->getChoices();
      for (size_t j = 0; j < choice_i.size(); j++) {
        //1.verify all referenced pages exist
        if (choice_i[j].first >= pages.size()) {
          std::cerr << "all referenced pages must be existed" << std::endl;
          exit(EXIT_FAILURE);
        }
        //2.change the pages with reference by choices with true;
        reference[choice_i[j].first] = true;
      }
    }
  }
  for (size_t i = 1; i < reference.size(); i++) {
    if (reference[i] == false) {
      std::cerr << "Every page must be referenced other page's choices" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

size_t Story::getNextPage(size_t currentPageNum, size_t choiceNum) const {
  const Npage * npage = dynamic_cast<const Npage *>(pages[currentPageNum]);
  const std::vector<std::pair<size_t, std::string> > & choices = npage->getChoices();
  if (choiceNum > 0 && choiceNum <= choices.size()) {
    if (choices[choiceNum - 1].second == "<UNAVAILABLE>") {
      std::cout << "That choice is not available at this time, please try again"
                << std::endl;
      return std::numeric_limits<size_t>::max();
    }
    else {
      return choices[choiceNum - 1].first;
    }
  }
  else {
    std::cout << "That is not a valid choice, please try again" << std::endl;
    return std::numeric_limits<size_t>::max();
  }
}
void addCondition(std::map<std::string, long int> & vars,
                  std::map<std::string, long int> & pathVars) {
  for (std::map<std::string, long int>::iterator it = vars.begin(); it != vars.end();
       ++it) {
    std::map<std::string, long int>::iterator pathIt = pathVars.find(it->first);
    if (pathIt != pathVars.end()) {
      // The element is found in pathVars, update its value
      pathIt->second = it->second;
    }
    else {
      // The element is not found in pathVars, insert the new element
      pathVars.insert(std::make_pair(it->first, it->second));
    }
  }
}
void Story::displayUserInput(std::map<std::string, long int> & pathVars) {
  size_t currentPage = 0;
  bool flag = true;
  while (flag) {
    if (pages[currentPage]->getType() == 'N') {
      Npage * npage = dynamic_cast<Npage *>(pages[currentPage]);
      // Method to update variables in the page
      npage->updateVariables(pathVars);
      addCondition(npage->pageVariables, pathVars);
    }
    pages[currentPage]->displayPage();  // 4a. Display the current page
    if (pages[currentPage]->getType() == 'W' || pages[currentPage]->getType() == 'L') {
      flag = false;
      continue;
    }
    std::string input;
    size_t choice;
    while (true) {
      getline(std::cin, input);
      std::stringstream ss(input);
      if (ss >> choice) {
        size_t nextpage =
            getNextPage(currentPage, choice);  // 4d. Navigate to the chosen page
        if (nextpage != std::numeric_limits<size_t>::max()) {
          currentPage = nextpage;
          break;
        }
      }
      else {
        std::cerr << "That is not a valid choice, please try again" << std::endl;
      }
    }
  }
}
/*************************************** step3 *********************************************/

void Story::findWinningPaths(size_t currentPage,
                             size_t & allPath,
                             std::vector<std::pair<size_t, size_t> > & path,
                             std::set<size_t> & visited) const {
  if (pages[currentPage]->getType() == 'W') {
    // Print the winning path
    for (size_t i = 0; i < path.size(); ++i) {
      std::cout << path[i].first << "(" << path[i].second << "),";
    }
    std::cout << currentPage << "(win)" << std::endl;
    allPath++;
    return;
  }
  if (pages[currentPage]->getType() == 'L') {
    return;
  }

  visited.insert(currentPage);  // Mark the current page as visited

  if (pages[currentPage]->getType() == 'N') {
    const Npage * npage = dynamic_cast<const Npage *>(pages[currentPage]);
    const std::vector<std::pair<size_t, std::string> > & choices = npage->getChoices();
    for (size_t i = 0; i < choices.size(); ++i) {
      size_t nextPage = choices[i].first;
      if (visited.find(nextPage) == visited.end()) {  // Check if current page in visited
        path.push_back(
            std::make_pair(currentPage, i + 1));  // Add current page to the path
        findWinningPaths(nextPage, allPath, path, visited);  // Recursive call
        path.pop_back();
      }
    }
  }
}
