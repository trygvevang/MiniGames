#include "iogame.h"
#include <QDebug>

/*
    Comparator to determin if a struct Game is larger than another Game.
    Is to be used when sorting games in descending order.
*/
bool compareGamesDesc (const Game& lhs, const Game& rhs)
{
    return lhs.score > rhs.score;
}

void saveGameScore(string playername, int score, string path)
{
    ofstream outstream;
    outstream.open(path, ios_base::out | ios_base::app);
    outstream << playername << ";" << score << "\r\n";
    outstream.close();
}

list<Game> loadGameScores(string filePath)
{
    list<Game> games;
    std::ifstream instream;
    string::size_type sz; // alias of size_type

    instream.open(filePath, std::ios_base::in);

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

    //sort games in descending descending order using the comparator "compareGameDesc"
    games.sort(compareGamesDesc);
    return games;
}
