#include "Stats.h"
#include "Player.h"

Stats::Stats(Player* player)
{
	TTF_Init();

	m_statsText = TTF_OpenFont("Assets/DejaVuSans.ttf", 25);
	m_player = player;
}

Stats::~Stats()
{
	if (nullptr != m_statsText)
	{
		TTF_CloseFont(m_statsText);
		m_statsText = nullptr;
	}
}

void Stats::UpdateText(std::string message, int x, int y, SDL_Renderer* renderer, TTF_Font* font, SDL_Color colour)
{
	SDL_Surface* pSurface{ nullptr };
	SDL_Texture* pTexture{ nullptr };

	int textWidth, textHeight = 0;

		// create a surface with the text using the font and a solid colour
	pSurface = TTF_RenderText_Solid(font, message.c_str(), colour);
	if (nullptr == pSurface)
	{
		SDL_Log("Surface for font not created: %s", SDL_GetError());
		return;
	}
	pTexture = SDL_CreateTextureFromSurface(renderer, pSurface);
	if (nullptr == pTexture)
	{
		SDL_Log("Texture for font not created: %s", SDL_GetError());
		return;
	}
	// get teh width and height of the surface with the text
	SDL_QueryTexture(pTexture, NULL, NULL, &textWidth, &textHeight);
	SDL_Rect textRectangle{ x, y, textWidth, textHeight };
	// render to a rectangle the size of the texture
	SDL_RenderCopy(renderer, pTexture, NULL, &textRectangle);

	// delete the texture and surface
	SDL_DestroyTexture(pTexture);
	SDL_FreeSurface(pSurface);
}
