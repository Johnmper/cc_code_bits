#include"ros_types.hh"
#include <iostream>
namespace ros_msg{

    std::ostream& operator<<(std::ostream& os, const Point_t& obj){
        os << "\n      x : " << obj.x << std::endl;
        os << "      y : " << obj.y << std::endl;
        os << "      z : " << obj.z;
    }

    std::ostream& operator<<(std::ostream& os, const Pupil& obj){
        os << "    diameter : " << obj.diameter << std::endl;
        os << "    confidence : " << obj.confidence << std::endl;
        os << "    model_id : " << obj.model_id << std::endl;
        os << "    model_confidence : " << obj.model_confidence << std::endl;
        os << "    timestamp : " << obj.timestamp << std::endl;
        os << "    model_birth_timestamp : " << obj.model_birth_timestamp << std::endl;
        os << "    diameter_3d : " << obj.diameter_3d << std::endl;
        os << "    method : " << obj.method << std::endl;
        os << "    topic : " << obj.topic << std::endl;
        os << "    phi : " << obj.phi << std::endl;
        os << "    theta : " << obj.theta << std::endl;
        os << "    id : " << obj.id << std::endl;
        os << "    norm_pos : " << obj.norm_pos << std::endl;
        os << "    projected_sphere_axes : " << obj.projected_sphere_axes << std::endl;
        os << "    projected_sphere_angle : " << obj.projected_sphere_angle << std::endl;
        os << "    projected_sphere_center : " << obj.projected_sphere_center << std::endl;
        os << "    sphere_radius : " << obj.sphere_radius << std::endl;
        os << "    sphere_center : " << obj.sphere_center << std::endl;
        os << "    ellipse_axes : " << obj.ellipse_axes << std::endl;
        os << "    ellipse_angle : " << obj.ellipse_angle << std::endl;
        os << "    ellipse_center : " << obj.ellipse_center << std::endl;
        os << "    circle_3d_radius : " << obj.circle_3d_radius << std::endl;
        os << "    circle_3d_center : " << obj.circle_3d_center << std::endl;
        os << "    circle_3d_normal : " << obj.circle_3d_normal << std::endl;
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Gaze& obj){
        os << "  topic : " << obj.topic << std::endl;
        os << "  timestamp : " << obj.timestamp << std::endl;
        os << "  confidence : " << obj.confidence << std::endl;
        os << "  norm_pos : " << obj.norm_pos << std::endl;

        for(int ii=0; ii < obj.base_data.size(); ++ii){
            os << "  base_data[" << ii << "] : " << std::endl << obj.base_data.at(ii) << std::endl;
        }
        return os;
    }

};
