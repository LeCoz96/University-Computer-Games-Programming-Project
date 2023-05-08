#include "Key.h"
#include "Image.h"

Key::Key(int x, int y, SDL_Renderer* renderer, Arena* arena)
	: StaticObject{ x, y, renderer, arena }
{
	m_animationSpeed = 50;

	m_listOfTextures.push_back(Image::GetTexture("Assets/KeySpriteSheet.png", m_renderer));

	for (int i = 0; i < m_listOfTextures.size(); i++)
	{
		m_imageDictionary.push_back(std::make_pair(SDL_Rect(), 0));

		SDL_QueryTexture(m_listOfTextures[i], NULL, NULL, &m_imageDictionary[i].first.w, &m_imageDictionary[i].first.h);
		m_imageDictionary[i].first.x = 0;
		m_imageDictionary[i].first.y = 0;
		m_imageDictionary[i].second = 12;
		m_imageDictionary[i].first.w /= m_imageDictionary[i].second;
	}
}
