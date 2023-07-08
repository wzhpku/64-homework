#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QLabel>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <QSoundEffect>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    static Dialog* wind;
    static int Count;
    static int Goal;
    static int Condition;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::Dialog *ui;

private slots:
};

#endif // DIALOG_H



















