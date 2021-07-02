#include "swarm.h"
#include "rod.h"
#include "global_vars.h"

Swarm::Swarm(){
    m_pRods = new Rod[NUM_RODS];
}

Swarm::~Swarm(){
    delete [] m_pRods;
}