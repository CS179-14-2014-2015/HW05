#ifdef WIN32
#include <windows.h>
#endif
#include <SDL2\SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <iostream>
#include "FPS.h"

using namespace std;

FPS::FPS()
{
	m_fps = 0;
	m_fpscount = 0;
	m_start = SDL_GetTicks();
}

void FPS::update()
{
	m_fpscount++;
	m_fpsinterval = SDL_GetTicks() - m_start;

	if( m_fpsinterval > 1000 )
	{
		m_fps = m_fpscount;

		m_fpscount = 0;
		m_start = m_fpsinterval;
		m_fpsinterval = 0;
		std::cout << "Fps: " << m_fps << '\n';
	}
}

unsigned int FPS::get() const
{
	return m_fps;
}