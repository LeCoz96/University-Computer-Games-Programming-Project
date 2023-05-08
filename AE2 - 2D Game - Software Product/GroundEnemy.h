#pragma once
#include "MovingObject.h"

class GroundEnemy :
	public MovingObject
{
private:
	void Left()override;
	void Right()override;
public:
	GroundEnemy(int x, int y, int speed, SDL_Renderer* renderer, Arena* arena);
	~GroundEnemy() = default;
};
