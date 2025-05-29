#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <QImage>
#include <QPainter>

class Card
{
private:
    static std::vector<std::string> suits;
    static std::vector<std::string> ranks;
    static std::vector<QImage> imgs;
public:
    enum {
        Spade,
        Heart,
        Club,
        Diamond
    };
    static int Width;
    static int Height;
    static QImage img_bk;
    static void load_img(int width, int height);
private:
    static void resize(QImage& img, int width, int height);
public:
    int suit;
    int rank;
    bool is_given;
    QImage* p_img;
public:
    Card(int suit, int rank);
    void draw(int x, int y, QPainter& paint);
};
#endif // CARD_H
