#include <random>
#include <iostream>

int maind()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6); // distribution in range [1, 6]

	std::cout << dist6(rng) << std::endl;
}