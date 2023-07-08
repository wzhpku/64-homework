#include "gamecontrol.h"
#include "gamedefine.h"
#include "gameobjectpool.h"

GameControl* GameControl::instance = nullptr;
GameControl::GameControl()
{
    this->setParent(Dialog::wind);
}

GameControl::~GameControl()
{
    BGM.stop();
}

//背景移动
void GameControl::BGMove()
{

    mBG2.moveBy(0,2);
    mBG1.moveBy(0,2);

    //接续
    if(mBG1.y() >= mBG1.pixmap().height())
    {
        mBG1.setY(-mBG1.pixmap().height());
    }
    else if(mBG2.y() >= mBG2.pixmap().height())
    {
        mBG2.setY(-mBG2.pixmap().height());
    }
}
//初始化对象
void GameControl::GameInit()
{
    //对象池初始化
    GameObjectPool::Instance()->Init();

    mGameView.setParent(Dialog::wind);

    LoadStartScene();

    //定时器初始化
    mBGMoveTimer = new QTimer(this);
    mPlaneMoveTimer = new QTimer(this);
    mPlaneShootTimer = new QTimer(this);
    mBulletMoveTimer = new QTimer(this);
    mPlaneFlashTimer = new QTimer(this);
    mEnemy3CrawTimer = new QTimer(this);
    mEnemy3MoveTimer = new QTimer(this);
    mEnemyCreateTimer = new QTimer(this);
    mEnemyMoveTimer = new QTimer(this);
    mMeDownTimer = new QTimer(this);

    //绑定
    connect(mBGMoveTimer,&QTimer::timeout,this,&GameControl::BGMove);
    connect(mBGMoveTimer,&QTimer::timeout,this,&GameControl::PlaneMove);
    connect(mPlaneShootTimer,&QTimer::timeout,this,&GameControl::PlaneBulletShoot);
    connect(mBulletMoveTimer,&QTimer::timeout,[this](){
        for(auto Bullet : mBulletList)
        {
            Bullet->BulletMove();
            if(Bullet->y() > GameDefine::ScreenHeight || Bullet->y() < 0)
            {
                Bullet->RecycleObject(&mGameScene);
                mBulletList.removeOne(Bullet);
            }
        }

        for(auto Bullet : eBulletList)
        {
            Bullet->BulletMove(QPoint(0,1));
            if(Bullet->y() > GameDefine::ScreenHeight)
            {
                mGameScene.removeItem(Bullet);
                delete Bullet;
                eBulletList.removeOne(Bullet);
            }
        }

        //碰撞检测
        Collision();
    });
    connect(mPlaneFlashTimer,&QTimer::timeout,this,&GameControl::PlaneFlash);
    connect(mEnemyCreateTimer,&QTimer::timeout,this,&GameControl::EnemyCreate);
    connect(mEnemyMoveTimer,&QTimer::timeout,[this](){
        for (auto Enemy : mEnemyList)
        {
            Enemy->EnemyMove();
            if(Enemy->y() > GameDefine::ScreenHeight)
            {
                Enemy->RecycleObject(&mGameScene);
                mEnemyList.removeOne(Enemy);
                for(int i = 0; i < 3; i ++)
                {
                    if(Enemy2Shoot_x[i] == Enemy->x())
                    {
                        Enemy2Shoot_x[i] = 0;
                    }
                }
            }
        }
    });
    connect(mMeDownTimer,&QTimer::timeout,this,&GameControl::MeDown);
}
//加载准备界面
void GameControl::LoadStartScene()
{
    mReadyScene.setSceneRect(QRect(0,0,750,1000));
    mReadyScene.addPixmap(QPixmap(":/img/images/background.png"));

    //过渡
    auto PushSButton = new QToolButton();
    PushSButton->setAutoRaise(true);
    PushSButton->setStyleSheet("background-color:rgba(0,0,0,0)");
    PushSButton->resize(310,51);
    PushSButton->setIcon(QIcon(":/img/images/start.png"));
    PushSButton->setIconSize(QSize(300,41));
    PushSButton->move(220,495);
    PushSButton->show();

    //开始游戏
    connect(PushSButton,&QToolButton::clicked,[this](){
        this->LoadGameScene();
        this->GameStart();
    });
    mReadyScene.addWidget(PushSButton);

    mGameView.setScene(&mReadyScene);
    mGameView.show();
}
//加载游戏界面
void GameControl::LoadGameScene()
{
    //设置景象参数
    mGameScene.setSceneRect(QRect(0,0,750,1000));

    //背景原图
    mBG1.setPixmap(QPixmap(":/img/images/background.png"));
    mBG2.setPixmap(QPixmap(":/img/images/background.png"));
    BOOMER.setPixmap(QPixmap(":/img/images/enemy3_n1.png"));

    //设置背景位置
    mBG2.setPos(0,-mBG2.pixmap().height());
    BOOMER.setPos(0,-300);

    //景象中添加原件
    mGameScene.addItem(&mBG1);
    mGameScene.addItem(&mBG2);
    mGameScene.addItem(&mMyPlane);

    //生效
    mGameView.setScene(&mGameScene);
    mGameView.show();

    //游戏内背景音乐设置
    this->BGM.setSource(QUrl("qrc:/audio/sound/Main track WAV.wav"));
    this->BGM.setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环
    this->BGM.play();
}

