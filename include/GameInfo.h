#pragma once

#include <irrlicht.h>


struct GameInfo
{
	GameInfo() { Reset(); }

	irr::f32 defaultScore;
	irr::f32 currentScore;

	void Reset()
	{
		defaultScore = 20000.f;
		currentScore = defaultScore;
	}
};