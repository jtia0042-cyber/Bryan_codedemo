//
// Created by ASUS on 25-8-27.
//

#include "Application.h"

Application::Application()
{
    currentPlayer=0;
    hint1=false;
    hint2=false;
    player1.setName("Player 1");
    player2.setName("Player 2");
}

Application::~Application()
{

}

void Application::playGame()
{
    int Players;
    int round = 0;
    hint1 = false;
    hint2 = false;

    cout << "How many players? (2 to 4): ";
    cin >> Players;

    // only allow 2 players in this version
    while (Players != 2)
    {
        cout << "Please enter '2' How many players? (2): ";
        cin >> Players;
    }

    // input names
    string player_1, player_2;
    cin.ignore();
    cout << "Enter player's name: ";
    getline(cin, player_1);
    player1.setName(player_1);
    cout << "Enter player's name: ";
    getline(cin, player_2);
    player2.setName(player_2);

    setTotal();// set rows and columns
    initialiseAndShuffleCards();// create and shuffle cards

    time_t gameStart = time(0);
    selectFirstPlayer();// decide who starts

    while (!isGameOver())
    {
        round++;
        time_t sTimeTurn = time(0);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "        Welcome to Memory Match Game!" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "------------------------------------------------Round " << round << endl;

        player1.display();
        player2.display();

        layoutCards();// show board

        // show current player options
        if (currentPlayer == 0)
        {
            cout << player1.getName() << ", will you [C]hoose or [P]ass or [H]elp : ";
        }
        else
        {
            cout << player2.getName() << ", will you [C]hoose or [P]ass or [H]elp : ";
        }

        char ch;
        cin >> ch;

        if (ch == 'P' || ch == 'p')
        {
            cout << "Pass chosen! -2 points" << endl;

            manageScores(-2);
            changePlayers();
        }
        else if (ch == 'C' || ch == 'c')
        {
            int card1, card2;
            cout << "Please insert the first position: ";
            cin >> card1;
            cout << "Please insert the second position: ";
            cin >> card2;

            // check invalid input
            while (card1 < 1 || card2 < 1 || card1 > Rows * Cols || card2 > Rows * Cols ||
                   card1 == card2 || deck[card1 - 1].getMatched() || deck[card2 - 1].getMatched())
            {
                cout << "Invalid input! Please Enter again! " << endl;
                cout << "Please insert the first position: ";
                cin >> card1;
                cout << "Please insert the second position: ";
                cin >> card2;
            }

            card1 = card1 - 1;
            card2 = card2 - 1;

            deck[card1].flip();
            deck[card2].flip();
            layoutCards();

            if (deck[card1].getLabel() == deck[card2].getLabel())
            {
                cout << "Match! +10 points\n";

                deck[card1].setMatched(true);
                deck[card2].setMatched(true);

                if (currentPlayer == 0)
                {
                    manageScores(10);// add score for match
                    cout << "Well Done!" << endl;
                    cout << player1.getName() << " You have found a match." << endl;
                }
                else
                {
                    manageScores(10);
                    cout << "Well Done!" << endl;
                    cout << player2.getName() << " You have found a match." << endl;
                }
            }
            else
            {
                cout << "Not a match! -5 points\n";

                deck[card1].flip();
                deck[card2].flip();

                manageScores(-5);
                changePlayers();// only switch if not matched
            }
        }
        else if (ch == 'H' || ch == 'h')
        {
            if (currentPlayer == 0)
            {
                if (hint1)
                {
                    cout << "You have already used the help in this game." << endl;
                }
                else
                {
                    hint1 = true;
                    for (int i = 0; i < Rows * Cols; i++)
                    {
                        if (!deck[i].getMatched() && !deck[i].getStatus())
                        {
                            deck[i].flip();
                        }
                    }

                    layoutCards();

                    time_t start = time(NULL), end = time(NULL);
                    while (end < start + 3) //wait for 3 seconds
                    {
                        end = time(NULL);
                    }

                    // flip them back
                    for (int i = 0; i < Rows * Cols; i++)
                    {
                        if (!deck[i].getMatched() && deck[i].getStatus())
                        {
                            deck[i].flip();
                        }
                    }

                    layoutCards();
                }
            }
            else
            {
                if (hint2)
                {
                    cout << "You have already used the help in this game." << endl;
                }
                else
                {
                    hint2 = true;
                    for (int i = 0; i < Rows * Cols; i++)
                    {
                        if (!deck[i].getMatched() && !deck[i].getStatus())
                        {
                            deck[i].flip();
                        }
                    }

                    layoutCards();

                    time_t start = time(NULL), end = time(NULL);
                    while (end < start + 3)
                    {
                        end = time(NULL);
                    }

                    for (int i = 0; i < Rows * Cols; i++)
                    {
                        if (!deck[i].getMatched() && deck[i].getStatus())
                        {
                            deck[i].flip();
                        }
                    }

                    layoutCards();
                }
            }
        }
        else
        {
            cout << "Invalid input! Please enter C or P or H.\n";
        }

        time_t eTimeTurn = time(0);
        cout << "This round took " << (eTimeTurn - sTimeTurn) << " seconds." << endl;
    }

    time_t gameEnd = time(0);
    cout << "Total game time: " << (gameEnd - gameStart) << " seconds" << endl;

    declareWinnerAndExit();// show result and ask if play again
}

