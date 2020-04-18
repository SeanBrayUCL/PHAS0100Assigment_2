#include "sfmBasicTypes.h"
#include "sfmForces.h"
#include <cmath>

const double dt = 2;
const double sigma = 0.3;
const double U_0 = 10;
const double c = 0.5;


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


double semiminor_axis_ellipse(Pedestrian pedestrian_1, Pedestrian pedestrian_2)
{
    sfm::pos2d position__pedestrian_1 = pedestrian_1.getposition();
    sfm::pos2d position_pedestrian_2 = pedestrian_2.getposition();
    sfm::dir2d direction_vector = position_pedestrian_2.direction(position__pedestrian_1);
    double term_1 = sqrt(direction_vector.scalar_product(direction_vector));

    sfm::dir2d desired_direction_pedestrian_2 = desired_direction_unit_vector(pedestrian_2);
    double desired_speed_pedestrian_2 = pedestrian_2.getdesired_speed();
    sfm::dir2d velocity_pedestrian_2 = desired_direction_pedestrian_2*desired_speed_pedestrian_2*dt;
    sfm::dir2d direction_vector_less_velocity = (direction_vector - velocity_pedestrian_2);
    double term_2 = sqrt(direction_vector_less_velocity.scalar_product(direction_vector_less_velocity));

    double term_3 = desired_speed_pedestrian_2*dt;
    return sqrt(pow((term_1 +term_2),2)-pow(term_3,2));
}

sfm::dir2d ped_ped_repulsive_force_no_line_sight(Pedestrian pedestrian_1, Pedestrian pedestrian_2)
{
    double semiminor_axis = semiminor_axis_ellipse(pedestrian_1, pedestrian_2);
    double scalars = (semiminor_axis/sigma)*U_0*exp(-(semiminor_axis/sigma));
    sfm::pos2d position__pedestrian_1 = pedestrian_1.getposition();
    sfm::pos2d position_pedestrian_2 = pedestrian_2.getposition();
    sfm::dir2d direction_vector = position_pedestrian_2.direction(position__pedestrian_1);
    sfm::dir2d unit_vector = direction_vector*(1/sqrt(direction_vector.scalar_product(direction_vector)));
    return unit_vector*scalars;
}

sfm::dir2d ped_ped_repulsive_force(Pedestrian pedestrian_1, Pedestrian pedestrian_2)
{
    sfm::dir2d force_no_line_sight = ped_ped_repulsive_force_no_line_sight(pedestrian_1, pedestrian_2);
    sfm::dir2d desired_direction_pedestrian_1 = desired_direction_unit_vector(pedestrian_1);
    sfm::dir2d result;
    if (desired_direction_pedestrian_1.scalar_product(force_no_line_sight) >= force_no_line_sight.scalar_product(force_no_line_sight)*force_no_line_sight.cos_angle(desired_direction_pedestrian_1)) {
        result = force_no_line_sight;
    } 
    else {
        result = force_no_line_sight*c;
    }
    return result;
}


}
