#include "StaticObject.h"

StaticObject::StaticObject(int x, int y, SDL_Renderer* renderer, Arena* arena)
	: GameObject{ x, y, renderer, arena }
{
}
