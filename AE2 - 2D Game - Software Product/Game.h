#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <conio.h>
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

class Arena;
class Lava;
class Key;
class FlyingEnemy;
class Door;
class Player;
class GroundEnemy;
class Stopwatch;
class Stats;

class Game
{
private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };

	Arena* m_arena{ nullptr };
	Player* m_player{ nullptr };
	GroundEnemy* m_groundEnemy{ nullptr };
	FlyingEnemy* m_flyEnemy{ nullptr };
	Door* m_door{ nullptr };
	Stats* m_stats{ nullptr };
	Stopwatch* m_stopwatch{ nullptr };

	std::vector<Key*> m_listOfKey;
	std::vector<Lava*> m_listOfLava;
	std::vector<FlyingEnemy*> m_listOfFlyingEnemy;
	std::vector<GroundEnemy*> m_listOfGroundEnemy;

	void SetBackgroundColour();
	void WinGame();
	void LoseGame();
	void ClearAndPresent();
	void Pause(float delay);
public:
	Game();
	~Game();

	void Update();

	bool m_replayGame{ true };
};
