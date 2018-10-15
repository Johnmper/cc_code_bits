#include"gaze_visitor.hh"


#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>


#if defined GAZE_VISITOR_DEBUG && defined GAZE_FUNCTION_ENTRY_DEBUG
    #define macro_found_item(a)  std::cout << std::setw(debug_entry_depth) << ""  << "[\e[34;1m" << a <<  "\e[0m]" << std::endl;
    #define macro_gaze_value(a)  std::cout << std::setw(debug_entry_depth) << ""  << "\e[35;1m" << a << "\e[0m" << std::endl;
    #define macro_gaze_visitor_func std::cout << std::setw(debug_entry_depth) << "" << "GazeVisitor::" << __func__ << std::endl;
    #define macro_increment_depth  debug_entry_depth = debug_entry_depth+1
    #define macro_decrement_depth  debug_entry_depth = debug_entry_depth-1
#elif defined GAZE_VISITOR_DEBUG && !defined GAZE_FUNCTION_ENTRY_DEBUG
    #define macro_found_item(a)  std::cout << "[\e[34;1m" << a <<  "\e[0m]" << std::endl;
    #define macro_gaze_value(a)  std::cout << "\e[35;1m" << a << "\e[0m" << std::endl;
    #define macro_gaze_visitor_func
    #define macro_increment_depth
    #define macro_decrement_depth
#else
    #define macro_found_item(a)
    #define macro_gaze_value(a)
    #define macro_gaze_visitor_func
    #define macro_increment_depth
    #define macro_decrement_depth
#endif

// Macro to simplify the array value update
#define macro_gaze_array(a) \
    switch(array_idx){  case 0:gaze_msg.a.x=v;break;\
                        case 1:gaze_msg.a.y=v;break;\
                        case 2:gaze_msg.a.z=v;break;}
// Macro to simplify the array value update
#define macro_pupil_array(a) \
    switch(array_idx){  case 0:gaze_msg.base_data[pupil_msg_idx].a.x=v;break;\
                        case 1:gaze_msg.base_data[pupil_msg_idx].a.y=v;break;\
                        case 2:gaze_msg.base_data[pupil_msg_idx].a.z=v;break;}


//===========================================================================================================
//  ########  ##     ## ########  #### ##          ##     ## ####  ######  #### ########  #######  ########
//  ##     ## ##     ## ##     ##  ##  ##          ##     ##  ##  ##    ##  ##     ##    ##     ## ##     ##
//  ##     ## ##     ## ##     ##  ##  ##          ##     ##  ##  ##        ##     ##    ##     ## ##     ##
//  ########  ##     ## ########   ##  ##          ##     ##  ##   ######   ##     ##    ##     ## ########
//  ##        ##     ## ##         ##  ##           ##   ##   ##        ##  ##     ##    ##     ## ##   ##
//  ##        ##     ## ##         ##  ##            ## ##    ##  ##    ##  ##     ##    ##     ## ##    ##
//  ##         #######  ##        #### ########       ###    ####  ######  ####    ##     #######  ##     #
//===========================================================================================================
GazeVisitor::GazeVisitor(){
    map_key = false;
    array_idx = 0;
    hashed_keys.reserve(6);
}



