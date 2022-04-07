#include "../include/pile.hh"
#include "../include/game.hh"

#include <fstream>
#include <random>

DeskPile::DeskPile() : Pile ()
{
}

DeskPile::~DeskPile()
{
}

//----------------------------
//        Init
//----------------------------
void DeskPile::Init()
{
    try
    {
        Clear();

        makePile();
        
        std::ofstream myfile ("/home/kentch/deskpile.txt");
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
//       Shuffle
//----------------------------
void DeskPile::Shuffle()
{
    int n = GetSize();
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    // Random number distribution that produces integer values from 0 to the number of card
    std::uniform_int_distribution<int> random(0, (n-1));

    for ( int i = 0; i < n; ++i )
    {
        // random number
        int j = random(gen);
        
        std::swap(mStack[i], mStack[j]);
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
