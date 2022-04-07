#include "../include/pile.hh"
#include "../include/game.hh"

TablePile::TablePile(int aSize) 
: Pile ()
, mInitNum ( aSize )
{
}

TablePile::~TablePile()
{
}

//----------------------------
//         GetHead
//----------------------------
Card* TablePile::GetHead( int aIndex )
{
    try
    {
        int count = 0;

        Card* p_head = GetTop();
        
        while ( p_head->mpChild )
        {
            if ( p_head->IsFaceUp() )
            {
                aIndex = count;
                break;
            }
            
            p_head = p_head->mpChild;
            
            ++count;
        }

        return p_head;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Heat TablePile: " << e.what() << '\n';
    }
    
    return NULL;
}

//----------------------------
//        Deal
//----------------------------
void TablePile::Deal( Pile* apPile )
{
    try
    {
        Clear();

        // checking for nullptr
        if ( apPile == nullptr )
            throw std::invalid_argument("Card is nullptr");

        // each tablepile hat a fixed number of cards by init
        for(int i = 0; i < mInitNum; i++ ) 
        {
            if ( !apPile->IsEmpty() )
            {
                // move the last card from desk to table
                addCard( std::move( apPile->GetLast() ) );

                // clear the last card after moving
                apPile->Pop();
            }
        }

        // flip the last card
        GetLast()->Flip();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Init TablePile: " << e.what() << '\n';
    }
}

//----------------------------
//        canTake
//----------------------------
bool TablePile::canTake(Card* apCard)
{
    try
    {
        // checking for nullptr
        if ( apCard == nullptr )
            throw std::invalid_argument("Card is nullptr");

        // Get the size of cards
        if ( IsEmpty() )
        {
            // the first card is K
            return ( apCard->GetRank() == Card::RANK_MAX );
        }
        else
        {
            // getting the last element in the list
            Card* p_last = GetLast();

            // the current card muss be the next element of the last element and alternated color
            return ( ( p_last->IsAlternateColor(*apCard) ) && ( (p_last->GetRank() + 1) == apCard->GetRank() ));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "canTake TablePile: " << e.what() << '\n';
    }

    return false;
}

//----------------------------
//       makeMove
//----------------------------
void TablePile::makeMove ( Game* apGame )
{
    try
    {
        if ( !IsEmpty() )
        {
            Card* p_lastCard = GetLast();
            
            bool done = false;
            if ( !p_lastCard->IsFaceUp() )
            {
                p_lastCard->Flip();
            }
            else
            {
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
                    int idx = 0;

                    Card* p_head = GetHead( idx );

                    if ( p_head )
                    {
                        for( int i = Game::COLUMN1; i <= Game::COLUMN7; i++ )
                        {
                            TablePile& tablePile = apGame->GetTablePile( i );

                            if ( tablePile.canTake( p_head ) )
                            {
                                for ( int i = idx, ie = GetSize(); i < ie; ++i )
                                {
                                    // add to the suitPile
                                    tablePile.addCard( std::move( tablePile[i] ) );
                                }

                                // Remove from index to end
                                tablePile.RemoveFrom(idx);

                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "makeMove TablePile: " << e.what() << '\n';
    }
}

//----------------------------
//         Print
//----------------------------
void TablePile::Print( std::ostream& arFile )
{
    arFile << "Table's pile (" << mInitNum << ") : ";
    Pile::Print(arFile);
}