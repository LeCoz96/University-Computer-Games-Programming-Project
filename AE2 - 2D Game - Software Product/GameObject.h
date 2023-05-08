#pragma once
#include <SDL.h>
#include <vector>
#include <string>

class Arena;

class GameObject
{
protected:
	SDL_Renderer* m_renderer{ nullptr };
	SDL_Texture* m_texture{ nullptr };

	Arena* m_arena{ nullptr };
	int m_xPos, m_yPos;
	int m_blockSize;

	SDL_Rect m_sourceRectangle{}, m_destinationRectangle{};

	int m_currentFrame;
	int m_animationSpeed;
	int m_imageSize;
	std::vector<SDL_Texture*> m_listOfTextures;
	std::vector<std::pair<SDL_Rect, int>> m_imageDictionary;

public:
	GameObject(int x, int y, SDL_Renderer* renderer, Arena* arena);
	GameObject() = default;
	~GameObject() = default;

	void SetX(int value);
	void SetY(int value);
	int GetX();
	int GetY();

	virtual void Render();

	bool Collision(GameObject* object);
	void Update();

	virtual void Animate();
};
