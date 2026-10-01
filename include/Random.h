#pragma once
#include <random>

// Small header-only utility for generating random integers.
// Shares a single engine across all callers so we don't reseed
// std::random_device for every call.
class Random {
public:
    // Returns a random integer in the inclusive range [min, max].
    static int Int(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
};
