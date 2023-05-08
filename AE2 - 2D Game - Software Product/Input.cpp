#include "Input.h"

Input::Input()
{
	for (int i = 0; i < SizeOfKeysEnum; i++)
	{
		m_keysPressed[i] = false;
	}
}

void Input::GetInput()
{
	static SDL_Event event;

	while (0 != SDL_PollEvent(&event))
	{
		SDL_Keycode keyPressed = event.key.keysym.sym;
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				m_keysPressed[Key_ESCAPE] = true;

			if (keyPressed == SDLK_SPACE)
				m_keysPressed[Key_SPACE] = true;

			if (keyPressed == SDLK_a)
				m_keysPressed[Key_A] = true;

			if (keyPressed == SDLK_d)
				m_keysPressed[Key_D] = true;

			break;

		case SDL_KEYUP:
			if (keyPressed == SDLK_ESCAPE)
				m_keysPressed[Key_ESCAPE] = false;

			if (keyPressed == SDLK_SPACE)
				m_keysPressed[Key_SPACE] = false;

			if (keyPressed == SDLK_a)
				m_keysPressed[Key_A] = false;

			if (keyPressed == SDLK_d)
				m_keysPressed[Key_D] = false;

			break;
		default:
			break;
		}
	}
}

bool Input::KeyIsPressed(KeyPressedList key)
{
	return m_keysPressed[key];
}
