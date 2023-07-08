#include "pause.h"
#include "ui_pause.h"

Pause::Pause(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pause)
{
    ui->setupUi(this);
}

Pause::~Pause()
{
    delete ui;
}

void Pause::on_Back_clicked()
{
    Dialog::Condition = 3;
    this->hide();
}

void Pause::on_ReOn_clicked()
{
    Dialog::Condition = 2;
    this->hide();
}

void Pause::on_GoBack_clicked()
{
    Dialog::Condition = 0;
    this->hide();
}
