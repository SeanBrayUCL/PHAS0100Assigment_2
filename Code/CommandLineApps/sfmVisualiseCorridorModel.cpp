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
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <omp.h>



const double desired_speed = 1.3;
const double tau = 0.5;
const int number_pedestrians = 30;



int main(int argc, char** argv)
{
  std::clock_t c_start = std::clock();
  auto t_start = std::chrono::high_resolution_clock::now();
  int returnStatus = EXIT_FAILURE;

  try
  {     
  //initial pedestrian setup 
  double x_wrap = sfm::pos2d::get_x_wrap();
  double y_wrap = sfm::pos2d::get_y_wrap();
  sfm::Visualiser viewer(number_pedestrians, x_wrap, y_wrap);

  std::vector<double> y_coordinate(number_pedestrians);
  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> y(0.0, 10.0);
  std::generate(y_coordinate.begin(), y_coordinate.end(), [&, y]() mutable {
        return y(gen);
	 });
   std::vector<TargetedPedestrian> p;
   std::vector<Pedestrian*> pedestrians;
   double x_coord = x_wrap-0.1;
   for(int i =0; i<(number_pedestrians/2); i++)
   {
     TargetedPedestrian pedestrian(sfm::pos2d(0,y_coordinate[i]),sfm::pos2d(x_coord,y_coordinate[i]),sfm::dir2d(0,0),sfm::pos2d(0,y_coordinate[i]),desired_speed,tau);
     p.push_back(pedestrian);
   }
   for(int i=(number_pedestrians/2); i<number_pedestrians; i++)
   {
     
     TargetedPedestrian pedestrian(sfm::pos2d(x_coord,y_coordinate[i]),sfm::pos2d(0,y_coordinate[i]),sfm::dir2d(0,0),sfm::pos2d(x_coord,y_coordinate[i]),desired_speed,tau);
     p.push_back(pedestrian);
   }

   for (auto & i : p){
     pedestrians.push_back(&i);
   }



     //Newton Equations
    for (int j=0; j < 100; j++){
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
    for(int i = 0; i < number_pedestrians; i++){
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