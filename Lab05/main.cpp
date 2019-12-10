//
// Created by Piotr Moszkowicz on 05/12/2019.
//

#include <cmath>
#include <iostream>
#include <vector>

#include "../utils/files_operations.h"

void relaksacjaWielosiatkowa(int k, std::vector<std::vector<double>>& V, int N_X, int N_Y, double DELTA,
                             double TOL) {
    std::string fileName = "wielosiatkowa_S_k_" + std::to_string(k) + ".dat";
    std::string fileName2 = "wielosiatkowa_V_k_" + std::to_string(k) + ".dat";

    clearFile(fileName);
    clearFile(fileName2);

    double S_prev = 1e-8;

    int it = 0;

    std::cout << "pre while" << std::endl;

    while (true) {
        for (int i = k; i <= N_X - k; i += k) {
            for (int j = k; j <= N_Y - k; j += k) {
                V[i][j] = 0.25 * (V[i + k][j] + V[i - k][j] + V[i][j + k] + V[i][j - k]);
            }
        }

        std::cout << "post vij" << std::endl;

        double sum = 0.0;
        for (int i = 0; i <= N_X - k; i += k) {
            for (int j = 0; j <= N_Y - k; j += k) {
                sum += (k * DELTA) * (k * DELTA) / 2 * (std::pow(((V[i + k][j] - V[i][j]) / (DELTA * 2 * k) +
                                                                  (V[i + k][j + k] - V[i][j + k]) / (DELTA * 2 * k)),
                                                                 2) +
                                                        std::pow(((V[i][j + k] - V[i][j]) / (DELTA * 2 * k) +
                                                                  (V[i + k][j + k] - V[i + k][j]) /
                                                                  (DELTA * 2 * k)), 2));
            }
        }

        std::cout << sum << std::endl;

        saveResults(fileName, it, sum);

        std::cout << "post save" << std::endl;

        if (it > 0 && std::abs((sum - S_prev) / S_prev) < TOL) {
            break;
        }

        S_prev = sum;

        it++;
    }

    std::cout << "pre 2xfor" << std::endl;

    for (int i = 0; i <= N_X - k; i += k) {
        for (int j = 0; j <= N_Y - k; j += k) {
            saveResults(fileName2, DELTA * i, DELTA * j, V[i][j]);
        }
    }

    std::cout << "pre k" << std::endl;

    if (k != 1.0) {
        for (int i = 0; i < N_X - k; i += k) {
            for (int j = 0; j < N_Y - k; j += k) {
                V[i + k / 2][j + k / 2] = 0.25 * (V[i][j] + V[i + k][j] + V[i][j + k] + V[i + k][j + k]);
                V[i + k][j + k / 2] = 0.5 * (V[i + k][j] + V[i + k][j + k]);
                V[i + k / 2][j + k] = 0.5 * (V[i][j + k] + V[i + k][j + k]);
                V[i + k / 2][j] = 0.5 * (V[i][j] + V[i + k][j]);
                V[i][j + k / 2] = 0.5 * (V[i][j] + V[i][j + k]);
            }
        }
    }
}

int main() {
    constexpr int N_X = 128;
    constexpr int N_Y = 128;

    constexpr double DELTA = 0.2;

    constexpr double MAX_X = DELTA * N_X;
    constexpr double MAX_Y = DELTA * N_Y;

    const double TOL = 1e-8;

    int k = 16;

    std::vector<std::vector<double>> V(N_X + 1);

    for (int i = 0; i < N_X + 1; i++) {
        V[i].resize(N_Y + 1);
    }

    for (int i = 0; i < N_X +1; i++) {
        for (int j = 0; j < N_Y + 1; j++) {
            V[i][j] = 0.0;
        }
    }

    for (int i = 0; i < N_Y + 1; i++) {
        V[0][i] = std::sin(M_PI * DELTA * i / MAX_Y);
        V[N_X][i] = std::sin(M_PI * DELTA * i / MAX_Y);
    }

    for (int i = 0; i < N_X + 1; i++) {
        V[i][N_Y] = -1.0 * std::sin(2 * M_PI * DELTA * i / MAX_X);
        V[i][0] = std::sin(2 * M_PI * DELTA * i / MAX_X);
    }

    while (k >= 1) {
        relaksacjaWielosiatkowa(k, V, N_X, N_Y, DELTA, TOL);
        k /= 2;
    }

    return 0;
}