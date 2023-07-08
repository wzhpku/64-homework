#include "enemy.h"

enemy::enemy(QPoint _pos, QPixmap _pixmap)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);
}

void enemy::EnemyMove(QPoint _dir)
{
    this->moveBy(_dir.x() * MoveSpeed , _dir.y() * MoveSpeed);
}

void enemy::Init(QPoint _pos, QPixmap _pixmap)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);
}
