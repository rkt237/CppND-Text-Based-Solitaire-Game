#include "../include/renderer.h"
#include "../include/controller.h"

#include <iostream>


int main() 
{
    srand(time(NULL));

    //  srand(3);
    setlocale(LC_ALL, "");

    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};

    Controller controller;    
    Renderer renderer ( kScreenWidth, kScreenHeight );
    Game game;
    game.Init();
    game.Print();
    
    renderer.Display( game );

    //game.Run( controller, renderer );

    return 0;
}