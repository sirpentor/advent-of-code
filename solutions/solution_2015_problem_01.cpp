#include <string>
#include <fstream>

// This file provides a solution for the first problem from 2015, as a proof of
// concept for the mini-framework and build/debug setup.
// https://adventofcode.com/2015/day/1

namespace solutions {
static int32_t incrementor_from_token(char c) {
    switch (c)
    {
    case '(': return 1;
    case ')': return -1;
    default:
        printf("DEBUG: How did we get unexpected token '%c'?\n", c);
        return 0;
    }
}

std::string solve_2015_01_a(const std::string& file_path) {
    std::ifstream ifs(file_path.c_str());
    int32_t floor = 0;
    char c;
    while (ifs.get(c)) {
        floor += incrementor_from_token(c);
    }

    return std::to_string(floor);
}

std::string solve_2015_01_b(const std::string& file_path) {
    std::ifstream ifs(file_path.c_str());
    int32_t floor = 0;
    int32_t pos = 0;
    char c;
    while (floor != -1 && ifs.get(c)) {
        pos += 1;
        floor += incrementor_from_token(c);
    }

    return std::to_string(pos);
}
}
