#include "Hangman.h";
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

#include <chrono>
#include <ctime>

#include <iomanip>


using namespace std;


// function to print a message 
void Hangman::PrintMessage(string message, bool printTop, bool printBottom) {
    if (printTop) 
    {
        cout << "|---------------------------------|" << endl;
        cout << "|";
    }
    else 
    {
        cout << "|";
    }
    // once we have done printing (or not printing) the top we print the actual message 
    bool front = true;
    for (int i = message.length(); i < 33; i++)  
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front; // we then set front to the opposite of what it was in this way we alternate by creating spaces between front and back to get the message in the middle
    }

    cout << message; // finally we print the message 

    // just like printTop if printBottom is true we add the below lines
    if (printBottom)
    {
        cout << "|" << endl;
        cout << "|---------------------------------|" << endl;
    }
    else
    {
        cout << "|" << endl;
    }

}

// function to draw hangman parts as the user continues guessing wrong

void Hangman::DrawHangmanPiece(int guessCount) 
{
    if (guessCount >= 1)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 2)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 3)
        PrintMessage("O", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 4)
        PrintMessage("/  ", false, false); // for the /|\ line we dont print a new line with else as we want them to print on the same line

    if (guessCount == 5)
        PrintMessage("/| ", false, false);

    if (guessCount >= 6)
        PrintMessage("/|\\", false, false); // \ is the escape character so we need to write it twice to show we mean to print it
    else
        PrintMessage("", false, false);

    if (guessCount >= 7)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 8)
        PrintMessage("/", false, false);

    if (guessCount >= 9)
        PrintMessage("/ \\", false, false);
    else
        PrintMessage("", false, false);
}


// function to print letters, guesses is the letters already inputted by the user.
void Hangman::PrintLetters(string guesses, char start, char stop)
{
    string s;
    // we loop from the start char to end char this works as each char has an ascii value
    for (char i = start; i <= stop; i++)
    {
        if (guesses.find(i) == string::npos) // if find returns string::npos it means the char was not in the guesses string so we can display it
        {
            s += i;
            s += " ";
        }
        else {
            s += "  "; // else the char was in the input string which holds the users guesses so dont show that char as the user already guessed that char
        }

    }
    PrintMessage(s, false, false); // finally print the message
}


// taken is the string which says the words the user already guessed so this function basiucally calls the above function from a to m and then n to z on the next line 
void Hangman::PrintAvailableLetters(string taken)
{
    PrintMessage("Available letters");
    PrintLetters(taken, 'a', 'm');
    PrintLetters(taken, 'n', 'z');
}

bool Hangman::CheckWin(string answer, string guesses) // guessed is the words the user has guessed thus far and 
{
    bool gameOver = true;
    string str;
    // loop through each char in the answer 
    for (int i = 0; i < answer.length(); i++)
    {
        // if answer[i] is not a substring of guesses then they havent guessed evrey word right yet 
        if (guesses.find(answer[i]) == string::npos)
        {
            gameOver = false;
            str += "_ "; // dont show the letter as they havent guessed it yet
        }
        else // else they already have guessed the current char so we can show it
        {
            str += answer[i];
            str += " ";
        }
    }
    PrintMessage(str, false); // print the str with the bottom border only as we dont need the top
    return gameOver;
}

// function to load a random word
string Hangman::LoadRandomWord(string path, int mode)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open())
    {
        while (getline(reader, word)) {
            if (mode == 2) {
                if (word.length() < 6) { // less than 6
                    v.push_back(word);
                }
            }

            else if (mode == 3) { // 6 to 7
                if (word.length() < 8 && word.length() > 5) {
                    v.push_back(word);
                }
            }

            else if (mode == 4) { // 8 to 9
                if (word.length() < 10 && word.length() > 7) {
                    v.push_back(word);
                }
            }

            else if (mode == 5) { // >9
                if (word.length() > 9) {
                    v.push_back(word);
                }
            }

            else { // else add any words as random option was selected
                v.push_back(word);
            }



        }

        int randomIndex = rand() % v.size();

        word = v.at(randomIndex);
        reader.close();
    }
    return word;
}

// returns the number of tries left
int Hangman::TriesLeft(string answer, string guesses)
{
    int mistakes = 0;
    for (int i = 0; i < guesses.length(); i++)
    {
        if (answer.find(guesses[i]) == string::npos)
            mistakes++;
    }
    return mistakes;
}

int Hangman::getMode() {
    return gameMode;
}
string Hangman::getName() {
    return playerName;
}

void Hangman::PlayGame() {
    //start time
    auto start = chrono::system_clock::now();

    srand(time(0)); 
    string guesses; // holds our guesses so far

    int mode = getMode();
    string name = getName();

    string wordToGuess = LoadRandomWord("RandomWords.txt", mode);
    int tries = 0;
    bool win = false;
    do
    {
        system("cls"); // clear the screen (this is why we had ifs and not if elses)
        PrintMessage("HANGMAN");
        DrawHangmanPiece(tries); // draw the hangman depending on the tries attempted
        PrintAvailableLetters(guesses); // print the letters 
        PrintMessage("Guess the word");
        win = CheckWin(wordToGuess, guesses);

        if (win)
            break;

        char x;
        cout << ">";
        cin >> x;

        if (guesses.find(x) == string::npos) // if the guess hasnt already been guessed then we add the char/guess to our string guesses
            guesses += x;
        // update tries left
        tries = TriesLeft(wordToGuess, guesses);

    } while (tries < 10);

    string status;
    if (win) {
        PrintMessage("Correct, well played!");
        status = "Result: Game won with " + to_string(tries) + " guesses used";
    }
    else {
        PrintMessage("Too many tries, maybe next time!");
        status = "Result: Game lost";
    }
    //calculate duration in seconds
    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;

    // save the game record once the game is over
    ofstream file("Records.txt", ios::app);
    file << "Name: " << getName() << " | Gamemode : " << mode << " | Answer : " << wordToGuess << " | " << "Duration : " << duration.count() << " seconds | " << status << endl;
    file.close();

}













