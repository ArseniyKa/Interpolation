#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>

#include <algorithm> // std::min_element
#include <iterator>  // std::begin, std::end
using namespace std;

class ExponentExtrapolation
{
public:
    ExponentExtrapolation(double first_x, double first_y, double second_y, double dx)
        : first_x_(first_x), first_y_(first_y), second_y_(second_y), dx_(dx) {}

    void extrapolate()
    {
        cout << "first_x_ " << first_x_ << " \n";
        cout << "first_y_ " << first_y_ << " \n";
        cout << "second_y_ " << second_y_ << " \n";

        double derivative_value = (second_y_ - first_y_ ) / dx_;
        cout << "derivative_value " << derivative_value << " \n";
        b_coeff_ = -0.5 / first_x_ * derivative_value / first_y_;
        a_coeff_ = first_y_ * exp(b_coeff_ * first_x_ * first_x_);

        cout << " b_coeff_ " << b_coeff_ << " \n";
        cout << " a_coeff_ " << a_coeff_ << " \n";
    }

    double a_coeff_{0};
    double b_coeff_{0};

private:
    double first_x_{0};
    double first_y_{0};
    double second_y_{0};
    double dx_{0};
};