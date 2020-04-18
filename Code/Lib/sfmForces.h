#ifndef sfmForces_h
#define sfmForces_h

#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"

namespace sfm 
{

sfm::dir2d desired_direction_unit_vector(Pedestrian pedestrian);

// force 1 
sfm::dir2d attractive_force_to_destination(Pedestrian pedestrian);

}
#endif