//游戏开始
void GameControl::GameStart()
{
    //开启定时器
    mBGMoveTimer->start(GameDefine::BackgroundUpdateTime);
    mPlaneMoveTimer->start(GameDefine::PlayerMoveUpdateTime);
    mPlaneShootTimer->start(GameDefine::PlaneShootUpdateTime);
    mBulletMoveTimer->start(GameDefine::BulletMoveUpdateTime);
    mPlaneFlashTimer->start(GameDefine::PlaneFlashUpdateTime);
    mEnemyCreateTimer->start(GameDefine::EnemyCreateUpdateTime);
    mEnemyMoveTimer->start(GameDefine::EnemyMoveUpdateTime);

    Dialog::Condition = 1;
}
//游戏暂停
void GameControl::mPause()
{
    for(auto K : mKeyList)
    {
        mKeyList.removeOne(K);
    }

    mBGMoveTimer->stop();
    mPlaneMoveTimer->stop();
    mPlaneShootTimer->stop();
    mBulletMoveTimer->stop();
    mPlaneFlashTimer->stop();
    mEnemyCreateTimer->stop();
    mEnemyMoveTimer->stop();
    mEnemy3CrawTimer->stop();
    BGM.stop();

    pauset = new Pause();
    pauset->show();

    PauseTimer = new QTimer(this);
    PauseTimer->start(100);
    connect(PauseTimer,&QTimer::timeout,[this](){
        switch (Dialog::Condition)
        {
        case 0:
        {
            PauseTimer->stop();GameOver();break;
        }
        case 3:
        {
            mBGMoveTimer->start();
            mPlaneMoveTimer->start();
            mPlaneShootTimer->start();
            mBulletMoveTimer->start();
            mPlaneFlashTimer->start();
            mEnemyCreateTimer->start();
            mEnemyMoveTimer->start();
            mEnemy3CrawTimer->start();
            BGM.play();
            Dialog::Condition = 1;
            PauseTimer->stop();
            break;
        }
        case 2:
        {
            ClearScreen();
            GameInit();
            Dialog::Condition = 1;
            PauseTimer->stop();
            break;
        }
        }
    });

}
//游戏结束
void GameControl::GameOver()
{
    mBGMoveTimer->stop();
    mPlaneMoveTimer->stop();
    mPlaneShootTimer->stop();
    mBulletMoveTimer->stop();
    mPlaneFlashTimer->stop();
    mEnemyCreateTimer->stop();
    mEnemyMoveTimer->stop();
    mEnemy3CrawTimer->stop();
    BGM.stop();
    mMeDownTimer->start(GameDefine::PlaneDownUpdateTime);

    Dialog::Count = GameCount;
    Dialog::Goal = GameGoal + GameCount;

    endt = new End();

    GameCount = 0;
    GameGoal = 0;

    endt->show();
    Dialog::wind->hide();
    ClearScreen();
}

