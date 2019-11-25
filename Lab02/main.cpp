//
// Created by Piotr Moszkowicz on 11/11/2019.
//

#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../utils/files_operations.h"

double count(double alfa, double beta, double x) {
    return alfa * x - beta * std::pow(x, 2);
}

void trapezy() {
    constexpr double beta = 0.001;
    constexpr int N = 500;
    constexpr double gamma = 0.1;
    constexpr int t_max = 100;
    constexpr double delta_t = 0.1;
    const double TOL = std::pow(10, -6);
    constexpr int MI = 20;
    constexpr int ITERATIONS = t_max / delta_t;
    constexpr double alfa = (beta * N) - gamma;

    std::vector<double> picard_results;
    std::vector<double> newton_results;

    std::string fileName1 = "1_picard_results.dat";
    std::string fileName2 = "1_newton_results.dat";

    clearFile(fileName1);
    clearFile(fileName2);

    // Picard
    picard_results.push_back(1.0);
    saveResults(fileName1, 0.0, 1.0, N - 1.0);
    for (int i = 1; i <= ITERATIONS; i++) {
        int actual_mi = 0;
        double u_n_1_mi_prev = picard_results[i - 1];
        double u_n_1_mi_now = 10.0;

        while (true) {
            if (std::abs(u_n_1_mi_now - u_n_1_mi_prev) < TOL || actual_mi > MI) {
                break;
            }
            if (actual_mi != 0) {
                u_n_1_mi_prev = u_n_1_mi_now;
            }
            u_n_1_mi_now = picard_results[i - 1] + (delta_t / 2.0) * (count(alfa, beta, picard_results[i - 1]) +
                                                                      count(alfa, beta, u_n_1_mi_prev));
            std::cout << "U_n_1_mi_now=" << u_n_1_mi_now << " MI: " << actual_mi << std::endl;
            actual_mi++;
        }
        picard_results.push_back(u_n_1_mi_now);
        std::cout << "Iter: " << i << " > " << picard_results[i] << std::endl;
        saveResults(fileName1, i * delta_t, picard_results[i], N - picard_results[i]);
    }

    // Newton
    newton_results.push_back(1.0);
    saveResults(fileName2, 0.0, 1.0, N - 1.0);

    for (int i = 1; i <= ITERATIONS; i++) {
        int actual_mi = 0;
        double u_n_1_mi_prev = newton_results[i];
        double u_n_1_mi_now = 10.0;

        while (true) {
            if (std::abs(u_n_1_mi_now - u_n_1_mi_prev) < TOL || actual_mi > MI) {
                break;
            }
            if (actual_mi != 0) {
                u_n_1_mi_prev = u_n_1_mi_now;
            }
            u_n_1_mi_now = u_n_1_mi_prev - (u_n_1_mi_prev - newton_results[i - 1] -
                                            (delta_t / 2.0) * (count(alfa, beta, picard_results[i - 1]) +
                                                               count(alfa, beta, u_n_1_mi_prev)));
            std::cout << "U_n_1_mi_now=" << u_n_1_mi_now << " MI: " << actual_mi << std::endl;
            actual_mi++;
        }
        picard_results.push_back(u_n_1_mi_now);
        std::cout << "Iter: " << i << " > " << picard_results[i] << std::endl;
        saveResults(fileName2, i * delta_t, picard_results[i], N - picard_results[i]);
    }
}

void rk2() {
    constexpr double beta = 0.001;
    constexpr int N = 500;
    constexpr double gamma = 0.1;
    constexpr int t_max = 100;
    constexpr double delta_t = 0.1;
    const double TOL = std::pow(10, -6);
    constexpr int MI = 20;
    constexpr int ITERATIONS = t_max / delta_t;
    constexpr double alfa = (beta * N) - gamma;

    const double a[2][2] = {
            {
                    0.25, 0.25 - (std::sqrt(3) / 6.0)
            },
            {
                    0.25 + (std::sqrt(3) / 6.0), 0.25
            }
    };

    constexpr double b[2] = {
            0.5, 0.5
    };

    const double c[2] = {
            0.5 - (std::sqrt(3) / 6.0),
            0.5 + (std::sqrt(3) / 6.0)
    };

    auto count_f1 = [&a, &delta_t, &alfa, &beta](double U1, double U2, double u) {
        return U1 - u - (delta_t * (a[0][0] * count(alfa, beta, U1) + a[0][1] * count(alfa, beta, U2)));
    };

    auto count_f2 = [&a, &delta_t, &alfa, &beta](double U1, double U2, double u) {
        return U2 - u - (delta_t * (a[1][0] * count(alfa, beta, U1) + a[1][1] * count(alfa, beta, U2)));
    };

    auto count_m = [&a, &delta_t, &alfa, &beta](int i, int j, double u) {
        double res = (-delta_t) * a[i][j] * (alfa - 2.0 * beta * u);
        if (i == j) {
            res += 1.0;
        }
        return res;
    };

    std::vector<double> rk2_results;

    std::string fileName1 = "2_rk2_results.dat";

    rk2_results.push_back(1.0);

    for (int i = 1; i <= ITERATIONS; i++) {
        std::vector<double> U1{};
        std::vector<double> U2{};
        U1.push_back(rk2_results[i - 1]);
        U2.push_back(rk2_results[i - 1]);
        int actual_mi = 0;
        while (true) {
            if (U1[actual_mi] < TOL || U2[actual_mi] < TOL || actual_mi > MI) {
                break;
            }

            const double m[2][2] = {
                    {
                            count_m(0, 0, U1[actual_mi]), count_m(0, 1, U2[actual_mi])
                    },
                    {
                            count_m(1, 0, U1[actual_mi]), count_m(1, 1, U2[actual_mi])
                    }
            };

            const double F1 = count_f1(U1[actual_mi], U2[actual_mi], rk2_results[i - 1]);
            const double F2 = count_f2(U1[actual_mi], U2[actual_mi], rk2_results[i - 1]);
            const double divider = (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
            const double delta_U1 = ((F2 * m[0][1]) - (F1 * m[1][1])) / divider;
            const double delta_U2 = ((F1 * m[1][0]) - (F2 * m[0][0])) / divider;

            U1.push_back(U1[actual_mi] + delta_U1);
            U2.push_back(U2[actual_mi] + delta_U2);

            actual_mi++;
        }

        double u_result = rk2_results[i - 1] + delta_t * (b[0] * count(alfa, beta, U1[(int) (c[0] * delta_t)]) +
                                                          b[1] * count(alfa, beta, U2[i + (int) (c[1] * delta_t)]));

        std::cout << "Iter " << i << " Res: " << u_result << std::endl;
        rk2_results.push_back(u_result);

        saveResults(fileName1, i * delta_t, u_result, N - u_result);
    }
}

int main() {
    trapezy();
    std::cout << "koniec trapezy" << std::endl;
    rk2();
    return 0;
}