//===========================================================================================================
//   ######  ######## ########  #### ##    ##  ######    #######  #### ##    ## ########
//  ##    ##    ##    ##     ##  ##  ###   ## ##    ##  ##     ##  ##  ###   ##    ##
//  ##          ##    ##     ##  ##  ####  ## ##               ##  ##  ####  ##    ##
//   ######     ##    ########   ##  ## ## ## ##   ####  #######   ##  ## ## ##    ##
//        ##    ##    ##   ##    ##  ##  #### ##    ##  ##         ##  ##  ####    ##
//  ##    ##    ##    ##    ##   ##  ##   ### ##    ##  ##         ##  ##   ###    ##
//   ######     ##    ##     ## #### ##    ##  ######   ######### #### ##    ##    ##
//===========================================================================================================
// GAZE DATUM FORMAT:
//
//      MAP_KEY NAME             |  HASHED  |   MAP_VALUE TYPE
//#==============================#==========#================================================================
// [topic]                       |  {543}   | (string_t)
// [confidence]                  |  {1038}  | (float64_t)
// [timestamp]                   |  {980}   | (float64_t)
// [norm_pos]                    |  {877}   | (float64_t, float64_t)
// [base_data]                   |  {916}   | (map_t)
//     [theta]                   |  {1450}  |     (float64_t)
//     [model_id]                |  {1745}  |     (int_t)
//     [id]                      |  {1121}  |     (int_t)
//     [phi]                     |  {1237}  |     (float64_t)
//     [diameter_3d]             |  {2005}  |     (float64_t)
//     [timestamp]               |  {1896}  |     (float64_t)
//     [model_birth_timestamp]   |  {3152}  |     (float64_t)
//     [confidence]              |  {1954}  |     (float64_t)
//     [diameter]                |  {1759}  |     (float64_t)
//     [model_confidence]        |  {2578}  |     (float64_t)
//     [norm_pos]                |  {1793}  |     (float64_t, float64_t)
//     [method]                  |  {1557}  |     (string_t)
//     [topic]                   |  {1459}  |     (string_t)
//     [circle_3d]               |  {1788}  |     (map_t)
//         [radius]              |  {2436}  |         (float64_t)
//         [normal]              |  {2437}  |         (float64_t, float64_t, float64_t)
//         [center]              |  {2429}  |         (float64_t, float64_t, float64_t)
//     [ellipse]                 |  {1666}  |     (map_t)
//         [angle]               |  {2185}  |         (float64_t)
//         [axes]                |  {2099}  |         (float64_t, float64_t)
//         [center]              |  {2307}  |         (float64_t, float64_t)
//     [projected_sphere]        |  {2618}  |     (map_t)
//         [angle]               |  {3137}  |         (float64_t)
//         [axes]                |  {3051}  |         (float64_t, float64_t)
//         [center]              |  {3259}  |         (float64_t, float64_t)
//     [sphere]                  |  {1563}  |     (map_t)
//         [radius]              |  {2211}  |         (float64_t)
//         [center]              |  {2204}  |         (float64_t, float64_t, float64_t)
unsigned int GazeVisitor::string2int(const char *str, size_t size){
    unsigned int res = 0;
    for(int ii = 0; ii < size; ++ii){
        res = res + str[ii];
    }
    return res;
}


//===========================================================================================================
//  ##    ## #### ##
//  ###   ##  ##  ##
//  ####  ##  ##  ##
//  ## ## ##  ##  ##
//  ##  ####  ##  ##
//  ##   ###  ##  ##
//  ##    ## #### ########
//===========================================================================================================
bool GazeVisitor::visit_nil(){
    macro_gaze_visitor_func;
    return true;
}

//===========================================================================================================
//  ########   #######   #######  ##       ########    ###    ##    ##
//  ##     ## ##     ## ##     ## ##       ##         ## ##   ###   ##
//  ##     ## ##     ## ##     ## ##       ##        ##   ##  ####  ##
//  ########  ##     ## ##     ## ##       ######   ##     ## ## ## ##
//  ##     ## ##     ## ##     ## ##       ##       ######### ##  ####
//  ##     ## ##     ## ##     ## ##       ##       ##     ## ##   ###
//  ########   #######   #######  ######## ######## ##     ## ##    ##
//===========================================================================================================
bool GazeVisitor::visit_boolean(bool v){
    macro_gaze_visitor_func;
    return true;
}


