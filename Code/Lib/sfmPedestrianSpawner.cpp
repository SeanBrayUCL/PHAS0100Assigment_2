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
        std::vector<TargetedPedestrian> p; 
        for(int i=0; i<n; i++){
            TargetedPedestrian pedestrian(sfm::pos2d(x_coordinates[i],y_coordinates[i]),dest,sfm::dir2d(0,0), sfm::pos2d(x_coordinates[i],y_coordinates[i]), 1.3, 0.5);
            p.push_back(pedestrian);
        }
        for(int i=0; i<n; i++){
            result.push_back(&p[i]);
        }
    }
    else {
        std::vector<DirectedPedestrian> p;
        for(int i=0; i<n; i++){
            sfm::dir2d dest_dir(dest[1], dest[0]);
            DirectedPedestrian pedestrian(sfm::pos2d(x_coordinates[i],y_coordinates[i]),dest_dir,sfm::dir2d(0,0), sfm::pos2d(x_coordinates[i],y_coordinates[i]), 1.3, 0.5);
            p.push_back(pedestrian);
    }
            for(int i=0; i<n; i++){
            result.push_back(&p[i]);
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
         std::vector<TargetedPedestrian> p;
         for(int i=0; i<n; i++){
         sfm::pos2d origin(x_coordinates[i],y_coordinates[i]);
         TargetedPedestrian pedestrian(origin,dest,sfm::dir2d(0,0), origin, speed, rt);
         p.push_back(pedestrian);
     }
       for(int i=0; i<n; i++){
            result.push_back(&p[i]);
     }
     }
     else {
         std::vector<DirectedPedestrian> p;
         for(int i=0; i<n; i++){
         sfm::pos2d origin(y_coordinates[i],x_coordinates[i]);
         sfm::dir2d dest_dir(dest[1], dest[0]);
         DirectedPedestrian pedestrian(origin,dest_dir,sfm::dir2d(0,0), origin, speed, rt);
         p.push_back(pedestrian);
     }
        for(int i=0; i<n; i++){
            result.push_back(&p[i]);

     }
     }
     return result;

};