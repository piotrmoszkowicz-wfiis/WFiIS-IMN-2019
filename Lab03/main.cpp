//
// Created by Piotr Moszkowicz on 20/11/2019.
//

#include <array>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

#include "../utils/files_operations.h"

double g(double alpha, double x, double v) {
    return alpha * (1.0 - std::pow(x, 2.0)) * v - x;
}

std::tuple<double, double> count_by_rk2(double x, double v, double delta_t, double alpha) {
    const double k1_x = v;
    const double k1_v = g(alpha, x, v);

    const double k2_x = v + delta_t * k1_v;
    const double k2_v = g(alpha, x + delta_t * k1_x, v + delta_t * k1_v);

    return {
            x + (delta_t / 2.0) * (k1_x + k2_x),
            v + (delta_t / 2.0) * (k1_v + k2_v)
    };
}

std::tuple<double, double> count_by_trapez(double x, double v, double delta_t, double alpha) {
    const double delta = std::pow(10.0, -10.0);

    double x_next = x;
    double v_next = v;

    while (true) {
        const double f = x_next - x - (delta_t / 2.0) * (v + v_next);
        const double g = v_next - v - (delta_t / 2.0) * ((alpha * (1 - std::pow(x, 2.0)) * v - x) +
                                                         (alpha * (1 - std::pow(x_next, 2.0)) * v_next - x_next));

        std::array<std::array<double, 2>, 2> A{};

        A[0][0] = 1.0;
        A[0][1] = -delta_t / 2.0;
        A[1][0] = -delta_t / 2.0 * (-2.0 * alpha * x_next * v_next - 1.0);
        A[1][1] = 1.0 - (delta_t / 2.0) * alpha * (1.0 - std::pow(x_next, 2.0));

        const double divider = A[0][0] * A[1][1] - A[0][1] * A[1][0];

        const double delta_x = (-f * A[1][1] - (-g) * A[0][1]) / divider;
        const double delta_v = (A[0][0] * (-g) - A[1][0] * (-f)) / divider;

        x_next += delta_x;
        v_next += delta_v;

        if (delta_x < delta && delta_v < delta) {
            break;
        }
    }

    return {
            x_next,
            v_next
    };
}

void rk2() {
    const std::vector<double> TOL = {
            std::pow(10.0, -2.0),
            std::pow(10.0, -5.0)
    };

    const double S = 0.75;
    const double p = 2.0;
    const double T_MAX = 40.0;
    const double ALPHA = 5.0;


    for (auto current_tol : TOL) {
        double x = 0.01;
        double v = 0.0;
        double delta_t = 1.0;
        double t = 0.0;
        std::string fileName = "1_rk2_results_";
        fileName += std::to_string(current_tol);
        fileName += ".dat";

        clearFile(fileName);

        while (t < T_MAX) {
            const auto next_1_step_first = count_by_rk2(x, v, delta_t, ALPHA);
            const auto next_1_step_second = count_by_rk2(std::get<0>(next_1_step_first), std::get<1>(next_1_step_first), delta_t, ALPHA);

            const auto next_2_step = count_by_rk2(x, v, 2.0 * delta_t, ALPHA);

            const double err_x = (std::get<0>(next_1_step_second) - std::get<0>(next_2_step)) / (std::pow(2, p) - 1.0);
            const double err_v = (std::get<1>(next_1_step_second) - std::get<1>(next_2_step)) / (std::pow(2, p) - 1.0);

            const double max_err = std::max(std::abs(err_x), std::abs(err_v));

            if (max_err < current_tol) {
                t += 2 * delta_t;
                x = std::get<0>(next_1_step_second);
                v = std::get<1>(next_1_step_second);
                saveResults(fileName, t, delta_t, x, v);
            }

            delta_t *= std::pow((S * current_tol) / max_err, (1.0 / (p + 1.0)));
        }
    }
}

void trapez() {
    const std::vector<double> TOL = {
            std::pow(10.0, -2.0),
            std::pow(10.0, -5.0)
    };

    const double S = 0.75;
    const double p = 2.0;
    const double T_MAX = 40.0;
    const double ALPHA = 5.0;

    for (auto current_tol : TOL) {
        double x = 0.01;
        double v = 0.0;
        double delta_t = 1.0;
        double t = 0.0;
        std::string fileName = "1_rk2_results_";
        fileName += std::to_string(current_tol);
        fileName += ".dat";

        clearFile(fileName);

        while (t < T_MAX) {
            const auto next_1_step_first = count_by_rk2(x, v, delta_t, ALPHA);
            const auto next_1_step_second = count_by_rk2(std::get<0>(next_1_step_first), std::get<1>(next_1_step_first), delta_t, ALPHA);

            const auto next_2_step = count_by_rk2(x, v, 2.0 * delta_t, ALPHA);

            const double err_x = (std::get<0>(next_1_step_second) - std::get<0>(next_2_step)) / (std::pow(2, p) - 1.0);
            const double err_v = (std::get<1>(next_1_step_second) - std::get<1>(next_2_step)) / (std::pow(2, p) - 1.0);

            const double max_err = std::max(std::abs(err_x), std::abs(err_v));

            if (max_err < current_tol) {
                t += 2 * delta_t;
                x = std::get<0>(next_1_step_second);
                v = std::get<1>(next_1_step_second);
                saveResults(fileName, t, delta_t, x, v);
            }

            delta_t *= std::pow((S * current_tol) / max_err, (1.0 / (p + 1.0)));
        }
    }
}

int main() {
    rk2();
    trapez();
    return 0;
}