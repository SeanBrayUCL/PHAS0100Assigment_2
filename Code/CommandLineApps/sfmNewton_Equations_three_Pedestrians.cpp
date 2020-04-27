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
#include <sfmTargetedPedestrian.h>
#include <sfmForces.h>
#include <iostream>
#include  <cmath>
#include  <vector>

int main(int argc, char** argv)
{

  int returnStatus = EXIT_FAILURE;

  try
  {
   //three pedestrians
    TargetedPedestrian p1(sfm::pos2d (0,0),sfm::pos2d (40,9),sfm::dir2d (0,0),sfm::pos2d (0,0), 4, 1);
    TargetedPedestrian p2(sfm::pos2d (1,0),sfm::pos2d (45,9.5),sfm::dir2d (0,0),sfm::pos2d (1,0), 7, 1);
    TargetedPedestrian p3(sfm::pos2d (0,1),sfm::pos2d (35,8),sfm::dir2d (0,0),sfm::pos2d (0,1), 10, 1);
    TargetedPedestrian* pedestrian_1 = &p1;
    TargetedPedestrian* pedestrian_2 = &p2;
    TargetedPedestrian* pedestrian_3 = &p3;
    std::vector<Pedestrian *> pedestrians{pedestrian_1,pedestrian_2,pedestrian_3};
    for (int j=0; j < 100; j++){
    for (std::vector<Pedestrian *>::size_type i = 0; i != pedestrians.size(); ++i){
        sfm::dir2d force = sfm::total_force(pedestrians[i], pedestrians);
        sfm::dir2d new_velocity = pedestrians[i]->getvelocity() + force*dt;
        double mag_new_velocity = sqrt(new_velocity.scalar_product(new_velocity));
        double mag_max_velocity = 1.3*(pedestrians[i]->getdesired_speed());
        if (mag_new_velocity > mag_max_velocity){
            new_velocity = new_velocity*(mag_max_velocity/mag_new_velocity);
        }
        sfm::pos2d new_position = (new_velocity*dt).displace(pedestrians[i]->getposition());
         pedestrians[i]->setvelocity(new_velocity);
         pedestrians[i]->setposition(new_position);
    }
    
    }
    
    std::cout << "Pedestrian_1 final positon" << std::endl << pedestrians[0]->getposition()[1] << std::endl << pedestrians[0]->getposition()[0] << std::endl;
    std::cout << "Pedestrian_1 final veloctiy" << std::endl << pedestrians[0]->getvelocity()[1] << std::endl << pedestrians[0]->getvelocity()[0] << std::endl;
    
    std::cout << "Pedestrian_2 final positon" << std::endl << pedestrians[1]->getposition()[1] << std::endl << pedestrians[1]->getposition()[0] << std::endl;
    std::cout << "Pedestrian_2 final veloctiy" << std::endl << pedestrians[1]->getvelocity()[1] << std::endl << pedestrians[1]->getvelocity()[0] << std::endl;
    
    std::cout << "Pedestrian_3 final positon" << std::endl << pedestrians[2]->getposition()[1] << std::endl << pedestrians[2]->getposition()[0] << std::endl;
    std::cout << "Pedestrian_3 final veloctiy" << std::endl << pedestrians[2]->getvelocity()[1] << std::endl << pedestrians[2]->getvelocity()[0] << std::endl;
    

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
