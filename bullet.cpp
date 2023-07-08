#include "bullet.h"

bullet::bullet(QPoint _pos, QPixmap _pixmap, int _type)
{
    //子弹的精参数设置
    this->setPos(_pos);
    this->setPixmap(_pixmap);

    this->mBulletType = _type;
    mSpeed = 5;

}

void bullet::BulletMove(QPoint _dir)
{
    //子弹移动定义
    this->moveBy(_dir.x()*mSpeed,_dir.y()*mSpeed);
}

void bullet::Init(QPoint _pos, QPixmap _pixmap)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);

    this->setX(this->x() - this->pixmap().width()/3);
}
