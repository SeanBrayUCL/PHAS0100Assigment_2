#ifndef sfmTargetedPedestrian_h
#define sfmTargetedPedestrian_h

#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"


class TargetedPedestrian : public Pedestrian {
    
    private:
        sfm::pos2d m_origin;
        sfm::pos2d m_destination;
        sfm::dir2d m_velocity;
        sfm::pos2d m_position;
        double m_desired_speed;
        double m_relaxation_time;
        
    public:
        TargetedPedestrian(sfm::pos2d origin, sfm::pos2d destination, sfm::dir2d velocity, sfm::pos2d position, double desired_speed, double m_relaxation_time);
 
        void SetTargetedPedestrian(sfm::pos2d origin, sfm::pos2d destination, sfm::dir2d velocity, sfm::pos2d position, double desired_speed, double m_relaxation_time); 
        
        sfm::pos2d getorigin() { return m_origin;}
        sfm::pos2d getdestination() { return m_destination; }
        sfm::dir2d getvelocity()  { return m_velocity; }
        sfm::pos2d getposition() { return m_position;}
        double getdesired_speed() { return m_desired_speed; }
        double getrelaxation_time()  { return m_relaxation_time; }

        void setvelocity(sfm::dir2d velocity) {m_velocity = velocity;}
        void setposition(sfm::pos2d position) {m_position = position;}



};

#endif
