/*
 * utility.cpp
 *
 *  Created on: 20 janv. 2026
 *      Author: Alex
 */

#include "utility_functions.hpp"

float drawProbability()
{
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    float roll = distribution(generator);
    return roll;
}

int drawRandint(int a, int b)
{
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(a, b);

    int roll = distribution(generator);
    return roll;
}
