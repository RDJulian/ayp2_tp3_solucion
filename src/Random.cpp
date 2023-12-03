#include "Random.hpp"
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

int Random::random(int low, int high) {
    std::uniform_int_distribution<> dist(low, high);
    return (dist(gen));
}