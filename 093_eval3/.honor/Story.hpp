// Story.hpp
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
    Story();
    ~Story();

    Story(const Story& rhs);
    Story& operator=(const Story& rhs);

    void loadStory(const std::string &directory);
    void displayStory() const;
};

#endif
