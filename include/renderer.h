#ifndef RENDERER_HH
#define RENDERER_HH

#include "game.h"
//#include <ncurses.h>
#include <curses.h>

class Renderer
{
private:
    
    int mScreenWidth;

    int mScreenHeight;

public:

    WINDOW* pDeskWindow;
    WINDOW* pSuitWindow;
    WINDOW* pTableWindow;
    WINDOW* pStateWindow;

public:

    Renderer(const std::size_t screen_width, const std::size_t screen_height);

    ~Renderer();

    void Init();

    void Display      ( Game& arGame );

    void DisplayDeck  ( int aRow, int aCols, Game& arGame );

    void DisplaySuit  ( int aRow, int aCols, Game& arGame );

    void DisplayTable ( int aRow, int aCols, Game& arGame );

    void DisplayState (  int aRow, int aCols, const std::string& arStr );

    void UpdateWindowTitle(int score, int move_state);

private:
    void Erase();

    void Refresh();

    void DisplaxBox();
};


#endif
