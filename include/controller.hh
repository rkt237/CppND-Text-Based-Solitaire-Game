#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "game.hh"
#include <string>
#include <vector>

class Game;

enum MOVE_STATE
{
  MOVE_OK = 1,
  INVALID_CMD,
  INVALID_MOVE,
  INVALID_DEST,
  INVALID_SRC,
  INVALID_AMOUNT,
  SOURCE_EMPTY,
  STOCK_EMPTY
};

struct ParseSolitaire
{
  char        mSrc;
  char        mDest;
  size_t      mSrcIndex;
  size_t      mDestIndex;
  int         mSrcAmount;
  MOVE_STATE  mState;
};

class Controller
{

 public:

  int HandleInput(const std::string& arCmdStr, ParseSolitaire& arParsedCmd, Game* apGame);

 private:

  void Parse ( const std::string& arCmd, ParseSolitaire& arData );

  std::vector<std::string> SplitStr( const std::string& arStr, const std::string aDelimeter );
};

#endif