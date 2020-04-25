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
#include <sfmPedestrian.h>
#include <sfmForces.h>
#include <iostream>
#include  <cmath>
#include  <vector>

const double dt = 2;

int main(int argc, char** argv)
{

  int returnStatus = EXIT_FAILURE;

  try
  {
   //three pedestrians
    Pedestrian pedestrian_1(sfm::pos2d (0,0),sfm::pos2d (40,9),sfm::dir2d (0,0),sfm::pos2d (0,0), 4, 1);
    Pedestrian pedestrian_2(sfm::pos2d (1,0),sfm::pos2d (45,9.5),sfm::dir2d (0,0),sfm::pos2d (1,0), 7, 1);
    Pedestrian pedestrian_3(sfm::pos2d (0,1),sfm::pos2d (35,8),sfm::dir2d (0,0),sfm::pos2d (0,1), 10, 1);
    std::vector<Pedestrian *> pedestrians{&pedestrian_1,&pedestrian_2,&pedestrian_3};



    
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
