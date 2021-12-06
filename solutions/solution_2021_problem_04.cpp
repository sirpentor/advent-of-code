#include <string>
#include <fstream>
#include <vector>
#include <sstream>

// Solutions for the third problem of 2021.
// https://adventofcode.com/2021/day/4

namespace solutions {

// Parses a line given a delimter, into the number format we want.
// In addition to the delimeter, this skips over empty portions of the string.
// For example, "1     2" with a delimiter of ' ' parses correctly as two numbers.
static std::vector<int32_t> parse_line(const std::string &line, char delim) {
    std::stringstream stream(line);
    std::vector<int32_t> numbers;

    std::string cur;
    while (std::getline(stream, cur, delim)) {
        if (cur.size() != 0) {
            numbers.push_back(std::stoi(cur));
        }
    }

    return numbers;
}

// Represents a game board, with the ability to mark values and check for victory.
// TOBIASB: I'm mostly happy with the abstraction here, but the amount of iterations
//          and copies of data involved in filling this in (plus input, below) is
//          maddening. I suspect there's something more efficient I could do
//          but I'd rather move on in to the next problem.
class Board {
public:
    Board(const std::vector<std::string> &lines) : _current_total_score(0), _has_won(false) {
        if (lines.size() != board_size) {
            printf("DEBUG: How did we get a number of lines %d that that isn't our board size?\n", lines.size());
            return;
        }

        for (int i = 0; i < lines.size(); ++i) {
            std::vector<int32_t> values = parse_line(lines[i], ' ');
            if (values.size() != board_size) {
                printf("DEBUG: How did we a board row with %d values in it?\n", values.size());
                return;
            }
            for (int j = 0; j < values.size(); ++j) {
                _current_total_score += values[j];
                _board[i][j] = values[j];
            }
        }
    }

    bool MarkAndCheck(int32_t value) {
        for (size_t row_pos = 0; row_pos < board_size; ++row_pos) {
            for (size_t col_pos = 0; col_pos < board_size; ++col_pos) {
                if (_board[row_pos][col_pos] == value) {
                    _current_total_score -= _board[row_pos][col_pos];
                    _board[row_pos][col_pos] = marked_value;

                    if (CheckRow(row_pos) || CheckCol(col_pos)) {
                        _has_won = true;
                        return true;
                    }
                }
            }
        }

        return false;
    }

    int32_t GetScore() const { return _current_total_score; }

    bool HasWon() const { return _has_won; }

    std::string ToDebugString() const {
        std::string str;
        str += "score: " + std::to_string(_current_total_score) + "\n";
        for (auto &row: _board) {
            for (auto space: row) {
                str += std::to_string(space) + " ";
            }
            str.back() = '\n';
        }

        return str;
    }

private:
    bool CheckRow(size_t row) {
        for (int col = 0; col < board_size; ++col) {
            if (_board[row][col] != marked_value) {
                return false;
            }
        }

        return true;
    }

    bool CheckCol(size_t col) {
        for (int row = 0; row < board_size; ++row) {
            if (_board[row][col] != marked_value) {
                return false;
            }
        }

        return true;
    }

    static constexpr size_t board_size = 5;
    static constexpr int32_t marked_value = -1;
    int32_t _board[board_size][board_size];
    int32_t _current_total_score;
    bool _has_won;
};

static Board get_board(std::istream &stream) {
    std::vector<std::string> rows;
    std::string line;
    while (std::getline(stream, line) && line.size() != 0) {
        rows.push_back(line);
    }

    return Board(rows);
}

// The only difference between the two puzzles is whether we want the first
// winner or the last winner. This helper handles both cases.
static std::string solve(const std::string &file_path, bool first_winner) {
    std::ifstream ifs(file_path);

    // Get the first line, which has the called numbers;
    std::string line;
    std::getline(ifs, line);
    std::vector<int32_t> called_numbers = parse_line(line, ',');

    // Second line is always empty, so discard it.
    std::getline(ifs, line);

    std::vector<Board> boards;

    // Collect the next board into a set of rows. A blank line signifies the next board.
    while (!ifs.eof()) {
        boards.push_back(get_board(ifs));
    }

    // We can finally start playing the game.
    int32_t answer = -1;
    for (auto number: called_numbers) {
        for (auto &board: boards) {
            if (!board.HasWon() && board.MarkAndCheck(number)) {
                answer = board.GetScore() * number;
                if (first_winner) {
                    return std::to_string(answer);
                }
            }
        }
    }

    return std::to_string(answer);
}

std::string solve_2021_04_a(const std::string& file_path) {
    return solve(file_path, true /*first_winner*/);
}

std::string solve_2021_04_b(const std::string& file_path) {
    return solve(file_path, false /*first_winner*/);
}
}