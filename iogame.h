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

void saveGameScore(string playername, int score, string path);
list<Game> loadGameScores(string filePath);

#endif // IOGAME_H
