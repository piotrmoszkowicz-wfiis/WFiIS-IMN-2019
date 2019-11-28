//
// Created by Piotr Moszkowicz on 27/11/2019.
//

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../utils/files_operations.h"

double firstDensity(double x, double y, double x_max, double y_max, double sigma_x, double sigma_y) {
    return std::exp((-1.0 * std::pow(x - 0.35 * x_max, 2) / std::pow(sigma_x, 2)) -
                    (std::pow(y - 0.5 * y_max, 2) / std::pow(sigma_y, 2)));
}

double secondDensity(double x, double y, double x_max, double y_max, double sigma_x, double sigma_y) {
    return -1.0 * std::exp((-1.0 * std::pow(x - 0.65 * x_max, 2) / std::pow(sigma_x, 2)) -
                           (std::pow(y - 0.5 * y_max, 2) / std::pow(sigma_y, 2)));
}

double finalDensity(double x, double y, double x_max, double y_max, double sigma_x, double sigma_y) {
    return firstDensity(x, y, x_max, y_max, sigma_x, sigma_y) + secondDensity(x, y, x_max, y_max, sigma_x, sigma_y);
}

double countGlobal(double v_ip1_j, double v_im1_j, double v_i_jp1, double v_i_jm1, double delta, double epsilon,
                   double density) {
    return 0.25 * (v_ip1_j + v_im1_j + v_i_jp1 + v_i_jm1 + density * std::pow(delta, 2) / epsilon);
}

double countStop(std::vector<std::vector<double>> &n, double delta, std::vector<std::vector<double>> &density, int N_X,
                 int N_Y) {
    double s = 0.0;

    for (int i = 0; i < N_X; i++) {
        for (int j = 0; j < N_Y; j++) {
            s += std::pow(delta, 2) *
                 (0.5 * std::pow((n[i + 1][j] - n[i][j]) / delta, 2) +
                  0.5 * std::pow((n[i][j + 1] - n[i][j]) / delta, 2) -
                  (density[i][j] * n[i][j]));
        }
    }

    return s;
}

double
countLocal(double omega_l, double v_i_j, double v_ip1_j, double v_im1_j, double v_i_jp1, double v_i_jm1, double delta,
           double epsilon,
           double density) {
    return (1.0 - omega_l) * v_i_j + (0.25 * omega_l) *
                                     (v_ip1_j + v_im1_j + v_i_jp1 + v_i_jm1 + (std::pow(delta, 2) / epsilon) * density);
}

double
countErr(double v_ip1_j, double v_i_j, double v_im1_j, double v_i_jp1, double v_i_jm1, double delta, double density,
         double epsilon) {
    return ((v_ip1_j - 2.0 * v_i_j + v_im1_j) / std::pow(delta, 2) +
            (v_i_jp1 - 2.0 * v_i_j + v_i_jm1) / (std::pow(delta, 2))) + density / epsilon;
}

