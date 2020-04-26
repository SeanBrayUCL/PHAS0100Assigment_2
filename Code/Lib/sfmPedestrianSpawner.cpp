#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"
#include "sfmPedestrianSpawner.h"
#include "sfmTargetedPedestrian.h"
#include "sfmDirectedPedestrian.h"
#include <vector>
#include <algorithm>
#include <random>


 std::vector<Pedestrian*> PedestrianSpawner::createUniform(int n, PedestrianType type, sfm::pos2d dest)
{
    std::vector<double> x_coordinates(n);
    std::vector<double> y_coordinates(n);
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> x(0.0, 50.0);
    std::uniform_real_distribution<> y(0.0, 10.0);

// Generate x & y coordinates
	std::generate(x_coordinates.begin(), x_coordinates.end(), [&, x]() mutable {
        return x(gen);
	 });
 
    std::generate(y_coordinates.begin(), y_coordinates.end(), [&, y]() mutable {
		return y(gen);
	 });

     std::vector<Pedestrian*> result;
     if(type == 0){
     for(int i=0; i<n; i++){
         sfm::pos2d origin(y_coordinates[i],x_coordinates[i]);
         TargetedPedestrian pedestrian(origin,dest,sv, origin, speed, speed);
         result.push_back(&pedestrian);
     }
     }
     else {
         for(int i=0; i<n; i++){
         sfm::pos2d origin(y_coordinates[i],x_coordinates[i]);
         sfm::dir2d dest_dir(dest[1], dest[0]);
         DirectedPedestrian pedestrian(origin,dest_dir,sv, origin, speed, speed);
         result.push_back(&pedestrian);

     }
     }
     return result;
};

std::vector<Pedestrian*> createDistributed(int n, PedestrianType type, sfm::pos2d dest, sfm::pos2d min, sfm::pos2d max)
{
    double x_min = min[0];
    double y_min = min[1];
    double x_max = max[0];
    double y_max = max[1];
    std::vector<double> x_coordinates(n);
    std::vector<double> y_coordinates(n);
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> x(x_min, y_min);
    std::uniform_real_distribution<> y(x_max, y_max);

// Generate x & y coordinates
	std::generate(x_coordinates.begin(), x_coordinates.end(), [&, x]() mutable {
        return x(gen);
	 });
 
    std::generate(y_coordinates.begin(), y_coordinates.end(), [&, y]() mutable {
		return y(gen);
	 });

     std::vector<Pedestrian*> result;
     if(type == 0){
     for(int i=0; i<n; i++){
         sfm::pos2d origin(y_coordinates[i],x_coordinates[i]);
         TargetedPedestrian pedestrian(origin,dest,sv, origin, speed, speed);
         result.push_back(&pedestrian);
     }
     }
     else {
         for(int i=0; i<n; i++){
         sfm::pos2d origin(y_coordinates[i],x_coordinates[i]);
         sfm::dir2d dest_dir(dest[1], dest[0]);
         DirectedPedestrian pedestrian(origin,dest_dir,sv, origin, speed, speed);
         result.push_back(&pedestrian);

     }
     }
     return result;

};

