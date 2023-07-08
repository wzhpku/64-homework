#include "ui_dialog.h"
#include "gamecontrol.h"

Dialog* Dialog::wind = nullptr;
int Dialog::Count = 0;
int Dialog::Goal = 0;
int Dialog::Condition = 0;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("UPON SKY NOW!");
    this->setFixedSize(750,1000);
    wind = this;

    //加载
    GameControl::Instance()->GameInit();
}
//按键落下写入方向容器
void Dialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W:
        case Qt::Key_A:
        case Qt::Key_S:
        case Qt::Key_D:
        case Qt::Key_Escape:

        GameControl::Instance()->mKeyList.append(event->key());
        break;
    }
}

//按键抬起移除容器中的方向
void Dialog::keyReleaseEvent(QKeyEvent *event)
{
    if(GameControl::Instance()->mKeyList.contains(event->key()))
    {
        GameControl::Instance()->mKeyList.removeOne(event->key());
    }
}

//析构
Dialog::~Dialog()
{

    delete ui;
}





