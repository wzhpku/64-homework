#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRect>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <dialog.h>
#include <guide.h>
#include <QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    Dialog *game;
    guide *tips;


private slots:
    void on_pushSButton_clicked();
    void on_pushQButton_clicked();
    void on_pushGButton_clicked();
};
#endif // WIDGET_H













