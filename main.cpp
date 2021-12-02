#include <iostream>
#include "solutions/solutions.h"

// This struct and the macro below enables us to get the function pointer and data
// file for the problem, using a pattern that has historically worked for these
// problems.
//
// Another way to do this would be to take the problem and file as a command-line
// paramter and have a registry of function pointers. But this way I only have to
// remember to change two places (add the function, and change the first line of
// main) instead of three (add the function, add it to the table, use it as a
// command-line parameter).
struct solution_data_t {
    solutions::solution_fn_t part_a_fn;
    solutions::solution_fn_t part_b_fn;
    std::string input_file_path;
    std::string friendly_name;
};

// This will create the solution data struct to run the solution test.
//
// For this to work, you need three things:
//  1. A function in the solutions namespace calls solve_<year_of_puzzle>_<problem_number_with_two_digits>_a
//     For example, solutions::solve_2015_01_a
//
//  2. A function in the solutions namespace calls solve_<year_of_puzzle>_<problem_number_with_two_digits>_b
//     For example, solutions::solve_2015_01_b
//
//  3. A data file in <root>/data called <year_of_puzzle>-<problem_number>-input.txt
//     For example: data/2015-01-input.txt
//
// You can then then invoke it like this:
//      solution_data_t solution_data = GET_SOLUTION_DATA(<year_of_puzzle>, <problem_number_with_two_digits>);
// For example:
//      solution_data_t solution_data = GET_SOLUTION_DATA(2015, 01);
#define GET_SOLUTION_DATA(_year_, _problem_)                        \
{                                                                   \
    solutions::solve_##_year_##_##_problem_##_a,                    \
    solutions::solve_##_year_##_##_problem_##_b,                    \
    std::string(".\\data\\" #_year_ "-" #_problem_ "-input.txt"),   \
    std::string(#_year_ "-" #_problem_),                            \
}                                                                   \

int main() {
    // Change this to work on a different problem.
    solution_data_t solution_data = GET_SOLUTION_DATA(2015, 01);

    printf("Solving problem '%s', using data file '%s'\n",
        solution_data.friendly_name.c_str(), solution_data.input_file_path.c_str());
    std::string answer = solution_data.part_a_fn(solution_data.input_file_path);
    printf("Part A answer: '%s'\n", answer.c_str());
    answer = solution_data.part_b_fn(solution_data.input_file_path);
    printf("Part B answer: '%s'\n", answer.c_str());
}