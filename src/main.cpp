#include "Game.hpp"

Game* Game::instance = nullptr;

int main(int argc, char **argv)
{

    Game game = Game::GetInstance();
    game.GetState().LoadAssets();
    game.Run();

    return 0;
}