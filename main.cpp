
#include <fstream>
#include <vector>
#include <iostream>
#include "Splines.h"
#include "Extrapolation.h"
#include <stdint.h>
#include <algorithm>

#include <boost/assign.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <omp.h>
#include <qt5/QtCore/QDebug>
#include<qt5/QtCore/QString>

// #include <boost/assign/list_inserter.hpp>
// #include <boost/assert.hpp>
using namespace boost::assign;
using namespace std;
// using namespace boost::numeric::ublas;

/**
 * @brief main function
 *
 * @return int
 */
int main()
{
    QString str = "What are you doing?";
    qDebug() << str;

    boost::numeric::ublas::matrix<double> m(3, 3);
    for (unsigned i = 0; i < m.size1(); ++i){
        for (unsigned j = 0; j < m.size2(); ++j)
            m(i, j) = 3 * i + j;
    }
    std::cout << m << std::endl;


   boost::numeric::ublas:: matrix<double> bu(3, 3);
    for (unsigned i = 0; i < bu.size1(); ++i){
        for (unsigned j = 0; j < bu.size2(); ++j)
            bu(i, j) = i + 5;
    }
    std::cout << bu << std::endl;

    auto cc = m - bu;
       std::cout << cc << std::endl;

    vector<double> a, b;

    fstream file;
    file.open("sample.txt", ios::in);
    if (!file)
    {
        cout << "Error" << endl;
        return 0;
    }

    int number_of_lines = 0;

    double ai, bi;
    while (file >> ai >> bi)
    {
        a.push_back(ai);
        b.push_back(bi);
        number_of_lines++;
    }
    vector<double> x_vec(number_of_lines, 0);
    vector<double> y_vec(number_of_lines, 0);

    for (int i = 0; i < number_of_lines; i++)
    {
        x_vec[i] = a[number_of_lines - 1 - i];
        y_vec[i] = b[number_of_lines - 1 - i];
    }
    /**
     * @brief create cubic Splines
     *
     * @return CubicSplines
     */
    CubicSplines spl(x_vec, y_vec);
    spl.interpolate();

    double max_value = *std::max_element(x_vec.begin(), x_vec.end());
    // std::cout << "max_value " << max_value << "\n";

    std::cout << "spline  a " << (*spl.splines_)[0].a_ << "\n";
    std::cout << "spline  c " << (*spl.splines_)[0].c_ << "\n";
    // for (auto elem : (*spl.splines_))
    // {
    //     cout << elem.a_ << ", " << elem.b_ << ", " << elem.c_ << ", " << elem.d_ << "\n--------------\n";
    // }

    const int64_t n = 100000;
    double dx = 1 / static_cast<double>(n);
    vector<double> new_x(n, 0);
    vector<double> new_y(n, 0);

    for (int64_t i = 0; i <= n; i++)
    {
        new_x[i] = dx * i;
        new_y[i] = spl.calculateFunctionValue(new_x[i]);
    }

    ////////////// Extrapolation
    // auto second_value = spl.calculateFunctionValue(x_vec[0] + dx);
    // ExponentExtrapolation extr(x_vec[0], y_vec[0], second_value, dx);
    // extr.extrapolate();

    // const int64_t extrapolate_number = 100;
    // double sub_dx = x_vec[0] / extrapolate_number;

    // vector<double> sub_new_x(extrapolate_number, 0);
    // vector<double> sub_new_y(extrapolate_number, 0);

    // auto a_coeff = extr.a_coeff_;
    // auto b_coeff = extr.b_coeff_;
    // for (int64_t i = 0; i < extrapolate_number; i++)
    // {
    //     sub_new_x[i] = sub_dx * i;
    //     sub_new_y[i] = a_coeff * exp(-b_coeff * sub_dx * i * sub_dx * i);
    // }

    ofstream fout("write_ceramic_interpolation2.txt");
    // for (int64_t i = 0; i < extrapolate_number; ++i)
    // {
    //     fout << sub_new_x[i] << "                   " << sub_new_y[i] << "\n";
    // }

    for (int64_t i = 0; i <= n; ++i)
    {
        if (new_x[i] >= x_vec[0])
        {
            fout << new_x[i] << "                   " << new_y[i] << "\n";
        }
    }
    fout.close();
}
