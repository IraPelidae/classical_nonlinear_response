#pragma once
#include <random>

class random_wrapper {
public:

    random_wrapper() : generator(rand_dev()) {}

    double gaussian(double sigma) {

        std::normal_distribution<double> dis(0, sigma);
        return dis(generator);

    }

    double uniform(double a, double b) {

        std::uniform_real_distribution<double> dis(a, b);
        return dis(generator);

    }

private:

    std::random_device rand_dev;
    std::mt19937 generator;

};