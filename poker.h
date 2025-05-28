#ifndef POKER_H
#define POKER_H

#include <string>
#include <vector>

#include <QImage>
#include <QPainter>

using namespace std;

#define pwidth 98
#define pheight 137
#define resizePic(p, w, h) p.scaled(w, h, Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation)

class Poker
{
public:
    struct Card
    {
        string rank;
        string suit;
        QImage img;
    };
    enum
    {
        man,
        bot
    };

    static vector<string> ranks;
    static vector<string> suits;
    static vector<Card> cards;
    static QImage bk;
    static void load_img();
    static int rand(int min, int max);

private:
    vector<pair<int, bool>> now_cards;
    vector<Card> player_cards;
    vector<Card> computer_cards;

public:
    Poker();
    ~Poker() = default;
    void reset();
    void shuffle(int times = 500);
    void deal(bool man_bot);
    int score(bool man_bot);

    friend class Widget;
};

#endif // POKER_H
