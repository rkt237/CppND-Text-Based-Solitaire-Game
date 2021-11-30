#include "../include/pile.hh"
#include "../include/game.hh"

DiscardPile::DiscardPile() : Pile ()
{
}

DiscardPile::~DiscardPile()
{
}

//----------------------------
//        Init
//----------------------------
void DiscardPile::Init( Game* apGame )
{
    Clear();

    std::cout << "Discard\n";
}

//----------------------------
//       makeMove
//----------------------------
void DiscardPile::makeMove ( Game* apGame )
{
    try
    {
        if ( !IsEmpty() )
        {
            Card* p_lastCard = GetLast();
            
            bool done = false;

            for( int i = 0; i < Card::SUIT_MAX; i++ )
            {
                SuitPile& suitPile = apGame->GetSuitPile(i);

                if ( suitPile.canTake( p_lastCard ) )
                {
                    p_lastCard->Flip();

                    // add to the suitPile
                    suitPile.addCard( std::move( p_lastCard ) );

                    // Remove the last empty pointer card
                    Pop();
                    
                    done = true;

                    break;
                }
            }

            if ( !done )
            {
                for( int i = Game::COLUMN1; i <= Game::COLUMN7; i++ )
                {
                    TablePile& tablePile = apGame->GetTablePile( i );

                    if ( tablePile.canTake( p_lastCard ) )
                    {
                        p_lastCard->Flip();

                        // add to the suitPile
                        tablePile.addCard( std::move( p_lastCard ) );

                        // Remove the last empty pointer card
                        Pop();
                        
                        break;
                    }
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "makeMove DiscardPile: " << e.what() << '\n';
    }
}

//----------------------------
//         Print
//----------------------------
void DiscardPile::Print( std::ostream& arFile )
{
    arFile << "Discard's pile : ";
    Pile::Print(arFile);
}