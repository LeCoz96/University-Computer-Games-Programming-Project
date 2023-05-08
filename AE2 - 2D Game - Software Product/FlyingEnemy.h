#pragma once
#include "MovingObject.h"
#include <iostream>
class FlyingEnemy :
	public MovingObject
{
private:
	float m_currentTimer;
	float m_interval;

	int m_chargingMovementSpeed;
	int m_normalSpeed;
	bool m_isCharging{ false };

	bool m_moveUp{ false };

	void FlyLeft();
	void FlyRight();
	void ChangeFlyPosition();

	void ChargingCheck();
	void Charge(GameObject* object);
public:
	FlyingEnemy(int x, int y, int speed, SDL_Renderer* renderer, Arena* arena);
	~FlyingEnemy() = default;

	void Patrol()override;

	bool PlayerWithinRange(GameObject* object);
};