//===========================================================================================================
//         #### ##    ## ########
//    ##    ##  ###   ##    ##
//    ##    ##  ####  ##    ##
//  ######  ##  ## ## ##    ##
//    ##    ##  ##  ####    ##
//    ##    ##  ##   ###    ##
//         #### ##    ##    ##
//===========================================================================================================
bool GazeVisitor::visit_positive_integer(uint64_t v){
    macro_gaze_visitor_func;
    macro_gaze_value(v);

    switch(std::accumulate(hashed_keys.begin(), hashed_keys.end(), 0)){
        case 1745:   // model_id
            gaze_msg.base_data[pupil_msg_idx].model_id = v;
            break;
        case 1121:   // id
            gaze_msg.base_data[pupil_msg_idx].id = v;
            break;
    }
    return true;
}

//===========================================================================================================
//          #### ##    ## ########
//           ##  ###   ##    ##
//           ##  ####  ##    ##
//  #######  ##  ## ## ##    ##
//           ##  ##  ####    ##
//           ##  ##   ###    ##
//          #### ##    ##    ##
//===========================================================================================================
bool GazeVisitor::visit_negative_integer(int64_t v){
    macro_gaze_visitor_func;
    macro_gaze_value(v);

    switch(std::accumulate(hashed_keys.begin(), hashed_keys.end(), 0)){
        case 1745:   // model_id
            gaze_msg.base_data[pupil_msg_idx].model_id = v;
            break;
        case 1121:   // id
            gaze_msg.base_data[pupil_msg_idx].id = v;
            break;
    }
    return true;
}

//===========================================================================================================
//  ######## ##        #######     ###    ########  #######   #######
//  ##       ##       ##     ##   ## ##      ##    ##     ## ##     ##
//  ##       ##       ##     ##  ##   ##     ##           ##        ##
//  ######   ##       ##     ## ##     ##    ##     #######   #######
//  ##       ##       ##     ## #########    ##           ## ##
//  ##       ##       ##     ## ##     ##    ##    ##     ## ##
//  ##       ########  #######  ##     ##    ##     #######  #########
//===========================================================================================================
bool GazeVisitor::visit_float32(float v){
    macro_gaze_visitor_func;
    macro_gaze_value(v);
    return true;
}

//===========================================================================================================
//  ######## ##        #######     ###    ########  #######  ##
//  ##       ##       ##     ##   ## ##      ##    ##     ## ##    ##
//  ##       ##       ##     ##  ##   ##     ##    ##        ##    ##
//  ######   ##       ##     ## ##     ##    ##    ########  ##    ##
//  ##       ##       ##     ## #########    ##    ##     ## #########
//  ##       ##       ##     ## ##     ##    ##    ##     ##       ##
//  ##       ########  #######  ##     ##    ##     #######        ##
//===========================================================================================================
bool GazeVisitor::visit_float64(double v){
    macro_gaze_visitor_func;

    macro_gaze_value(v);

    switch(std::accumulate(hashed_keys.begin(), hashed_keys.end(), 0)){
        // GAZE MESSAGE :
        case 980:   // timestamp (gaze)
            gaze_msg.timestamp = v;
            break;
        case 1038:  // confidence (gaze)
            gaze_msg.confidence = v;
            break;
        case 877:   // norm_pos (gaze)
            macro_gaze_array(norm_pos);
            break;

        // PUPIL MESSAGE :
        // ARRAY of FLOAT64
        case 1793:   // norm_pos
            macro_pupil_array(norm_pos);
            break;
        case 3051:  // projected_sphere_axes
            macro_pupil_array(projected_sphere_axes);
            break;
        case 3259:  // projected_sphere_center
            macro_pupil_array(projected_sphere_center);
            break;
        case 2204:  // sphere_center
            macro_pupil_array(sphere_center);
            break;
        case 2099:  // ellipse_axes
            macro_pupil_array(ellipse_axes);
            break;
        case 2307:  // ellipse_center
            macro_pupil_array(ellipse_center);
            break;
        case 2429:  // circle_3d_center
            macro_pupil_array(circle_3d_center);
            break;
        case 2437:  // circle_3d_normal
            macro_pupil_array(circle_3d_normal);
            break;

        // single FLOAT64
        case 1759:   // diameter
            gaze_msg.base_data[pupil_msg_idx].diameter = v;
            break;
        case 1954:  // confidence
            gaze_msg.base_data[pupil_msg_idx].confidence = v;
            break;
        case 2578:  // model_confidence
            gaze_msg.base_data[pupil_msg_idx].model_confidence = v;
            break;
        case 1896:  // timestamp
            gaze_msg.base_data[pupil_msg_idx].timestamp = v;
            break;
        case 3152:  // model_birth_timestamp
            gaze_msg.base_data[pupil_msg_idx].model_birth_timestamp = v;
            break;
        case 2005:  // diameter_3d
            gaze_msg.base_data[pupil_msg_idx].diameter_3d = v;
            break;
        case 1237:   // phi
            gaze_msg.base_data[pupil_msg_idx].phi = v;
            break;
        case 1450:   // theta
            gaze_msg.base_data[pupil_msg_idx].theta = v;
            break;
        case 3137:  // projected_sphere_angle
            gaze_msg.base_data[pupil_msg_idx].projected_sphere_angle = v;
            break;
        case 2211:  // sphere_radius
            gaze_msg.base_data[pupil_msg_idx].sphere_radius = v;
            break;
        case 2185:  // ellipse_angle
            gaze_msg.base_data[pupil_msg_idx].ellipse_angle = v;
            break;
        case 2436:  // circle_3d_radius
            gaze_msg.base_data[pupil_msg_idx].circle_3d_radius = v;
            break;

    }

    return true;
}

