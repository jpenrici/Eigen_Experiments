#include "functions.h"

auto main() -> int
{
    std::cout << "Simple Help/Test with Eigen ...\n";

    Eigen::VectorXd v1(3);
    view(v1, "VectorXd");
    view(v1.transpose(), "VectorXd.transpose");

    Eigen::MatrixXi m1(3, 2);
    m1 << 0, 1, 2, 3, 4, 5;
    view(m1, "MatrixXi");
    view(m1.transpose(), "MatrixXi.transpose");

    Eigen::MatrixXd m2(4, 4);
    m2.setConstant(-1.1);
    view(m2, "MatrixXd");

    std::function<double(double, double, double)> sumDoubles = [](double a, double b, double c) {
        return a + b + c;
    };

    m2.setConstant(sumDoubles(1, 2, 3));
    view(m2, "MatrixXd");

    fit(m2, sumDoubles);
    view(m2, "MatrixXd");

    Eigen::VectorXi v2(3);
    v2.setOnes();
    view(v2, "VectorXi");

    Eigen::MatrixXd m3;
    border(m3, v2, 0);
    view(m3, "MatrixXd");

    border(m3, v2.transpose(), 0);
    view(m3, "MatrixXd");

    return 0;
}

