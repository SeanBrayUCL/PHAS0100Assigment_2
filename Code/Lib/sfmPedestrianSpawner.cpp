#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"
#include "sfmPedestrianSpawner.h"
#include "sfmTargetedPedestrian.h"
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

// Generate 10 random numbers by lambda func and fill it in vector
	std::generate(x_coordinates.begin(), x_coordinates.end(), [&, x]() mutable {
        return x(gen);
	 });
 
    std::generate(y_coordinates.begin(), y_coordinates.end(), [&, y]() mutable {
		return y(gen);
	 });

     std::vector<Pedestrian*> result;
     for(int i=0; i<n; i++){
         sfm::pos2d origin(y_coordinates[i],x_coordinates[i]);
         TargetedPedestrian pedestrian(origin,dest,starting_velocity, origin, speed, speed);
         result.push_back(&pedestrian);
     }
     return result;

};

