#ifndef sfmPedestrianSpawner_h
#define sfmPedestrianSpawner_h

#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"
#include <vector>

const double speed = 1.3;
const double rt = 0.5;

enum PedestrianType {pos, dir};

class PedestrianSpawner {
        
    public:
    static std::vector<Pedestrian*> createUniform(int n, PedestrianType type, sfm::pos2d dest);

    static std::vector<Pedestrian*> createDistributed(int n, PedestrianType type, sfm::pos2d dest, sfm::pos2d min, sfm::pos2d max);




};

#endif