//===========================================================================================================
//   ######  ######## ########  #### ##    ##  ######
//  ##    ##    ##    ##     ##  ##  ###   ## ##    ##
//  ##          ##    ##     ##  ##  ####  ## ##
//   ######     ##    ########   ##  ## ## ## ##   ####
//        ##    ##    ##   ##    ##  ##  #### ##    ##
//  ##    ##    ##    ##    ##   ##  ##   ### ##    ##
//   ######     ##    ##     ## #### ##    ##  ######
//===========================================================================================================
bool GazeVisitor::visit_str(const char* v, uint32_t size){

    macro_gaze_visitor_func;

    if(map_key){
        // FOUND STRING THAT IS A KEY!!!
        // NOTE: map_key is toggled in start_map_key() and end_map_key() functions
        macro_found_item(std::string(v,size));
        hashed_keys.push_back(string2int(v,size));
        // std::string tmp = {""};
        // map_str.push_back(std::string(v,size));
        // complete_key.push_back(std::accumulate(hashed_keys.begin(), hashed_keys.end(), 0));
        // for(const auto& it : map_str){
        //     tmp = tmp + "_" + it;
        // }
        // complete_str.push_back(tmp);

    }
    else{
        macro_gaze_value(std::string(v,size));
        switch(std::accumulate(hashed_keys.begin(), hashed_keys.end(), 0)){
            // GAZE MESSAGE :
            case 543:   // topic (gaze)
                gaze_msg.topic = std::string(v,size);
                break;
            // PUPIL MESSAGE :
            case 1557:   // method
                gaze_msg.base_data[pupil_msg_idx].method = std::string(v,size);
                break;
            case 1459:   // topic
                gaze_msg.base_data[pupil_msg_idx].topic = std::string(v,size);
                break;
        }
    }
    return true;
}

//===========================================================================================================
//  ########  #### ##    ##
//  ##     ##  ##  ###   ##
//  ##     ##  ##  ####  ##
//  ########   ##  ## ## ##
//  ##     ##  ##  ##  ####
//  ##     ##  ##  ##   ###
//  ########  #### ##    ##
//===========================================================================================================
bool GazeVisitor::visit_bin(const char* v, uint32_t size){
    macro_gaze_visitor_func;
    return true;
}

