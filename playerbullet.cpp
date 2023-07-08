#include "playerbullet.h"

PlayerBullet::PlayerBullet(QObject *parent)
{
    mObjectType = GameObject::OT_BulletPlayer;
    mSpeed = 5;
}

void PlayerBullet::PlayerSound()
{
    mMedia.setSource(QUrl("qrc:/audio/sound/bullet.wav"));
    mMedia.play();
}