void Application::initialiseAndShuffleCards()
{
    deck.erase(deck.begin(), deck.end());

    for (int i = 1; i <= Rows*Cols/2; i++)
    {
        int j = rand() % (100-1+1)+1;
        deck.push_back(Card(j, false, false));
        deck.push_back(Card(j, false, false));
    }

    for (int i = 0; i < Rows*Cols; i++)
    {
        int r = rand() % (Rows*Cols);
        Card temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}
void Application::layoutCards()
{
    int i = 0;

    for (int row = 0; row < Rows; row++)
    {
        for (int col = 0; col < Cols; col++)
        {
            deck[i].display();
            cout << "  ";
            i++;
        }
        cout <<endl;
    }
    cout <<endl;
}
void Application::selectFirstPlayer()
{
    currentPlayer=rand()%2;
    if (currentPlayer == 0)
        cout << player1.getName() << " it's your turn." << endl;
    else
        cout << player2.getName() << " it's your turn." << endl;
}
void Application::changePlayers()
{
    if (currentPlayer == 0)
    {
        currentPlayer = 1;
    }
    else
    {
        currentPlayer = 0;
    }

    if (currentPlayer == 0)
    {
        cout << player1.getName() << ", it's your turn."<<endl;
    }
    else
    {
        cout << player2.getName() << ", it's your turn."<<endl;
    }

}
void Application::manageScores(int scores)
{
    if (currentPlayer == 0)
    {
        player1.addScore(scores);
    }
    else
    {
        player2.addScore(scores);
    }

}

void Application::showScores()
{
    cout << player1.getName() << "  Total: " << player1.getScore() << "\n"
         << player2.getName() << "  Total: " << player2.getScore() << "\n";
}
bool Application::isGameOver()
{
    for (int i=0; i<deck.size(); i++)
    {
        if (!deck[i].getMatched())
        {
            return false;
        }
    }
            return true;
}

void Application::declareWinnerAndExit()
{
    cout << "This round has been ended!"<< endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    cout << "\tIt's game over, man!" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << player1.getName() << " final score: " << player1.getScore() << endl;
    cout << player2.getName() << " final score: " << player2.getScore() << endl;

    if (player1.getScore() > player2.getScore())
    {
        cout << player1.getName() << " is the winner!\n";
    }
    else if (player2.getScore() > player1.getScore())
    {
        cout << player2.getName() << " is the winner!\n";
    }
    else
    {
        cout << "It's a draw!\n";
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    char again;
    cout << "Do you want to play again! (Y/N): ";
    cin >> again;
    if (again == 'y' || again == 'Y')
    {
        playGame();
    }
    else
    {
        cout << "Thanks for playing! Goodbye! "<<endl;
    }
}
void Application::setTotal()
{
    cout << "Enter number of rows: ";
    cin >> Rows;
    cout << "Enter number of cols: ";
    cin >> Cols;
    while (Rows * Cols % 2 != 0)
    {
        cout << "Rows * Cols must be even.";
        cout << "Enter number of rows: ";
        cin >> Rows;
        cout << "Enter number of cols: ";
        cin >> Cols;
    }
}

void Application::runMenu()
{
    int choice;
    do
    {
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"\tProgramming Fundamental Concepts"<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"[1] Ending The Program"<<endl;
        cout<<"[2] Display "<<"Game Rules"<<" Information"<<endl;
        cout<<"[3] Play Memory Match Game"<<endl;
        cout<<"[4] Display the Reflection Report"<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"Which option would you like (1 to 4): ";
        cin>>choice;

        while (choice < 1 || choice > 4)
        {
            cout<<"Invalid input, you should enter option between (1-4): ";
            cin>>choice;
        }
        switch(choice)
        {
        case 1:displayExit("ASCII_art.txt");break;
        case 2:displayHowToPlay("gameRules.txt");break;
        case 3:playGame();break;
        case 4:displayReport("ReflectionReport.txt");break;
        default:cout<<"Invalid Input! Please enter a number between 1 and 4. "<<endl;
        }
    }
    while (choice!=1);


}
void Application::displayHowToPlay(string filename)
{
    ifstream readfile;
    string str;
    readfile.open(filename);
    if (readfile.is_open())
    {
        while(!readfile.eof())
        {
            getline(readfile, str);
            cout << str << endl;
        }
        readfile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}
void Application::displayReport(string filename)
{
    ifstream readfile;
    string str;
    readfile.open(filename);
    if (readfile.is_open())
    {
        while(!readfile.eof())
        {
            getline(readfile, str);
            cout << str << endl;
        }
        readfile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}
void Application::displayExit(string filename)
{
    ifstream readfile;
    string str;
    readfile.open(filename);
    if (readfile.is_open())
    {
        while(!readfile.eof())
        {
            getline(readfile, str);
            cout << str << endl;
        }
        readfile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}




