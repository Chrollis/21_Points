#include "game.h"

Game::Game()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            poker.push_back(Card(i, j));
        }
    }
    is_standed = 0;
}
void Game::new_game()
{
    poker.clear();
    human.clear();
    computer.clear();
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            poker.push_back(Card(i, j));
        }
    }
    is_standed = 0;
    for (int i = 0; i < 500; i++) {
        std::swap(poker[rand() % 52], poker[rand() % 52]);
    }
}
void Game::hit(int who)
{
    auto it = poker.begin();
    for (; it != poker.end();) {
        if (!it->is_given) {
            break;
        }
        it++;
    }
    if (it == poker.end()) {
        QMessageBox msg(QMessageBox::Icon::Warning, "Warning", "All the cards have dealt. ");
        msg.exec();
        return;
    }
    it->is_given = 1;
    if (who == Player) {
        human.push_back(&*it);
    } else if (who == Robot) {
        computer.push_back(&*it);
    }
}
int Game::score(int who)
{
    int less = 0, more = 0;
    std::list<Card*>* p_cs;
    if (who == Player) {
        p_cs = &human;
    } else if (who == Robot) {
        p_cs = &computer;
    } else {
        return 0;
    }
    for (const Card* p_c : *p_cs) {
        less += std::min(10, p_c->rank);
        more += p_c->rank == 1 ? 11 : std::min(10, p_c->rank);
    }
    if (more > 21) {
        return less;
    } else {
        return more;
    }
}
void Game::draw(int x, int y, int each_line, QPainter& paint, int who)
{
    std::list<Card*>* p_cs;
    if (who == Player) {
        p_cs = &human;
    } else if (who == Robot) {
        p_cs = &computer;
    } else {
        return;
    }
    int i = 0;
    for (Card* p_c : *p_cs) {
        if (who == Robot && !is_standed && i == 0) {
            paint.drawImage(x, y, Card::img_bk);
        } else {
            p_c->draw(x + i % each_line * Card::Width,
                y + i / each_line * Card::Height, paint);
        }
        i++;
    }
}
int Game::stand()
{
    while (score(Robot) < 17) {
        hit(Robot);
    }
    is_standed = 1;
    int p_s = score(Player);
    int r_s = score(Robot);

    if ((p_s > 21 && r_s > 21) || (p_s == r_s)) {
        return Tied;
    }
    if ((p_s <= 21 && r_s > 21) || (abs(21 - p_s) < abs(21 - r_s))) {
        return Won;
    } else if ((p_s > 21 && r_s <= 21) || (abs(21 - p_s) > abs(21 - r_s))) {
        return Lost;
    } else {
        return Tied;
    }
}