void relaksacjaGlobalna() {
    auto omega = std::vector<double>{
            0.6, 1.0
    };

    const double TOL = std::pow(10, -8);
    constexpr double EPSILON = 1.0;
    constexpr double DELTA = 0.1;
    constexpr int N_X = 150;
    constexpr int N_Y = 100;
    constexpr double V_1 = 10.0;
    constexpr double X_MAX = DELTA * N_X;
    constexpr double Y_MAX = DELTA * N_Y;
    constexpr double SIGMA_X = 0.1 * X_MAX;
    constexpr double SIGMA_Y = 0.1 * Y_MAX;

    for (auto o : omega) {
        std::string fileNameRes = "1_global_";
        std::string fileNameGrid = "1_global_";
        std::string fileNameErr = "1_global_";
        fileNameRes += std::to_string(o) + "_res.dat";
        fileNameGrid += std::to_string(o) + "_grid.dat";
        fileNameErr += std::to_string(o) + "_err.dat";

        clearFile(fileNameRes);
        clearFile(fileNameGrid);
        clearFile(fileNameErr);

        std::vector<std::vector<double>> density(N_X + 1);

        std::vector<std::vector<double>> s(N_X + 1);
        std::vector<std::vector<double>> n(N_X + 1);
        std::vector<std::vector<double>> err(N_X + 1);

        for (int i = 0; i < N_X + 1; i++) {
            density[i].resize(N_Y + 1, 0.0);

            s[i].resize(N_Y + 1, 0.0);
            n[i].resize(N_Y + 1, 0.0);
            err[i].resize(N_Y + 1, 0.0);

            s[i][0] = V_1;
            n[i][0] = V_1;

            for (int j = 0; j < N_Y + 1; j++) {
                density[i][j] = finalDensity(i * DELTA, j * DELTA, X_MAX, Y_MAX, SIGMA_X, SIGMA_Y);
            }
        }

        double S = 0.0;
        double S_1;

        int iter = 0;

        do {
            for (int i = 1; i < N_X; i++) {
                for (int j = 1; j < N_Y; j++) {
                    n[i][j] = countGlobal(s[i + 1][j], s[i - 1][j], s[i][j + 1], s[i][j - 1], DELTA, EPSILON,
                                          density[i][j]);
                }
            }

            for (int i = 1; i < N_Y + 1; i++) {
                n[0][i] = n[1][i];
                n[N_X][i] = n[N_X - 1][i];
            }

            for (int i = 0; i < N_X + 1; i++) {
                for (int j = 0; j < N_Y + 1; j++) {
                    s[i][j] = (1.0 - o) * s[i][j] + o * n[i][j];
                }
            }

            S_1 = S;
            S = countStop(n, DELTA, density, N_X, N_Y);

            saveResults(fileNameRes, iter, S);

            iter++;
        } while (std::abs((S - S_1) / S_1) > TOL);

        for (int i = 1; i < N_X; i++) {
            for (int j = 1; j < N_Y; j++) {
                err[i][j] = countErr(n[i + 1][j], n[i][j], n[i - 1][j], n[i][j + 1], n[i][j - 1], DELTA, density[i][j],
                                     EPSILON);
                saveResults(fileNameErr, i * DELTA, j * DELTA, err[i][j]);
                saveResults(fileNameGrid, i * DELTA, j * DELTA, n[i][j]);
            }
        }
    }
}

void relaksacjaLokalna() {
    auto omega = std::vector<double>{
            1.0, 1.4, 1.8, 1.9
    };

    const double TOL = std::pow(10, -8);
    constexpr double EPSILON = 1.0;
    constexpr double DELTA = 0.1;
    constexpr int N_X = 150;
    constexpr int N_Y = 100;
    constexpr double V_1 = 10.0;
    constexpr double X_MAX = DELTA * N_X;
    constexpr double Y_MAX = DELTA * N_Y;
    constexpr double SIGMA_X = 0.1 * X_MAX;
    constexpr double SIGMA_Y = 0.1 * Y_MAX;

    for (auto o : omega) {
        std::string fileNameRes = "1_local_";
        fileNameRes += std::to_string(o) + "_res.dat";

        clearFile(fileNameRes);

        std::vector<std::vector<double>> density(N_X + 1);

        std::vector<std::vector<double>> n(N_X + 1);

        for (int i = 0; i < N_X + 1; i++) {
            density[i].resize(N_Y + 1, 0.0);

            n[i].resize(N_Y + 1, 0.0);

            n[i][0] = V_1;

            for (int j = 0; j < N_Y + 1; j++) {
                density[i][j] = finalDensity(i * DELTA, j * DELTA, X_MAX, Y_MAX, SIGMA_X, SIGMA_Y);
            }
        }

        double S = 0.0;
        double S_1;

        int iter = 0;

        do {
            for (int i = 1; i < N_X; i++) {
                for (int j = 1; j < N_Y; j++) {
                    n[i][j] = countLocal(o, n[i][j], n[i + 1][j], n[i - 1][j], n[i][j + 1], n[i][j - 1], DELTA, EPSILON,
                                         density[i][j]);
                }
            }

            for (int i = 1; i < N_Y; i++) {
                n[0][i] = n[1][i];
                n[N_X][i] = n[N_X - 1][i];
            }

            S_1 = S;
            S = countStop(n, DELTA, density, N_X, N_Y);

            saveResults(fileNameRes, iter, S);

            iter++;
        } while (std::abs((S - S_1) / S_1) > TOL);
    }
}

int main() {
    relaksacjaGlobalna();
    // relaksacjaLokalna();
    return 0;
}