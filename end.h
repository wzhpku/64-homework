#ifndef END_H
#define END_H

#include <QDialog>
#include "dialog.h"

namespace Ui {
class End;
}

class End : public QDialog
{
    Q_OBJECT

public:
    explicit End(QWidget *parent = nullptr);
    ~End();

private slots:
    void on_ReStart_clicked();

    void on_Quit_clicked();

private:
    Ui::End *ui;
};

#endif // END_H
