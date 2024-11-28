#include "random.hpp"
#include <random>

static auto& generator()
{
    static std::default_random_engine gen{std::random_device{}()};
    return gen;
}

int random_int(int min, int max)
{
    std::uniform_int_distribution<int> distribution{min, max - 1};
    return distribution(generator());
}

float random_float(float min, float max)
{
    // std::uniform_real_distribution<float> distribution{min, max};
    // return distribution(generator());
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void set_random_seed(int seed)
{
    generator().seed(seed);
}