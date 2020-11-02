#pragma once

#include <vector>

int LUPDecompose(double **A, int N, double Tol, int *P);
void LUPSolve(double **A, int *P, double *b, int N, double *x);
void LUPInvert(double **A, int *P, int N, double **IA);
double LUPDeterminant(double **A, int *P, int N);
std::vector<double> solve(const std::vector<std::vector<double>> &A, const std::vector<double> &b);
