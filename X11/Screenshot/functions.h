#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <eigen3/Eigen/Core>

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>


auto rows(const auto &matrix) -> std::string
{
    return std::to_string(matrix.rows());
}

auto cols(const auto &matrix) -> std::string
{
    return std::to_string(matrix.cols());
}

auto shape(const auto &matrix) -> std::string
{
    return "(" + rows(matrix) + ", " + cols(matrix) + ")";
}

auto toStr(const auto &matrix, std::string label = "Matrix") -> std::string
{
    std::stringstream ss;
    Eigen::IOFormat HeavyFmt(Eigen::FullPrecision, 0, ", ", ",\n", "[", "]", "[", "]");

    if (!label.empty()) {
        ss << std::string(label.size(), '-') << "\n"
           << label                          << "\n";
    }

    ss << "Shape: " << shape(matrix)         << "\n"
       << "Size : " << matrix.size()         << "\n"
       << std::string(label.size(), '-')     << "\n"
       << matrix.format(HeavyFmt)            << "\n";

    return ss.str();
}

void view(const auto &matrix, std::string label = "")
{
    std::cout << toStr(matrix, label);
}

void vec2matrix(Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic> &matrix,
                const std::vector<uint8_t> &values, int &width, int &height)
{
    if (values.empty()) {
        std::cerr << "Vector is empty!\n";
        return;
    }

    if (width < 1 || height < 1 || values.size() < (width * height)) {
        std::cerr << "Invalid dimensions!\n";
        return;
    }

    // Fill
    matrix.resize(height, width);
    matrix.setZero();
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            try {
                matrix(row, col) = values.at(row * width + col);
            }
            catch (...) {
                // Fill in with zero if non-numeric value.
                matrix(row, col) = 0;
            }
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
            fs << text; // Append text at the end of the file.
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

void saveCSV(const auto &matrix, const std::string &filename, char delimiter = ',')
{
    std::stringstream ss;
    Eigen::IOFormat csvFmt(Eigen::FullPrecision, 0, {delimiter}, "\n");
    ss << matrix.format(csvFmt);

    save(filename, ss.str(), false);
}

#endif // FUNCTIONS_H
