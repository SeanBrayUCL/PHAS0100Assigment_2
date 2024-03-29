#include "sfmBasicTypes.h"
#include "sfmTargetedPedestrian.h"
 
// Date constructor
TargetedPedestrian::TargetedPedestrian(sfm::pos2d origin, sfm::pos2d destination, sfm::dir2d velocity, sfm::pos2d position, double desired_speed, double relaxation_time)
{
    SetTargetedPedestrian(origin, destination, velocity, position, desired_speed, relaxation_time);
}
 
// Date member function
void TargetedPedestrian::SetTargetedPedestrian(sfm::pos2d origin, sfm::pos2d destination, sfm::dir2d velocity, sfm::pos2d position, double desired_speed, double relaxation_time)
{
    m_origin = origin;
    m_destination = destination;
    m_velocity = velocity;
    m_position = position;
    m_desired_speed = desired_speed;
    m_relaxation_time = relaxation_time;

}