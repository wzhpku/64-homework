#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <QDialog>

namespace Ui {
class Resolution;
}

class Resolution : public QDialog
{
    Q_OBJECT

public:
    explicit Resolution(QWidget *parent = nullptr);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Resolution *ui;

};

#endif // RESOLUTION_H
