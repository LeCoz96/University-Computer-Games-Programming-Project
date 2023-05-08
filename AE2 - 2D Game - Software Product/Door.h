#pragma once
#include "StaticObject.h"
#include <vector>

class Key;

class Door :
    public StaticObject
{
private:
    bool m_playerAtDoor{ false };
    bool m_allKeysCollected{ false };
public:
    Door(int x, int y, SDL_Renderer* renderer, Arena* arena);
    ~Door() = default;

    void Render()override;

    void PlayerAtDoor();
    bool IsPlayerAtTheDoor();
    bool AllCoinsCollected(std::vector<Key*> keyList);
};
