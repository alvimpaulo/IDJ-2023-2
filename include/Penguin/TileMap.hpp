#pragma once
#include <string>
#include "GameObject.hpp"
#include "TileSet.hpp"
#include <vector>

class TileMap : public Component
{
public:
    TileMap(GameObject &associated,
            std::string file,
            TileSet *tileSet);

    void Load(std::string file);
    void SetTileSet(TileSet *tileSet);

    int &At(int x, int y, int z = 0);
    void Render();
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
    int GetWidth();
    int GetHeight();
    int GetDepth();
    void Update(float dt);

private:
    std::vector<int> tileMatrix;
    TileSet *tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};
