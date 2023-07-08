#ifndef ENEMY_H
#define ENEMY_H

#include "plane.h"

class enemy : public Plane
{

public:
    enemy()
    {

    }
    enemy(QPoint _pos, QPixmap _pixmap);

    void EnemyMove(QPoint _dir = QPoint(0,1));

    void Init(QPoint _pos, QPixmap _pixmap);

    ~enemy()
    {}
};

#endif // ENEMY_H
