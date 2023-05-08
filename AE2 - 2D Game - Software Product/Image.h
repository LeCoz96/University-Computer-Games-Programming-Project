#pragma once
#include <SDL.h>
class Image
{
public:
	static SDL_Texture* GetTexture(const char* fileName, SDL_Renderer* renderer);
	static void PrintImage(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle);
};
