#include <iostream>  
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "rod.h"
#include "global_vars.h"
#include "swarm.h"

/*
Simulation of the 1D hard rod problem in equilibrium. Rods scatter elastically and are confined by hard walls.
For simplicity, set the mass of the rods m =1
*/
using namespace std;

void check_next_collision(){

};

void collision() {

};

int main(int argc, char *argv[]) {

    Swarm swarm;

    const Rod *const pRods = swarm.getRods();

    for (int i=0; i<NUM_RODS; i++){
        Rod rod = pRods[i];
        double x = rod.m_x;
        double v = rod.m_v;
}; 
}



