#include <string>

namespace solutions {
    typedef std::string (*solution_fn_t)(const std::string&);

    std::string solve_2015_01_a(const std::string& file_path);
    std::string solve_2015_01_b(const std::string& file_path);

    std::string solve_2021_01_a(const std::string& file_path);
    std::string solve_2021_01_b(const std::string& file_path);
}