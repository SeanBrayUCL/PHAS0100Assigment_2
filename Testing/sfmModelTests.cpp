#include "catch.hpp"
#include "sfmCatchMain.h"
#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"
#include "sfmForces.h"
#include <iostream>

// instantiating instance of class Pedestrian
sfm::pos2d origin (0,0);
sfm::pos2d destination(10,10); 
sfm::dir2d velocity(1,1); 
sfm::pos2d position(5,5); 
double desired_speed = 2; 
double relaxation_time = 1;

Pedestrian ped(origin, destination, velocity, position, desired_speed, relaxation_time);

//testing boundary conditions behave as expected
double x_wrap = sfm::pos2d::get_x_wrap();
double y_wrap = sfm::pos2d::get_y_wrap();
sfm::pos2d boundary(x_wrap,y_wrap);
sfm::pos2d over_boundary(x_wrap+1,y_wrap+1);
sfm::pos2d in_boundary(x_wrap-1,y_wrap-1);

TEST_CASE("Test the boundary conditions", "[Tests]") {
    // position on x/y_wrap should be same as (0,0)
    REQUIRE(boundary[0] == 0);
    REQUIRE(boundary[1] == 0);
    REQUIRE(over_boundary[0] == 1);
    REQUIRE(over_boundary[1] == 1);
    REQUIRE(in_boundary[0] == y_wrap-1);
    REQUIRE(in_boundary[1] == x_wrap-1);
}


//testing attractive_force_to_destination

// zero velocity and zero desired speed will give no force 
sfm::dir2d zero_velocity(0,0);  
double zero_desired_speed = 0; 
Pedestrian stationary_pedestrian(origin, destination, zero_velocity, position, zero_desired_speed, relaxation_time);

// desired speed of one, relaxation time of one, zero velocity, force will be unit direction vector
double unit_speed = 1;
Pedestrian unit_desired_speed_pedestrian(origin, destination, zero_velocity, position, unit_speed, relaxation_time);

// one dimensional unit desired speed pedestrian
sfm::pos2d one_d_destination(1,0); 
sfm::pos2d one_d_position(0,0); 
Pedestrian one_d_pedestrian(origin, one_d_destination, zero_velocity, one_d_position, unit_speed, relaxation_time);





TEST_CASE("Test attractive_force_to_destination", "[Tests]") {
    // position on x/y_wrap should be same as (0,0)
    REQUIRE(sfm::attractive_force_to_destination(stationary_pedestrian)[0] == 0);
    REQUIRE(sfm::attractive_force_to_destination(stationary_pedestrian)[0] == 0);
    REQUIRE(sfm::attractive_force_to_destination(unit_desired_speed_pedestrian)[0] == sfm::desired_direction_unit_vector(unit_desired_speed_pedestrian)[0]);
    REQUIRE(sfm::attractive_force_to_destination(unit_desired_speed_pedestrian)[1] == sfm::desired_direction_unit_vector(unit_desired_speed_pedestrian)[1]);    
    REQUIRE(sfm::attractive_force_to_destination(one_d_pedestrian)[1] == 1);
    REQUIRE(sfm::attractive_force_to_destination(one_d_pedestrian)[0] == 0);

}




