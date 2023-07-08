#ifndef FLASHITEM_H
#define FLASHITEM_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QDebug>
namespace Ui {
class flashItem;
}
class ItemClass;
class flashItem : public QWidget
{
    Q_OBJECT

public:
    explicit flashItem(QWidget *parent = nullptr);
    ~flashItem();
private slots:
    void on_valuechange(QVariant value);
private:
    Ui::flashItem *ui;
    ItemClass *flashItem3;
    QPropertyAnimation *m_Panimation3;

};


#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include <QTransform>
class ItemClass : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(int RotateAngle READ RotateAngle WRITE setRotateAngle)
public:
    explicit ItemClass(QObject *parent = nullptr, const int& type = int());
    QRectF boundingRect() const override;

    int RotateAngle();
    void setRotateAngle(int angle);
private:
    int m_angle;
    int m_type;

};

#endif // FLASHITEM_H
