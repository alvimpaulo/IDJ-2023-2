#include "Game.hpp"
#include "Resources.hpp"
#include "Camera.hpp"
#include <unordered_map>
#include "TitleState.hpp"
#include <BattleState.hpp>

Game* Game::instance = nullptr;

int main(int argc, char **argv)
{

    Game game = Game::GetInstance();
    auto initState = new BattleState();
    game.Push(initState);
    game.Run();

    return 0;
}