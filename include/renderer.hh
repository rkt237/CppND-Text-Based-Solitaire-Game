#ifndef RENDERER_HH
#define RENDERER_HH

#include "game.hh"
#include <ncurses.h>

class Renderer
{
private:
    
    int mScreenWidth;

    int mScreenHeight;

public:

    Renderer(const std::size_t screen_width, const std::size_t screen_height);

    ~Renderer();

    void Init();

    void Display      ( Game& arGame );

    void DisplayDeck  ( int aRow, int aCols, Game& arGame, WINDOW* window );

    void DisplaySuit  ( int aRow, int aCols, Game& arGame, WINDOW* window );

    void DisplayTable ( int aRow, int aCols, Game& arGame, WINDOW* window );

    void DisplayState (  int aRow, int aCols, const std::string& arStr, WINDOW* window );

    void UpdateWindowTitle(int score, int move_state);
};


#endif
