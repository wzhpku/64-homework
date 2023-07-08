#ifndef ENEMY2_H
#define ENEMY2_H

#include "enemy.h"

class Enemy2 : public enemy
{
public:
    explicit Enemy2(QObject *parent = nullptr);
    QPoint position2;
};

#endif // ENEMY2_H
