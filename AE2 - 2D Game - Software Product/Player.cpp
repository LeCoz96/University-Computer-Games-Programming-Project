#include "Player.h"
#include "Arena.h"
#include "Image.h"
#include "Input.h"

Player::Player(int x, int y, int speed, SDL_Renderer* renderer, Arena* arena)
	: MovingObject{ x, y, speed, renderer, arena }
{
	m_y_velocity = 0.0f;

	m_lives = 3;

	m_input = new Input();

	m_animationSpeed = 100;

	m_listOfTextures.push_back(Image::GetTexture("Assets/PlayerWalkSpriteSheet.png", m_renderer));
	m_listOfTextures.push_back(Image::GetTexture("Assets/PlayerIdle.png", m_renderer));
	m_listOfTextures.push_back(Image::GetTexture("Assets/PlayerJump.png", m_renderer));

	for (size_t i = 0; i < m_listOfTextures.size(); i++)
	{
		m_imageDictionary.push_back(std::make_pair(SDL_Rect(), 0));
		SDL_QueryTexture(m_listOfTextures[i], NULL, NULL, &m_imageDictionary[i].first.w, &m_imageDictionary[i].first.h);
		m_imageDictionary[i].first.x = 0;
		m_imageDictionary[i].first.y = 0;

		if (i == 0)
			m_imageDictionary[i].second = 11;
		else
			m_imageDictionary[i].second = 1;

		m_imageDictionary[i].first.w /= m_imageDictionary[i].second;
	}
}

Player::~Player()
{
	if (nullptr != m_input)
	{
		delete m_input;
		m_input = nullptr;
	}
}

void Player::TakeDamage(int x, int y)
{
	m_lives--;
	SetX(x);
	SetY(y);
}

int Player::GetLives()
{
	return m_lives;
}

void Player::GetPlayerInput()
{
	m_input->GetInput();

	if (m_input->KeyIsPressed(Key_A) || m_input->KeyIsPressed(Key_D))
	{
		m_isIdle = false;

		if (m_input->KeyIsPressed(Key_A))
			Left();

		if (m_input->KeyIsPressed(Key_D))
			Right();
	}
	else
		m_isIdle = true;

	if (m_input->KeyIsPressed(Key_SPACE))
		Jump(7.5f);
}

bool Player::PlayerEndGame()
{
	if (m_input->KeyIsPressed(Key_ESCAPE))
		return true;

	return false;
}

void Player::Render()
{
	if (!m_isJumping && !m_isIdle)
	{
		if (m_movingRight)
			SDL_RenderCopyEx(m_renderer, m_listOfTextures[0], &m_imageDictionary[0].first, &m_destinationRectangle, 0, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(m_renderer, m_listOfTextures[0], &m_imageDictionary[0].first, &m_destinationRectangle);
	}
	if (!m_isJumping && m_isIdle)
	{
		if (m_movingRight)
			SDL_RenderCopyEx(m_renderer, m_listOfTextures[1], &m_imageDictionary[1].first, &m_destinationRectangle, 0, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(m_renderer, m_listOfTextures[1], &m_imageDictionary[1].first, &m_destinationRectangle);
	}
	if (m_isJumping)
	{
		if (m_movingRight)
			SDL_RenderCopyEx(m_renderer, m_listOfTextures[2], &m_imageDictionary[2].first, &m_destinationRectangle, 0, NULL, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopy(m_renderer, m_listOfTextures[2], &m_imageDictionary[2].first, &m_destinationRectangle);
	}
}

void Player::Jump(float velocity)
{
	if ((m_arena->IsWall(m_xPos, m_yPos + (m_blockSize)) ||
		m_arena->IsWall(m_xPos + (m_blockSize - 1), m_yPos + (m_blockSize))))
		m_y_velocity = velocity;
}

void Player::Gravity()
{
	m_y_velocity -= m_arena->GetGravity();

	if (m_y_velocity > 0)
		Up(m_y_velocity);
	else
		Down(-m_y_velocity);
}

void Player::Up(int velocity)
{
	int y = m_yPos - velocity;
	if (!m_arena->IsWall(m_xPos, y) &&
		!m_arena->IsWall((m_xPos + m_blockSize - 1), y))
	{
		m_yPos = y;
		m_isJumping = true;
	}
	else
		m_y_velocity = 0;
}

void Player::Down(int velocity)
{
	int y = m_yPos + velocity;
	if (!m_arena->IsWall(m_xPos, (y + m_blockSize - 1)) &&
		!m_arena->IsWall((m_xPos + m_blockSize - 1), (y + m_blockSize - 1)))
		m_yPos = y;
	else
	{
		m_y_velocity = 0;
		m_isJumping = false;
	}
}
