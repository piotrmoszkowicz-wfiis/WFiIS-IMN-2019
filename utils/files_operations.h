//
// Created by Piotr Moszkowicz on 05/11/2019.
//

#pragma once

#include <fstream>
#include <string>

void clearFile(const std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void saveResults(const std::string &fileName, double x, double y) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << x << "\t" << y << std::endl;
    file.close();
}

void saveResults(const std::string &fileName, double x, double y, double z) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << x << "\t" << y << "\t" << z << std::endl;
    file.close();
}