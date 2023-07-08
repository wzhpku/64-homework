#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"

class EnemyBullet : public bullet
{
public:
    explicit EnemyBullet(QObject *parent = nullptr);
    void EnemySound();
};

#endif // ENEMYBULLET_H
