#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/**
 * @brief Класс экстраполяции
 *
 */
class ExponentExtrapolation
{
public:
    /**
     * @brief Construct a new Exponent Extrapolation object
     *
     * @param first_x
     * @param first_y
     * @param second_y
     * @param dx
     */
    ExponentExtrapolation(double first_x, double first_y, double second_y, double dx);

    void extrapolate();

    double a_coeff_{0};
    double b_coeff_{0};

private:
    double first_x_{0};
    double first_y_{0};
    double second_y_{0};
    double dx_{0};
};