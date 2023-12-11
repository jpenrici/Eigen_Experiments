#include "functions.h"


void test();

auto main() -> int
{
    std::cout << "Simple Help/Test with Eigen ...\n";

    test();

    return EXIT_SUCCESS;
}

void test()
{
    Eigen::VectorXd v1(3);
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

