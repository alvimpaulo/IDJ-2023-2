#include "TileSet.hpp"

TileSet::TileSet(int tileWidth,
                 int tileHeight,
                 std::string file) : tileWidth(tileWidth), tileHeight(tileHeight)
{
    tileSet.Open(file);

    int height = tileSet.getHeight();
    int width = tileSet.GetWidth();

    rows = height / tileHeight;
    columns = width / tileWidth;
}

void TileSet::RenderTile(size_t index,
                    float x,
                    float y)
{
    int tilesNum = rows * columns;
    if (index >= 0 && index <= tilesNum - 1)
    {
        int row = index / columns;
        int col = index - (row * columns);

        int topX = col * tileWidth;
        int topY = row * tileHeight;
        tileSet.SetClip(topX, topY, tileWidth, tileHeight);
    }
}


int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}