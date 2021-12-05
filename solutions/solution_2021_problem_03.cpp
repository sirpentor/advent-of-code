#include <string>
#include <vector>
#include <fstream>
#include <iterator>

// Solutions for the third problem of 2021.
// https://adventofcode.com/2021/day/3

namespace solutions {
std::string solve_2021_03_a(const std::string& file_path) {

    // These will hold the counts of zeroes and ones, from left to right.
    // Note that we don't know the size of the vectors until we read the first line.
    std::vector<int32_t> counts_of_zeroes;
    std::vector<int32_t> counts_of_ones;

    std::ifstream ifs(file_path);

    std::string line;
    while (std::getline(ifs, line)) {
        // Initialize the bit-counters the first time through the loop.
        if (counts_of_zeroes.size() != line.length()) {
            counts_of_zeroes.resize(line.length());
            counts_of_ones.resize(line.length());
        }

        // Walk through each bit in the current binary number,
        // Updating our counter each one.
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '0') counts_of_zeroes[i] += 1;
            else if (line[i] == '1') counts_of_ones[i] += 1;
            else {
                printf("DEBUG: How did we get a token '%c' that we didn't expect?\n", line[i]);
            }
        }
    }

    std::string gamma;
    std::string epsilon;

    // Create the numbers out of the most common and least
    // common bits in each column.
    for (int i = 0; i < counts_of_zeroes.size(); ++i) {
        if (counts_of_zeroes[i] > counts_of_ones[i]) {
            gamma += "0";
            epsilon += "1";
        } else {
            gamma += "1";
            epsilon += "0";
        }
    }

    // Convert the binary numbers and multiply them for the final answer.
    int32_t gamma_value = std::stoi(gamma, nullptr, 2 /*base*/);
    int32_t epsilon_value = std::stoi(epsilon, nullptr, 2 /*base*/);
    return std::to_string(gamma_value * epsilon_value);
}

// For Part B, we use and discard strings based on bits in a given position, over and over until we only have one.
// This function discards one set, based on bit_position, returning the strings that have the most common
// bit in that position.
static std::vector<std::string> reduce(const std::vector<std::string> &strings, int32_t bit_position, bool most_common) {
    std::vector<std::string> start_with_zero;
    std::vector<std::string> start_with_one;

    for (const auto &str: strings) {
        if (str[bit_position] == '0') start_with_zero.push_back(str);
        else if (str[bit_position] == '1') start_with_one.push_back(str);
        else {
            printf("DEBUG: How did we get a token '%c' that we didn't expect?\n", str[bit_position]);
        }
    }

    if (most_common) {
        // When we want the most comment, tie goes to 1.
        if (start_with_zero.size() > start_with_one.size()) return start_with_zero;
        else return start_with_one;
    } else {
        // When we want the least comment, tie goes to 0.
        if (start_with_zero.size() > start_with_one.size()) return start_with_one;
        else return start_with_zero;
    }
}

std::string solve_2021_03_b(const std::string& file_path) {
    std::ifstream ifs(file_path);
    std::vector<std::string> all_lines((std::istream_iterator<std::string>(ifs)), std::istream_iterator<std::string>());

    std::vector<std::string> oxygen(all_lines.begin(), all_lines.end());
    int bit = 0;
    while (oxygen.size() != 1) {
        oxygen = reduce(oxygen, bit, true /*most_common*/);
        bit += 1;
    }

    std::vector<std::string> co2(all_lines);
    bit = 0;
    while (co2.size() != 1) {
        co2 = reduce(co2, bit, false /*most_common*/);
        bit += 1;
    }

    int32_t oxygen_value = std::stoi(oxygen[0], nullptr, 2 /*base*/);
    int32_t co2_value = std::stoi(co2[0], nullptr, 2 /*base*/);

    return std::to_string(oxygen_value * co2_value);
}
}