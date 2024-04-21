#include "GUIApplication.hpp"
#include "TileType.hpp"
#include <vector>

/**
 * Represents an Application that is used for loading, saving, and editing PacMan levels.
*/
struct PacManEditor : public GUIApplication {
    public:
        /**
         * Constructs the PacManEditor with the given window dimensions.
         * @param width the window width.
         * @param height the window height.
        */
        PacManEditor(float width, float height);
        /**
         * Loads the given level file in the editor.
         * @param fileName the name of the file to load.
        */
        void LoadLevelFile(std::string fileName);
    protected:
        void HandleKeyboardInputs(float deltaTime) override;
        void Update(float deltaTime) override;
        void Render() override;
    private:
        void SetSelectedTile(TileType tileType);
        void RenderImageOnGrid(const char* filePath, int x, int y);
        float mGridSize;
        int mCursorX{9};
        int mCursorY{9};
        std::string mFileName;
        std::vector<std::vector<TileType>> mTileGrid;
        bool mShowHelp{false};
};