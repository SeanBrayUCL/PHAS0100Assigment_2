#ifndef sfmForces_h
#define sfmForces_h

#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"
#include <vector>

const double dt = 1;
const double sigma = 0.3;
const double V_0 = 2.1;
const double c = 0.5;
const double U_0 = 10;
const double R = 0.2;


namespace sfm 
{

sfm::dir2d desired_direction_unit_vector(Pedestrian* pedestrian);

// force 1 
sfm::dir2d attractive_force_to_destination(Pedestrian* pedestrian);

double semiminor_axis_ellipse(Pedestrian* pedestrian_1, Pedestrian* pedestrian_2);

sfm::dir2d ped_ped_repulsive_force_no_line_sight(Pedestrian* pedestrian_1, Pedestrian* pedestrian_2);

//force 2 - pair pedestrians
sfm::dir2d ped_ped_repulsive_force(Pedestrian* pedestrian_1, Pedestrian* pedestrian_2);

//force 2 - aggregate for a pedestrian
sfm::dir2d aggregate_ped_ped_repulsive_force(Pedestrian* pedestrian_1, std::vector<Pedestrian *> pedestrians);

//returns direction vector to nearest border 
sfm::dir2d border_vector(Pedestrian* pedestrian);

//force 3
sfm::dir2d border_pedestrian_force(Pedestrian* pedestrian);

//combining three forces
sfm::dir2d total_force(Pedestrian* pedestiran_1, std::vector<Pedestrian *> pedestrians);

}
#endif