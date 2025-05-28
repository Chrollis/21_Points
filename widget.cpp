#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    Poker::load_img();
    newGame();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newGame()
{
    shown = 0;
    poker.shuffle();
    poker.deal(Poker::bot);
    poker.deal(Poker::bot);
    poker.deal(Poker::man);
    poker.deal(Poker::man);
}

void Widget::paintEvent(QPaintEvent *)
{
    painter.begin(this);
    int i = 0;
    for (const Poker::Card &card : poker.player_cards)
    {
        painter.drawImage(ui->labelMan->x() + (i % 5) * pwidth, ui->labelMan->y() + (i / 5) * pheight + ui->labelMan->height(), card.img);
        i++;
    }
    i = 0;
    for (const Poker::Card &card : poker.computer_cards)
    {
        if (i == 0)
        {
            if (!shown)
            {
                painter.drawImage(ui->labelBot->x() + (i % 5) * pwidth, ui->labelBot->y() + (i / 5) * pheight + ui->labelBot->height(), Poker::bk);
                i++;
                continue;
            }
        }
        painter.drawImage(ui->labelBot->x() + (i % 5) * pwidth, ui->labelBot->y() + (i / 5) * pheight + ui->labelBot->height(), card.img);
        i++;
    }
    ui->labelMan->setText(QString("Player's Cards: (Points = %1)").arg(poker.score(Poker::man)));
    painter.end();
}

void Widget::on_HitBtn_clicked()
{
    poker.deal(Poker::man);
    update();
}

void Widget::on_NewBtn_clicked()
{
    newGame();
    update();
}

void Widget::on_StandBtn_clicked()
{
    while (poker.score(Poker::bot) < 17)
    {
        poker.deal(Poker::bot);
    }
    shown = 1;
    update();
    int a = poker.score(Poker::man);
    int b = poker.score(Poker::bot);
    string c;
    if ((a > 21 && b > 21) || (a == b))
    {
        c = "平局！";
    }
    else if ((a <= 21 && b > 21) || (abs(21 - a) < abs(21 - b)))
    {
        c = "您赢了！";
    }
    else if ((a > 21 && b <= 21) || (abs(21 - a) > abs(21 - b)))
    {
        c = "您输了！";
    }
    QMessageBox msg(QMessageBox::Icon::Question, "已亮牌", QString("您的点数是%1；\n电脑点数是%2；\n%3游戏结束是否重新开始？").arg(a).arg(b).arg(c), (QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel));
    if (QMessageBox::Ok == msg.exec())
    {
        newGame();
        update();
    }
    else
    {
        this->close();
        exit(0);
    }
}
