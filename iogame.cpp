#include "iogame.h"

IOgame::IOgame()
{

}

void IOgame::saveGame(QString playername, int score)
{
    outstream.open("highscores.csv", fstream::in | fstream::out | fstream::app);
    outstream << playername << ";" << score << "\n";
    outstream.close();
}

list<Game> IOgame::loadScores()
{
    list<Game> games;
    ifstream instream;
    string game;

    instream.open("highscores.csv");
    if (instream.is_open())
    {
        while (!instream.eof())
        {
            instream >> game;
            // parse input and add to games
        }
    }
    instream.close();
    return games;
}

IOgame::~IOGame()
{

}
