#include "guide.h"
#include "ui_guide.h"

guide::guide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guide)
{
    ui->setupUi(this);
    this->setWindowTitle("Guidance");
}

guide::~guide()
{
    delete ui;
}

void guide::on_pushButton_clicked()
{
    this->hide();
}
