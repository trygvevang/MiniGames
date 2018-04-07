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

void saveGame(QString playername, int score);
list<Game> loadScores();

#endif // IOGAME_H
