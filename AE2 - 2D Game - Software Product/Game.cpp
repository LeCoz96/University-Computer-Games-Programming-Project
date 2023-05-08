#include "Game.h"
#include "Stopwatch.h"
#include "Arena.h"
#include "Player.h"
#include "Stats.h"
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "Lava.h"
#include "Key.h"
#include "Door.h"

Game::Game()
{
	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow
	(
		"Game Window",
		250,
		50,
		640,
		640,
		0
	);

	if (nullptr == m_window)
	{
		std::cout << "Window initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		_getch();
		return;
	}

	m_renderer = SDL_CreateRenderer
	(
		m_window,			// link the renderer to the window
		-1,					// index rendering driver (don't worry about this)
		0					// renderer behavior flags (ignore for now)
	);

	if (nullptr == m_renderer)
	{
		std::cout << "Renderer initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press a key to continue" << std::endl;
		_getch();
	}

#pragma region Constructors
	m_stopwatch = new Stopwatch();

	m_arena = new Arena(m_renderer, 32);

	m_player = new Player(96, 576, 3, m_renderer, m_arena);
	m_stats = new Stats(m_player);

	m_door = new Door(576, 128, m_renderer, m_arena);

	m_listOfGroundEnemy.push_back(new GroundEnemy(192, 128, 2, m_renderer, m_arena));
	m_listOfGroundEnemy.push_back(new GroundEnemy(96, 352, 2, m_renderer, m_arena));
	m_listOfGroundEnemy.push_back(new GroundEnemy(384, 576, 2, m_renderer, m_arena));

	m_listOfLava.push_back(new Lava(384, 160, m_renderer, m_arena));
	m_listOfLava.push_back(new Lava(416, 160, m_renderer, m_arena));
	m_listOfLava.push_back(new Lava(288, 384, m_renderer, m_arena));
	m_listOfLava.push_back(new Lava(320, 384, m_renderer, m_arena));
	m_listOfLava.push_back(new Lava(256, 608, m_renderer, m_arena));
	m_listOfLava.push_back(new Lava(288, 608, m_renderer, m_arena));

	m_listOfKey.push_back(new Key(34, 160, m_renderer, m_arena));
	m_listOfKey.push_back(new Key(256, 352, m_renderer, m_arena));
	m_listOfKey.push_back(new Key(575, 576, m_renderer, m_arena));

	m_listOfFlyingEnemy.push_back(new FlyingEnemy(96, 66, 1, m_renderer, m_arena));
	m_listOfFlyingEnemy.push_back(new FlyingEnemy(576, 550, 1, m_renderer, m_arena));
#pragma endregion
}

