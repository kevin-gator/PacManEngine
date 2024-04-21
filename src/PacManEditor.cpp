#include "PacManEditor.hpp"
#include "SaveLoadUtilities.hpp"

PacManEditor::PacManEditor(float width, float height) : GUIApplication(width, height) {
    mGridSize = width / 19;
}

void PacManEditor::LoadLevelFile(std::string fileName) {
    mFileName = fileName;
    mTileGrid = LoadTileGridFromFile(fileName);
}

void PacManEditor::HandleKeyboardInputs(float deltaTime) {
    if (KeyPressStart(SDL_SCANCODE_LEFT) && mCursorX > 0) {
        mCursorX -= 1;
    }
    if (KeyPressStart(SDL_SCANCODE_RIGHT) && mCursorX < 18) {
        mCursorX += 1;
    }
    if (KeyPressStart(SDL_SCANCODE_UP) && mCursorY > 0) {
        mCursorY -= 1;
    }
    if (KeyPressStart(SDL_SCANCODE_DOWN) && mCursorY < 18) {
        mCursorY += 1;
    }
    if (KeyPressStart(SDL_SCANCODE_Q)) {
        SetSelectedTile(Empty);
    }
    if (KeyPressStart(SDL_SCANCODE_W)) {
        SetSelectedTile(Coin);
    }
    if (KeyPressStart(SDL_SCANCODE_E)) {
        SetSelectedTile(PowerUpCoin);
    }
    if (KeyPressStart(SDL_SCANCODE_R)) {
        SetSelectedTile(Wall);
    }
    if (KeyPressStart(SDL_SCANCODE_A)) {
        SetSelectedTile(Player);
    }
    if (KeyPressStart(SDL_SCANCODE_S)) {
        SetSelectedTile(Inky);
    }
    if (KeyPressStart(SDL_SCANCODE_D)) {
        SetSelectedTile(Blinky);
    }
    if (KeyPressStart(SDL_SCANCODE_F)) {
        SetSelectedTile(Pinky);
    }
    if (KeyPressStart(SDL_SCANCODE_Z)) {
        SetSelectedTile(Clyde);
    }
    if (KeyPressStart(SDL_SCANCODE_X)) {
        SetSelectedTile(Gate);
    }
    if (KeyPressStart(SDL_SCANCODE_Y)) {
        SaveTileGridToFile(mTileGrid, mFileName);
    }
    if (KeyPressStart(SDL_SCANCODE_H)) {
        mShowHelp = !mShowHelp;
    }
    if (KeyPressStart(SDL_SCANCODE_O)) {
        for (int y = 0; y < 19; ++y) {
            for (int x = 0; x < 19; x++) {
                mTileGrid[y][x] = Empty;
            }
        }
    }
}

void PacManEditor::SetSelectedTile(TileType tileType) {
    mTileGrid[mCursorY][mCursorX] = tileType;
}

void PacManEditor::Update(float deltaTime) {
    
}

void PacManEditor::Render() {
    for (int y = 0; y < 19; ++y) {
        std::vector<TileType> row = mTileGrid[y];
        for (int x = 0; x < 19; ++x) {
            if (row[x] == Empty) {
                continue;
            }
            const char* path;
            switch (row[x]) {
                case Coin:
                    path = "./assets/art/coin.bmp";
                    break;
                case PowerUpCoin:
                    path = "./assets/art/powerup-coin.bmp";
                    break;
                case Wall:
                    path = "./assets/art/wall.bmp";
                    break;
                case Gate:
                    path = "./assets/art/gate.bmp";
                    break;
                case Player:
                    path = "./assets/art/player.bmp";
                    break;
                case Inky:
                    path = "./assets/art/inky.bmp";
                    break;
                case Blinky:
                    path = "./assets/art/blinky.bmp";
                    break;
                case Pinky:
                    path = "./assets/art/pinky.bmp";
                    break;
                case Clyde:
                    path = "./assets/art/clyde.bmp";
                    break;
                default:
                    break;
            }
            RenderImageOnGrid(path, x, y);
        }
    }
    RenderImageOnGrid("./assets/art/selection.bmp", mCursorX, mCursorY);
    RenderImage("./assets/art/toggle-help.bmp", 0, 0, mWidth, mHeight);
    if (mShowHelp) {
        RenderImage("./assets/art/help-screen.bmp", 0, 0, mWidth, mHeight);
    }
}

void PacManEditor::RenderImageOnGrid(const char* filePath, int x, int y) {
    float worldX = mGridSize * x;
    float worldY = mGridSize * y;
    RenderImage(filePath, worldX, worldY, mGridSize, mGridSize);
}