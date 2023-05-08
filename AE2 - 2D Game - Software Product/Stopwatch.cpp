#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
	Reset();
	m_frequency = SDL_GetPerformanceFrequency();
}

void Stopwatch::Start()
{
	m_start = SDL_GetPerformanceCounter();
}

void Stopwatch::Stop()
{
	m_end = SDL_GetPerformanceCounter();
}

float Stopwatch::GetTimeElapsedMS()
{
	float elapsed = (float)(m_end - m_start) / m_frequency;
	elapsed *= 1000;
	return elapsed;
}

void Stopwatch::Reset()
{
	m_start = 0.0f;
	m_end = 0.0f;
}