//创建敌机
void GameControl::EnemyCreate()
{
    GameCount ++;
    if(GameCount >= 1)
    {
        QPixmap Enemy1(":/img/images/enemy1.png");
        int randX1 = (qrand() % (730 - Enemy1.width())) + 10;

        GameObject* Obj = GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy1);
        enemy* aEnemy = (enemy*)Obj;
        aEnemy->MoveSpeed = 1;
        aEnemy->Init(QPoint(randX1,-Enemy1.height()),Enemy1);

        mGameScene.addItem(aEnemy);

        mEnemyList.append(aEnemy);
    }
    if(GameCount >= 11 && GameCount % 3 == 0)
    {
        QPixmap Enemy1(":/img/images/enemy1.png");
        int randX1 = (qrand() % (730 - Enemy1.width())) + 10;

        GameObject* Obj1 = GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy1);
        enemy* aEnemy = (enemy*)Obj1;
        aEnemy->MoveSpeed = 2;
        aEnemy->Init(QPoint(randX1,-Enemy1.height()),Enemy1);

        mGameScene.addItem(aEnemy);

        mEnemyList.append(aEnemy);


        QPixmap Enemy2(":/img/images/enemy2.png");
        int randX2 = (qrand() % (730 - Enemy2.width())) + 10;

        GameObject* Obj2 = GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy1);
        enemy* bEnemy = (enemy*)Obj2;
        bEnemy->MoveSpeed = 1.5;
        bEnemy->Init(QPoint(randX2,-Enemy2.height()),Enemy2);

        Enemy2Shoot_x[2] = Enemy2Shoot_x[1];
        Enemy2Shoot_x[1] = Enemy2Shoot_x[0];
        Enemy2Shoot_x[0] = randX2;

        if(Enemy2Shoot_y[0] == 0)
        {
            Enemy2Shoot_y[0] = Enemy2Shoot_y[1];
            Enemy2Shoot_y[1] = Enemy2Shoot_y[2];
            Enemy2Shoot_y[2] = Enemy2Shoot_y[2] + bEnemy->MoveSpeed*100;
        }

        Enemy2BulletShoot();

        mGameScene.addItem(bEnemy);

        mEnemyList.append(bEnemy);
    }
    if(GameCount >= 21 && GameCount % 2 == 0)
    {
        QPixmap Enemy1(":/img/images/enemy1.png");
        int randX1 = (qrand() % (730 - Enemy1.width())) + 10;

        GameObject* Obj = GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy1);
        enemy* aEnemy = (enemy*)Obj;
        aEnemy->MoveSpeed = 3;
        aEnemy->Init(QPoint(randX1,-Enemy1.height()),Enemy1);

        mGameScene.addItem(aEnemy);

        mEnemyList.append(aEnemy);
    }
    if(GameCount >= 30 && GameCount % 30 == 0)
    {
        int randX3 = (qrand() % (730 - BOOMER.pixmap().width())) + 10;

        BOOMER.setPos(randX3,-250);

        BOOMER.MoveSpeed = 1;
        mGameScene.addItem(&BOOMER);
        mEnemy3CrawTimer->start(10);
        connect(mEnemy3CrawTimer,&QTimer::timeout,[this](){
            if(BLD == false)
            {
                BLD = true;
                BOOMER.hide();
                BOOMER.setPixmap(QPixmap(":/img/images/enemy3_n2.png"));
                BOOMER.show();
            }
            else
            {
                BLD = false;
                BOOMER.hide();
                BOOMER.setPixmap(QPixmap(":/img/images/enemy3_n1.png"));
                BOOMER.show();
            }
            BOOMER.EnemyMove();
            if(BOOMER.y() > 750)
            {
                BOOM();
            }
        });
    }
    if(GameCount >= 31 && GameCount % 2 == 0)
    {
        QPixmap Enemy1(":/img/images/enemy1.png");
        int randX1 = (qrand() % (730 - Enemy1.width())) + 10;

        GameObject* Obj = GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy1);
        enemy* aEnemy = (enemy*)Obj;
        aEnemy->MoveSpeed = 5;
        aEnemy->Init(QPoint(randX1,-Enemy1.height()),Enemy1);

        mGameScene.addItem(aEnemy);

        mEnemyList.append(aEnemy);
    }
    if(GameCount >= 41)
    {
        QPixmap Enemy1(":/img/images/enemy1.png");
        int randX1 = (qrand() % (730 - Enemy1.width())) + 10;

        GameObject* Obj = GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy1);
        enemy* aEnemy = (enemy*)Obj;
        aEnemy->MoveSpeed = 4;
        aEnemy->Init(QPoint(randX1,-Enemy1.height()),Enemy1);

        mGameScene.addItem(aEnemy);

        mEnemyList.append(aEnemy);
    }
    if(GameCount >= 51)
    {
        QPixmap Enemy1(":/img/images/enemy1.png");
        int randX1 = (qrand() % (730 - Enemy1.width())) + 10;

        GameObject* Obj = GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy1);
        enemy* aEnemy = (enemy*)Obj;
        aEnemy->MoveSpeed = 6;
        aEnemy->Init(QPoint(randX1,-Enemy1.height()),Enemy1);

        mGameScene.addItem(aEnemy);

        mEnemyList.append(aEnemy);
    }
}

