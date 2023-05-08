#include "Image.h"
#include <SDL_image.h>

SDL_Texture* Image::GetTexture(const char* fileName, SDL_Renderer* renderer)
{
	SDL_Surface* temporarySurface = IMG_Load(fileName);
	SDL_Texture* FinalTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);
	SDL_FreeSurface(temporarySurface);

	return FinalTexture;
}

void Image::PrintImage(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect)
{
	SDL_RenderCopy(renderer, texture, &sourceRect, &destinationRect);
}