//===========================================================================================================
//  ######## ##     ## ########
//  ##        ##   ##     ##
//  ##         ## ##      ##
//  ######      ###       ##
//  ##         ## ##      ##
//  ##        ##   ##     ##
//  ######## ##     ##    ##
//===========================================================================================================
bool GazeVisitor::visit_ext(const char* v, uint32_t size){
    macro_gaze_visitor_func;
    return true;
}

//===========================================================================================================
//   ######  ########    ###    ########  ########       ###    ########  ########     ###    ##    ##
//  ##    ##    ##      ## ##   ##     ##    ##         ## ##   ##     ## ##     ##   ## ##    ##  ##
//  ##          ##     ##   ##  ##     ##    ##        ##   ##  ##     ## ##     ##  ##   ##    ####
//   ######     ##    ##     ## ########     ##       ##     ## ########  ########  ##     ##    ##
//        ##    ##    ######### ##   ##      ##       ######### ##   ##   ##   ##   #########    ##
//  ##    ##    ##    ##     ## ##    ##     ##       ##     ## ##    ##  ##    ##  ##     ##    ##
//   ######     ##    ##     ## ##     ##    ##       ##     ## ##     ## ##     ## ##     ##    ##
//===========================================================================================================
bool GazeVisitor::start_array(uint32_t num_elements){
    macro_increment_depth;
    macro_gaze_visitor_func;
    if(std::accumulate(hashed_keys.begin(), hashed_keys.end(), 0) == 916){ // Starting base_data array
        pupil_msg_idx = 0;
    }
    else{
        array_idx = 0;
    }
    return true;
}

//===========================================================================================================
//   ######  ########    ###    ########  ########    #### ######## ######## ##     ##
//  ##    ##    ##      ## ##   ##     ##    ##        ##     ##    ##       ###   ###
//  ##          ##     ##   ##  ##     ##    ##        ##     ##    ##       #### ####
//   ######     ##    ##     ## ########     ##        ##     ##    ######   ## ### ##
//        ##    ##    ######### ##   ##      ##        ##     ##    ##       ##     ##
//  ##    ##    ##    ##     ## ##    ##     ##        ##     ##    ##       ##     ##
//   ######     ##    ##     ## ##     ##    ##       ####    ##    ######## ##     ##
//===========================================================================================================
bool GazeVisitor::start_array_item(){
    macro_increment_depth;
    macro_gaze_visitor_func;
    if(std::accumulate(hashed_keys.begin(), hashed_keys.end(), 0) == 916){ // Starting base_data array
        if(gaze_msg.base_data.size() <= pupil_msg_idx){
            gaze_msg.base_data.push_back(ros_msg::Pupil());
        }
    }
    return true;
}

//===========================================================================================================
//  ######## ##    ## ########     #### ######## ######## ##     ##
//  ##       ###   ## ##     ##     ##     ##    ##       ###   ###
//  ##       ####  ## ##     ##     ##     ##    ##       #### ####
//  ######   ## ## ## ##     ##     ##     ##    ######   ## ### ##
//  ##       ##  #### ##     ##     ##     ##    ##       ##     ##
//  ##       ##   ### ##     ##     ##     ##    ##       ##     ##
//  ######## ##    ## ########     ####    ##    ######## ##     ##
//===========================================================================================================
bool GazeVisitor::end_array_item(){
    macro_gaze_visitor_func;
    macro_decrement_depth;
    if(std::accumulate(hashed_keys.begin(), hashed_keys.end(), 0) == 916){ // Finished base_data array element
        pupil_msg_idx = pupil_msg_idx + 1;
    }
    else{
        array_idx = array_idx + 1;
    }
    return true;
}

//===========================================================================================================
//  ######## ##    ## ########        ###    ########  ########     ###    ##    ##
//  ##       ###   ## ##     ##      ## ##   ##     ## ##     ##   ## ##    ##  ##
//  ##       ####  ## ##     ##     ##   ##  ##     ## ##     ##  ##   ##    ####
//  ######   ## ## ## ##     ##    ##     ## ########  ########  ##     ##    ##
//  ##       ##  #### ##     ##    ######### ##   ##   ##   ##   #########    ##
//  ##       ##   ### ##     ##    ##     ## ##    ##  ##    ##  ##     ##    ##
//  ######## ##    ## ########     ##     ## ##     ## ##     ## ##     ##    ##
//===========================================================================================================
bool GazeVisitor::end_array(){
    macro_gaze_visitor_func;
    macro_decrement_depth;
    return true;
}

