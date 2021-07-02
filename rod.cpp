#include "rod.h"
#include <stdlib.h>
#include <math.h>
#include <random>
#include "global_vars.h"
Rod::Rod() {
    std::random_device rd; //Initalise random seed
    std::mt19937 gen(rd()); //Mersenne twister PRNG

    std::uniform_real_distribution<double> u(0.0, LENGTH); //Distributions
    std::normal_distribution<double> n(0, sqrt(TEMPERATURE)); 

    m_x = u(gen);
    m_v = n(gen); 
};