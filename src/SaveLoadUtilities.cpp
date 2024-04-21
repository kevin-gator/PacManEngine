#include "SaveLoadUtilities.hpp"
#include <filesystem>
#include <fstream>

std::vector<std::vector<TileType>> LoadTileGridFromFile(std::string fileName) {
    std::filesystem::path path = "./assets/levels/" + fileName;
    if (!std::filesystem::exists(path)) {
        throw std::invalid_argument("File not found!");
    }
    std::ifstream fileStream(path, std::ios::binary);
    std::vector<std::vector<TileType>> tileGrid;
    if (fileStream.is_open()) {
        std::string currLine;
        while (std::getline(fileStream, currLine)) {
            std::vector<TileType> row;
            for (char c : currLine) {
                switch(c) {
                    case ' ':
                        row.push_back(Empty);
                        break;
                    case '.':
                        row.push_back(Coin);
                        break;
                    case '*':
                        row.push_back(PowerUpCoin);
                        break;
                    case '#':
                        row.push_back(Wall);
                        break;
                    case '&':
                        row.push_back(Player);
                        break;
                    case 'I':
                        row.push_back(Inky);
                        break;
                    case 'B':
                        row.push_back(Blinky);
                        break;
                    case 'P':
                        row.push_back(Pinky);
                        break;
                    case 'C':
                        row.push_back(Clyde);
                        break;
                    case '-':
                        row.push_back(Gate);
                        break;
                }
            }
            tileGrid.push_back(row);
        }
        fileStream.close();
    }
    return tileGrid;
}

void SaveTileGridToFile(std::vector<std::vector<TileType>> tileGrid, std::string fileName) {
    std::string fileContents;
    for (auto row : tileGrid) {
        for (TileType tile : row) {
            switch (tile) {
                case Empty:
                    fileContents.push_back(' ');
                    break;
                case Coin:
                    fileContents.push_back('.');
                    break;
                case PowerUpCoin:
                    fileContents.push_back('*');
                    break;
                case Wall:
                    fileContents.push_back('#');
                    break;
                case Player:
                    fileContents.push_back('&');
                    break;
                case Inky:
                    fileContents.push_back('I');
                    break;
                case Blinky:
                    fileContents.push_back('B');
                    break;
                case Pinky:
                    fileContents.push_back('P');
                    break;
                case Clyde:
                    fileContents.push_back('C');
                    break;
                case Gate:
                    fileContents.push_back('-');
                    break;
            }
        }
        fileContents.push_back('\n');
    }
    std::filesystem::path path = "./assets/levels/" + fileName;
    if (!std::filesystem::exists(path)) {
        throw std::invalid_argument("File not found!");
    }
    std::ofstream fileStream(path);
    fileStream << fileContents;
    fileStream.close();
}