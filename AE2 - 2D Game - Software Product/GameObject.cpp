#include "GameObject.h"
#include "Arena.h"

GameObject::GameObject(int x, int y, SDL_Renderer* renderer, Arena* arena)
	: m_xPos{ x }, m_yPos{ y }, m_renderer{ renderer }, m_arena{ arena }
{
	m_currentFrame = 0;
	m_animationSpeed = 0;
	m_imageSize = 1;

	m_blockSize = m_arena->GetBlockSize();

	m_sourceRectangle.w = m_destinationRectangle.w = 32;
	m_sourceRectangle.h = m_destinationRectangle.h = 32;
}

void GameObject::SetX(int value)
{
	m_xPos = value;
}

void GameObject::SetY(int value)
{
	m_yPos = value;
}

int GameObject::GetX()
{
	return m_xPos;
}

int GameObject::GetY()
{
	return m_yPos;
}

void GameObject::Render()
{
	SDL_RenderCopy(m_renderer, m_listOfTextures[0], &m_imageDictionary[0].first, &m_destinationRectangle);
}

bool GameObject::Collision(GameObject* object)
{
	if (m_xPos <= object->GetX() + (m_blockSize - 1) &&
		m_xPos + (m_blockSize - 1) >= object->GetX() &&
		m_yPos <= object->GetY() + (m_blockSize - 1) &&
		m_yPos + (m_blockSize - 1) >= object->GetY())
		return true;

	return false;
}

void GameObject::Update()
{
	Animate();
	m_destinationRectangle.x = m_xPos;
	m_destinationRectangle.y = m_yPos;
}

void GameObject::Animate()
{
	for (size_t i = 0; i < m_imageDictionary.size(); i++)
	{
		m_imageDictionary[i].first.x = m_imageDictionary[i].first.w * static_cast<int>(((SDL_GetTicks() / m_animationSpeed) % m_imageDictionary[i].second));
	}

	m_destinationRectangle.w = m_imageDictionary[0].first.w * m_imageSize;
	m_destinationRectangle.h = m_imageDictionary[0].first.h * m_imageSize;
}
