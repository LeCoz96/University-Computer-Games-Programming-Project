#pragma once
#include "StaticObject.h"
class Key :
    public StaticObject
{
public:
    Key(int x, int y, SDL_Renderer* renderer, Arena* arena);
    ~Key() = default;
};

