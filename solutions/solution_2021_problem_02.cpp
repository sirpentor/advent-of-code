#include <string>
#include <fstream>

// Solutions for the second problem of 2021.
// https://adventofcode.com/2021/day/2

namespace solutions {

// The core of this problem is handling strings with associated numbers. The parts
// just handle those numbers a bit differently.
//
// This base class provides the command handling and delegates to derived classes
// how to handle them.
//
// The derived classes are really straightforward implementations of the instructions.
class PositionAccumulator {
public:
    PositionAccumulator() : _horizontal_pos(0), _depth(0) { }

    void HandleDirection(const std::string& direction, int32_t amount) {
        if (direction == "forward") {
            OnForward(amount);
        } else if (direction == "down") {
            OnDown(amount);
        } else if (direction == "up") {
            OnUp(amount);
        } else {
            printf("DEBUG: How did we get unexpected direction '%s'?\n", direction.c_str());
        }
    }

    int32_t GetHorizontalPos() const { return _horizontal_pos; }
    int32_t GetDepth() const { return _depth; }

protected:
    virtual void OnForward(int32_t amount) = 0;
    virtual void OnDown(int32_t amount) = 0;
    virtual void OnUp(int32_t amount) = 0;

    int32_t _horizontal_pos;
    int32_t _depth;
};

class BasicPositionAccumulator : public PositionAccumulator {
protected:
    void OnForward(int32_t amount) override {
        _horizontal_pos += amount;
    }

    void OnDown(int32_t amount) override {
            _depth += amount;
    }

    void OnUp(int32_t amount) override {
            _depth -= amount;
    }
};

class AimingPositionAccumulator : public PositionAccumulator {
public:
    AimingPositionAccumulator() : PositionAccumulator(), _aim(0) { }

protected:
    void OnForward(int32_t amount) override {
        _horizontal_pos += amount;
        _depth += _aim * amount;
    }

    void OnDown(int32_t amount) override {
        _aim += amount;
    }

    void OnUp(int32_t amount) override {
        _aim -= amount;
    }

private:
    int32_t _aim;
};

// Helper that will loop through input, adding the instructions to the accumulator.
// The individual solution functions just need to create the right accumulator.
std::string solve(const std::string& file_path, PositionAccumulator& accum) {
    std::ifstream ifs(file_path);

    while (!ifs.eof()) {
        std::string direction;
        int32_t amount;
        ifs >> direction >> amount;
        accum.HandleDirection(direction, amount);
    }

    return std::to_string(accum.GetHorizontalPos() * accum.GetDepth());
}

std::string solve_2021_02_a(const std::string& file_path) {
    BasicPositionAccumulator accum;
    return solve(file_path, accum);
}

std::string solve_2021_02_b(const std::string& file_path) {
    AimingPositionAccumulator accum;
    return solve(file_path, accum);
}
}
