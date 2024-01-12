// Reference:
//  https://docs.opencv.org/4.x/dd/d49/tutorial_py_contour_features.html

#include "../../functions.h"

#include <opencv4/opencv2/imgproc.hpp>

void opencv_test();

auto main() -> int
{
    std::cout << "Simple Help/Test with Eigen ...\n";

    opencv_test();

    return EXIT_SUCCESS;
}

void opencv_test()
{
    cv::Mat image;
    image = cv::imread("Resources/plant.png", cv::IMREAD_GRAYSCALE);

    cv::Mat thresh;
    cv::threshold(image, thresh, 127, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresh, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    // Moments
    auto cnt = contours.front();
    auto M = cv::moments(cnt);

    // Centroid
    auto cx = int(M.m10 / M.m00);
    auto cy = int(M.m01 / M.m00);

    // Area, Perimeter
    auto area = cv::contourArea(cnt);
    auto perimeter = cv::arcLength(cnt, true);

    std::cout << "Image    : " << image.rows  << " x " << image.cols << " x " << image.channels() << "\n";
    std::cout << "Threshold: " << thresh.rows << " x " << thresh.cols << " x " << thresh.channels() << "\n";
    std::cout << "Centroid : " << cx << "," << cy << "\n";
    std::cout << "Area     : " << area << " (" << (area * 100) / (image.rows * image.cols) << "%)\n";
    std::cout << "Perimeter: " << perimeter << "\n";

    Eigen::MatrixXd matrix;
    matrix.resize(thresh.rows, thresh.cols);
    matrix.setZero();
    for (auto points : contours) {
        for (auto point : points) {
            matrix(point.y, point.x) = 1;
        }
    }
    matrix(cy, cx) = 2;

    //save("contours.txt", toStr(matrix, "Contours"), false);
    saveCSV(matrix, "contours.csv");
}
