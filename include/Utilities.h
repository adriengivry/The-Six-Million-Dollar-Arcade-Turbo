#pragma once
#include <string>
#include <random>

namespace Utils
{
	inline std::string LoadAsset(const std::string& p_path)
	{
		return "../assets/" + p_path;
	}

	inline int GetRandom(const int min, const int max)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		const std::uniform_int_distribution<> distr(min, max); // define the range

		return distr(eng);
	}
}