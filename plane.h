#ifndef PLANE_H
#define PLANE_H

#include "gameobject.h"

class Plane : public GameObject
{
public:
    explicit Plane(QObject *parent = nullptr);

    float MoveSpeed = 1.5;

protected:
    //参数
};

#endif // PLANE_H
