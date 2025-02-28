#pragma comment(lib,"Winmm.lib")

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"

int main()
{
    GameManager gameManager;
    gameManager.Initialize();
    gameManager.Run();

    return 0;
}
