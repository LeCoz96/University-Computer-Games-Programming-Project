#include "Arena.h"
#include "Image.h"


Arena::Arena(SDL_Renderer* renderer, int size)
	: m_renderer{ renderer }, m_blockSize{ size }
{
	LoadArena("Assets/Arena.txt");

	m_grassTop = Image::GetTexture("Assets/GrassWallTop.png", renderer);
	m_grassCenter = Image::GetTexture("Assets/GrassWallCenter.png", renderer);

	m_gravity = 0.2f;

	m_sourceRectangle.w = m_sourceRectangle.h = m_blockSize;
	m_destinationrectangle.w = m_destinationrectangle.h = m_blockSize;
}

Arena::~Arena()
{
	m_gridLayout.clear();
}

void Arena::LoadArena(std::string fileName)
{
	char block;
	int arenaX = 0;
	int arenaY = 0;
	std::ifstream arenaFile;
	arenaFile.open(fileName);

	std::string rowValue;
	while (getline(arenaFile, rowValue))
		arenaY++;

	std::stringstream s(rowValue);
	char customValue;
	while (s >> customValue) if (customValue != ',') arenaX++;

	m_gridLayout.resize(arenaY);

	arenaFile.clear();
	arenaFile.seekg(0);

	for (int column = 0; column < arenaY; column++)
	{
		for (int row = 0; row < arenaX; row++)
		{
			arenaFile.get(block);

			m_gridLayout[column] += block;

			arenaFile.ignore();
		}
	}

	m_arenaHeight = arenaY;
	m_arenaWidth = arenaX;

	arenaFile.close();
}

int Arena::GetArenaHeight()
{
	return m_gridLayout.size();
}

int Arena::GetArenaWidth()
{
	return m_gridLayout[0].length();
}

int Arena::GetBlockSize()
{
	return m_blockSize;
}

float Arena::GetGravity()
{
	return m_gravity;
}

void Arena::RenderArena()
{
	for (int row = 0; row < m_arenaHeight; row++)
	{
		for (int column = 0; column < m_arenaWidth; column++)
		{
			switch (m_gridLayout[row][column])
			{
			case 'T':
				m_destinationrectangle.x = column * m_blockSize;
				m_destinationrectangle.y = row * m_blockSize;
				Image::PrintImage(m_renderer, m_grassTop, m_sourceRectangle, m_destinationrectangle);
				break;

			case 'C':
				m_destinationrectangle.x = column * m_blockSize;
				m_destinationrectangle.y = row * m_blockSize;
				Image::PrintImage(m_renderer, m_grassCenter, m_sourceRectangle, m_destinationrectangle);
				break;

			default:
				break;
			}
		}
	}
}

bool Arena::IsWall(int x, int y)
{
	if (m_gridLayout[y / m_blockSize][x / m_blockSize] != '.')
		return true;
	return false;
}

bool Arena::IsWalkableSurface(int x, int y)
{
	if (m_gridLayout[y / m_blockSize][x / m_blockSize] == 'T')
		return true;
	return false;
}
