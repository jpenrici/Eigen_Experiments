#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <eigen3/Eigen/Core>
#include <functional>
#include <iostream>
#include <string>

auto rows(const auto &mat) -> std::string
{
    return std::to_string(mat.rows());
}

auto cols(const auto &mat) -> std::string
{
    return std::to_string(mat.cols());
}

auto shape(const auto &mat) -> std::string
{
    return "(" + rows(mat) + ", " + cols(mat) + ")";
}

void view(const auto &mat, std::string label)
{
    std::cout << std::string(label.size(), '-') << "\n"
              << label                          << "\n"
              << "Shape:" << shape(mat)         << "\n"
              << "Size :" << mat.size()         << "\n"
              << std::string(label.size(), '-') << "\n"
              << mat                            << "\n";
}

void fit(auto &mat, std::function<double(double, double, double)> func)
{
    for (int row = 0; row < mat.rows(); ++row) {
        for (int col = 0; col < mat.cols(); ++col) {
            mat(row, col) = func(row, col, 0.1);
        }
    }
}

template<typename T>
void border(auto &matrix, const auto &mat, T value, int width = 1)
{
    if (width < 1) {
        std::cerr << "Invalid border width!\n";
        return;
    }

    matrix.resize(mat.rows() +  2 * width, mat.cols() + 2 * width);
    matrix.setConstant(value);
    for (int row = 0; row < mat.rows(); ++row) {
        for (int col = 0; col < mat.cols(); ++col) {
            matrix(row + width, col + width) = mat(row, col);
        }
    }
}

#endif // FUNCTIONS_H
