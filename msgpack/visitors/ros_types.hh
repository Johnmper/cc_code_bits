#pragma once
#include<fstream>
#include<vector>
//===========================================================================================================
//        ########   #######   ######          ##     ##  ######   ######
//        ##     ## ##     ## ##    ##         ###   ### ##    ## ##    ##
//        ##     ## ##     ## ##               #### #### ##       ##
//        ########  ##     ##  ######          ## ### ##  ######  ##   ####
//        ##   ##   ##     ##       ##         ##     ##       ## ##    ##
//        ##    ##  ##     ## ##    ##         ##     ## ##    ## ##    ##
//        ##     ##  #######   ######  ####### ##     ##  ######   ######
//===========================================================================================================
namespace ros_msg{
    // Std types
    typedef float float32_t;
    typedef double float64_t;

//===========================================================================================================
//        ########   #######  #### ##    ## ########         ########
//        ##     ## ##     ##  ##  ###   ##    ##               ##
//        ##     ## ##     ##  ##  ####  ##    ##               ##
//        ########  ##     ##  ##  ## ## ##    ##               ##
//        ##        ##     ##  ##  ##  ####    ##               ##
//        ##        ##     ##  ##  ##   ###    ##               ##
//        ##         #######  #### ##    ##    ##    #######    ##
//===========================================================================================================
    struct Point_t{
        float64_t x;
        float64_t y;
        float64_t z;

        friend std::ostream& operator<<(std::ostream& os, const Point_t& obj);
    };

//===========================================================================================================
//        ########  ##     ## ########  #### ##
//        ##     ## ##     ## ##     ##  ##  ##
//        ##     ## ##     ## ##     ##  ##  ##
//        ########  ##     ## ########   ##  ##
//        ##        ##     ## ##         ##  ##
//        ##        ##     ## ##         ##  ##
//        ##         #######  ##        #### ########
//===========================================================================================================
    struct Pupil{
        float64_t diameter;
        float64_t confidence;
        int64_t model_id;
        float64_t model_confidence;
        float64_t timestamp;
        float64_t model_birth_timestamp;
        float64_t diameter_3d;
        std::string method;
        std::string topic;
        float64_t phi;
        float64_t theta;
        int64_t id;
        Point_t norm_pos;
        Point_t projected_sphere_axes;
        float64_t projected_sphere_angle;
        Point_t projected_sphere_center;
        float64_t sphere_radius;
        Point_t sphere_center;
        Point_t ellipse_axes;
        float64_t ellipse_angle;
        Point_t ellipse_center;
        float64_t circle_3d_radius;
        Point_t circle_3d_center;
        Point_t circle_3d_normal;

        friend std::ostream& operator<<(std::ostream& os, const Pupil& dt);
    };

//===========================================================================================================
//         ######      ###    ######## ########
//        ##    ##    ## ##        ##  ##
//        ##         ##   ##      ##   ##
//        ##   #### ##     ##    ##    ######
//        ##    ##  #########   ##     ##
//        ##    ##  ##     ##  ##      ##
//         ######   ##     ## ######## ########
//===========================================================================================================
    struct Gaze{

        std::string topic;
        float64_t timestamp;
        float64_t confidence;
        Point_t norm_pos;
        std::vector<Pupil> base_data;

        friend std::ostream& operator<<(std::ostream& os, const Gaze& dt);
    };

};