//===========================================================================================================
//   ######  ########    ###    ########  ########    ##     ##    ###    ########
//  ##    ##    ##      ## ##   ##     ##    ##       ###   ###   ## ##   ##     ##
//  ##          ##     ##   ##  ##     ##    ##       #### ####  ##   ##  ##     ##
//   ######     ##    ##     ## ########     ##       ## ### ## ##     ## ########
//        ##    ##    ######### ##   ##      ##       ##     ## ######### ##
//  ##    ##    ##    ##     ## ##    ##     ##       ##     ## ##     ## ##
//   ######     ##    ##     ## ##     ##    ##       ##     ## ##     ## ##
//===========================================================================================================
bool GazeVisitor::start_map(uint32_t num_kv_pairs){
    macro_increment_depth;
    macro_gaze_visitor_func;
    return true;
}

//===========================================================================================================
//   ######  ########    ###    ########  ########    ##    ## ######## ##    ##
//  ##    ##    ##      ## ##   ##     ##    ##       ##   ##  ##        ##  ##
//  ##          ##     ##   ##  ##     ##    ##       ##  ##   ##         ####
//   ######     ##    ##     ## ########     ##       #####    ######      ##
//        ##    ##    ######### ##   ##      ##       ##  ##   ##          ##
//  ##    ##    ##    ##     ## ##    ##     ##       ##   ##  ##          ##
//   ######     ##    ##     ## ##     ##    ##       ##    ## ########    ##
//===========================================================================================================
bool GazeVisitor::start_map_key(){
    macro_increment_depth;
    macro_gaze_visitor_func;
    map_key = true;
    return true;
}

//===========================================================================================================
//  ######## ##    ## ########     ##    ## ######## ##    ##
//  ##       ###   ## ##     ##    ##   ##  ##        ##  ##
//  ##       ####  ## ##     ##    ##  ##   ##         ####
//  ######   ## ## ## ##     ##    #####    ######      ##
//  ##       ##  #### ##     ##    ##  ##   ##          ##
//  ##       ##   ### ##     ##    ##   ##  ##          ##
//  ######## ##    ## ########     ##    ## ########    ##
//===========================================================================================================
bool GazeVisitor::end_map_key(){
    macro_gaze_visitor_func;
    macro_decrement_depth;
    map_key = false;
    return true;
}

//===========================================================================================================
//   ######  ########    ###    ########  ########    ##     ##    ###    ##       ##     ## ########
//  ##    ##    ##      ## ##   ##     ##    ##       ##     ##   ## ##   ##       ##     ## ##
//  ##          ##     ##   ##  ##     ##    ##       ##     ##  ##   ##  ##       ##     ## ##
//   ######     ##    ##     ## ########     ##       ##     ## ##     ## ##       ##     ## ######
//        ##    ##    ######### ##   ##      ##        ##   ##  ######### ##       ##     ## ##
//  ##    ##    ##    ##     ## ##    ##     ##         ## ##   ##     ## ##       ##     ## ##
//   ######     ##    ##     ## ##     ##    ##          ###    ##     ## ########  #######  ########
//===========================================================================================================
bool GazeVisitor::start_map_value(){
    macro_increment_depth;
    macro_gaze_visitor_func;
    return true;
}

