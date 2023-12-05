#include <iostream>
#include <string>

#include "Story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <story_directory>" << std::endl;
    return 1;
  }

  std::string directory = argv[1];
  Story story;
  story.loadStory(directory);
  story.verifyPage();
  story.displayUserInput();
  return 0;
}
