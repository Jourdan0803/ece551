// Story.hpp
#ifndef _STORY_HPP_
#define _STORY_HPP_

#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Page.hpp"  // Include your Page classes

class Story {
 private:
  std::vector<Page *> pages;

 public:
  Story();
  ~Story();

  Story(const Story & rhs);
  Story & operator=(const Story & rhs);

  void loadStory(const std::string & directory);
  void displayStory() const;
  void verifyPage() const;
  size_t getNextPage(size_t currentPageNum, size_t choiceNum) const;
  void displayUserInput(std::map<std::string, long int> & pathVars);
  void findWinningPaths(size_t currentPage,
                        size_t & allPath,
                        std::vector<std::pair<size_t, size_t> > & path,
                        std::set<size_t> & visited) const;
};

#endif
