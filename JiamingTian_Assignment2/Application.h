//
// Created by ASUS on 25-8-27.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;


class Application {
private:
    vector<Card> deck;
    int Rows;
    int Cols;
    Player player1;
    Player player2;
    int currentPlayer;
    bool hint1;
    bool hint2;

    void initialiseAndShuffleCards();
    void layoutCards();
    void selectFirstPlayer();
    void changePlayers();
    void manageScores(int scores);
    void showScores();
    bool isGameOver();
    void declareWinnerAndExit();
    void setTotal();

public:
    Application();
    ~Application();

    void playGame();
    void runMenu();
    void displayHowToPlay(string filename);
    void displayReport(string filename);
    void displayExit(string filename);
};

#endif //APPLICATION_H
