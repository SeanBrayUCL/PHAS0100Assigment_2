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
double desired_speed = 1; 
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
Pedestrian sp(origin, destination, zero_velocity, position, zero_desired_speed, relaxation_time);
Pedestrian* stationary_pedestrian = &sp;
// desired speed of one, relaxation time of one, zero velocity, force will be unit direction vector
double unit_speed = 1;
Pedestrian udsp(origin, destination, zero_velocity, position, unit_speed, relaxation_time);
Pedestrian* unit_desired_speed_pedestrian = &udsp;

// one dimensional unit desired speed pedestrian
sfm::pos2d one_d_destination(1,0); 
sfm::pos2d one_d_position(0,0); 
Pedestrian odp(origin, one_d_destination, zero_velocity, one_d_position, unit_speed, relaxation_time);
Pedestrian* one_d_pedestrian = &odp;

TEST_CASE("Test attractive_force_to_destination", "[Tests]") {
    // position on x/y_wrap should be same as (0,0)
    REQUIRE(sfm::attractive_force_to_destination(stationary_pedestrian)[0] == 0);
    REQUIRE(sfm::attractive_force_to_destination(stationary_pedestrian)[0] == 0);
    REQUIRE(sfm::attractive_force_to_destination(unit_desired_speed_pedestrian)[0] == sfm::desired_direction_unit_vector(unit_desired_speed_pedestrian)[0]);
    REQUIRE(sfm::attractive_force_to_destination(unit_desired_speed_pedestrian)[1] == sfm::desired_direction_unit_vector(unit_desired_speed_pedestrian)[1]);    
    REQUIRE(sfm::attractive_force_to_destination(one_d_pedestrian)[1] == 1);
    REQUIRE(sfm::attractive_force_to_destination(one_d_pedestrian)[0] == 0);
}

//testing repulsive ped_ped_repulsive_force
//create three pedestrian (1,2,3), existing in 1 dimnsion (x direction)
sfm::pos2d destination_1(2,0); 
sfm::dir2d velocity_1(1,0); 
sfm::pos2d position_1(1,0); 
sfm::pos2d destination_2(10,0); 
sfm::dir2d velocity_2(1,0); 
sfm::pos2d position_2(1.1,0); 
sfm::pos2d destination_3(9,0); 
sfm::dir2d velocity_3(1,0); 
sfm::pos2d position_3(8,0); 

Pedestrian p1(origin, destination_1, velocity_1, position_1, desired_speed, relaxation_time);
Pedestrian p2(origin, destination_2, velocity_2, position_2, desired_speed, relaxation_time);
Pedestrian p3(origin, destination_3, velocity_3, position_3, desired_speed, relaxation_time);
Pedestrian* pedestrian_1 = &p1;
Pedestrian* pedestrian_2 = &p2;
Pedestrian* pedestrian_3 = &p3;

TEST_CASE("Test ped_ped_repulsive_force", "[Tests]") {
    // position on x/y_wrap should be same as (0,0)
    REQUIRE(sfm::ped_ped_repulsive_force(pedestrian_1,pedestrian_2)[0] == 0); //no force in y direction
    REQUIRE(sfm::ped_ped_repulsive_force(pedestrian_1,pedestrian_2)[1] <= 0); // force should be repulsive
    REQUIRE(sfm::ped_ped_repulsive_force(pedestrian_1,pedestrian_2)[1] <= sfm::ped_ped_repulsive_force(pedestrian_1,pedestrian_3)[1]); //pedestrian_3 is further away so expect a weaker force
}



