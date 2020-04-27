/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Social Force Model

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/


#include <sfmExceptionMacro.h>
#include "sfmBasicTypes.h"
#include "sfmTargetedPedestrian.h"
#include "sfmVisualiser.h"
#include "sfmForces.h"
#include "sfmPedestrianSpawner.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>


const int number_pedestrian = 40;
const double des_speed = 1.3;
const double tau = 0.5;
const double min_x = 0;
const double min_y = 0;
const double max_x = 2;
const double max_y = 2;
const double x_destination = 45;
const double y_destination = 9;
const double loop_number = 100;


int main(int argc, char** argv)
{
  std::clock_t c_start = std::clock();
  auto t_start = std::chrono::high_resolution_clock::now();
  int returnStatus = EXIT_FAILURE;

  try
  {
    double x_wrap = sfm::pos2d::get_x_wrap();
    double y_wrap = sfm::pos2d::get_y_wrap();
    sfm::Visualiser viewer(number_pedestrian, x_wrap, y_wrap);
    
    //initial pedestrian setup 
    sfm::pos2d min(min_x,min_y);
    sfm::pos2d max(max_x,max_y);
    std::vector<double> x_coordinates(number_pedestrian);
    std::vector<double> y_coordinates(number_pedestrian);
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> x(min[1], max[1]);
    std::uniform_real_distribution<> y(min[0], max[0]);
    
    // Generate x & y coordinates
	  std::generate(x_coordinates.begin(), x_coordinates.end(), [&, x]() mutable {
        return x(gen);
	  });
 
    std::generate(y_coordinates.begin(), y_coordinates.end(), [&, y]() mutable {
		return y(gen);
	  });

    //Creating Pedestrians
    PedestrianType ty =  pos;
    sfm::pos2d dest(x_destination,y_destination);
    std::vector<Pedestrian*> pedestrians; 
    std::vector<TargetedPedestrian> p; 
    for(int i=0; i<40; i++){
        TargetedPedestrian pedestrian(sfm::pos2d(x_coordinates[i],y_coordinates[i]),dest,sfm::dir2d(0,0), sfm::pos2d(x_coordinates[i],y_coordinates[i]), des_speed, tau);
        p.push_back(pedestrian);
        }
    for(int i=0; i<40; i++){
        pedestrians.push_back(&p[i]);
        }


    //Newton Equations
    for (int j=0; j < loop_number; j++){
    Pedestrian* x;  
    std::vector<sfm::dir2d> force;  
    #pragma omp parallel private(x), shared(force)
    {
        #pragma omp for
        for (std::vector<TargetedPedestrian *>::size_type i = 0; i != pedestrians.size(); ++i){
             x = pedestrians[i];
             force.push_back(sfm::total_force(x, pedestrians));
    }
    }
    std::vector<sfm::dir2d> new_velocity;
    std::vector<sfm::pos2d> new_position;
    #pragma omp parallel private(x), shared(force)
    {
      #pragma omp for
       for (std::vector<TargetedPedestrian *>::size_type i = 0; i != pedestrians.size(); ++i){
         x = pedestrians[i]; 
        sfm::dir2d new_velocity = x->getvelocity() + force[i]*dt;
        double mag_new_velocity = sqrt(new_velocity.scalar_product(new_velocity));
        double mag_max_velocity = 1.3*(x->getdesired_speed());
        if (mag_new_velocity > mag_max_velocity){
            new_velocity = new_velocity*(mag_max_velocity/mag_new_velocity);
        }
        sfm::pos2d new_position = (new_velocity*dt).displace(x->getposition());
         pedestrians[i]->setvelocity(new_velocity);
         pedestrians[i]->setposition(new_position);
    }
    }
        
    // Send updated pedestrian positions to viewer 
    for(int i = 0; i < number_pedestrian; i++){
      viewer.SetPedestrian(i, pedestrians[i]->getposition()[1],  pedestrians[i]->getposition()[0], 
		  pedestrians[i]->getvelocity()[1],  pedestrians[i]->getvelocity()[0]);
    }
    // Tell viewer to redraw scene
    viewer.UpdateScene();

    // Sleep for a bit so can see visualiser updating 
    std::this_thread::sleep_for (std::chrono::milliseconds(100));



    }

    
    


    returnStatus = EXIT_SUCCESS;
  }

  catch (sfm::Exception& e)
  {
    std::cerr << "Caught sfm::Exception: " << e.GetDescription() << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "Caught std::exception: " << e.what() << std::endl;
  }

  std::clock_t c_end = std::clock();
  auto t_end = std::chrono::high_resolution_clock::now();

  std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
            << 1000.0*(c_end-c_start) / CLOCKS_PER_SEC << " ms\n"
            << "Wall clock time passed: "
            << std::chrono::duration<double, std::milli>(t_end -t_start).count()
            << " ms\n";

  return returnStatus;
}