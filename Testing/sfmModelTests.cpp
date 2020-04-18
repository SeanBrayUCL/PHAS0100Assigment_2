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


