#include "Door.h"
#include "Image.h"

Door::Door(int x, int y, SDL_Renderer* renderer, Arena* arena)
	: StaticObject{ x, y, renderer, arena }
{
	m_animationSpeed = 100;
	
	m_listOfTextures.push_back(Image::GetTexture("Assets/DoorClosed.png", m_renderer));
	m_listOfTextures.push_back(Image::GetTexture("Assets/DoorOpen.png", m_renderer));

	for (size_t i = 0; i < m_listOfTextures.size(); i++)
	{
		m_imageDictionary.push_back(std::make_pair(SDL_Rect(), 0));

		SDL_QueryTexture(m_listOfTextures[i], NULL, NULL, &m_imageDictionary[i].first.w, &m_imageDictionary[i].first.h);
		m_imageDictionary[i].first.x = 0;
		m_imageDictionary[i].first.y = 0;
		m_imageDictionary[i].second = 1;
		m_imageDictionary[i].first.w /= m_imageDictionary[i].second;
	}
}

void Door::Render()
{
	if (!m_allKeysCollected)
		SDL_RenderCopy(m_renderer, m_listOfTextures[0], &m_imageDictionary[0].first, &m_destinationRectangle);
	else
		SDL_RenderCopy(m_renderer, m_listOfTextures[1], &m_imageDictionary[1].first, &m_destinationRectangle);
}

bool Door::IsPlayerAtTheDoor()
{
	return m_playerAtDoor;
}

void Door::PlayerAtDoor()
{
	m_playerAtDoor = true;
}

bool Door::AllCoinsCollected(std::vector<Key*> keyList)
{
	if (keyList.empty())
	{
		m_allKeysCollected = true;
		return true;
	}
	return false;
}
