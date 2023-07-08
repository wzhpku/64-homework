#include "gameobjectpool.h"

GameObjectPool* GameObjectPool::instance = nullptr;

GameObjectPool::GameObjectPool(QObject *parent) : QObject(parent)
{

}

void GameObjectPool::Init()
{
    //预生成
    for(int i = 0; i < 60; i ++)
    {
        PlayerBullet* Bullet1 = new PlayerBullet();
        Bullet1->mObjectType = 0;
        mPlayerBulletPool.append(Bullet1);

        enemy* Enemy1 = new enemy();
        Enemy1->mObjectType = 1;
        mEnemy1Pool.append(Enemy1);
    }
}

GameObject *GameObjectPool::GetGameObject(int _objType)
{
    switch (_objType)
    {
    case GameObject::OT_BulletPlayer:
    {PlayerBullet* Bullet = mPlayerBulletPool.first();
    mPlayerBulletPool.pop_front();
    return Bullet;}

    case GameObject::OT_Enemy1:
    {enemy* Enemy = mEnemy1Pool.first();
    mEnemy1Pool.pop_front();
    return Enemy;}
    }
}

void GameObjectPool::RecycleGameObject(GameObject *_obj)
{
    switch (_obj->GetType())
    {
    case GameObject::OT_BulletPlayer:
    {
       mPlayerBulletPool.append((PlayerBullet*)_obj);
       break;
    }
    case GameObject::OT_Enemy1:
    {
        mEnemy1Pool.append((enemy*)_obj);
        break;
    }
    }
}

void GameObjectPool::Clear()
{
    for(auto pBullet : mPlayerBulletPool)
    {
        delete pBullet;
    }
    for(auto pEnemy1 : mEnemy1Pool)
    {
        delete pEnemy1;
    }
}

GameObjectPool::~GameObjectPool()
{
    Clear();
}
