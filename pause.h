#ifndef PAUSE_H
#define PAUSE_H

#include <QDialog>
#include "dialog.h"

namespace Ui {
class Pause;
}

class Pause : public QDialog
{
    Q_OBJECT

public:
    explicit Pause(QWidget *parent = nullptr);
    ~Pause();

private slots:
    void on_Back_clicked();

    void on_ReOn_clicked();

    void on_GoBack_clicked();

private:
    Ui::Pause *ui;
};

#endif // PAUSE_H