Game::~Game()
{
	for (size_t i = 0; i < m_listOfFlyingEnemy.size(); i++)
	{
		if (nullptr != m_listOfFlyingEnemy[i])
		{
			delete m_listOfFlyingEnemy[i];
			m_listOfFlyingEnemy[i] = nullptr;
		}
	}
	for (size_t i = 0; i < m_listOfKey.size(); i++)
	{
		if (nullptr != m_listOfKey[i])
		{
			delete m_listOfKey[i];
			m_listOfKey[i] = nullptr;
		}
	}
	for (size_t i = 0; i < m_listOfLava.size(); i++)
	{
		if (nullptr != m_listOfLava[i])
		{
			delete m_listOfLava[i];
			m_listOfLava[i] = nullptr;
		}
	}
	for (size_t i = 0; i < m_listOfGroundEnemy.size(); i++)
	{
		if (nullptr != m_listOfGroundEnemy[i])
		{
			delete m_listOfGroundEnemy[i];
			m_listOfGroundEnemy[i] = nullptr;
		}
	}
	if (nullptr != m_player)
	{
		delete m_player;
		m_player = nullptr;
	}
	if (nullptr != m_arena)
	{
		delete m_arena;
		m_arena = nullptr;
	}
	if (nullptr != m_stats)
	{
		delete m_stats;
		m_stats = nullptr;
	}
	if (nullptr != m_stopwatch)
	{
		delete m_stopwatch;
		m_stopwatch = nullptr;
	}
	if (nullptr != m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
	if (nullptr != m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
	// shut down
	SDL_Quit();
}

void Game::Update()
{
	if (nullptr == m_renderer) return;

	SetBackgroundColour();

	m_door->Update();

	float time;

	while (!m_player->PlayerEndGame() && m_player->GetLives() != 0 && !m_door->IsPlayerAtTheDoor())
	{
		time = m_stopwatch->GetTimeElapsedMS();
		m_stopwatch->Reset();
		m_stopwatch->Start();

		m_player->GetPlayerInput();

#pragma region UpdateMovingObjects
		m_player->Gravity();

		m_player->Update();

		for (size_t i = 0; i < m_listOfKey.size(); i++)
			m_listOfKey[i]->Update();

		for (size_t i = 0; i < m_listOfLava.size(); i++)
			m_listOfLava[i]->Update();

		for (size_t i = 0; i < m_listOfGroundEnemy.size(); i++)
		{
			m_listOfGroundEnemy[i]->Patrol();
			m_listOfGroundEnemy[i]->Update();
		}

		for (size_t i = 0; i < m_listOfFlyingEnemy.size(); i++)
		{
			m_listOfFlyingEnemy[i]->Patrol();
			m_listOfFlyingEnemy[i]->Update();
			m_listOfFlyingEnemy[i]->PlayerWithinRange(m_player);

		}
#pragma endregion

#pragma region CheckCollisions
		for (size_t i = 0; i < m_listOfGroundEnemy.size(); i++)
		{
			if (m_listOfGroundEnemy[i]->Collision(m_player))
				m_player->TakeDamage(96, 576);
		}

		for (size_t i = 0; i < m_listOfKey.size(); i++)
		{
			if (m_listOfKey[i]->Collision(m_player))
			{
				delete m_listOfKey[i];
				m_listOfKey[i] = nullptr;
				m_listOfKey.erase(m_listOfKey.begin() + i);
			}
		}

		for (size_t i = 0; i < m_listOfLava.size(); i++)
		{
			if (m_listOfLava[i]->Collision(m_player))
				m_player->TakeDamage(96, 576);
		}

		if (m_door->AllCoinsCollected(m_listOfKey))
		{
			if (m_door->Collision(m_player))
				m_door->PlayerAtDoor();
		}

		for (size_t i = 0; i < m_listOfFlyingEnemy.size(); i++)
		{
			if (m_listOfFlyingEnemy[i]->Collision(m_player))
				m_player->TakeDamage(96, 576);
		}
#pragma endregion

		ClearAndPresent();

		m_stopwatch->Stop();

		if (time < 1000.0f / 60.0f)
			Pause((1000.0f / 60.0f) - time);
	}

	if (m_player->PlayerEndGame())
		m_replayGame = false;
	if (m_player->GetLives() == 0)
		LoseGame();
	else if (m_player->GetLives() != 0 && !m_player->PlayerEndGame())
		WinGame();
}

void Game::SetBackgroundColour()
{
	// render a sky blue
	int result = SDL_SetRenderDrawColor
	(
		m_renderer,		// the target renderer
		50,				// red value
		175,			// green value
		250,			// blue value
		150				// alpha
	);
}

void Game::WinGame()
{
	SDL_RenderClear(m_renderer);
	m_stats->UpdateText("Congradulations you WON!", 150, 300, m_renderer, m_stats->m_statsText, { 255, 255, 255 });
	SDL_RenderPresent(m_renderer);
	Pause(5000);
	m_replayGame = false;
}

void Game::LoseGame()
{
	SDL_RenderClear(m_renderer);
	m_stats->UpdateText("You Lost!", 263, 200, m_renderer, m_stats->m_statsText, { 255, 255, 255 });
	m_stats->UpdateText("Wait to replay", 233, 300, m_renderer, m_stats->m_statsText, { 255, 255, 255 });
	SDL_RenderPresent(m_renderer);
	Pause(5000);
}

void Game::ClearAndPresent()
{
	SDL_RenderClear(m_renderer);

	m_arena->RenderArena();

	m_door->Render();

	for (size_t i = 0; i < m_listOfGroundEnemy.size(); i++)
		m_listOfGroundEnemy[i]->Render();

	for (size_t i = 0; i < m_listOfLava.size(); i++)
		m_listOfLava[i]->Render();

	for (size_t i = 0; i < m_listOfKey.size(); i++)
		m_listOfKey[i]->Render();

	for (size_t i = 0; i < m_listOfFlyingEnemy.size(); i++)
		m_listOfFlyingEnemy[i]->Render();

	m_player->Render();

	m_stats->UpdateText("Lives:     " + std::to_string(m_player->GetLives()), 33, 1, m_renderer, m_stats->m_statsText, { 255, 255, 255 });
	m_stats->UpdateText("Keys Remaining:     " + std::to_string(m_listOfKey.size()), 345, 1, m_renderer, m_stats->m_statsText, { 255, 255, 255 });
	m_stats->UpdateText("A = Left   D = Right  SPACE = Jump   ESC = Quit", 17, 610, m_renderer, m_stats->m_statsText, { 255, 255, 255 });

	SDL_RenderPresent(m_renderer);
}

void Game::Pause(float delay)
{
	SDL_Delay(delay);
}
