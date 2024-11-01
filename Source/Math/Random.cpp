#include "Random.h"

int Random::RandomInt(const int min, const int max) {

	if (min >= max) {
		return 0;
	}

	std::random_device seed_gen;

	std::mt19937 mt(seed_gen());

	std::uniform_int_distribution<> dist(min,max);

	return dist(seed_gen);
}

float Random::RandomFloat(const float min, const float max) {

	if (min >= max) {
		return 0;
	}

	std::random_device seed_gen;

	std::mt19937 mt(seed_gen());
	std::uniform_real_distribution<float> dist(min, max);

	return dist(seed_gen);
}