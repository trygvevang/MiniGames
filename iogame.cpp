#include "iogame.h"

bool compareGamesDesc (const Game& lhs, const Game& rhs)
{
    return lhs.score > rhs.score;
}

void saveGame(string playername, int score)
{
    fstream outstream;
    outstream.open("highscores.csv", fstream::in | fstream::out | fstream::app);
    outstream << playername << ";" << score << "\n";
    outstream.close();
}

list<Game> loadScores()
{
    list<Game> games;
    ifstream instream;
    string::size_type sz; // alias of size_t

    instream.open("highscores.csv");
    if (instream.is_open())
    {
        stringstream game;
        string parts;
        vector<string> segments;
        while (!instream.eof())
        {
            //instream >> game;
            while (getline(instream, parts, ';'))
            {
                segments.push_back(parts);
            }

            if (segments.size() == 2)
            {
                games.push_back(Game(segments[0], stoi (segments[1], &sz)));
            }
        }
    }
    instream.close();

    //sort games descending on score
    games.sort(compareGamesDesc);
    return games;
}
