#include "TileMap.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include "Camera.hpp"

TileMap::TileMap(GameObject &associated,
                 std::string file,
                 TileSet *tileSet) : Component(associated)
{
    SetTileSet(tileSet);
    this->Load(file);
}

void TileMap::Load(std::string file)
{
    std::ifstream mapFile("assets/map/tileMap.txt");
    int lineCounter = 0;
    int readSection = 0; // Can be 0, 1 or 2. 0 is map dimensions. 1 or 2 are map layers.

    int tilesetWidth = 0;
    int tilesetHeight = 0;
    int tilesetDepth = 0;

    std::regex dimensionsRegex("(\\d+),(\\d+),(\\d+)");
    std::smatch dimensionsResult;

    std::string line;
    while (std::getline(mapFile, line))
    {

        bool whiteSpacesOnly = std::all_of(line.begin(), line.end(), isspace);
        if (whiteSpacesOnly)
        {
            readSection++;
            lineCounter++;
            continue;
        }

        if (lineCounter == 0)
        {
            std::regex_search(line, dimensionsResult, dimensionsRegex);
            tilesetWidth = std::stoi(dimensionsResult[1].str());
            tilesetHeight = std::stoi(dimensionsResult[2].str());
            tilesetDepth = std::stoi(dimensionsResult[3].str());

            readSection++;
            lineCounter++;
            continue;
        }

        if (readSection != 0)
        {
            std::string auxString = "";
            std::stringstream ss(line);
            while (std::getline(ss, auxString, ','))
            {
                if (std::all_of(auxString.begin(), auxString.end(), isspace))
                {
                    continue;
                }
                int num = std::stoi(auxString);
                num = num - 1; // see specification.
                this->tileMatrix.push_back(num);
            }

            lineCounter++;
            continue;
        }

        lineCounter++;
    }

    this->mapWidth = tilesetWidth;
    this->mapHeight = tilesetHeight;
    this->mapDepth = tilesetDepth;

    mapFile.close();

    associated.setBoxW(float(mapWidth * tileSet->GetTileWidth()));
    associated.setBoxH(float(mapHeight * tileSet->GetTileHeight()));
}

void TileMap::SetTileSet(TileSet *tileSet)
{
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z)
{
    if (x >= mapWidth && y >= mapHeight && z >= mapDepth)
    {
        std::cerr << "Erro tentando accesar At do tilemap, coords: "
                  << "x = " << x << "y = " << y << "z = " << z;
        x = y = z = 0;
    }

    return this->tileMatrix[x + (y * mapWidth) + (z * mapWidth * mapHeight)];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            auto dstX = float(x * tileSet->GetTileWidth() - cameraX);
            auto dstY = float(y * tileSet->GetTileHeight() - cameraY);

            int tile = At(x, y, layer);

            if (tile >= 0)
            {
                tileSet->RenderTile(unsigned(tile), dstX, dstY);
            }
        }
    }
}

void TileMap::Render()
{
    const auto &cameraPos = Camera::pos;
    for (int i = 0; i < this->GetDepth(); i++)
    {
        RenderLayer(i, int(cameraPos.x) * ((i + 1)), int(cameraPos.y) * ((i + 1))); //Layers start at zero
    }
}

bool TileMap::Is(std::string type)
{
    return type == "TileMap";
}

void TileMap::Update(float dt)
{
}

int TileMap::GetWidth()
{
    return this->mapWidth;
}
int TileMap::GetHeight()
{
    return this->mapHeight;
}
int TileMap::GetDepth()
{
    return this->mapDepth;
}