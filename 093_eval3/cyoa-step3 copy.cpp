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
    std::vector<std::pair<size_t,size_t> > path;
    std::set<size_t> visited;
    findWinningPaths(0, path, visited);

    if (path.empty()) {
        std::cout << "This story is unwinnable!" << std::endl;
    }
  return 0;
}
