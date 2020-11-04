#pragma once

#include <vector>

namespace lu
{
std::vector<double> solve(const std::vector<std::vector<double>> &A, const std::vector<double> &b);
}  // namespace lu
