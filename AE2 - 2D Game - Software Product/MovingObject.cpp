#include "MovingObject.h"
#include "Arena.h"

MovingObject::MovingObject(int x, int y, int speed, SDL_Renderer* renderer, Arena* arena)
	: GameObject{ x, y, renderer, arena }, m_movementSpeed{ speed }
{
}

void MovingObject::Patrol()
{
	if (!m_turn)
	{
		if (m_movingRight)
			Right();
		else
			Left();
	}
	else
	{
		m_turn = false;
		m_movingRight = !m_movingRight;
	}
}

void MovingObject::Render()
{
	if (m_movingRight)
		SDL_RenderCopyEx(m_renderer, m_listOfTextures[0], &m_imageDictionary[0].first, &m_destinationRectangle, 0, NULL, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopy(m_renderer, m_listOfTextures[0], &m_imageDictionary[0].first, &m_destinationRectangle);
}

void MovingObject::Left()
{
	int x = m_xPos - m_movementSpeed;
	if (!m_arena->IsWall(x, m_yPos) &&
		!m_arena->IsWall(x, (m_yPos + m_blockSize - 1)))
	{
		m_movingRight = false;
		m_xPos = x;
	}
	else
		m_turn = true;
}

void MovingObject::Right()
{
	int x = m_xPos + m_movementSpeed;
	if (!m_arena->IsWall((x + m_blockSize - 1), m_yPos) &&
		!m_arena->IsWall((x + m_blockSize - 1), (m_yPos + m_blockSize - 1)))
	{
		m_movingRight = true;
		m_xPos = x;
	}
	else
		m_turn = true;
}
