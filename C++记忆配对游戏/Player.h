//
// Created by ASUS on 25-8-27.
//

#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<string>
using namespace std;

class Player {
private:
    string name;
    int score;

public:
    Player();
    Player(string name);
    ~Player();
    string getName();
    int getScore();
    void setName(string newName);
    void addScore(int newScore);
    void display();

};

#endif //PLAYER_H
