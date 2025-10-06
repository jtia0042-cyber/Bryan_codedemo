//
// Created by ASUS on 25-8-27.
//

#ifndef CARD_H
#define CARD_H
#include<iostream>
#include<string>
using namespace std;


class Card {
private:
    int Label;
    bool status;
    bool matched;

public:
    Card(int Label, bool Status, bool matched);
    ~Card();
    int getLabel();
    bool getStatus();
    bool getMatched();

    void setLabel(int newLabel);
    void setStatus(bool newStatus);
    void setMatched(bool newMatched);
    void flip();
    void display();

};

#endif //CARD_H
