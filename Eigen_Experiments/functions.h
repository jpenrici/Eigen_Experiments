#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <eigen3/Eigen/Core>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
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

auto toStr(const auto &mat, std::string label = "Matrix") -> std::string
{
    std::stringstream ss;
    Eigen::IOFormat HeavyFmt(Eigen::FullPrecision, 0, ", ", ",\n", "[", "]", "[", "]");

    if (!label.empty()) {
        ss << std::string(label.size(), '-') << "\n"
           << label                          << "\n";
    }

    ss << "Shape:" << shape(mat)         << "\n"
       << "Size :" << mat.size()         << "\n"
       << std::string(label.size(), '-') << "\n"
       << mat.format(HeavyFmt)           << "\n";

    return ss.str();
}

void view(const auto &mat, std::string label = "")
{
    std::cout << toStr(mat, label);
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

void save(const std::string &filename, std::string text, bool view = true)
{
    if (text.empty()) {
        std::cerr << "Text empty!\n";
        return;
    }

    try {
        std::fstream fs(filename, std::fstream::in | std::fstream::out | std::fstream::app);
        if (fs.is_open()) {
            fs << text;
        }
        fs.close();
        if (view) {
            std::cout << text << "\n";
        }
        std::cout << "Saved: " << filename << "\n";
    }
    catch (...) {
        std::cerr << "There was something wrong while saving the file!\n";
    }
}

#endif // FUNCTIONS_H
