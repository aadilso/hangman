#include <string>
class Hangman {
private:
    std::string playerName;
    int gameMode;

public:

    // Constructor
    Hangman(std::string name, int mode) { 
        playerName = name;
        gameMode = mode;
    }

    void PrintMessage(std::string message, bool printTop = true, bool printBottom = true);
    void DrawHangmanPiece(int guessCount = 0);
    void PrintLetters(std::string input, char start, char stop);
    void PrintAvailableLetters(std::string taken);
    bool CheckWin(std::string answer, std::string guesses);
    std::string LoadRandomWord(std::string path, int mode);
    int TriesLeft(std::string answer, std::string guessed);
    int getMode();
    std::string getName();
    void PlayGame();

};
