#pragma once
#include <SDL.h>

enum KeyPressedList {
	Key_ESCAPE,
	Key_SPACE,
	Key_A,
	Key_D,
	SizeOfKeysEnum
};

class Input
{
private:
	bool m_keysPressed[SizeOfKeysEnum];
public:
	Input();
	~Input() = default;
	void GetInput();
	bool KeyIsPressed(KeyPressedList key);
};
