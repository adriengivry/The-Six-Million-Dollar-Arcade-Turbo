#pragma once

#include <irrlicht.h>

struct GameInfo
{
	GameInfo() { Reset(); }

	void Reset()
	{
		// The default score represent the default amount of cash you have at the beginning of the game
		defaultScore = 20000.f;
		currentScore = defaultScore;
	}

	irr::f32 defaultScore;
	irr::f32 currentScore;
};