//我的移动原则
void GameControl::PlaneMove()
{
    //根据写入的方向执行
    for(int KeyCode : mKeyList)
    {
        switch (KeyCode)
        {
            case Qt::Key_W: mMyPlane.moveBy(0,-mMyPlane.MoveSpeed);break;
            case Qt::Key_A: mMyPlane.moveBy(-mMyPlane.MoveSpeed,0);break;
            case Qt::Key_S: mMyPlane.moveBy(0,mMyPlane.MoveSpeed);break;
            case Qt::Key_D: mMyPlane.moveBy(mMyPlane.MoveSpeed,0);break;
            case Qt::Key_Escape: mPause();break;
        }
    }
    //防止我出屏幕
    if(mMyPlane.x() <= 0)
    {
        mMyPlane.setX(0);
    }
    if(mMyPlane.x() >= GameDefine::ScreenWidth - mMyPlane.pixmap().width())
    {
        mMyPlane.setX(GameDefine::ScreenWidth - mMyPlane.pixmap().width());
    }
    if(mMyPlane.y() <= 0)
    {
        mMyPlane.setY(0);
    }
    if(mMyPlane.y() >= GameDefine::ScreenHeight - mMyPlane.pixmap().height())
    {
        mMyPlane.setY(GameDefine::ScreenHeight - mMyPlane.pixmap().height());
    }
    for(int j = 0; j < mEnemyList.size(); j ++)
    {
        if(mMyPlane.collidesWithItem(mEnemyList[j]) == true)
        {
            GameOver();
        }
    }
    for(int i = 0; i < eBulletList.size(); i ++)
    {
        if(mMyPlane.collidesWithItem(eBulletList[i]) == true)
        {
            mGameScene.removeItem(eBulletList[i]);
            delete eBulletList[i];
            eBulletList.removeOne(eBulletList[i]);
            GameOver();
        }
    }
    if(mMyPlane.x() < BOOMER.x() + 180 && mMyPlane.x() > BOOMER.x() - 110 && mMyPlane.y() > BOOMER.y() - 130 && mMyPlane.y() < BOOMER.y() + 260)
    {
        BOOM();
    }
}
//我的死亡动画
void GameControl::MeDown()
{
    medown ++;
    if(medown == 1)
    {
        mMyPlane.hide();
        mMyPlane.setPixmap(QPixmap(":/img/images/me_destroy_1.png"));
        mMyPlane.show();
    }
    else if(medown == 2)
    {
        mMyPlane.hide();
        mMyPlane.setPixmap(QPixmap(":/img/images/me_destroy_2.png"));
        mMyPlane.show();
    }
    else if(medown == 3)
    {
        mMyPlane.hide();
        mMyPlane.setPixmap(QPixmap(":/img/images/me_destroy_3.png"));
        mMyPlane.show();
    }
    else if(medown == 4)
    {
        mMyPlane.hide();
        mMyPlane.setPixmap(QPixmap(":/img/images/me_destroy_4.png"));
        mMyPlane.show();
    }
    else
    {
        mMeDownTimer->stop();
    }
}
//我的子弹发射
void GameControl::PlaneBulletShoot()
{
    //对象池创建子弹
    QPixmap bulletImg(":/img/images/bullet2.png");
    QPoint pos(mMyPlane.x() + mMyPlane.pixmap().width()/2, mMyPlane.y());
    GameObject* Obj = GameObjectPool::Instance()->GetGameObject(GameObject::OT_BulletPlayer);
    PlayerBullet* Bullet = (PlayerBullet*)Obj;
    Bullet->Init(pos,bulletImg);
    Bullet->PlayerSound();

    //我的子弹添加到场景
    mGameScene.addItem(Bullet);

    //写入子弹容器
    mBulletList.append(Bullet);
}
//执行我的飞行动画
void GameControl::PlaneFlash()
{
    if(FLD == false)
    {
        FLD = true;
        mMyPlane.hide();
        mMyPlane.setPixmap(QPixmap(":/img/images/me2.png"));
        mMyPlane.show();
    }
    else if(FLD == true)
    {
        FLD = false;
        mMyPlane.hide();
        mMyPlane.setPixmap(QPixmap(":/img/images/me1.png"));
        mMyPlane.show();
    }
}

