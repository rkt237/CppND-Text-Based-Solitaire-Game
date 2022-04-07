#include "../include/pile.hh"

#include <curses.h>

#include <iostream>
#include <iomanip>

//----------------------------
//        constructor
//----------------------------
Pile::Pile()
{

}

//----------------------------
//        destructor
//----------------------------
Pile::~Pile()
{
}

//----------------------------
//        Init
//----------------------------
void Pile::Init()
{
    Clear();
}

//----------------------------
//        IsEmpty
//----------------------------
bool Pile::IsEmpty()
{
    return mStack.empty();
}

//----------------------------
//        GetTop
//----------------------------
Card* Pile::GetTop()
{
    Card* p_card = nullptr;
    if ( !mStack.empty() )
        p_card = *(mStack.begin());

    return p_card;
}

//----------------------------
//        GetLast
//----------------------------
Card* Pile::GetLast()
{
    Card* p_card = nullptr;
    if ( !mStack.empty() )
        p_card = mStack.back();

    return p_card;
}

//----------------------------
//      operator []
//----------------------------
Card* Pile::operator[](int aIndex)
{
    if ( (aIndex >= 0) && (aIndex < GetSize()) )
        return mStack[aIndex];
    else
        throw std::out_of_range("out of range");

    return NULL;
}

void Pile::RemoveFrom( int aIndex )
{
    mStack.erase( std::next(mStack.begin(), aIndex), mStack.end() );
}

//----------------------------
//        Pop
//----------------------------
void Pile::Pop()
{
    mStack.pop_back();
}

//----------------------------
//        GetSize
//----------------------------
int Pile::GetSize()
{
    return mStack.size();
}

//----------------------------
//        Clear
//----------------------------
void Pile::Clear()
{
    for ( auto p_card : mStack )
    {
        delete p_card;
        p_card = nullptr;
    }

    mStack.clear();
}

//----------------------------
//        addCard
//----------------------------
void Pile::addCard(Card* pCard)
{
    if ( pCard )
    {
        Card* p_prev = NULL;
        
        if ( !mStack.empty() )
        {
            p_prev = mStack.back();

            pCard->mpParent = p_prev;
            
            p_prev->mpChild = pCard;
        }

        mStack.push_back(pCard);
    }
    else
    {
        throw std::invalid_argument("Card is nullptr");
    }
}

//----------------------------
//        canTake
//----------------------------
bool Pile::canTake(Card* apCard)
{
    return false;
}

//----------------------------
//           Show
//----------------------------
void Pile::Show( int row, int cols, WINDOW* window )
{
    try
    {
        std::string size_str = SizeTotext();
        mvwprintw(window, ++row, cols, size_str.c_str());

        for ( auto p_card : mStack )
        {
            if ( p_card == nullptr )
                continue;
            
            std::string card_str = p_card->ToText();
            
            int color_pair = p_card->IsRed() ? Card::CARD_COLOR::RED : Card::CARD_COLOR::BLACK;

            attron(COLOR_PAIR(color_pair));
            mvwprintw(window, ++row, cols, card_str.c_str());
            attroff(COLOR_PAIR(color_pair));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "show TablePile: " << e.what() << '\n';
    }   
}

std::string Pile::SizeTotext()
{
    std::stringstream stream;
    stream << "[ " << GetSize() << " ]";
    std::string str = stream.str();

    return str;
}

//----------------------------
//         Print
//----------------------------
void Pile::Print( std::ostream& arFile )
{
    for ( auto p_card : mStack )
    {
        if (p_card)
            arFile << std::fixed << std::left << std::setw(6) << p_card->ToText();
    }

    arFile << std::endl;
}