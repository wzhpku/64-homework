#include "end.h"
#include "ui_end.h"


End::End(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::End)
{
    ui->setupUi(this);

    long a = Dialog::Count;
    long b = Dialog::Goal;
    //qDebug() << a;
    QString AL = QString::number(a,10);
    QString BL = QString::number(b,10);

    QLabel* record = new QLabel(this);
    record->setGeometry(50,225,500,80);

    QFont ft;
    ft.setPointSize(14);
    record->setFont(ft);
    record->setText("你飞行了"+AL+"秒，得分为"+BL+"。\n拜托你很弱欸！");
    record->show();
}

End::~End()
{
    delete ui;
}

void End::on_ReStart_clicked()
{
    this->hide();
}

void End::on_Quit_clicked()
{
    exit(0);
}
