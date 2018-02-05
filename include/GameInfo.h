#pragma once

struct GameInfo
{
	GameInfo() { Reset(); }

	void Reset()
	{
		score = 0;
	}

	int score;
};