#include "../include/renderer.hh"

#include <iostream>
#include <string>

const static int DEFAULT_COLOR = -1;

//----------------------------
//       Constructor
//----------------------------
Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height)
: mScreenWidth(screen_width)
, mScreenHeight(screen_height)
{
  Init();
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
  keypad(stdscr, TRUE); // enable abbreviation of function keys 
  use_default_colors(); // use default color
  cbreak();             // terminate ncurses on ctrl + c
  start_color();        // enable color
  
  init_pair(Card::CARD_COLOR::BLACK, DEFAULT_COLOR, DEFAULT_COLOR);
  init_pair(Card::CARD_COLOR::RED,   COLOR_RED,     DEFAULT_COLOR);
}

//----------------------------
//          Init
//----------------------------
void Renderer::Display( Game& arGame ) 
{
  try
  {   
    int x_max{getmaxx(stdscr)};
    WINDOW* desk_window    = newwin(9,  x_max - 1, 0, 0);
    WINDOW* suit_window    = newwin(40, x_max - 1, 0, 0);
    WINDOW* table_window   = newwin(9,  x_max - 1, suit_window->_maxy  + 4, 0);
    WINDOW* state_window   = newwin(9,  x_max - 1, table_window->_maxy + 4, 0);

    box( desk_window,  0, 0 );
    box( suit_window,  0, 0 );
    box( table_window, 0, 0 );
    box( state_window, 0, 0 );

    DisplayDeck  ( 9,  0, arGame, desk_window );
  
    DisplaySuit  ( 40, 0, arGame, suit_window );

    DisplayTable ( 9, suit_window->_maxy, arGame, table_window );

    DisplayState ( 9, table_window->_maxy, "Game Score: ", state_window );
  }
  catch(const std::exception& e)
  {
    std::cerr << "Display: " << e.what() << '\n';
  }
}

//----------------------------
//         DisplayDeck
//----------------------------
void Renderer::DisplayDeck ( int aRow, int aCols, Game& arGame, WINDOW* window )
{
  try
  {
    int row{aRow};
    int const cols_desk = aCols + 1;
    int const cols_disc = aCols + 10;

    DeskPile& deskpile = arGame.GetDeskPile();
    
    DiscardPile& discpile = arGame.GetDiscardPile();
    
    Card* head = discpile.GetLast();

    wattron(window, COLOR_PAIR(COLOR_GREEN));
    mvwprintw(window, ++row, cols_desk, "STOCK");
    mvwprintw(window, row, cols_disc, "WASTE");
    wattroff(window, COLOR_PAIR(COLOR_GREEN));
    mvwprintw(window, ++row, cols_desk, "---");
    move(row, cols_disc);
    head->Show();
    std::string size_desk_str = deskpile.SizeTotext();
    mvwprintw(window, ++row, cols_desk, size_desk_str.c_str());
    std::string size_disc_str = deskpile.SizeTotext();
    mvwprintw(window, row, cols_disc, size_disc_str.c_str());
  }
  catch(const std::exception& e)
  {
    std::cerr << "Display Deck : " << e.what() << '\n';
  }
}

//----------------------------
//        DisplaySuit
//----------------------------
void Renderer::DisplaySuit ( int aRow, int aCols, Game& arGame, WINDOW* window )
{
  try
  {
    int start_row = aRow;
    for (int i = 0; i < Card::SUIT_MAX; ++i) 
    {
      int cols = aCols + (10*i);
      std::string suit_name = "FOUNDATION " + std::to_string(i+1);

      wattron   (window, COLOR_PAIR(COLOR_GREEN));
      mvwprintw (window, start_row, cols, suit_name.c_str());
      wattroff  (window, COLOR_PAIR(COLOR_GREEN));

      SuitPile& suit = arGame.GetSuitPile(i);
      suit.Show( start_row, cols, window );
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
void Renderer::DisplayTable ( int aRow, int aCols, Game& arGame, WINDOW* window )
{
  try
  {
    int start_row = aRow;
    int count = 0;
    for( int i = Game::COLUMN1; i <= Game::COLUMN7; i++ )
    {
      int cols = aCols + (10*count);
      std::string table_name = "TABLEAU " + std::to_string(i+1);

      wattron   (window, COLOR_PAIR(COLOR_GREEN));
      mvwprintw (window, start_row, cols, table_name.c_str());
      wattroff  (window, COLOR_PAIR(COLOR_GREEN));

      TablePile& tablePile = arGame.GetTablePile( i );
      tablePile.Show( start_row, cols, window );
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
void Renderer::DisplayState (  int aRow, int aCols, const std::string& arStr, WINDOW* window )
{
  try
  {
      int row{aRow};
      mvwprintw(window, ++row, aCols, "Score: 0");
      mvwprintw(window, ++row, aCols, "solitaire-cli > ");
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