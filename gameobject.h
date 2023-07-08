#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QSoundEffect>

class GameObject : public QGraphicsPixmapItem
{
public:
    enum ObjectType
    {
        OT_BulletPlayer = 0,
        OT_Enemy1 = 1
    };

    explicit GameObject(QObject *parent = nullptr);

    int GetType()
    {
        return mObjectType;
    }

    void RecycleObject(QGraphicsScene* _scene);


    ~GameObject(){}

    int mObjectType;

};

#endif // GAMEOBJECT_H
