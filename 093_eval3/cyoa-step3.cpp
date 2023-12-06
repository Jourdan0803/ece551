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
  std::vector<std::pair<size_t, size_t> > path;
  std::set<size_t> visited;
  size_t pathNum = 0;
  story.findWinningPaths(0, pathNum, path, visited);

  if (pathNum == 0) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
  return 0;
}
