#include "PacManGame.hpp"
#include "PacManEditor.hpp"
#include <iostream>

int main() {
    std::string appMode;
    int levelNum;

    std::cout << "Enter the application type to open (editor or game): ";
    std::cin >> appMode;

    // Check if the input is either "editor" or "game"
    if (appMode != "editor" && appMode != "game") {
        std::cout << "Invalid input. Please enter either 'editor' or 'game'.\n";
        return 1; // Return an error code
    }

    std::cout << "Enter an integer between 1 and 10 to load a level: ";
    std::cin >> levelNum;

    // Check if the integer is between 1 and 10
    if (levelNum < 1 || levelNum > 10) {
        std::cout << "Invalid input. Please enter an integer between 1 and 10.\n";
        return 1; // Return an error code
    }

    std::string itemToStr = std::to_string(levelNum);
    std::string levelFile = "level" + itemToStr + ".txt";
    if (appMode == "editor") {
        PacManEditor editor(608, 640);
        editor.LoadLevelFile(levelFile);
        editor.Run(60.0f);
    } else {
        PacManGame game(608, 608);
        game.LoadLevelFile(levelFile);
        game.Run(60.0f);
    }

    return 0;
}