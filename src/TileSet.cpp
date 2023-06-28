#include "TileSet.hpp"
#include "Sprite.hpp"

TileSet::TileSet(int tileWidth,
                 int tileHeight,
                 std::string file) :  go(new GameObject()), tileSet(Sprite(*go, file))
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
     
    int height = tileSet.GetHeight();
    int width = tileSet.GetWidth();

    rows = height / tileHeight;
    columns = width / tileWidth;
}

void TileSet::RenderTile(size_t index,
                         float x,
                         float y)
{
    int tilesNum = rows * columns;
    if (static_cast<int>(index) <= tilesNum - 1)
    {
        int row = static_cast<int>(index) / columns;
        int col = static_cast<int>(index) - (row * columns);

        int topX = col * tileWidth;
        int topY = row * tileHeight;
        tileSet.SetClip(topX, topY, tileWidth, tileHeight);
        tileSet.Render(x, y, static_cast<float>(tileWidth), static_cast<float>(tileHeight));
    }
}

int TileSet::GetTileWidth()
{
    return tileWidth;
}

int TileSet::GetTileHeight()
{
    return tileHeight;
}