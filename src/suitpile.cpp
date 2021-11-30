#include "../include/pile.hh"
#include "../include/game.hh"

SuitPile::SuitPile(int aSuitTyp) 
: Pile ()
, mTyp ( aSuitTyp )
{
}

SuitPile::~SuitPile()
{
}

//----------------------------
//        Init
//----------------------------
void SuitPile::Init( Game* apGame )
{
    Clear();
}

//----------------------------
//        canTake
//----------------------------
bool SuitPile::canTake(Card* apCard)
{
    try
    {
        // Get the size of cards
        if ( IsEmpty() )
        {
            // the first card is A
            return ( apCard->GetRank() == Card::RANK_MIN );
        }
        else
        {
            // getting the last element in the list
            Card* p_last = GetLast();

            // check if the current card is the next element of the last element
            return ( (p_last->GetSuitTyp() == apCard->GetSuitTyp()) && ( (p_last->GetRank() + 1) == apCard->GetRank() ));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "canTake SuitPile: "<< e.what() << '\n';
    }

    return false;
}

//----------------------------
//       makeMove
//----------------------------
void SuitPile::makeMove ( Game* apGame )
{
    try
    {
        // do nothing
    }
    catch(const std::exception& e)
    {
        std::cerr << "makeMove SuitPile: " << e.what() << '\n';
    }
}

//----------------------------
//         Print
//----------------------------
void SuitPile::Print( std::ostream& arFile )
{
    arFile << "Suit's pile (" << mTyp << ") : ";
    Pile::Print(arFile);
}