#include "catch.hpp"
#include "sfmCatchMain.h"
#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"
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


