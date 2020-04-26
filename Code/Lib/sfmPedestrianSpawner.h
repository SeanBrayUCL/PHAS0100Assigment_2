#ifndef sfmPedestrianSpawner_h
#define sfmPedestrianSpawner_h

#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"
#include <vector>

const double speed = 1;
const double relaxation_time = 1;
sfm::dir2d starting_velocity(0,0);

enum PedestrianType {pos, dir};

class PedestrianSpawner {
        
    public:
    static std::vector<Pedestrian*> createUniform(int n, PedestrianType type, sfm::pos2d dest);


};

#endif
