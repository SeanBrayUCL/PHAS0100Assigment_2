#include "sfmBasicTypes.h"
#include "sfmDirectedPedestrian.h"
 
// Date constructor
DirectedPedestrian::DirectedPedestrian(sfm::pos2d origin, sfm::dir2d direction, sfm::dir2d velocity, sfm::pos2d position, double desired_speed, double relaxation_time)
{
    SetDirectedPedestrian(origin, direction, velocity, position, desired_speed, relaxation_time);
}
 
// Date member function
void DirectedPedestrian::SetDirectedPedestrian(sfm::pos2d origin, sfm::dir2d direction, sfm::dir2d velocity, sfm::pos2d position, double desired_speed, double relaxation_time)
{
    m_origin = origin;
    m_direction = direction;
    m_velocity = velocity;
    m_position = position;
    m_desired_speed = desired_speed;
    m_relaxation_time = relaxation_time;

}
