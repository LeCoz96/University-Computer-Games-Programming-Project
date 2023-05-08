#pragma once
#include <SDL.h>
class Stopwatch
{
private:
	Uint64 m_start, m_end;
	Uint64 m_frequency;
public:
	Stopwatch();
	~Stopwatch() = default;

	void Start();
	void Stop();

	float GetTimeElapsedMS();

	void Reset();
};
