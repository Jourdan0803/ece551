#include <iostream>
#include "Story.hpp"
#include <string>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <story_directory>" << std::endl;
        return 1;
    }

    std::string directory = argv[1];
    Story story;

    try {
        story.loadStory(directory);
        story.displayStory();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
