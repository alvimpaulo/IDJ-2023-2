#include "Game.hpp"
#include "Resources.hpp"
#include "Camera.hpp"
#include <unordered_map>
#include <States/BattleState.hpp>

int main(int argc, char **argv)
{

    Game game = Game::GetInstance();
    BattleState* initState = BattleState::GetInstance();
    game.Push(initState);
    game.Run();

    return 0;
}