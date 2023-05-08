#include "FlyingEnemy.h"
#include "Image.h"
#include "Arena.h"

FlyingEnemy::FlyingEnemy(int x, int y, int speed, SDL_Renderer* renderer, Arena* arena)
	: MovingObject{ x, y, speed, renderer, arena }
{
	m_chargingMovementSpeed = 4;

	m_normalSpeed = speed;

	m_currentTimer = 0;
	m_interval = 30;

	m_animationSpeed = 500;

	m_listOfTextures.push_back(Image::GetTexture("Assets/FlyingEnemySpriteSheet.png", m_renderer));

	for (size_t i = 0; i < m_listOfTextures.size(); i++)
	{
		m_imageDictionary.push_back(std::make_pair(SDL_Rect(), 0));

		SDL_QueryTexture(m_listOfTextures[i], NULL, NULL, &m_imageDictionary[i].first.w, &m_imageDictionary[i].first.h);
		m_imageDictionary[i].first.x = 0;
		m_imageDictionary[i].first.y = 0;
		m_imageDictionary[i].second = 2;
		m_imageDictionary[i].first.w /= m_imageDictionary[i].second;
	}
}

void FlyingEnemy::Patrol()
{
	if (!m_turn)
	{
		if (m_movingRight)
			FlyRight();
		else
			FlyLeft();
	}
	else
	{
		m_turn = false;
		m_movingRight = !m_movingRight;
	}
}

void FlyingEnemy::FlyLeft()
{
	ChargingCheck();
	int x = m_xPos - m_movementSpeed;
	if (!m_arena->IsWall(x, m_yPos) &&
		!m_arena->IsWall(x, (m_yPos + m_blockSize - 1)))
	{
		m_movingRight = false;
		m_xPos = x;
	}
	else
	{
		m_turn = true;
		m_isCharging = false;
	}
	ChangeFlyPosition();
}

void FlyingEnemy::FlyRight()
{
	ChargingCheck();
	int x = m_xPos + m_movementSpeed;
	if (!m_arena->IsWall((x + m_blockSize - 1), m_yPos) &&
		!m_arena->IsWall((x + m_blockSize - 1), (m_yPos + m_blockSize - 1)))
	{
		m_movingRight = true;
		m_xPos = x;
	}
	else
	{
		m_turn = true;
		m_isCharging = false;
	}
	ChangeFlyPosition();
}

void FlyingEnemy::ChangeFlyPosition()
{
	m_currentTimer += 1;
	if (m_currentTimer == m_interval)
	{
		m_currentTimer = 0;
		if (m_moveUp)
		{
			m_yPos += 3;
			m_moveUp = false;
		}
		else
		{
			m_yPos -= 3;
			m_moveUp = true;
		}
	}
}

void FlyingEnemy::ChargingCheck()
{
	if (m_isCharging)
		m_movementSpeed = m_chargingMovementSpeed;
	else
		m_movementSpeed = m_normalSpeed;
}

bool FlyingEnemy::PlayerWithinRange(GameObject* object)
{
	if (object->GetY() == m_yPos)
	{
		Charge(object);
		return true; 
	}
	else
	{
		Patrol();
		return false;
	}
}

void FlyingEnemy::Charge(GameObject* object)
{
	if (object->GetX() < m_xPos || object->GetX() > m_xPos)
	{
		m_isCharging = true;

		if (object->GetX() < m_xPos)
			FlyLeft();
		else if (object->GetX() > m_xPos)
			FlyRight();
	}
}
