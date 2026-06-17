#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace labtest {

inline void fail(const char* expression, const char* file, int line, const std::string& detail) {
    std::ostringstream out;
    out << file << ':' << line << " expectation failed: " << expression;
    if (!detail.empty()) {
        out << " (" << detail << ')';
    }
    throw std::runtime_error(out.str());
}

template <typename Left, typename Right>
void expect_eq(const Left& left, const Right& right, const char* expression, const char* file, int line) {
    if (!(left == right)) {
        std::ostringstream detail;
        detail << "left=" << left << ", right=" << right;
        fail(expression, file, line, detail.str());
    }
}

inline int run(const std::string& suite, void (*test_body)()) {
    try {
        test_body();
        std::cout << "[PASS] " << suite << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "[FAIL] " << suite << ": " << error.what() << '\n';
        return 1;
    }
}

} // namespace labtest

#define EXPECT_TRUE(expression) \
    do { \
        if (!(expression)) { \
            ::labtest::fail(#expression, __FILE__, __LINE__, "expected true"); \
        } \
    } while (false)

#define EXPECT_EQ(left, right) \
    do { \
        ::labtest::expect_eq((left), (right), #left " == " #right, __FILE__, __LINE__); \
    } while (false)
