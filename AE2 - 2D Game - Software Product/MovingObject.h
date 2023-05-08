#pragma once
#include "GameObject.h"

class MovingObject :
    public GameObject
{
protected:
    int m_movementSpeed;
    bool m_movingRight = true;
    bool m_turn = false;
public:
    MovingObject(int x, int y, int speed, SDL_Renderer* renderer, Arena* arena);
    MovingObject() = default;
    ~MovingObject() = default;

    virtual void Left();
    virtual void Right();
    virtual void Patrol();

    void Render()override;
};
