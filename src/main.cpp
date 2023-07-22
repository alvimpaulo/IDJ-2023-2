#include "Game.hpp"
#include "Resources.hpp"
#include "Camera.hpp"
#include <unordered_map>
#include "TileState.hpp"

Game* Game::instance = nullptr;

int main(int argc, char **argv)
{

    Game game = Game::GetInstance();
    auto initState = new TitleState();
    game.Push(initState);
    game.Run();

    return 0;
}