//===========================================================================================================
//  ######## ##    ## ########     ##     ##    ###    ##       ##     ## ########
//  ##       ###   ## ##     ##    ##     ##   ## ##   ##       ##     ## ##
//  ##       ####  ## ##     ##    ##     ##  ##   ##  ##       ##     ## ##
//  ######   ## ## ## ##     ##    ##     ## ##     ## ##       ##     ## ######
//  ##       ##  #### ##     ##     ##   ##  ######### ##       ##     ## ##
//  ##       ##   ### ##     ##      ## ##   ##     ## ##       ##     ## ##
//  ######## ##    ## ########        ###    ##     ## ########  #######  ########
//===========================================================================================================
bool GazeVisitor::end_map_value(){
    macro_gaze_visitor_func;
    macro_decrement_depth;
    hashed_keys.pop_back();
    //map_str.pop_back();
    return true;
}

//===========================================================================================================
//  ######## ##    ## ########     ##     ##    ###    ########
//  ##       ###   ## ##     ##    ###   ###   ## ##   ##     ##
//  ##       ####  ## ##     ##    #### ####  ##   ##  ##     ##
//  ######   ## ## ## ##     ##    ## ### ## ##     ## ########
//  ##       ##  #### ##     ##    ##     ## ######### ##
//  ##       ##   ### ##     ##    ##     ## ##     ## ##
//  ######## ##    ## ########     ##     ## ##     ## ##
//===========================================================================================================
bool GazeVisitor::end_map(){
    macro_gaze_visitor_func;
    macro_decrement_depth;
    return true;
}

//===========================================================================================================
//  ########     ###    ########   ######  ########    ######## ########  ########   #######  ########
//  ##     ##   ## ##   ##     ## ##    ## ##          ##       ##     ## ##     ## ##     ## ##     ##
//  ##     ##  ##   ##  ##     ## ##       ##          ##       ##     ## ##     ## ##     ## ##     ##
//  ########  ##     ## ########   ######  ######      ######   ########  ########  ##     ## ########
//  ##        ######### ##   ##         ## ##          ##       ##   ##   ##   ##   ##     ## ##   ##
//  ##        ##     ## ##    ##  ##    ## ##          ##       ##    ##  ##    ##  ##     ## ##    ##
//  ##        ##     ## ##     ##  ######  ########    ######## ##     ## ##     ##  #######  ##     ##
//===========================================================================================================
void GazeVisitor::parse_error(size_t parsed_offset, size_t error_offset){
    macro_gaze_visitor_func;
}

//===========================================================================================================
//  #### ##    ##  ######  ##     ## ########    ########  ##    ## ######## ########  ######
//   ##  ###   ## ##    ## ##     ## ##          ##     ##  ##  ##     ##    ##       ##    ##
//   ##  ####  ## ##       ##     ## ##          ##     ##   ####      ##    ##       ##
//   ##  ## ## ##  ######  ##     ## ######      ########     ##       ##    ######    ######
//   ##  ##  ####       ## ##     ## ##          ##     ##    ##       ##    ##             ##
//   ##  ##   ### ##    ## ##     ## ##          ##     ##    ##       ##    ##       ##    ##
//  #### ##    ##  ######   #######  ##          ########     ##       ##    ########  ######
//===========================================================================================================
void GazeVisitor::insufficient_bytes(size_t parsed_offset, size_t error_offset){
    macro_gaze_visitor_func;
}

//===========================================================================================================
//  ########  ######## ######## ######## ########  ######## ##    ##  ######  ######## ########
//  ##     ## ##       ##       ##       ##     ## ##       ###   ## ##    ## ##       ##     ##
//  ##     ## ##       ##       ##       ##     ## ##       ####  ## ##       ##       ##     ##
//  ########  ######   ######   ######   ########  ######   ## ## ## ##       ######   ##     ##
//  ##   ##   ##       ##       ##       ##   ##   ##       ##  #### ##       ##       ##     ##
//  ##    ##  ##       ##       ##       ##    ##  ##       ##   ### ##    ## ##       ##     ##
//  ##     ## ######## ##       ######## ##     ## ######## ##    ##  ######  ######## ########
//===========================================================================================================
bool GazeVisitor::referenced() const{
    return true;
}
