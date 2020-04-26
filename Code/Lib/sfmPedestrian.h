#ifndef sfmPedestrian_h
#define sfmPedestrian_h

#include "sfmBasicTypes.h"

class Pedestrian {

        
    public:

        virtual sfm::pos2d getorigin() =0;
        virtual sfm::pos2d getdestination() = 0;
        virtual sfm::dir2d getvelocity() = 0;
        virtual sfm::pos2d getposition() = 0;
        virtual double getdesired_speed()=0;
        virtual double getrelaxation_time()=0;
        virtual void setvelocity(sfm::dir2d velocity)=0;
        virtual void setposition(sfm::pos2d position)=0;



};

#endif