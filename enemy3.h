#ifndef ENEMY3_H
#define ENEMY3_H

#include "enemy.h"

class Enemy3 : public enemy
{
public:
    explicit Enemy3(QObject *parent = nullptr);
    QPoint position3;
};

#endif // ENEMY3_H
