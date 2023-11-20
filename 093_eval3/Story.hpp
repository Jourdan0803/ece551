// Story.hpp
#ifndef _STORY_HPP_
#define _STORY_HPP_

#include <fstream>
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
};

#endif
