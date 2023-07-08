#include "resolution.h"
#include "ui_resolution.h"

Resolution::Resolution(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resolution)
{
    ui->setupUi(this);

}

Resolution::~Resolution()
{
    delete ui;
}

void Resolution::on_pushButton_clicked()
{
    this->hide();
}
