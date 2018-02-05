#pragma once

struct AppInfo
{
	AppInfo() { Reset(); }

	void Reset()
	{
		isRunning = true;
	}

	bool isRunning;
};