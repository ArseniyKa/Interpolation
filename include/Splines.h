#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>
using namespace std;

class CubicSplines
{

    /**
     * @brief  Структура, описывающая сплайн на каждом сегменте сетки
     *
     */
    struct spline_tuple
    {
        double a_;
        double b_;
        double c_;
        double d_;

        double x_;
    };

public:
    /**
     * @brief Construct a new Cubic Splines object Создать кубический сплайн для интерполяции
     *
     * @param x_vector
     * @param y_vector
     */
    CubicSplines(const vector<double> &x_vector, const vector<double> &y_vector);

    /**
     * @brief Решение СЛАУ относительно коэффициентов сплайнов c[i] методом прогонки для трехдиагональных матриц
    //
     *
     */
    void tridiagonalMatrixAlgorithm();
    /**
     * @brief Главная функция для интерполяции
     *
     */
    void interpolate();

    void vector1();
    void vector2();


    /**
     * @brief Вычислить значение  интерполяционной кривой по заданному x
     *
     * @param x
     * @return double
     */
    double calculateFunctionValue(double x);

public:
    /**
     * @brief Вектор в котором хранятся коэффициенты сплайна
     *
     */
    shared_ptr<vector<spline_tuple>> splines_; // Сплайн
    /**
     * @brief Здесь хранятся абсциссы исходных точек дискретной функции
     *
     */
    vector<double> x_vector_;
    /**
     * @brief Здесь хранятся ординаты исходных точек дискретной функции
     *
     */
    vector<double> y_vector_;
};