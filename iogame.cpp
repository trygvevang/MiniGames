#include "iogame.h"
#include <QDebug>
bool compareGamesDesc (const Game& lhs, const Game& rhs)
{
    return lhs.score > rhs.score;
}

void saveGame(string playername, int score)
{
    ofstream outstream;
    outstream.open("highscores.csv", ios_base::out | ios_base::app);
    outstream << playername << ";" << score << "\r\n";
    outstream.close();
}

list<Game> loadScores()
{
    list<Game> games;
    std::ifstream instream;
    string::size_type sz; // alias of size_t

    instream.open("highscores.csv", std::ios_base::in);

    if (instream.is_open())
    {
        string line;
        while (getline(instream, line))
        {
            stringstream game(line);
            string parts;
            vector<string> segments;

            while (getline(game, parts, ';'))
            {
                segments.push_back(parts);
                if (segments.size() == 2)
                {
                    games.push_back(Game(segments[0], stoi (segments[1], &sz)));
                }
            }
        }
    }
    instream.close();

    //sort games descending on score
    games.sort(compareGamesDesc);
    return games;
}
