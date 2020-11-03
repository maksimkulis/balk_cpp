#pragma once

/*
    Balk calculation
*/

#include <vector>
#include <string>
#include <memory>

#include "forces_and_moments.h"

class Balk
{
public:
    Balk(int balk_size, double segment_length, double E, double J);
    ~Balk() = default;

    void add_hinge_support(int shift, double segment_length);

    void add_elastic_support(int shift, double segment_length, double value);

    void add_hard_pinching(int shift, double segment_length);

    void add_concentrated_power(int shift, double segment_length, double value);

    void add_moment(int shift, double segment_length, double value);

    void add_uniform_load(int shift, double segment_length, double value);

    /// Solve the balk.
    void solve_balk();

    // Getters
    [[nodiscard]]
    constexpr inline int getBalkSize() const { return balk_size; }

    [[nodiscard]]
    constexpr inline double getSegmentLength() const { return segment_length; }

    [[nodiscard]]
    inline auto &getTerms() { return terms; }

    [[nodiscard]]
    constexpr inline double getEJ() const { return E * J; }

    [[nodiscard]]
    constexpr inline auto &getA() { return A; }

private:
    const int balk_size;
    const double segment_length;
    const double E;
    const double J;
    std::vector<std::shared_ptr<Term>> terms;

    // Block for matrix solving
private:
    std::vector<std::vector<double>> A;
    std::vector<double> x;
    std::vector<double> b;

    // functions for calculations
public:
    void func(int degree, double value);
};