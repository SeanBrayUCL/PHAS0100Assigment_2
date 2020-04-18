#include "sfmBasicTypes.h"
#include "sfmForces.h"
#include <cmath>

namespace sfm 
{

sfm::dir2d desired_direction_unit_vector(Pedestrian pedestrian)
{
    sfm::pos2d position = pedestrian.getposition();
    sfm::pos2d destination = pedestrian.getdestination();
    sfm::dir2d direction_vector = position.direction(destination);
    double distance = position.distance(destination);
    return direction_vector*(1/distance);
}

sfm::dir2d attractive_force_to_destination(Pedestrian pedestrian)
{
    sfm::dir2d desired_direction = desired_direction_unit_vector(pedestrian); 
    double desired_speed = pedestrian.getdesired_speed();
    sfm::dir2d desired_velocity = desired_direction*desired_speed;
    sfm::dir2d actual_velocity = pedestrian.getvelocity();
    double relaxation_time = pedestrian.getrelaxation_time();
    return (desired_velocity - actual_velocity)*(1/relaxation_time);
}

}
