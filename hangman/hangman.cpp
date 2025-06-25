#include <iostream>
// #include <random>
#include <cstdlib>
#include <ctime>
//
#include <algorithm>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "hangman.h"

Hangman::Hangman()
{
    srand(static_cast<unsigned int>(time(0)));
}

void Hangman::initGame()
{
    std::cout << "\nGenereting a new secret word...\n";
    loadWords();
    size_t wordIdx{rand() % availableWords.size()};
    currentWord = availableWords[wordIdx].word;
    tries = availableWords[wordIdx].maxMistakes;
    std::cout << "Starting a new game....\n\n";
    std::cout << "You have " << tries << " mistakes allowed\n\n";
    currentGuess = {};
    for (int i{0}; i < currentWord.size(); ++i)
        currentGuess += filler;
    for (auto& [ch, strike] : selectedLetters)
        strike = false;
}

void Hangman::loadWords()
{
    std::ifstream in(wordsFile);
    if (!in) throw std::runtime_error("Cannot open words.json");

    nlohmann::json j;
    in >> j;

    for (const auto& item : j) {
        availableWords.push_back({ item.at("word").get<std::string>(),
                          item.at("max_mistakes").get<int>() });
    }
}

char Hangman::askForGuess()
{
    std::cout << "Current guess: " << currentGuess << "\n" << formatSelectedLetters() << "\n";
    while (true)
    {
        std::cout << "Please enter a character guess: ";
        std::string input;
        std::getline(std::cin, input);
        if (input.size() == 1 && std::isalpha(static_cast<unsigned char>(input[0])))
        {
            char c = static_cast<unsigned char>(input[0]);
            if (selectedLetters[c] == true)
                std::cout << c << " was already selected. Please try again.\n";
            else
            {
                selectedLetters[c] = true;
                return std::tolower(c);
            }
        }
        else
            std::cout << "Please type exactly ONE alphabetic character (A-Z).\n";
    }
}

GameState Hangman::checkState(char guess)
{
    std::vector<int> foundIdx;
    for (size_t i{0}; i < currentWord.size(); ++i)
    {
        if (currentWord[i] == guess)
            foundIdx.emplace_back(i);
    }
    if (foundIdx.size() != 0)
    {
        for(int i : foundIdx)
            currentGuess[i] = guess;

        std::cout << "letter found!\n";
    }
    else
    {
        --tries;
        if (!tries)
        {
            std::cout << "No more tries left\n";
            return GameState::Lost;
        }
        std::cout << "letter not found. Number of mistakes allowed " << tries << "\n";
    }

    for (int i{0}; i < currentGuess.size(); ++i)
    {
        if (currentGuess[i] == '_')
        {
            return GameState::Playing;
        }
    }
    return GameState::Won;
}

std::string Hangman::formatSelectedLetters()
{
    std::ostringstream out;

    for (auto const& [ch, strike] : selectedLetters)
    {
        if (strike)
            out << "\x1B[9m";

        out << " " << ch << " ";

        if (strike)
            out << "\x1B[0m";
    }
    return out.str();
}

void Hangman::play()
{
    initGame();

    std::string input;
    while(true)
    {
        char guess = askForGuess();
        GameState state = checkState(guess);
        switch (state)
        {
        case Playing:
            continue;
            break;
        case Won:
            std::cout << "You Won :)" << std::endl;
            mainMenu();
            break;
        case Lost:
            std::cout << "You Lost :(" << std::endl;
            mainMenu();
            break;
        }
    }
}

void Hangman::mainMenu()
{
    while (true)
    {
        printStartMenu();
        std::string input;
        std::getline(std::cin, input);
        if (input.size() == 1 && std::isdigit(static_cast<unsigned char>(input[0])))
        {
            int choice = input[0] - '0';
            switch (choice)
            {
            case 1:
                play();
                break;
            case 2:
                addWord();
                break;
            case 3:
                std::cout << "GoodBye :)" << std::endl;
                return;
                break;
            default:
                std::cout << "Invalid input, please select again\n";
                break;
            }
        }
    }
}

bool Hangman::isValidWord(const std::string& w)
{
    if (w.size() < 2) return false;
    for (char ch : w)
        if (!std::isalpha(static_cast<unsigned char>(ch)))
            return false;
    return true;
}

void Hangman::addWord()
{
    WordEntry newEntry;

    if(availableWords.empty())
        loadWords();

    do
    {
        std::cout << "Enter a new word to add: ";
        std::cin >> newEntry.word;

        if (!isValidWord(newEntry.word))
        {
            std::cout << "Invalid word. Must be alphabetic and at least 2 letters.\n";
            continue;
        }

        bool isUnique{true};
        for (const auto& [word, mistakes] : availableWords)
        {
            if (newEntry.word == word)
            {
                isUnique = false;
                break;
            }
        }
        if (!isUnique)
            std::cout << "Word already exists. Try again.\n";
        else
            break;

    } while (true);

    do
    {
        std::cout << "Enter number of allowed mistakes for \"" << newEntry.word << "\": ";
        std::cin >> newEntry.maxMistakes;

        if (newEntry.maxMistakes < 1)
        {
            std::cout << "Number of mistakes should be more then 1.\n";
            continue;
        }
        else
            break;

    } while (true);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    availableWords.push_back({newEntry});
    saveWords(availableWords);
    std::cout << "Word added successfully!\n";
}

void Hangman::saveWords(const std::vector<WordEntry>& words)
{
    nlohmann::json j =  nlohmann::json::array();
    for (const auto& w : words)
        j.push_back({ {"word", w.word}, {"max_mistakes", w.maxMistakes} });

    std::ofstream out(wordsFile);
    if (!out)
        throw std::runtime_error("Cannot write " + wordsFile);
    out << std::setw(4) << j;
}

void Hangman::printStartMenu()
{
    std::cout << "Hangman - the Game\n\n";
    std::cout << "Please select one of the following options\n" <<
    "1. Play\n" <<
    "2. Add word\n" <<
    "3. Quit\n" << std::endl;
}
