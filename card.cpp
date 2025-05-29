#include "card.h"

int Card::Width;
int Card::Height;
std::vector<std::string> Card::suits = {
    "Spade",
    "Heart",
    "Club",
    "Diamond"
};
std::vector<std::string> Card::ranks = {
    "A",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "J",
    "Q",
    "K"
};
std::vector<QImage> Card::imgs = std::vector<QImage>(52);
QImage Card::img_bk;

void Card::load_img(int width, int height) {
    Width = width;
    Height = height;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            imgs[i * 13 + j].load(QString(":/pics/pics/%1%2.gif").
                arg(suits[i]).arg(ranks[j]));
        }
    }
    img_bk.load(":/pics/pics/Background.gif");
    resize(img_bk, Width, Height);
    for (int i = 0; i < 52; i++) {
        resize(imgs[i], Width, Height);
    }
}
void Card::resize(QImage& img, int width, int height) {
    img = img.scaled(width, height,
        Qt::AspectRatioMode::IgnoreAspectRatio,
        Qt::TransformationMode::SmoothTransformation);
}

Card::Card(int suit, int rank) {
    this->suit = suit;
    this->rank = rank;
    p_img = &imgs[suit * 13 + (rank - 1)];
    is_given = 0;
}
void Card::draw(int x, int y, QPainter& paint) {
    paint.drawImage(x, y, *p_img);
}
