#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <eigen3/Eigen/Core>
#include <opencv4/opencv2/opencv.hpp>

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

void fit(auto &matrix, std::function<double(double, double, double)> func)
{
    for (int row = 0; row < matrix.rows(); ++row) {
        for (int col = 0; col < matrix.cols(); ++col) {
            matrix(row, col) = func(row, col, 0.1);
        }
    }
}

template<typename T>
void border(auto &matrix, const auto &matrixBase, T value, int width = 1)
{
    if (width < 1) {
        std::cerr << "Invalid border width!\n";
        return;
    }

    matrix.resize(matrixBase.rows() +  2 * width, matrixBase.cols() + 2 * width);
    matrix.setConstant(value);
    for (int row = 0; row < matrixBase.rows(); ++row) {
        for (int col = 0; col < matrixBase.cols(); ++col) {
            matrix(row + width, col + width) = matrixBase(row, col);
        }
    }
}

void vecStr2matrix(auto &matrix, std::vector<std::vector<std::string> > vector2D)
{
    if (vector2D.empty()) {
        std::cerr << "Vector 2D of strings is empty!\n";
        return;
    }

    // Analyze
    int maxCols{0};
    for (auto row : vector2D) {
        maxCols = row.size() >= maxCols ? row.size() : maxCols;
    }

    // Fill
    matrix.resize(vector2D.size(), maxCols);
    matrix.setZero();
    for (int row = 0; row < vector2D.size(); ++row) {
        for (int col = 0; col < vector2D.at(row).size(); ++col) {
            try {
                matrix(row, col) = stod(vector2D[row][col]);
            }
            catch (...) {
                // Fill in with zero if non-numeric value.
                matrix(row, col) = 0;
            }
        }
    }
}

void cv2eigen(auto &matrix, const cv::Mat &matrixBase)
{
    int rows = matrixBase.rows;
    int cols = matrixBase.cols;
    int channels = matrixBase.channels();
    int dims = matrixBase.dims; // Dimensionality.

    if (dims > 2) {
        std::cerr << "Conversion not recommended!\n";
        return;
    }

    matrix.resize(rows, cols * channels);
    matrix.setZero();
    for (int row = 0; row < rows; ++row) {
        auto *ptr = matrixBase.ptr(row);
        for (int col = 0; col < cols * channels; ++col) {
            matrix(row, col) = *ptr++;
        }
    }
}

auto loadCSV(const std::string &filename, char delimiter = ',') -> std::vector<std::vector<std::string> >
{
    std::vector<std::vector<std::string> > table;
    try {
        std::ifstream fIn(filename, std::ios::in);
        if (fIn.is_open()) {
            std::string line{};
            while (getline(fIn, line)) {
                std::vector<std::string> row;
                std::string str{};
                for (auto character : line) {
                    if (character == delimiter) {
                        row.emplace_back(str);
                        str.clear();
                    }
                    else {
                        str.push_back(character);
                    }
                }
                if (!str.empty()) {
                    row.emplace_back(str);
                }
                table.emplace_back(row);
            }
            fIn.close();
        }
    }
    catch (...) {
        std::cerr << "There was something wrong while loading the file!\n";
    }

    return table;
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
