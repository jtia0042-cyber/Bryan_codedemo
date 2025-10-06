//
// Created by ASUS on 25-8-27.
//

#include "Card.h"
Card::Card(int newLabel, bool newStatus, bool newMatched)
{
    setLabel(newLabel);
    setStatus(newStatus);
    setMatched(newMatched);
}
Card::~Card()
{

}

int Card::getLabel()
{
    return Label;
}
bool Card::getStatus()
{
    return status;
}
bool Card::getMatched()
{
    return matched;
}

void Card::setLabel(int newLabel)
{
    Label = newLabel;
}
void Card::setStatus(bool newStatus)
{
    status = newStatus;
}
void Card::setMatched(bool newMatched)
{
    matched = newMatched;
}
void Card::flip()
{
    if (!matched)
    {
        status = !status;
    }

}

void Card::display()
{
    if (matched || status)
    {
        if (Label < 10)
        {
            cout << "  " << Label;
        }
        else
        {
            cout << " " << Label;
        }
    }
    else
    {
        cout << "  X  ";
    }
}