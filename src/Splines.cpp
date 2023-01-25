#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>
#include "Splines.h"
using namespace std;

/**
 * @brief Construct a new Cubic Splines:: Cubic Splines object
 *
 * @param x_vector
 * @param y_vector
 */
CubicSplines::CubicSplines(const vector<double> &x_vector, const vector<double> &y_vector)
    : x_vector_(x_vector), y_vector_(y_vector)
{
    cout << "cubic spline class \n";
}

/**
 * @brief it is traditional algorithm for variables colculation in triadigonal case
 *
 */
void CubicSplines::tridiagonalMatrixAlgorithm()
{
    auto size = x_vector_.size();
    //Вычисление прогоночных коэффициентов - прямой ход метода прогонки

    vector<double> alpha(size - 1, 0);
    vector<double> beta(size - 1, 0);
    double A, B, C, F, h_i, h_i1, z;

    alpha[0] = beta[0] = 0.;
    for (std::size_t i = 1; i < size - 1; ++i)
    {
        h_i = x_vector_[i] - x_vector_[i - 1];
        h_i1 = x_vector_[i + 1] - x_vector_[i];
        A = h_i;
        C = 2. * (h_i + h_i1);
        B = h_i1;
        F = 6. * ((y_vector_[i + 1] - y_vector_[i]) / h_i1 -
                  (y_vector_[i] - y_vector_[i - 1]) / h_i);
        z = (A * alpha[i - 1] + C);
        alpha[i] = -B / z;
        beta[i] = (F - A * beta[i - 1]) / z;
    }

    (*splines_)[size - 1].c_ =
        (F - A * beta[size - 2]) / (C + A * alpha[size - 2]);

    // Нахождение решения - обратный ход метода прогонки
    for (std::size_t i = size - 2; i > 0; --i)
        (*splines_)[i].c_ = alpha[i] * (*splines_)[i + 1].c_ + beta[i];
}
void CubicSplines::interpolate()
{
    auto size = x_vector_.size();
    spline_tuple s_t{0, 0, 0, 0, 0};
    std::cout << "x_vector size " << x_vector_.size();
    splines_ = make_shared<vector<spline_tuple>>(x_vector_.size(), s_t);

    for (std::size_t i = 0; i < size; ++i)
    {
        (*splines_)[i].x_ = x_vector_[i];
        (*splines_)[i].a_ = y_vector_[i];
    }
    (*splines_)[0].c_ = 0.;

    tridiagonalMatrixAlgorithm();

    // По известным коэффициентам c[i] находим значения b[i] и d[i]
    for (std::size_t i = size - 1; i > 0; --i)
    {
        double h_i = x_vector_[i] - x_vector_[i - 1];
        (*splines_)[i].d_ = ((*splines_)[i].c_ -
                             (*splines_)[i - 1].c_) /
                            h_i;
        (*splines_)[i].b_ = h_i * (2. * (*splines_)[i].c_ + (*splines_)[i - 1].c_) / 6. +
                            (y_vector_[i] - y_vector_[i - 1]) / h_i;
    }

       std::cout << "splines_ size " << splines_->size();
}

double CubicSplines::calculateFunctionValue(double x)
{
    auto size = x_vector_.size();

    if (splines_ == nullptr)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    // Если сплайны ещё не построены - возвращаем NaN

    vector<spline_tuple>::iterator iter = splines_->begin();
    // spline_tuple *s;

    if (x <= (*splines_)[0].x_) // Если x меньше точки сетки x[0] - пользуемся первым эл-том массива
        iter++;
    else if (x >= (*splines_)[size - 1].x_)
        // Если x больше точки сетки x[n - 1] - пользуемся последним эл-том массива
        iter += size - 1;
    else // Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
    {
        std::size_t i = 0;
        std::size_t j = size - 1;
        while (i + 1 < j)
        {
            std::size_t k = i + (j - i) / 2;
            if (x <= (*splines_)[k].x_)
                j = k;
            else
                i = k;
        }
        iter += j;
    }

    double dx = (x - iter->x_);
    return iter->a_ + (iter->b_ +
                       (iter->c_ / 2. + iter->d_ * dx / 6.) * dx) *
                          dx;
    // Вычисляем значение сплайна в заданной точке.


}
