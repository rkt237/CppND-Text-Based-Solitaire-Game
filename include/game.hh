#ifndef GAME_HH
#define GAME_HH

#include "../include/pile.hh"
#include "../include/controller.hh"
#include "../include/renderer.hh"

#include <vector>

class Controller;
class Renderer;
class Pile;
class DeskPile;
class DiscardPile;
class SuitPile;
class TablePile;

class Game
{
public:
    
    enum
    {
        DESK = 0,
        HEARTS,
        TILES,
        CLOVERS,
        PIKES,
        DISCARD,
        COLUMN1,
        COLUMN2,
        COLUMN3,
        COLUMN4,
        COLUMN5,
        COLUMN6,
        COLUMN7,
        TYP_MAX
    };

private:

    int mScore;
    
    std::vector<Pile*> mPilesList;

public:

    Game  ();

    ~Game ();

    void Init();

    void Run( Controller& arCtrl, Renderer& arRender );

    void UpdateScore();

    DeskPile&    GetDeskPile();

    DiscardPile& GetDiscardPile();

    SuitPile&    GetSuitPile(int aIndex);

    TablePile&   GetTablePile(int aIndex);

    void         Print();
};

#endif
