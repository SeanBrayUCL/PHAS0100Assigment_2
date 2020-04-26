/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Social Force Model

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include <sfmMyFunctions.h>
#include <sfmExceptionMacro.h>
#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"
#include <iostream>
#include  <cmath>
#include  <vector>
#include <algorithm>
#include <random>

const double desired_speed = 1.3;
const double tau = 0.5;
const double dt = 1;


int main(int argc, char** argv)
{

  int returnStatus = EXIT_FAILURE;

  try
  { //initial pedestrian setup 
  double x_wrap = sfm::pos2d::get_x_wrap();
  std::vector<double> y_coordinate(40);
  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> y(0.0, 10.0);
  std::generate(y_coordinate.begin(), y_coordinate.end(), [&, y]() mutable {
        return y(gen);
	 });
   std::vector<Pedestrian*> pedestrians;
   for(int i =0; i<20; i++)
   {
     Pedestrian pedestrian(sfm::pos2d(0,y_coordinate[i]),sfm::pos2d(x_wrap-0.01,y_coordinate[i]),sfm::dir2d(0,0),sfm::pos2d(0,y_coordinate[i]),desired_speed,tau);
     pedestrians.push_back(&pedestrian);
   }
   for(int i=20; i<40; i++)
   {
     Pedestrian pedestrian(sfm::pos2d(x_wrap-0.01,y_coordinate[i]),sfm::pos2d(0,y_coordinate[i]),sfm::dir2d(0,0),sfm::pos2d(x_wrap-0.01,y_coordinate[i]),desired_speed,tau);
     pedestrians.push_back(&pedestrian);
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

  return returnStatus;
}
