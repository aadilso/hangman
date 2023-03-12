#include <iostream>

#include "Hangman.h"

using namespace std;

int main()
{
    bool play = true;
    do
    {
        string name;
        cout << "Please enter your name: " << endl;
        cin >> name;


        int mode = -1;

        cout << "1 - random words" << endl;
        cout << "2 - easy words (5 or less letters)" << endl;
        cout << "3 - medium words (6-7 letters)" << endl;
        cout << "4 - hard words (8-9 letters)" << endl;
        cout << "5 - hardest (>9 letters)" << endl;

        while (mode > 5 || mode < 1) { // while not in range 
            cout << "Enter a valid number corresponding to the mode you would like to play: " << endl;
            cin >> mode;
        }
        
        Hangman hangman(name, mode);
    
        hangman.PlayGame();

        string replay;
        hangman.PrintMessage("Would you like to play again?");
        hangman.PrintMessage("enter 'yes' if so");
        cin >> replay;
        if (replay != "yes")
        {
            hangman.PrintMessage("Hope to see you again soon!");
            play = false;
        }
    } while (play);
    
    return 0;
}
