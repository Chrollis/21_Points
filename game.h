#ifndef GAME_H
#define GAME_H

#include "card.h"

#include <list>
#include <QMessageBox>

class Game
{
private:
    std::vector<Card> poker;
    std::list<Card*> human;
    std::list<Card*> computer;
    bool is_standed;
public:
    enum {
        Player,
        Robot
    };
    enum {
        Won,
        Lost,
        Tied
    };
public:
    Game();
    void new_game();
    void hit(int who);
    int score(int who);
    void draw(int x, int y, int each_line, QPainter& paint, int who);
    int stand();
};

#endif // GAME_H