//Hunter子弹发射
void GameControl::Enemy2BulletShoot()
{
    for(int i = 0; i < 3; i ++)
    {
            if(Enemy2Shoot_x[i] != 0 && Enemy2Shoot_y[i] != 0)
            {
                QPixmap bulletImg(":/img/images/bullet1.png");
                QPoint pos(Enemy2Shoot_x[i] + 35,Enemy2Shoot_y[i] + 100);
                EnemyBullet* Bullet = new EnemyBullet();
                Bullet->Init(pos,bulletImg);
                Bullet->EnemySound();

                mGameScene.addItem(Bullet);

                eBulletList.append(Bullet);
            }
    }
}
//BOOMER爆炸动画
void GameControl::Enemy3Flash()
{
    mEnemy3CrawTimer->stop();
    mEnemy3FlashTimer = new QTimer(this);
    mEnemy3FlashTimer->start(80);
    connect(mEnemy3FlashTimer,&QTimer::timeout,[this](){
        f++;
        if(f == 1)
        {
            BOOMER.hide();
            BOOMER.setPixmap(QPixmap(":/img/images/enemy3_down1.png"));
            BOOMER.show();
        }
        else if(f == 2)
        {
            BOOMER.hide();
            BOOMER.setPixmap(QPixmap(":/img/images/enemy3_down2.png"));
            BOOMER.show();
        }
        else if(f == 3)
        {
            BOOMER.hide();
            BOOMER.setPixmap(QPixmap(":/img/images/enemy3_down3.png"));
            BOOMER.show();
        }
        else if(f == 4)
        {
            BOOMER.hide();
            BOOMER.setPixmap(QPixmap(":/img/images/enemy3_down4.png"));
            BOOMER.show();
        }
        else if(f == 5)
        {
            BOOMER.hide();
            BOOMER.setPixmap(QPixmap(":/img/images/enemy3_down5.png"));
            BOOMER.show();
        }
        else if(f == 6)
        {
            BOOMER.hide();
            BOOMER.setPixmap(QPixmap(":/img/images/enemy3_down6.png"));
            BOOMER.show();
        }
        else
        {
            BOOMER.hide();
            mEnemy3FlashTimer->stop();
        }

    });

}
//BOOMER到达末端
void GameControl::BOOM()
{
    Enemy3Flash();
    GameOver();
}

//碰撞检测
void GameControl::Collision()
{
    for(int i = 0; i < mBulletList.size(); i ++)
    {
        for(int j = 0; j < mEnemyList.size(); j ++)
        {
            if(mBulletList[i]->collidesWithItem(mEnemyList[j]) == true)
            {
                for(int u = 0; u < 3; u ++)
                {
                    if(mEnemyList[j]->x() == Enemy2Shoot_x[u])
                    {
                        Enemy2Shoot_x[u] = 0;
                    }
                }
                mBulletList[i]->setY(-300);
                mEnemyList[j]->setY(GameDefine::ScreenHeight);
                GameGoal ++;
            }
        }
        if(BOOMER.collidesWithItem(mBulletList[i]) == true)
        {
            if(BHit <= 6)
            {
                BHit ++;
                mBulletList[i]->setY(-300);
            }
            else
            {
                Enemy3Flash();
                for(int j = 0; j < mEnemyList.size(); j ++)
                {
                    if((mEnemyList[j]->x()-BOOMER.x())*(mEnemyList[j]->x()-BOOMER.x())+(mEnemyList[j]->y()-BOOMER.y())*(mEnemyList[j]->y()-BOOMER.y()) <= 400)
                    {
                        mEnemyList[j]->setY(GameDefine::ScreenHeight);
                    }
                }
                BHit = 0;
                BOOMER.setPos(0,-300);
                GameGoal += 10;
            }
        }
    }

}

//清理
void GameControl::ClearScreen()
{
    for(auto Bullet : mBulletList)
    {
        Bullet->RecycleObject(&mGameScene);
        mBulletList.removeOne(Bullet);
    }
    for(auto Enemy : mEnemyList)
    {
        Enemy->RecycleObject(&mGameScene);
        mEnemyList.removeOne(Enemy);
    }
    for(auto Bullet : eBulletList)
    {
        mGameScene.removeItem(Bullet);
        delete Bullet;
        eBulletList.removeOne(Bullet);
    }

    mMyPlane.setPos(324,760);
    mBG1.setPos(0,0);
    mBG2.setPos(0,-mBG2.pixmap().height());
    BOOMER.setPos(0,-300);
}







