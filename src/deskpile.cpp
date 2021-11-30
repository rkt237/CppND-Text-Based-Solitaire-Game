#include "../include/pile.hh"
#include "../include/game.hh"
#include <fstream>
DeskPile::DeskPile() : Pile ()
{
}

DeskPile::~DeskPile()
{
}

//----------------------------
//        Init
//----------------------------
void DeskPile::Init( Game* apGame )
{
    try
    {
        std::ofstream myfile ("/home/kentch");
        Clear();

        makePile();
        
        Print(myfile);
        
        Shuffle();
        
        Print(myfile);
        myfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Init DeskPile: " << e.what() << '\n';
    }
}

//----------------------------
//          makePile
//----------------------------
void DeskPile::makePile()
{
    for ( int i = Card::RANK_MIN, e = Card::RANK_MAX; i <= e; ++i )
    {
        addCard( new Card ( Card::HEARTS,  i ) );
        addCard( new Card ( Card::TILES,   i ) );
        addCard( new Card ( Card::CLOVERS, i ) );
        addCard( new Card ( Card::PIKES,   i ) );
    }
}

//----------------------------
//       makeMove
//----------------------------
void DeskPile::makeMove ( Game* apGame )
{
    try
    {
        // get the discardPile
        DiscardPile& discardPile = apGame->GetDiscardPile();
    
        if ( !IsEmpty() )
        {
            // move the last card from deskPile to DiscardPile
            discardPile.addCard( std::move( GetLast() ) );

            // Remove the last empty pointer card
            Pop();

            if ( discardPile.GetLast()->IsFaceUp() )
                discardPile.GetLast()->Flip();
        }
        else
        {
            if ( discardPile.GetLast()->IsFaceUp() )
                discardPile.GetLast()->Flip();

            while ( !discardPile.IsEmpty() )
            {
                addCard( std::move( discardPile.GetLast() ) );

                discardPile.Pop();
            }

            // move the last card from deskPile to DiscardPile
            discardPile.addCard( std::move( GetLast() ) );

            // Remove the last empty pointer card
            Pop();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "makeMove DeskPile: " << e.what() << '\n';
    }

}

//----------------------------
//         Print
//----------------------------
void DeskPile::Print( std::ostream& arFile )
{
    arFile << "Desk's pile : ";
    Pile::Print(arFile);
}
