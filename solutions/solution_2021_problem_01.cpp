#include <string>
#include <fstream>
#include <limits>

// Solutions for the first problem of 2021.
// https://adventofcode.com/2021/day/1

namespace solutions {
    // This class keeps track sliding windows of sums (defined in the template value window_size).
    // It tracks enough sliding windows so that every time you add a number, it adds that number
    // to all windows that are active. See details in the implementation of add_number.
    template<size_t window_size>
    class sliding_window_adder {
    public:
        sliding_window_adder() : _sums(), _last_complete_sum(-1)
        {
            // The first window_size numbers added will not go in every available window.
            // For example, with 3 windows, the first time add_number is called, it only goes
            // in the first window. The second time, that number will go in the first two windows.
            // finally when the third number is added, that number goes in every window.
            //
            // To account for this, we initialize the _items_in_window array to non-positive numbers
            // and only add a number to that window once it becomes positive.
            for (int i = 0; i < window_size; ++i) {
                _items_in_window[i] = -i;
            }
        }

        // Adds a number to the sliding windows.
        // Returns true if after adding this number, one of the windows is full. False otherwise.
        bool add_number(int32_t number) {
            bool window_filled = false;

            for (int i = 0; i < window_size; ++i) {
                // This is inititially filled such that the first element is set to 0 but the rest
                // are negative numbers (the value is set to -i).
                //
                // This allows us to stagger the start of the sliding window.
                if (_items_in_window[i] >= 0) {
                    _sums[i] += number;
                }

                _items_in_window[i] += 1;

                // We've reached our window size, so we need to record this as the last complete
                // sum, and reset this current window.
                //
                // This will happen at most once per call of this function, because
                // the elements of _items_in_window is initialized with different numbers.
                if (_items_in_window[i] == window_size) {
                    _last_complete_sum = _sums[i];
                    _sums[i] = 0;
                    _items_in_window[i] = 0;
                    window_filled = true;
                }
            }

            return window_filled;
        }

        // Gets sum from the most recently filled window.
        int32_t get_last_complete_sum() const {
            return _last_complete_sum;
        }

    private:
        // This stores the number of items that have been added to a given window.
        int32_t _items_in_window[window_size];

        // This stores the sums of each window.
        int32_t _sums[window_size];

        int32_t _last_complete_sum;
    };

    // Solves the problem using a sliding window adder with the given size.
    template<size_t window_size>
    static std::string solve(const std::string& file_path) {
        std::ifstream ifs(file_path);

        sliding_window_adder<window_size> adder;
        int32_t last_sum = std::numeric_limits<int32_t>::max();
        int32_t increased_count = 0;
        while (!ifs.eof()) {
            int32_t current;
            ifs >> current;

            // If adding a number fills a window, check if it's an increase
            // set our new most recent sum.
            if (adder.add_number(current)) {
                int32_t new_sum = adder.get_last_complete_sum();
                if (new_sum > last_sum) {
                    increased_count += 1;
                }

                last_sum = new_sum;
            }
        }

        return std::to_string(increased_count);
    }

    // This first version is very straightforward -- it's just checking
    // if the current number is higher than the previous. Simple loop.
    //
    // It's also a degenerate case of the sliding window version (part b)
    // with the window sizes of 1.
    std::string solve_2021_01_a(const std::string& file_path) {
        return solve<1>(file_path);
    }

    // Second version actually requires the sliding window solution.
    std::string solve_2021_01_b(const std::string& file_path) {
        return solve<3>(file_path);
    }
}
