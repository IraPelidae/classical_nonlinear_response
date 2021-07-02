#ifndef SWARM_H_
#define SWARM_H_

#include "rod.h"

class Swarm {
private:
    Rod m_pRods;
public:
    Swarm();
    
    const Rod const getRods() {return m_pRods;};
};

#endif 