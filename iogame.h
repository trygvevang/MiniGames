#ifndef IOGAME_H
#define IOGAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <QString>

using namespace std;

struct Game
{
    string playername;
    int score;
    Game(string playername, int score): playername(playername), score(score) {}
};

void saveGameScore(string playername, int score, string path); // Write game to file as CSV
list<Game> loadGameScores(string filePath); // Load games from CSV file

#endif // IOGAME_H
