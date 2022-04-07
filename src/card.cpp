#include "../include/card.hh"

#include "../include/renderer.hh"

//----------------------------
//          Card
//----------------------------
Card::Card(void)
: mpParent ( nullptr )
, mpChild  ( nullptr )
, mTyp     (0)
, mRank    (0)
, mFaceUp  ( false   )
{
}

//----------------------------
//          Card
//----------------------------
Card::Card(int aTyp, int aRank)
: mpParent ( nullptr )
, mpChild  ( nullptr )
, mTyp     (0)
, mRank    (0)
, mFaceUp  ( false   )
{
    SetSuitTyp(aTyp);
    SetRank(aRank);
}

//----------------------------
//        ~Card
//----------------------------
Card::~Card(void)
{
}

//----------------------------
//          Card
//----------------------------
Card::Card (const Card &other)
{
    if ( mpParent != nullptr )
        delete mpParent;
    
    if ( mpChild != nullptr )
        delete mpChild;

    mpParent = new Card();
    mpChild  = new Card();

    mpParent = other.mpParent;
    mpChild  = other.mpChild;
    mTyp     = other.mTyp;
    mRank    = other.mRank;
    mFaceUp  = other.mFaceUp;
}

//----------------------------
//          Card
//----------------------------
Card& Card::operator=(const Card &other)
{
    if (this == &other)
        return *this;

    if ( mpParent != nullptr )
        delete mpParent;
    
    if ( mpChild != nullptr )
        delete mpChild;

    mpParent = new Card();
    mpChild  = new Card();

    mpParent = other.mpParent;
    mpChild  = other.mpChild;
    mTyp     = other.mTyp;
    mRank    = other.mRank;
    mFaceUp  = other.mFaceUp;

    return *this;
}

//----------------------------
//          Card
//----------------------------
Card::Card (Card&& other)
{
    mpParent = other.mpParent;
    mpChild  = other.mpChild;
    mTyp     = other.mTyp;
    mRank    = other.mRank;
    mFaceUp  = other.mFaceUp;

    other.mpParent = nullptr;
    other.mpChild  = nullptr;
}

//----------------------------
//          Card
//----------------------------
Card& Card::operator=(Card&& other)
{
    if (this == &other)
        return *this;

    mpParent = other.mpParent;
    mpChild  = other.mpChild;
    mTyp     = other.mTyp;
    mRank    = other.mRank;
    mFaceUp  = other.mFaceUp;

    other.mpParent = nullptr;
    other.mpChild  = nullptr;

    return *this;
}

//----------------------------
//        GetSuitTyp
//----------------------------
int Card::GetSuitTyp() const
{
    return mTyp;
}

//----------------------------
//          GetRank
//----------------------------
int Card::GetRank() const
{
    return mRank;
}

//----------------------------
//          SetRank
//----------------------------
void Card::SetRank( int aRank )
{
    if ( (aRank >= RANK_MIN) && (aRank <= RANK_MAX) )
        mRank = aRank;
    else
        throw std::invalid_argument("rank must be between 1 and 13");
}

//----------------------------
//          SetSuitTyp
//----------------------------
void Card::SetSuitTyp( int aTyp )
{
    if ( (aTyp >= HEARTS) && (aTyp <= PIKES) )
        mTyp = aTyp;
    else
        throw std::invalid_argument("invalid suit typ");
}

//----------------------------
//        Flip
//----------------------------
void Card::Flip()
{
    if ( !mFaceUp )
        mFaceUp = !mFaceUp;
}

//----------------------------
//         ToText
//----------------------------
std::string Card::ToText()
{
    //std::string str = mFaceUp ? "*" : "";
    //return RankToString() + SuitToString() + str;
    return RankToString() + SuitToString();
}

//----------------------------
//         Show
//----------------------------
void Card::Show()
{
    if ( mFaceUp )
    {
        int color_pair = IsRed() ? CARD_COLOR::RED : CARD_COLOR::BLACK;

        attron(COLOR_PAIR(color_pair));
        printw( "%s%s", RankToString(), SuitToString() );
        attroff(COLOR_PAIR(color_pair));
    }
    else
    {
        printw("---");
    }
}

//----------------------------
//       SuitToString
//----------------------------
std::string Card::SuitToString ()
{
    std::string suit;
    switch (mTyp)
    {
        case HEARTS:
            suit = "\u2665";
            break;
        case TILES:
            suit = "\u2666";
            break;
        case CLOVERS:
            suit = "\u2663";
            break;
        case PIKES:
            suit = "\u2660";
            break;
    }

    return suit;
}

//----------------------------
//       RankToString
//----------------------------
std::string Card::RankToString ()
{
    if      ( mRank == RANK_A ) return "A";
    else if ( mRank == RANK_J ) return "J";
    else if ( mRank == RANK_Q ) return "Q";
    else if ( mRank == RANK_K ) return "K";
    else
    {
        return std::to_string(mRank);
    }
}

//----------------------------
//        IsRed
//----------------------------
bool Card::IsRed()
{
    return ( (mTyp == HEARTS) || (mTyp == TILES) );
}

//----------------------------
//        IsBlack
//----------------------------
bool Card::IsBlack()
{
    return ( (mTyp == CLOVERS) || (mTyp == PIKES) );
}

//----------------------------
//     IsAlternateColor
//----------------------------
bool Card::IsAlternateColor ( Card& other )
{
    return ( ( this->IsBlack() && other.IsRed() ) || ( this->IsRed() && other.IsBlack() ) );
}
