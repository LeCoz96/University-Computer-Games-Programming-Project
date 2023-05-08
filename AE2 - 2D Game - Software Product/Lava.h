#pragma once
#include "StaticObject.h"
class Lava :
    public StaticObject
{
public:
    Lava(int x, int y, SDL_Renderer* renderer, Arena* arena);
    ~Lava() = default;
};
