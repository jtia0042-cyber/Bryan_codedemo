//
// Created by ASUS on 25-8-27.
//

#include "Player.h"
Player::Player()
{
    name = "NoName";
    score = 0;
}

Player::Player(string newName)
{
    setName(newName);
    score = 0;
}
Player::~Player()
{

}
string Player::getName()
{
    return name;
}
void Player::setName(string newName)
{
    name = newName;
}
int Player::getScore()
{
    return score;
}
void Player::addScore(int newScore)
{
    score += newScore;
}
void Player::display()
{
    cout<<"Player Name: "<<name<<endl;
    cout<<"Score: "<<score<<endl;
}


