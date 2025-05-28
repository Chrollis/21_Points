#include "poker.h"

vector<string> Poker::ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
vector<string> Poker::suits = {"Diamond", "Club", "Heart", "Spade"};
vector<Poker::Card> Poker::cards = vector<Poker::Card>(52);
QImage Poker::bk;

int Poker::rand(int min, int max)
{
    srand(clock() ^ std::rand());
    return std::rand() % (max - min + 1) + min;
}

void Poker::load_img()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            cards[i * 13 + j].rank = ranks[j];
            cards[i * 13 + j].suit = suits[i];
            cards[i * 13 + j].img.load(QString(":/pic/GIF/%1%2.gif").arg(suits[i]).arg(ranks[j]));
            cards[i * 13 + j].img = resizePic(cards[i * 13 + j].img, pwidth, pheight);
        }
    }
    bk.load(":/pic/GIF/Background.gif");
    bk = resizePic(bk, pwidth, pheight);
}

Poker::Poker()
{
    now_cards = vector<pair<int, bool>>(52);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            now_cards[i * 13 + j].first = i * 13 + j;
            now_cards[i * 13 + j].second = 0;
        }
    }
}

void Poker::reset()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            now_cards[i * 13 + j].first = i * 13 + j;
            now_cards[i * 13 + j].second = 0;
        }
    }
    player_cards.clear();
    computer_cards.clear();
}
void Poker::shuffle(int times)
{
    reset();
    for (int i = 0; i < times; i++)
    {
        swap(now_cards[rand(0, 51)], now_cards[rand(0, 51)]);
    }
}
void Poker::deal(bool man_bot)
{
    if (now_cards[51].second)
    {
        return;
    }
    int a = 0;
    for (int i = 0; i < 52; i++)
    {
        if (!now_cards[i].second)
        {
            a = i;
            break;
        }
    }
    if (man_bot == man)
    {
        now_cards[a].second = 1;
        player_cards.push_back(cards[now_cards[a].first]);
    }
    else if (man_bot == bot)
    {
        now_cards[a].second = 1;
        computer_cards.push_back(cards[now_cards[a].first]);
    }
}
int Poker::score(bool man_bot)
{
    int a = 0, b = 0;
    vector<Card> current;
    if (man_bot == man)
    {
        current = player_cards;
    }
    else if (man_bot == bot)
    {
        current = computer_cards;
    }
    for (const Card &card : current)
    {
        auto it = find(ranks.begin(), ranks.end(), card.rank);
        int k = distance(ranks.begin(), it);
        a += min(10, k + 1);
        b += min(10, k + 1);
        if (k == 0)
        {
            b += 10;
        }
    }
    if (b > 21)
    {
        return a;
    }
    else
    {
        return b;
    }
}
