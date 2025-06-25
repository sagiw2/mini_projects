#pragma once

#include <vector>
#include <string>
#include <map>

enum GameState
{
    Playing,
    Won,
    Lost,
};

struct WordEntry {
    std::string word;
    int maxMistakes;
};

class Hangman
{
public:
    Hangman();
    void mainMenu();

private:
    void initGame();
    void loadWords();
    char askForGuess();
    GameState checkState(char guess);
    std::string formatSelectedLetters();
    void play();
    void addWord();
    void printStartMenu();
    bool isValidWord(const std::string& w);
    void saveWords(const std::vector<WordEntry>& words);


private:
    std::string filler{"_"};
    std::string currentWord;
    std::string currentGuess;
    int tries;
    std::string wordsFile{"hangman/words.json"};
    std::vector<WordEntry> availableWords;
    std::map<char, bool> selectedLetters{
                                        {'a', false},
                                        {'b', false},
                                        {'c', false},
                                        {'d', false},
                                        {'e', false},
                                        {'f', false},
                                        {'g', false},
                                        {'h', false},
                                        {'i', false},
                                        {'j', false},
                                        {'k', false},
                                        {'l', false},
                                        {'m', false},
                                        {'n', false},
                                        {'o', false},
                                        {'p', false},
                                        {'q', false},
                                        {'r', false},
                                        {'s', false},
                                        {'t', false},
                                        {'u', false},
                                        {'v', false},
                                        {'w', false},
                                        {'x', false},
                                        {'w', false},
                                        {'z', false}
                                    };
};