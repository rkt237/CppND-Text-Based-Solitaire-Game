#include "../include/controller.h"

#include <algorithm>
#include <iterator>
#include <regex>

const static int TABLE_COUNT = 7;
const static int SUIT_COUNT = 4;
const static int AMOUNT_MAX = 13;

//----------------------------
//         HandleInput
//----------------------------
int Controller::HandleInput(const std::string& arCmdStr, ParseSolitaire& arParsedCmd, Game* apGame)
{
    int State = MOVE_OK;
    try
    {       
        Parse ( arCmdStr, arParsedCmd );

        //catch source / destination too high
        if ( (arParsedCmd.mSrcAmount < 0) && ( arParsedCmd.mSrcAmount > AMOUNT_MAX ) )
        {
            arParsedCmd.mState = INVALID_AMOUNT;
            State = INVALID_AMOUNT;
            return State;
        }

        if ( (arParsedCmd.mSrc != 't') || (arParsedCmd.mDest != 't') 
            || (arParsedCmd.mDest != 'f') || (arParsedCmd.mSrc != 'n') )
        {
            arParsedCmd.mState = INVALID_CMD;
            State = INVALID_CMD;
            return State;
        }

        if ( (arParsedCmd.mSrc == 't') && ( (arParsedCmd.mSrcIndex > TABLE_COUNT) || (arParsedCmd.mSrcIndex < 1)) )
        {
            arParsedCmd.mState = INVALID_SRC;
            State = INVALID_SRC;
            return State;
        }

        if (  ( (arParsedCmd.mDest == 't') && 
                ((arParsedCmd.mDestIndex > TABLE_COUNT) || (arParsedCmd.mDestIndex < 1)))
           || ( (arParsedCmd.mDest == 'f') && 
                ((arParsedCmd.mDestIndex > SUIT_COUNT) || (arParsedCmd.mDestIndex < 1))) )
        {
            arParsedCmd.mState = INVALID_DEST;
            State = INVALID_DEST;
            return State;
        }

        if (arParsedCmd.mSrc == 'n')
        {
            // get the deskpile
            DeskPile& pile = apGame->GetDeskPile();
            if ( pile.IsEmpty() )
                State = STOCK_EMPTY;
            else
                State = MOVE_OK;

            arParsedCmd.mState = (MOVE_STATE)State;
            return State;
        }

        if ( arParsedCmd.mSrc == 't' )
        {
            TablePile& pile = apGame->GetTablePile( arParsedCmd.mSrcIndex );

            if ( pile.IsEmpty() )
            {
                arParsedCmd.mState = SOURCE_EMPTY;
                State = SOURCE_EMPTY;
                return State;
            }

            if ( pile.GetSize() < arParsedCmd.mSrcAmount )
            {
                arParsedCmd.mState = INVALID_AMOUNT;
                State = INVALID_AMOUNT;
                return State;
            }
        }

        arParsedCmd.mState = MOVE_OK;
        State = MOVE_OK;
        return State;
    }
    catch(const std::exception& e)
    {
        std::cerr << "HandleInput: " << e.what() << '\n';
    }
    return State;
}

//----------------------------
//         Parse
//----------------------------
void Controller::Parse( const std::string& arCmd, ParseSolitaire& arData )
{
    try
    {
        std::vector<std::string> splittedStrings = SplitStr( arCmd, " " );
        size_t noof = splittedStrings.size();

        if ( noof && noof < 3 )
        {
            for( size_t i = 0; i < noof; ++i )
            {
                std::string str = splittedStrings[i];
                
                int amount = 0, cols = -1;
                char ch;
                if (  !str.empty() && isdigit( str[0] ) )
                {
                    sscanf (str.c_str(),"%d%c%d", &amount, &ch, &cols);
                }
                else
                {
                    sscanf (str.c_str(),"%c%d", &ch, &cols);
                }

                if ( i == 0 )
                {
                    arData.mSrcAmount = amount;
                    arData.mSrcIndex  = cols;
                    arData.mSrc       = tolower(ch);
                    arData.mState     = MOVE_OK; 
                }
                else
                {
                    arData.mDestIndex = cols;
                    arData.mSrcAmount = 0;
                    arData.mSrc       = tolower(ch);
                    arData.mState     = MOVE_OK; 
                }
            }
        }
        else
        {
            arData.mState = INVALID_CMD;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Parse: " << e.what() << '\n';
    }
}

//----------------------------
//         SplitStr
//----------------------------
std::vector<std::string> Controller::SplitStr( const std::string& arStr, const std::string aDelimeter )
{
    try
    {
        std::regex reg (aDelimeter);
        return { std::sregex_token_iterator(arStr.begin(), arStr.end(), reg, -1), std::sregex_token_iterator()};
    }
    catch(const std::exception& e)
    {
        std::cerr << "Splitting string : " << e.what() << '\n';
    }
    return std::vector<std::string>();
}