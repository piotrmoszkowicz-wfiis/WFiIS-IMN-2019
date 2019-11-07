//
// Created by Piotr Moszkowicz on 05/11/2019.
//

#include <array>
#include <cmath>
#include <string>
#include <vector>

#include "../utils/files_operations.h"

double getY(double x = 1.0, double c = 1.0) {
    return std::exp(x * c);
}

double voltage(double t, double omega) {
    return 10.0 * std::sin(t * omega);
}

void euler() {
    constexpr double c = -1.0;
    constexpr double t_min = 0.0;
    constexpr double t_max = 5.0;
    std::array<const double, 3> time_steps = {0.01, 0.1, 1.0};

    std::string fileNameDef = "euler_def.dat";
    clearFile(fileNameDef);

    for (const double time_step : time_steps) {
        std::string fileName = "euler_";
        fileName += std::to_string(time_step) + ".dat";

        std::string fileNameErr = "euler_";
        fileNameErr += std::to_string(time_step) + "_err.dat";

        clearFile(fileName);
        clearFile(fileNameErr);

        const int n = int((t_max - t_min) / time_step);
        std::vector<double> y{};
        y.push_back(1.0);

        for(int i = 0; i < n; i++) {
            const double arg = static_cast<double>(i) * time_step;
            const double result = y[i] + (time_step * c) * y[i];

            y.push_back(result);

            saveResults(fileName, arg, result);
            saveResults(fileNameErr, arg, result - getY(arg, c));
        }
    }

    const double time_step = 0.01;
    const int n = int((t_max - t_min) / time_step);

    for (int i = 0; i < n; i++) {
        const double arg = static_cast<double>(i) * time_step;
        const double result = getY(arg, c);

        saveResults(fileNameDef, arg, result);
    }
}

void rk2() {
    constexpr double c = -1.0;
    constexpr double t_min = 0.0;
    constexpr double t_max = 5.0;
    std::array<const double, 3> time_steps = {0.01, 0.1, 1.0};

    std::string fileNameDef = "rk2_def.dat";
    clearFile(fileNameDef);

    for (const double time_step : time_steps) {
        std::string fileName = "rk2_";
        fileName += std::to_string(time_step) + ".dat";

        std::string fileNameErr = "rk2_";
        fileNameErr += std::to_string(time_step) + "_err.dat";

        clearFile(fileName);
        clearFile(fileNameErr);

        const int n = int((t_max - t_min) / time_step);
        std::vector<double> y{};
        y.push_back(1.0);

        for(int i = 0; i < n; i++) {
            const double k1 = c * y[i];
            const double k2 = c * (y[i] + time_step * k1);

            const double arg = static_cast<double>(i) * time_step;
            const double result = y[i] + (time_step / 2.0) * (k1 + k2);

            y.push_back(result);

            saveResults(fileName, arg, result);
            saveResults(fileNameErr, arg, result - getY(arg, c));
        }
    }

    const double time_step = 0.01;
    const int n = int((t_max - t_min) / time_step);

    for (int i = 0; i < n; i++) {
        const double arg = static_cast<double>(i) * time_step;
        const double result = getY(arg, c);

        saveResults(fileNameDef, arg, result);
    }
}

void rk4() {
    constexpr double c = -1.0;
    constexpr double t_min = 0.0;
    constexpr double t_max = 5.0;
    std::array<const double, 3> time_steps = {0.01, 0.1, 1.0};

    std::string fileNameDef = "rk4_def.dat";
    clearFile(fileNameDef);

    for (const double time_step : time_steps) {
        std::string fileName = "rk4_";
        fileName += std::to_string(time_step) + ".dat";

        std::string fileNameErr = "rk4_";
        fileNameErr += std::to_string(time_step) + "_err.dat";

        clearFile(fileName);
        clearFile(fileNameErr);

        const int n = int((t_max - t_min) / time_step);
        std::vector<double> y{};
        y.push_back(1.0);

        for(int i = 0; i < n; i++) {
            const double k1 = c * y[i];
            const double k2 = c * (y[i] + (time_step / 2.0) * k1);
            const double k3 = c * (y[i] + (time_step / 2.0) * k2);
            const double k4 = c * (y[i] + time_step * k3);

            const double arg = static_cast<double>(i) * time_step;
            const double result = y[i] + (time_step / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);

            y.push_back(result);

            saveResults(fileName, arg, result);
            saveResults(fileNameErr, arg, result - getY(arg, c));
        }
    }

    const double time_step = 0.01;
    const int n = int((t_max - t_min) / time_step);

    for (int i = 0; i < n; i++) {
        const double arg = static_cast<double>(i) * time_step;
        const double result = getY(arg, c);

        saveResults(fileNameDef, arg, result);
    }
}

void rlc() {
    const double time_step = std::exp(-4);
    const double R = 100.0;
    const double L = 0.1;
    const double C = 0.001;
    const double omega0 = 1.0 / std::sqrt(L * C);
    const double T0 = (2.0 * M_PI) / omega0;
    const double t_min = 0.0;
    const double t_max = 4.0 * T0;

    std::array<const double, 4> omega_sources = {0.5 * omega0, 0.8 * omega0, omega0, 1.2 * omega0};

    for (const double omega : omega_sources) {
        std::string fileName = "rlc_";
        fileName += std::to_string(omega) + ".dat";

        clearFile(fileName);

        const int n = int((t_max - t_min) / time_step);

        std::vector<double> iArr{};
        std::vector<double> qArr{};

        iArr.push_back(0.0);
        qArr.push_back(0.0);

        for (int i = 0; i < n; i++) {
            const double time = static_cast<double>(i) * time_step;
            const double halfTime = (static_cast<double>(i) + 0.5) * time_step;
            const double nextTime = (static_cast<double>(i) + 1.0) * time_step;

            const double v = voltage(time, omega);
            const double vHalf = voltage(halfTime, omega);
            const double vNext = voltage(nextTime, omega);

            const double I = iArr[i];
            const double Q = qArr[i];

            const double k1I = (v / L) - ((1.0 / (L * C)) * Q) - ((R / L) * I);
            const double k1Q = I;

            const double k2I = (vHalf / L) - ((1.0 / (L * C)) * (Q + (time_step / 2.0) * k1Q)) - ((R / L) * (I + (time_step / 2.0) * k1I));
            const double k2Q = I + ((time_step / 2.0) * k1I);

            const double k3I = (vHalf / L) - ((1.0 / (L * C)) * (Q + (time_step / 2.0) * k2Q)) - ((R / L) * (I + (time_step / 2.0) * k2I));
            const double k3Q = I + (time_step / 2.0) * k2I;

            const double k4I = I + (time_step * k3I);
            const double k4Q = (vNext / (L - 1) / (L * C)) * (Q + (time_step / 2.0) * k3Q) - ((R / L) * (I + (time_step * k3I)));

            iArr.push_back(I + (time_step / 6.0) * (k1I + k2I + k3I + k4I));
            qArr.push_back(Q + (time_step / 6.0) * (k1Q + k2Q + k3Q + k4Q));

            saveResults(fileName, time, Q, I);
        }
    }
}

int main() {
    euler();
    rk2();
    rk4();
    rlc();
    return 0;
}