#include "GroundEnemy.h"
#include "Arena.h"
#include "Image.h"

GroundEnemy::GroundEnemy(int x, int y, int speed, SDL_Renderer* renderer, Arena* arena)
	: MovingObject{ x, y, speed, renderer, arena }
{
	m_animationSpeed = 600;

	m_listOfTextures.push_back(Image::GetTexture("Assets/SlimeSpriteSheet.png", m_renderer));

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

void GroundEnemy::Left()
{
	int x = m_xPos - m_movementSpeed;
	if (m_arena->IsWalkableSurface(x, m_yPos + m_blockSize))
		m_xPos = x;
	else
		m_turn = true;
}

void GroundEnemy::Right()
{
	int x = m_xPos + m_movementSpeed;
	if (m_arena->IsWalkableSurface((x + m_blockSize - 1), (m_yPos + m_blockSize)))
		m_xPos = x;
	else
		m_turn = true;
}
