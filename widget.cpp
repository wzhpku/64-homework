#include "widget.h"
#include "ui_widget.h"
#include <QRect>
#include <QTimer>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("极度困难的飞机大战！");
    this->setFixedSize(800,600);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushSButton_clicked()
{
    game = new Dialog(this);
    game->show();
}

void Widget::on_pushQButton_clicked()
{
    exit(0);
}

void Widget::on_pushGButton_clicked()
{
    tips = new guide(this);
    tips->show();
}















