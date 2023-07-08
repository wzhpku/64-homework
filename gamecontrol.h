#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "gamedefine.h"
#include "dialog.h"
#include "end.h"
#include "pause.h"


class GameControl : public QObject
{
    GameControl();
    static GameControl* instance;
public:
    static GameControl* Instance()
    {
        if(instance == nullptr)
        {
            return instance = new GameControl();
        }
        return instance;
    }

    ~GameControl();

    void GameInit();
    void LoadStartScene();
    void LoadGameScene();
    void GameStart();
    void mPause();
    void GameOver();

    static int GetResult(int c)
    {
        return c;
    }

    //效果函数定义
    void BGMove();
    void EnemyCreate();
    void PlaneMove();
    void MeDown();
    void PlaneBulletShoot();
    void Enemy2BulletShoot();
    void PlaneFlash();
    void BOOMERCRAW();
    void Enemy3Flash();
    void BOOM();
    void Collision();

    void ClearScreen();

    bool FLD = false;
    bool BLD = false;
    int GameCount = 0;
    int GameGoal = 0;
    int f = 0;

    End* endt;
    Pause* pauset;

    float Enemy2Shoot_y[3] = {0};
    int Enemy2Shoot_x[3] = {0};

    int Bx,BHit = 0;

    QList<int> mKeyList;

protected:
    //景象、原件的设置和转移
    QGraphicsView mGameView;
    QGraphicsScene mGameScene;
    QGraphicsScene mReadyScene;

    QGraphicsPixmapItem mBG1,mBG2;

    Player mMyPlane;
    enemy BOOMER;

    //定时器
    QTimer* mBGMoveTimer;
    QTimer* mPlaneMoveTimer;
    QTimer* mPlaneShootTimer;
    QTimer* mBulletMoveTimer;
    QTimer* mPlaneFlashTimer;
    QTimer* mEnemy3FlashTimer;
    QTimer* mEnemy3CrawTimer;
    QTimer* mEnemy3MoveTimer;
    QTimer* mEnemyCreateTimer;
    QTimer* mEnemyMoveTimer;
    QTimer* mEnemyShootTimer;
    QTimer* mEnemy2ShootTimer;
    QTimer* mMeDownTimer;
    QTimer* PauseTimer;

    //帧数指示器
    int medown = 0;


    //容器
    QList<bullet*> mBulletList;
    QList<enemy*> mEnemyList;
    QList<bullet*> eBulletList;
    QList<enemy*> mEnemy3List;

    //音乐与音效
    QSoundEffect BGM;

};

#endif // GAMECONTROL_H
