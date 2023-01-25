#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Extrapolation.h"

using namespace std;

/**
 * @brief To extrapolate curve in the begining spline
 *
 * @param first_x
 * @param first_y
 * @param second_y
 * @param dx
 * @return ExponentExtrapolation::
 */
ExponentExtrapolation::ExponentExtrapolation(double first_x, double first_y, double second_y, double dx)
    : first_x_(first_x), first_y_(first_y), second_y_(second_y), dx_(dx) {}

void ExponentExtrapolation::extrapolate()
{
    cout << "first_x_ " << first_x_ << " \n";
    cout << "first_y_ " << first_y_ << " \n";
    cout << "second_y_ " << second_y_ << " \n";

    double derivative_value = (second_y_ - first_y_) / dx_;
    b_coeff_ = -0.5 / first_x_ * derivative_value / first_y_;
    a_coeff_ = first_y_ * exp(b_coeff_ * first_x_ * first_x_);

    cout << " b_coeff_ " << b_coeff_ << " \n";
    cout << " a_coeff_ " << a_coeff_ << " \n";

    cout << "hey hey!\n";
}
