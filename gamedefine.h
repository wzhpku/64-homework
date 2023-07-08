#ifndef GAMEDEFINE_H
#define GAMEDEFINE_H


#include <QGraphicsPixmapItem>
#include <QtDebug>
#include <QSoundEffect>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QLabel>
#include <QToolButton>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "playerbullet.h"
#include "enemybullet.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"

//游戏定义类
class GameDefine
{
    GameDefine();
public:
    static const int PlaneShootUpdateTime = 500;
    static const int Enemy2ShootUpdateTime = 600;
    static const int PlayerMoveUpdateTime = 10;
    static const int EnemyMoveUpdateTime = 10;
    static const int BulletMoveUpdateTime = 10;
    static const int BackgroundUpdateTime = 10;
    static const int EnemyCreateUpdateTime = 1000;
    static const int PlaneFlashUpdateTime = 10;
    static const int PlaneDownUpdateTime = 100;
    //static const int ItemRecycleUpdateTime = 10;

    static const int ScreenWidth = 750;
    static const int ScreenHeight = 1000;


};

#endif // GAMEDEFINE_H
