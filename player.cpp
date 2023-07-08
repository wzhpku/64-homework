#include "player.h"

Player::Player()
{
    this->setPixmap(QPixmap(":/img/images/me1.png"));
    this->setPos(324,760);

    MoveSpeed = 2;
}
