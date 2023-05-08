#pragma once
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Arena
{
protected:
	SDL_Texture* m_grassTop;
	SDL_Texture* m_grassCenter;

	SDL_Renderer* m_renderer;
	SDL_Rect m_sourceRectangle, m_destinationrectangle;

	int m_blockSize;
	int m_arenaHeight, m_arenaWidth;
	std::vector<std::string> m_gridLayout;

	float m_gravity;

	int GetArenaHeight();
	int GetArenaWidth();

	void LoadArena(std::string fileName);
public:
	Arena(SDL_Renderer* renderer, int size);
	~Arena();

	int GetBlockSize();

	float GetGravity();

	void RenderArena();

	bool IsWall(int x, int y);
	bool IsWalkableSurface(int x, int y);
};
