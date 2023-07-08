#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"

class bullet : public GameObject
{

public:

    //子弹分类及内容
    enum BulletType
    {
        BT_Player,
        BT_Enemy1,
        BT_Enemy2,
        BT_Enemy3
    };

    bullet(){}
    bullet(QPoint _pos, QPixmap _pixmap, int _type);

    //移动效果
    void BulletMove(QPoint _dir = QPoint(0,-1));

    //实现
    void Init(QPoint _pos, QPixmap _pixmap);

    ~bullet()
    {
        //qDebug() << "released";
    }

protected:
    //参数
    int mBulletType;
    int mSpeed;
    QSoundEffect mMedia;

};

#endif // BULLET_H
