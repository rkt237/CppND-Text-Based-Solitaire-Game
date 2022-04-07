#ifndef PILE_HH
#define PILE_HH

#include "card.hh"
#include "game.hh"

#include <iostream>
#include <vector>
#include <ncurses.h>

class Game;

class Pile
{
protected :
    
    std::vector<Card*> mStack;

public:

    Pile();

    virtual ~Pile();

    virtual void Init();

    virtual bool  IsEmpty();

    virtual Card* GetTop();

    virtual Card* GetLast();

    virtual Card* operator[](int aIndex);

    virtual void  RemoveFrom( int aIndex );

    virtual void  Pop();

    virtual int   GetSize();

    virtual void  Clear();

    virtual void  addCard(Card* pCard);

    virtual bool  canTake(Card* apCard);

    virtual void  makeMove ( Game* apGame ) = 0;

    virtual void  Show( int row, int cols, WINDOW* window );

    virtual void  Print( std::ostream& arFile );

    virtual std::string SizeTotext();
};

class DeskPile : public Pile
{
private:
    

public:

    DeskPile();

    ~DeskPile();

    void  Shuffle();
    
    void Init     () override;
    
    void makeMove ( Game* apGame ) override;

    void Print    ( std::ostream& arFile ) override;
    
    void makePile ( );
};

class DiscardPile : public Pile
{
private:
    
public:
    
    DiscardPile();

    ~DiscardPile();

    void makeMove ( Game* apGame ) override;

    void Print    ( std::ostream& arFile ) override;
};

class SuitPile : public Pile
{
private:
    
    int mTyp;

public:
    
    SuitPile(int aSuitTyp);
    
    ~SuitPile();

    bool canTake  ( Card* apCard ) override;

    void makeMove ( Game* apGame ) override;

    void Print    ( std::ostream& arFile ) override;
};

class TablePile : public Pile
{
private:
    
    int mInitNum;

public:
    
    TablePile      ( int aSize );
    
    ~TablePile     ();

    Card* GetHead  ( int aIndex );

    void  Deal     ( Pile* apPile );

    bool  canTake  ( Card* apCard) override;

    void  makeMove ( Game* apGame ) override;

    void  Print    ( std::ostream& arFile ) override;
};

#endif