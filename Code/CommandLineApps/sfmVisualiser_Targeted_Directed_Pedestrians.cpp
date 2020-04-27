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
#include "sfmDirectedPedestrian.h"
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


const int number__TargetedPedestrian = 40;
const int number__DirectedPedestrians = 40;
const double des_speed = 1.3;
const double tau = 0.5;
const double t_min_x = 0;
const double t_min_y = 0;
const double t_max_x = 2;
const double t_max_y = 2;
const double x_destination = 45;
const double y_destination = 9;
const double loop_number = 100;
const double d_min_x = 45;
const double d_min_y = 9;
const double d_max_x = 49;
const double d_max_y = 9.9;
const double x_direction = -1;
const double y_direction = 0;


int main(int argc, char** argv)
{
  std::clock_t c_start = std::clock();
  auto t_start = std::chrono::high_resolution_clock::now();
  int returnStatus = EXIT_FAILURE;

  try
  { int number_pedestrian = number__TargetedPedestrian + number__DirectedPedestrians;
    double x_wrap = sfm::pos2d::get_x_wrap();
    double y_wrap = sfm::pos2d::get_y_wrap();
    sfm::Visualiser viewer(number_pedestrian, x_wrap, y_wrap);
    
    //initial pedestrian setup 
    sfm::pos2d t_min(t_min_x,t_min_y);
    sfm::pos2d t_max(t_max_x,t_max_y);
    sfm::pos2d d_min(d_min_x,d_min_y);
    sfm::pos2d d_max(d_max_x,d_max_y);
    std::vector<double> t_x_coordinates(number_pedestrian);
    std::vector<double> t_y_coordinates(number_pedestrian);
    std::vector<double> d_x_coordinates(number_pedestrian);
    std::vector<double> d_y_coordinates(number_pedestrian);
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> t_x(t_min[1], t_max[1]);
    std::uniform_real_distribution<> t_y(t_min[0], t_max[0]);
    std::uniform_real_distribution<> d_x(d_min[1], d_max[1]);
    std::uniform_real_distribution<> d_y(d_min[0], d_max[0]);
    
    // Generate x & y coordinates
	  std::generate(t_x_coordinates.begin(), t_x_coordinates.end(), [&, t_x]() mutable {
        return t_x(gen);
	  });
 
    std::generate(t_y_coordinates.begin(), t_y_coordinates.end(), [&, t_y]() mutable {
		return t_y(gen);
	  });

	std::generate(d_x_coordinates.begin(), d_x_coordinates.end(), [&, d_x]() mutable {
        return d_x(gen);
	  });
 
    std::generate(d_y_coordinates.begin(), d_y_coordinates.end(), [&, d_y]() mutable {
		return d_y(gen);
	  });


    //Creating Pedestrians
    sfm::pos2d dest(x_destination,y_destination);
    std::vector<Pedestrian*> pedestrians; 
    std::vector<TargetedPedestrian> p_1; 
    for(int i=0; i<number__TargetedPedestrian; i++){
        TargetedPedestrian pedestrian(sfm::pos2d(t_x_coordinates[i],t_y_coordinates[i]),dest,sfm::dir2d(0,0), sfm::pos2d(t_x_coordinates[i],t_y_coordinates[i]), des_speed, tau);
        p_1.push_back(pedestrian);
        }
    for(int i=0; i<number__TargetedPedestrian; i++){
        pedestrians.push_back(&p_1[i]);
        }
    
    sfm::dir2d dir(x_direction,y_direction);
    std::vector<DirectedPedestrian> p_2; 
    for(int i=0; i<number__DirectedPedestrians; i++){
        DirectedPedestrian pedestrian(sfm::pos2d(d_x_coordinates[i],d_y_coordinates[i]),dir,sfm::dir2d(0,0), sfm::pos2d(d_x_coordinates[i],d_y_coordinates[i]), des_speed, tau);
        p_2.push_back(pedestrian);
        }
    for(int i=0; i<number__DirectedPedestrians; i++){
        pedestrians.push_back(&p_2[i]);
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
