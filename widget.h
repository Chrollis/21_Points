#ifndef WIDGET_H
#define WIDGET_H

#include "game.h"

#include <QPaintEvent>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT
private:
    Game game;
    QPainter paint;

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private slots:
    void on_newBtn_clicked();
    void on_hitBtn_clicked();
    void on_standBtn_clicked();

private:
    Ui::Widget* ui;
    void paintEvent(QPaintEvent*);
};
#endif // WIDGET_H
