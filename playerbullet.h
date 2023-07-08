#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "bullet.h"

class PlayerBullet : public bullet
{
public:
    explicit PlayerBullet(QObject *parent = nullptr);
    void PlayerSound();
};

#endif // PLAYERBULLET_H
