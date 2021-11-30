#include "../include/game.hh"
#include "../include/pile.hh"

#include <fstream>
#include <iostream>
#include <exception>

//----------------------------
//       Constructor
//----------------------------
Game::Game()
: mScore(0)
, mPilesList(TYP_MAX, 0)
{
}

//----------------------------
//       Destructor
//----------------------------
Game::~Game()
{
}

//----------------------------
//          Init
//----------------------------
void Game::Init()
{
    try
    {
        int num_card = 1;
        for ( int i = 0; i < TYP_MAX; ++i )
        {
            if ( i == DESK )
            {
                mPilesList[DESK] = new DeskPile();
            }
            else if ( i == DISCARD )
            {
                mPilesList[DISCARD] = new DiscardPile();
            }
            else if ( (i == HEARTS) || (i == TILES) || (i == CLOVERS) || (i == PIKES) )
            {
                // Suit type is needed
                mPilesList[i] = new SuitPile (i);
            }
            else if ( (i == COLUMN1) || (i == COLUMN2) || (i == COLUMN3) || (i == COLUMN4) ||
                      (i == COLUMN5) || (i == COLUMN6) || (i == COLUMN7) )
            {
                // Number of card by Init for all tablepile ( 1 - 2 - 3 - 4 - 5 - 6 - 7 )
                mPilesList[i] = new TablePile( num_card );
                ++num_card;
            }
        }

        // Initialization of CardPiles, Init of Desk must be done befor the init of Table
        for ( auto p_pile : mPilesList )
            p_pile->Init(this);

        for ( auto p_pile : mPilesList )
        {
            Card* p_last = p_pile->GetLast();
            if (p_last)
                p_last->Flip();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Init Game: "<< e.what() << '\n';
    }
}

//----------------------------
//       Run
//----------------------------
void Game::Run( Controller& arCtrl, Renderer& arRender )
{
    try
    {
        char buffer[80];
        
        bool running = true;
        // game loop
        while(running)
        {
            getstr(buffer);

            erase();

            // Input, Update, Renderer - the main game loop.
            ParseSolitaire parse_cmd; 
            arCtrl.HandleInput( buffer, parse_cmd, this );

            //Update();

            arRender.Display(*this);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Run game: " << e.what() << '\n';
    }
    
}

//----------------------------
//       UpdateScore
//----------------------------
void Game::UpdateScore()
{
    try
    {

    }
    catch(const std::exception& e)
    {
        std::cerr << "Update score: "<< e.what() << '\n';
    }
}

//----------------------------
//        GetDeskPile
//----------------------------
DeskPile& Game::GetDeskPile()
{
     DeskPile* p_desk;
    try
    {
        if ( (p_desk = dynamic_cast<DeskPile*>(mPilesList[DESK])) != nullptr )
        {
            return *p_desk;
        }
        else
            throw "bad dynamic cast!";
    }
    catch(std::bad_cast &e) 
    { 
        std::cout << "Getting DeskPile: " << e.what(); // bad dynamic_cast
    }
    return *p_desk;
}

//----------------------------
//      GetDiscardPile
//----------------------------
DiscardPile& Game::GetDiscardPile()
{
    DiscardPile* p_disc = nullptr;
    try
    {
        if ( (p_disc = dynamic_cast<DiscardPile*>(mPilesList[DISCARD])) != nullptr )
        {
            return *p_disc;
        }
        else
            throw "bad dynamic cast!";
    }
    catch(std::bad_cast &e) 
    { 
        std::cout << "Getting DiscardPile: " << e.what(); // bad dynamic_cast
    }
    return *p_disc;
}

//----------------------------
//       GetTablePile
//----------------------------
TablePile& Game::GetTablePile(int aIndex)
{
    TablePile* p_table;
    try
    {
        if ( (aIndex == COLUMN1) || (aIndex == COLUMN2) || (aIndex == COLUMN3) || (aIndex == COLUMN4) ||
             (aIndex == COLUMN5) || (aIndex == COLUMN6) || (aIndex == COLUMN7) )
        {
            if ( (p_table = dynamic_cast<TablePile*>(mPilesList[aIndex])) != nullptr )
            {
                return *p_table;
            }
            else
                throw "bad dynamic cast!";
        }
        else
        {
            throw std::out_of_range("Giving Index is out of range");
        }
    }
    catch(std::bad_cast &e) 
    {
        std::cout << "Getting TablePile: " << e.what(); // bad dynamic_cast
    }
    return *p_table;
}

//----------------------------
//       GetSuitPile
//----------------------------
SuitPile& Game::GetSuitPile(int aIndex)
{
    SuitPile* p_suit;
    try
    {
        if ( (aIndex == HEARTS) || (aIndex == TILES) || (aIndex == CLOVERS) || (aIndex == PIKES) )
        {
            if ( (p_suit = dynamic_cast<SuitPile*>(mPilesList[aIndex])) != nullptr )
            {
                return *p_suit;
            }
            else
                throw "bad dynamic cast!";

        }
        else
        {
            throw std::out_of_range("Giving Index is out of range");
        }
    }
    catch(std::bad_cast &e) 
    { 
        std::cout << "Getting SuitPile: " << e.what(); // bad dynamic_cast
    }
    return *p_suit;
}

void Game::Print()
{
    std::ofstream myfile ("/home/kentch");
    for ( auto p_pile : mPilesList )
        p_pile->Print(myfile);
    myfile.close();
}
