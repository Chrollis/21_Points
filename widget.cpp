#include "widget.h"
#include "./ui_widget.h"

constexpr int EachLine = 4;
constexpr int cWidth = 98;
constexpr int cHeight = 137;

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Card::load_img(cWidth, cHeight);
    on_newBtn_clicked();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent*) {
    paint.begin(this);
    game.draw(ui->labelPlayer->x(), ui->labelPlayer->y() + ui->labelPlayer->height(), EachLine, paint, Game::Player);
    game.draw(ui->labelRobot->x(), ui->labelRobot->y() + ui->labelRobot->height(), EachLine, paint, Game::Robot);
    paint.end();
}

void Widget::on_newBtn_clicked()
{
    game.new_game();
    game.hit(Game::Robot);
    game.hit(Game::Player);
    game.hit(Game::Robot);
    game.hit(Game::Player);
    ui->labelRobot->setText("Computer's Cards:");
    ui->labelPlayer->setText(QString("Your Cards (%1 points):").arg(game.score(Game::Player)));
    update();
}


void Widget::on_hitBtn_clicked()
{
    game.hit(Game::Player);
    ui->labelPlayer->setText(QString("Your Cards (%1 points):").arg(game.score(Game::Player)));
    update();
}


void Widget::on_standBtn_clicked()
{
    QString feedback;
    switch (game.stand()) {
    case Game::Tied:
        feedback = "tied";
        break;
    case Game::Won:
        feedback = "won";
        break;
    case Game::Lost:
        feedback = "lost";
        break;
    }
    ui->labelRobot->setText(QString("Computer's Cards (%1 points):").arg(game.score(Game::Robot)));
    update();
    QMessageBox msg(QMessageBox::Icon::Question, "Outcome", QString("You %1! Whether restart? ").arg(feedback),
        (QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel));
    if (QMessageBox::Ok == msg.exec())
    {
        on_newBtn_clicked();
    }
    else
    {
        this->close();
        exit(0);
    }
}

