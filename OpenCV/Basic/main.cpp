#include "functions.h"


void basic_test();
void csv_test();
void opencv_test();

auto main() -> int
{
    std::cout << "Simple Help/Test with Eigen ...\n";

    basic_test();
    csv_test();
    opencv_test();

    return EXIT_SUCCESS;
}

void opencv_test()
{
    cv::Mat m1;
    m1.create(2, 4, CV_8UC(5));
    for (int i = 0; i < m1.rows * m1.cols * m1.channels(); ++i) {
        m1.at<uchar>(i) = i + 1;
    }

    auto fmt = cv::Formatter::FMT_PYTHON;
    std::cout << format(m1, fmt) << "\n";
    std::cout << "Shape: (" << m1.rows << ", " << m1.cols << ", " << m1.channels() << ")\n";

    Eigen::MatrixXd m2;
    cv2eigen(m2, m1);
    view(m2, "MatrixXd");

    cv::Mat image;
    image = cv::imread("Resources/image.png");

    std::cout << "Image:\n";
    //std::cout << format(image, fmt) << "\n";
    std::cout << "Shape: (" << image.rows << ", " << image.cols << ", " << image.channels() << ")\n";

    //cv::imshow("Display Image", image);
    //cv::waitKey(0);

    cv2eigen(m2, image);
    save("image.txt", toStr(m2, "image.png"), false);
    saveCSV(m2, "image.csv");
}

void csv_test()
{
    auto csv = loadCSV("Resources/table.csv");

    Eigen::MatrixXi m1;
    vecStr2matrix(m1, csv);
    view(m1, "MatrixXi");

    Eigen::MatrixXd m2;
    vecStr2matrix(m2, csv);
    view(m2, "MatrixXd");

    saveCSV(m2, "output.csv");
}

void basic_test()
{
    Eigen::VectorXd v1(3);
    v1.setOnes();
    view(v1);
    save("output.txt", toStr(v1, "VectorXd"));
    save("output.txt", toStr(v1.transpose(), "VectorXd.transpose"));

    Eigen::MatrixXi m1(3, 2);
    m1 << 0, 1, 2, 3, 4, 5;
    save("output.txt", toStr(m1, "MatrixXi"));
    save("output.txt", toStr(m1.transpose(), "MatrixXi.transpose"));

    Eigen::MatrixXd m2(4, 4);
    m2.setConstant(-1.1);
    save("output.txt", toStr(m2, "MatrixXd"));

    std::function<double(double, double, double)> sumDoubles = [](double a, double b, double c) {
        return a + b + c;
    };

    m2.setConstant(sumDoubles(1, 2, 3));
    save("output.txt", toStr(m2, "MatrixXd"));

    fit(m2, sumDoubles);
    save("output.txt", toStr(m2, "MatrixXd"));

    Eigen::VectorXi v2(3);
    v2.setOnes();
    save("output.txt", toStr(v2, "VectorXi"));

    Eigen::MatrixXd m3;
    border(m3, v2, 0);
    save("output.txt", toStr(m3, "MatrixXd"));

    border(m3, v2.transpose(), 0);
    save("output.txt", toStr(m3, "MatrixXd.transpose"));
}
