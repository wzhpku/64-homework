#ifndef GAMEOBJECTPOOL_H
#define GAMEOBJECTPOOL_H

#include <QObject>
#include "gamedefine.h"
#include "dialog.h"

//对象缓存池

class GameObjectPool : public QObject
{
    GameObjectPool(QObject *parent = nullptr);
    static GameObjectPool* instance;
public:
    static GameObjectPool* Instance()
    {
        if(instance == nullptr)
        {
            return instance = new GameObjectPool(Dialog::wind );
        }
        return instance;
    }
    void Init();
    GameObject* GetGameObject(int _objType);

    void RecycleGameObject(GameObject* _obj);

    void Clear();

    ~GameObjectPool();


protected:
    //容器
    QList<PlayerBullet*> mPlayerBulletPool;
    QList<enemy*> mEnemy1Pool;

};

#endif // GAMEOBJECTPOOL_H
