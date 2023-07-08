#include "gameobject.h"
#include "gameobjectpool.h"
#include <QGraphicsScene>


GameObject::GameObject(QObject *parent)
{
}

void GameObject::RecycleObject(QGraphicsScene* _scene)
{
    _scene->removeItem(this);
    GameObjectPool::Instance()->RecycleGameObject(this);
}
