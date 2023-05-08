#pragma once
#include "MovingObject.h"

class Input;
class Player :
    public MovingObject
{
private:
    Input* m_input{ nullptr };

    int m_lives;

    float m_y_velocity;

    bool m_isIdle = true;
    bool m_isJumping = false;

    void Jump(float velocity);
    void Up(int velocity);
    void Down(int velocity);
public:
    Player(int x, int y, int speed, SDL_Renderer* renderer, Arena* arena);
    Player() = default;
    ~Player();

    void TakeDamage(int x, int y);
    int GetLives();

    void GetPlayerInput();
    bool PlayerEndGame();

    void Render()override;

    void Gravity();
};
