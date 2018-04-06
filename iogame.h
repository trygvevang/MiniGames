#ifndef IOGAME_H
#define IOGAME_H

#include <iostream>
#include <string>
#include <list>
#include <QString>

using namespace std;
using namespace chrono;

struct Game
{
private:
    string playername;
    string score;
public:
    Game(string playername, string score): playername(playername), score(score) {}
};

class IOgame
{
public:
    IOgame();
    void saveGame(QString playername, int score);
    list<Game> loadScores(); // Should return highscores in a list or something
    ~IOGame();
private:
};

#endif // IOGAME_H
