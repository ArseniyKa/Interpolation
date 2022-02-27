
#include <fstream>
#include <vector>
#include <iostream>
#include "Splines.h"
#include "Extrapolation.h"
#include <stdint.h>
using namespace std;

int main()
{
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

    CubicSplines spl(x_vec, y_vec);
    spl.interpolate();

    const int64_t n = 100000;
    double dx = 1. / static_cast<double>(n);
    vector<double> new_x(n, 0);
    vector<double> new_y(n, 0);

    for (int64_t i = 0; i <= n; i++)
    {
        new_x[i] = dx * i;
        new_y[i] = spl.calculateFunctionValue(new_x[i]);
    }

    auto second_value = spl.calculateFunctionValue(x_vec[0] + dx);
    ExponentExtrapolation extr(x_vec[0], y_vec[0], second_value, dx);
    extr.extrapolate();

    const int64_t extrapolate_number = 100;
    double sub_dx = x_vec[0] / extrapolate_number;

    vector<double> sub_new_x(extrapolate_number, 0);
    vector<double> sub_new_y(extrapolate_number, 0);

    auto a_coeff = extr.a_coeff_;
    auto b_coeff = extr.b_coeff_;
    for (int64_t i = 0; i < extrapolate_number; i++)
    {
        sub_new_x[i] = sub_dx * i;
        sub_new_y[i] = a_coeff * exp(-b_coeff * sub_dx * i * sub_dx * i);
    }

    ofstream fout("write_extrapolation.txt");
    for (int64_t i = 0; i < extrapolate_number; ++i)
    {
        fout << sub_new_x[i] << "                   " << sub_new_y[i] << "\n";
    }

    for (int64_t i = 0; i <= n; ++i)
    {
        if (new_x[i] >= x_vec[0])
        {
            fout << new_x[i] << "                   " << new_y[i] << "\n";
        }
    }
    fout.close();
}