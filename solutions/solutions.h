#include <string>

namespace solutions {
    typedef std::string (*solution_fn_t)(const std::string&);

    std::string solve_2015_01_a(const std::string& file_path);
    std::string solve_2015_01_b(const std::string& file_path);

    std::string solve_2021_01_a(const std::string& file_path);
    std::string solve_2021_01_b(const std::string& file_path);

    std::string solve_2021_02_a(const std::string& file_path);
    std::string solve_2021_02_b(const std::string& file_path);

    std::string solve_2021_03_a(const std::string& file_path);
    std::string solve_2021_03_b(const std::string& file_path);

    std::string solve_2021_04_a(const std::string& file_path);
    std::string solve_2021_04_b(const std::string& file_path);
}
