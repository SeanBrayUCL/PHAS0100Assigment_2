#ifndef sfmDirectedPedestrian_h
#define sfmDirectedPedestrian_h

#include "sfmBasicTypes.h"
#include "sfmPedestrian.h"


class DirectedPedestrian : public Pedestrian {
    
    private:
        sfm::pos2d m_origin;
        sfm::dir2d m_direction;
        sfm::dir2d m_velocity;
        sfm::pos2d m_position;
        double m_desired_speed;
        double m_relaxation_time;
        
    public:
        DirectedPedestrian(sfm::pos2d origin, sfm::dir2d direction, sfm::dir2d velocity, sfm::pos2d position, double desired_speed, double m_relaxation_time);
 
        void SetDirectedPedestrian(sfm::pos2d origin, sfm::dir2d direction, sfm::dir2d velocity, sfm::pos2d position, double desired_speed, double m_relaxation_time); 
        
        sfm::pos2d getorigin() { return m_origin;}
        sfm::dir2d getdirection() { return m_direction; }
        sfm::dir2d getvelocity()  { return m_velocity; }
        sfm::pos2d getposition() { return m_position;}
        double getdesired_speed() { return m_desired_speed; }
        double getrelaxation_time()  { return m_relaxation_time; }
        sfm::pos2d getdestination() { return this->getdirection().displace(this->getposition()); }

        void setvelocity(sfm::dir2d velocity) {m_velocity = velocity;}
        void setposition(sfm::pos2d position) {m_position = position;}



};

#endif