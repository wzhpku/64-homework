#include "enemybullet.h"

EnemyBullet::EnemyBullet(QObject *parent)
{
    mSpeed = 3;
}

void EnemyBullet::EnemySound()
{
    mMedia.setSource(QUrl("qrc:/audio/sound/button.wav"));
    mMedia.play();
}
