#include "../include/renderer.h"

#include <curses.h>

#include <iostream>
#include <chrono>
#include <string>
#include <thread>

const static int DEFAULT_COLOR = -1;

//----------------------------
//       Constructor
//----------------------------
Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height)
: mScreenWidth(screen_width)
, mScreenHeight(screen_height)
, pDeskWindow(nullptr)
, pSuitWindow(nullptr)
, pTableWindow(nullptr)
, pStateWindow(nullptr)
{
}

//----------------------------
//       Destructor
//----------------------------
Renderer::~Renderer() 
{}

//----------------------------
//          Init
//----------------------------
void Renderer::Init()
{
  initscr();            // start ncurses
  noecho();             // do not print input values
  //keypad(stdscr, TRUE); // enable abbreviation of function keys 
  //use_default_colors(); // use default color
  cbreak();             // terminate ncurses on ctrl + c
  start_color();        // enable color
  
  int x_max{getmaxx(stdscr)};
  
  pDeskWindow    = newwin(9,                      x_max - 1, 0,                       0);
  pSuitWindow    = newwin(pDeskWindow->_maxx + 4, x_max - 1, 0,                       0);
  pTableWindow   = newwin(9,                      x_max - 1, pSuitWindow->_maxy  + 4, 0);
  pStateWindow   = newwin(9,                      x_max - 1, pTableWindow->_maxy + 4, 0);

}

//----------------------------
//      Erase
//----------------------------
void Renderer::Erase()
{
  werase( pDeskWindow  );
  werase( pSuitWindow  );
  werase( pTableWindow );
  werase( pStateWindow );
}

//----------------------------
//      Refresh
//----------------------------
void Renderer::Refresh()
{
  wrefresh( pDeskWindow  );
  wrefresh( pSuitWindow  );
  wrefresh( pTableWindow );
  wrefresh( pStateWindow );
}

void Renderer::DisplaxBox()
{
  box( pDeskWindow,  0, 0 );
  box( pSuitWindow,  0, 0 );
  box( pTableWindow, 0, 0 );
  box( pStateWindow, 0, 0 );
}

//----------------------------
//          Init
//----------------------------
void Renderer::Display( Game& arGame ) 
{
  try
  {   
      // Erase all Windows
      Erase();

      // init black color
      init_pair(Card::CARD_COLOR::BLACK, DEFAULT_COLOR, DEFAULT_COLOR);

      // init red color
      init_pair(Card::CARD_COLOR::RED,   COLOR_RED,     DEFAULT_COLOR);

      // display box
      DisplaxBox();

      // display deskpile
      DisplayDeck  ( 9,  0, arGame );

      // display suit cards
      DisplaySuit  ( 40, 0, arGame );

      // display tablepile
      DisplayTable ( 9, pSuitWindow->_maxy, arGame );

      // display state
      DisplayState ( 9, pStateWindow->_maxy, "Game Score: " );

      // refresh
      refresh();
      std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  catch(const std::exception& e)
  {
    std::cerr << "Display: " << e.what() << '\n';
  }
}

//----------------------------
//         DisplayDeck
//----------------------------
void Renderer::DisplayDeck ( int aRow, int aCols, Game& arGame )
{
  try
  {
    int row{aRow};
    int const cols_desk = aCols + 1;
    int const cols_disc = aCols + 10;

    DeskPile& deskpile = arGame.GetDeskPile();
    
    DiscardPile& discpile = arGame.GetDiscardPile();
    
    Card* head = discpile.GetLast();

    wattron   (pDeskWindow, COLOR_PAIR(COLOR_GREEN));
    mvwprintw (pDeskWindow, ++row, cols_desk, "STOCK");
    mvwprintw (pDeskWindow, row, cols_disc, "WASTE");
    wattroff  (pDeskWindow, COLOR_PAIR(COLOR_GREEN));
    mvwprintw (pDeskWindow, ++row, cols_desk, "---");
    if ( head )
    {
      move(row, cols_disc);
      head->Show();
    }
    std::string size_desk_str = deskpile.SizeTotext();
    mvwprintw  (pDeskWindow, ++row, cols_desk, size_desk_str.c_str());
    std::string size_disc_str = deskpile.SizeTotext();
    mvwprintw  (pDeskWindow, row, cols_disc, size_disc_str.c_str());
  }
  catch(const std::exception& e)
  {
    std::cerr << "Display Deck : " << e.what() << '\n';
  }
}

//----------------------------
//        DisplaySuit
//----------------------------
void Renderer::DisplaySuit ( int aRow, int aCols, Game& arGame )
{
  try
  {
    int start_row = aRow;
    int count = 0;
    for (int i = Game::HEARTS; i < Game::PIKES; ++i) 
    {
      int cols = aCols + (10*count);
      std::string suit_name = "FOUNDATION " + std::to_string(i+1);

      wattron   (pSuitWindow, COLOR_PAIR(COLOR_GREEN));
      mvwprintw (pSuitWindow, start_row, cols, suit_name.c_str());
      wattroff  (pSuitWindow, COLOR_PAIR(COLOR_GREEN));

      SuitPile& suit = arGame.GetSuitPile(i);
      suit.Show( start_row, cols, pSuitWindow );
      ++count;
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << "Display Suit: " << e.what() << '\n';
  }
  
}

//----------------------------
//        DisplayTable
//----------------------------
void Renderer::DisplayTable ( int aRow, int aCols, Game& arGame )
{
  try
  {
    int start_row = aRow;
    int count = 0;
    for( int i = Game::COLUMN1; i <= Game::COLUMN7; i++ )
    {
      int cols = aCols + (10*count);
      std::string table_name = "TABLEAU " + std::to_string(i+1);

      wattron   (pTableWindow, COLOR_PAIR(COLOR_GREEN));
      mvwprintw (pTableWindow, start_row, cols, table_name.c_str());
      wattroff  (pTableWindow, COLOR_PAIR(COLOR_GREEN));

      TablePile& tablePile = arGame.GetTablePile( i );
      tablePile.Show( start_row, cols, pTableWindow );
      ++count;
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << "Display Table : " << e.what() << '\n';
  }
}

//----------------------------
//        DisplayState
//----------------------------
void Renderer::DisplayState (  int aRow, int aCols, const std::string& arStr )
{
  try
  {
      int row{aRow};
      mvwprintw(pStateWindow, ++row, aCols, "Score: 0");
      mvwprintw(pStateWindow, ++row, aCols, "solitaire-cli > ");
  }
  catch(const std::exception& e)
  {
    std::cerr << "Display State : " << e.what() << '\n';
  }
}

//----------------------------
//     UpdateWindowTitle
//----------------------------
void Renderer::UpdateWindowTitle(int score, int move_state)
{
  std::string title {"Game Score: " + std::to_string(score) + " Move State : " + std::to_string(move_state) };
}