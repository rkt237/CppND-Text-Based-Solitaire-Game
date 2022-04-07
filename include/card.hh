#ifndef CARD_HH
#define CARD_HH

#include <stdexcept>

/**
 * 
 * 
 */
class Card
{
public:

    enum SUIT_TYP
    {
        HEARTS      = 0,      // ♡
        TILES       = 1,      // ♢
        CLOVERS     = 2,      // ♣
        PIKES       = 3,      // ♠
        SUIT_MAX    = 4,
    };

    enum CARD_COLOR
    {
        BLACK = 1,
        RED   = 2,
    };
    
    enum SUIT_RANK
    {
        RANK_MIN    = 1,
        RANK_A      = RANK_MIN,
        RANK_2      = 2,
        RANK_3      = 3,
        RANK_4      = 4,
        RANK_5      = 5,
        RANK_6      = 6,
        RANK_7      = 7,
        RANK_8      = 8,
        RANK_9      = 9,
        RANK_10     = 10,
        RANK_J      = 11,
        RANK_Q      = 12,
        RANK_K      = 13,
        RANK_MAX    = RANK_K,
    };
    
    Card ();                            // constructor
    Card ( int aTyp, int aRank );       // constructor
    ~Card();                            // destructor

    Card (const Card &other);           // 2 : copy constructor
    Card &operator=(const Card &other); // 3 : copy assignment operator
    Card (Card&& other);                // 4 : move constructor
    Card &operator=(Card&& other);      // 5 : move assignment operator

    // getter
    int         GetSuitTyp() const;
    int         GetRank() const;

    // setter
    void        SetRank( int aRank );
    void        SetSuitTyp( int aTyp );
    void        Flip();
    
    // Card Text
    std::string ToText();
    void        Show();

    bool IsFaceUp() { return mFaceUp; }
    
    bool IsAlternateColor ( Card& other );
    bool IsRed();
    bool IsBlack();

protected:
    
    std::string SuitToString ();
    std::string RankToString ();

public:
    
    /* 
     *  Used to get the next and prev card, data handles (not owned)
     */
    Card* mpParent = nullptr;
    Card* mpChild  = nullptr;

private:

    int mTyp;       // card suit
    int mRank;      // card rank
    bool mFaceUp;   // is face up
};

#endif