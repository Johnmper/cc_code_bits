#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>
#include<msgpack.hpp>

#include"ros_types.hh"


//#define GAZE_VISITOR_DEBUG
//#define GAZE_FUNCTION_ENTRY_DEBUG

//===========================================================================================================
//   ######      ###    ######## ########    ##     ## ####  ######  #### ########  #######  ########
//  ##    ##    ## ##        ##  ##          ##     ##  ##  ##    ##  ##     ##    ##     ## ##     ##
//  ##         ##   ##      ##   ##          ##     ##  ##  ##        ##     ##    ##     ## ##     ##
//  ##   #### ##     ##    ##    ######      ##     ##  ##   ######   ##     ##    ##     ## ########
//  ##    ##  #########   ##     ##           ##   ##   ##        ##  ##     ##    ##     ## ##   ##
//  ##    ##  ##     ##  ##      ##            ## ##    ##  ##    ##  ##     ##    ##     ## ##    ##
//   ######   ##     ## ######## ########       ###    ####  ######  ####    ##     #######  ##     ##
//===========================================================================================================
class GazeVisitor {
public:
    #ifdef GAZE_FUNCTION_ENTRY_DEBUG
    int debug_entry_depth = 0;
    std::vector<std::string> map_str;
    std::vector<std::string> complete_str;
    std::vector<unsigned int> complete_key;
    #endif

    bool map_key = false;
    unsigned int array_idx = 0;
    unsigned int pupil_msg_idx = 0;
    std::vector<unsigned int> hashed_keys;

    ros_msg::Gaze gaze_msg;

    GazeVisitor();

    unsigned int string2int(const char* v,size_t size);

    bool visit_nil();
    bool visit_boolean(bool v);
    bool visit_positive_integer(uint64_t v);
    bool visit_negative_integer(int64_t v);
    bool visit_float32(float v);
    bool visit_float64(double v);
    bool visit_str(const char* v, uint32_t size);
    bool visit_bin(const char* v, uint32_t size);
    bool visit_ext(const char* v, uint32_t size);
    bool start_array(uint32_t num_elements);
    bool start_array_item();
    bool end_array_item();
    bool end_array();
    bool start_map(uint32_t num_kv_pairs);
    bool start_map_key();
    bool end_map_key();
    bool start_map_value();
    bool end_map_value();
    bool end_map();
    void parse_error(size_t parsed_offset, size_t error_offset);
    void insufficient_bytes(size_t parsed_offset, size_t error_offset);
    bool referenced() const; // Only when you want to use the visitor with a parser
};
