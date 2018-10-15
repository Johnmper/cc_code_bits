#include"ros_types.hh"
#include<iostream>
#include<sstream>
#include<zmq.hpp>
#include<msgpack.hpp>
#include<vector>


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
unsigned int string2int(std::string str){
    unsigned int res = 0;
    for(int ii = 0; ii < str.size(); ++ii){
        res = res + str[ii];
    }
    return res;
}


namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
namespace adaptor {

    template<>
    struct convert<ros_msg::Point_t> {
        msgpack::object const& operator()(msgpack::object const& o, ros_msg::Point_t& p) const {
            if (o.type != msgpack::type::ARRAY){
                throw msgpack::type_error();
            }
            if (o.via.array.size > 3){      // Point_t
                throw msgpack::type_error();
            }
            // NOTE: ros_msg vector should have enough elements reserved before hand


            std::cout << "ROS_MSG::POINT_T Conversion" << std::endl;


            return o;
        }
    };

    template<>
    struct convert<std::vector<ros_msg::Pupil>> {
        msgpack::object const& operator()(msgpack::object const& o, std::vector<ros_msg::Pupil>& p) const {
            if (o.type != msgpack::type::ARRAY){
                throw msgpack::type_error();
            }
            if (o.via.array.size > 2){      // Humans only have 2 eyes... bummer
                throw msgpack::type_error();
            }
            // NOTE: ros_msg vector should have enough elements reserved before hand

            std::cout << "ROS_MSG::PUPIL Conversion" << std::endl;
            for(int ii=0; ii < o.via.array.size; ++ii){
                for(int kk=0; kk < o.via.array.ptr[ii].via.map.size; ++kk){
                    std::string key_str = o.via.array.ptr[ii].via.map.ptr[kk].key.as<std::string>();
                    std::stringstream ss,ss2;
                    switch(o.via.array.ptr[ii].via.map.ptr[kk].val.type){
                        case msgpack::type::NIL:
                            ss << std::setw(10) << std::right << "[NIL] "; break;
                        case msgpack::type::BOOLEAN:
                            ss << std::setw(10) << std::right << "[BOOL] "; break;
                        case msgpack::type::POSITIVE_INTEGER:
                            ss << std::setw(10) << std::right << "[+INT] "; break;
                        case msgpack::type::NEGATIVE_INTEGER:
                            ss << std::setw(10) << std::right << "[-INT] "; break;
                        case msgpack::type::FLOAT32:
                            ss << std::setw(10) << std::right << "[FLOAT32] "; break;
                        case msgpack::type::FLOAT64:
                            ss << std::setw(10) << std::right << "[FLOAT64] "; break;
                        case msgpack::type::STR:
                            ss << std::setw(10) << std::right << "[STRING] "; break;
                        case msgpack::type::ARRAY:
                            ss << std::setw(10) << std::right << "[ARRAY] "; break;
                        case msgpack::type::MAP:
                            ss << std::setw(10) << std::right << "[MAP] "; break;
                        case msgpack::type::EXT:
                            ss << std::setw(10) << std::right << "[EXT] "; break;
                        case msgpack::type::BIN:
                            ss << std::setw(10) << std::right << "[BIN] "; break;
                    }
                    ss2 << "(" << string2int(key_str) <<")";
                    std::cout << ss.str() << std::setw(6) << std::right << ss2.str() << " " << key_str <<std::endl;
                }
            }



            for(int ii=0; ii < o.via.array.size; ++ii){
                // Check size of vector and allocate only if necessary
                // Dev should reserve the correct size according to the number of eye cameras used (1 or 2)
                if(p.size() <= ii ){
                    p.push_back(ros_msg::Pupil());
                }
                for(int kk=0; kk < o.via.array.ptr[ii].via.map.size; ++kk){
                    // Hash key string (optimizes the switch)
                    std::string key_str = o.via.array.ptr[ii].via.map.ptr[kk].key.as<std::string>();
                    switch(string2int(key_str)){
                        case 205:   // id (+int)
                            o.via.array.ptr[ii].via.map.ptr[kk].val >> p[ii].id; break;
                        case 321:   // phi (+int / float64) NOTE: necessary explicity casting since it can be of 2 types
                            p[ii].phi = o.via.array.ptr[ii].via.map.ptr[kk].val.as<double>(); break;
                        case 534:   // theta (+int / float64) NOTE: necessary explicity casting since it can be of 2 types
                            p[ii].phi = o.via.array.ptr[ii].via.map.ptr[kk].val.as<double>(); break;
                        case 543:   // topic (string)
                            o.via.array.ptr[ii].via.map.ptr[kk].val >> p[ii].topic; break;
                        case 641:   // method (string)
                            o.via.array.ptr[ii].via.map.ptr[kk].val >> p[ii].method; break;
                        // case 647:   // method (map)
                        //     o.via.array.ptr[ii].via.map.ptr[kk].val >> p[ii].method; break;

                    }
                }
            }

            return o;
        }
    };

    template<>
    struct convert<ros_msg::Gaze> {

        msgpack::object const& operator()(msgpack::object const& o, ros_msg::Gaze& g) const {
            if (o.type != msgpack::type::MAP){
                 throw msgpack::type_error();
            }
            if (o.via.map.size != 5){
                throw msgpack::type_error();
            }
            std::cout << "ROS_MSG::GAZE Conversion" << std::endl;

            for(int kk=0; kk < o.via.map.size; ++kk){
                std::string key_str = o.via.map.ptr[kk].key.as<std::string>();
                std::stringstream ss,ss2;
                switch(o.via.map.ptr[kk].val.type){
                    case msgpack::type::NIL:
                        ss << std::setw(10) << std::right << "[NIL] "; break;
                    case msgpack::type::BOOLEAN:
                        ss << std::setw(10) << std::right << "[BOOL] "; break;
                    case msgpack::type::POSITIVE_INTEGER:
                        ss << std::setw(10) << std::right << "[+INT] "; break;
                    case msgpack::type::NEGATIVE_INTEGER:
                        ss << std::setw(10) << std::right << "[-INT] "; break;
                    case msgpack::type::FLOAT32:
                        ss << std::setw(10) << std::right << "[FLOAT32] "; break;
                    case msgpack::type::FLOAT64:
                        ss << std::setw(10) << std::right << "[FLOAT64] "; break;
                    case msgpack::type::STR:
                        ss << std::setw(10) << std::right << "[STRING] "; break;
                    case msgpack::type::ARRAY:
                        ss << std::setw(10) << std::right << "[ARRAY] "; break;
                    case msgpack::type::MAP:
                        ss << std::setw(10) << std::right << "[MAP] "; break;
                    case msgpack::type::EXT:
                        ss << std::setw(10) << std::right << "[EXT] "; break;
                    case msgpack::type::BIN:
                        ss << std::setw(10) << std::right << "[BIN] "; break;
                }
                ss2 << "(" << string2int(key_str) <<")";
                std::cout << ss.str() << std::setw(6) << std::right << ss2.str() << " " << key_str <<std::endl;
            }

            for(int ii=0; ii < o.via.map.size; ++ii ){
                // Hash key string (optimizes the switch)
                std::string key_str = o.via.map.ptr[ii].key.as<std::string>();
                switch(string2int(key_str)){
                    case 543:   // topic (string)
                        o.via.map.ptr[ii].val >> g.topic;
                        break;
                    case 877:   // norm_pos (point)
                        o.via.map.ptr[ii].val.convert<ros_msg::Point_t>(g.norm_pos);
                        break;
                    case 916:   // base_data (pupil)
                        o.via.map.ptr[ii].val.convert<std::vector<ros_msg::Pupil>>(g.base_data);
                        break;
                    case 980:   // timestamp (float64)
                        o.via.map.ptr[ii].val >> g.timestamp;
                        break;
                    case 1038:  // confidence (float64)
                        o.via.map.ptr[ii].val >> g.confidence;
                        break;
                }
            }






            //o.via.map.ptr[0].val >> g.topic;
            //o.via.map.ptr[1].val.convert<std::vector<ros_msg::Pupil>>(g.base_data);
            //o.via.map.ptr[2].val >> g.timestamp;
            //o.via.map.ptr[3].val >> g.confidence;
            //o.via.map.ptr[4].val.convert<ros_msg::Point_t>(g.norm_pos);

            // std::cout << o.via.map.ptr[2].key << "("<<o.via.map.ptr[2].val.type <<")"<< std::endl;

            // std::cout<<"NIL("<<msgpack::type::NIL<<")\n";
            // std::cout<<"BOOLEAN("<<msgpack::type::BOOLEAN<<")\n";
            // std::cout<<"POSITIVE_INTEGER("<<msgpack::type::POSITIVE_INTEGER<<")\n";
            // std::cout<<"NEGATIVE_INTEGER("<<msgpack::type::NEGATIVE_INTEGER<<")\n";
            // std::cout<<"FLOAT32("<<msgpack::type::FLOAT32<<")\n";
            // std::cout<<"FLOAT64("<<msgpack::type::FLOAT64<<")\n";
            // std::cout<<"STR("<<msgpack::type::STR<<")\n";
            // std::cout<<"BIN("<<msgpack::type::BIN<<")\n";
            // std::cout<<"EXT("<<msgpack::type::EXT<<")\n";
            // std::cout<<"ARRAY("<<msgpack::type::ARRAY<<")\n";
            // std::cout<<"MAP("<<msgpack::type::MAP<<")\n";


            return o;
        }
    };
}}}

class PupilComms{
public:
    zmq::context_t ctx;
    zmq::socket_t remote;
    zmq::socket_t sub;

    zmq::message_t msg_topic;
    zmq::message_t msg_raw;


    ros_msg::Gaze g;

    //GazeVisitor g;
    const int buf_sz;


    PupilComms() : ctx(1), remote(ctx, ZMQ_REQ), sub(ctx,ZMQ_SUB), buf_sz(1024), msg_topic(buf_sz), msg_raw(buf_sz){

        // Connect to Pupil Remote Plugin!
        remote.connect("tcp://localhost:50020");

        // Asks Pupil Remote Plugin for the Pupil IPC_SUB_URL
        zmq::message_t request(8), response;
        memcpy (request.data(), "SUB_PORT", 8);
        remote.send(request);
        if(!remote.recv(&response)){
            std::cerr << "Failed to receive the Pupil Remote SUB_URL" << std::endl;
            return;
        }

        // Subscribe to Pupil ICP_SUB_URL
        char sub_url[20];
        memcpy(sub_url,"tcp://localhost:",16);
        memcpy(sub_url+16,response.data(),response.size());
        sub_url[16+response.size()] = '\0';
        std::cout << "Connecting to: " << sub_url << std::endl;
        sub.connect(sub_url);

        // Subscribe to everything
        sub.setsockopt(ZMQ_SUBSCRIBE, "gaze", 0);
    }

    ~PupilComms(){
        sub.close();
        ctx.close();
    }

    bool printed = true;
    bool processIncomming(void){
        // recv message in a non blocking way
        sub.recv(&msg_topic);

        //std::cout << "alive" << std::endl;
        //std::cout << "Topic [" << msg_raw.size() << "]: " << std::string(static_cast<char*>(msg_topic.data()),msg_topic.size()) << std::endl;

        // Find "gaze" in topic name
        if( strstr(static_cast<char*>(msg_topic.data()),"gaze") != NULL){


            sub.recv(&msg_raw);

            //size_t off = 0;
            //msgpack::v2::parse(static_cast<const char *>(msg_raw.data()), msg_raw.size(), off, g);
            //std::cout << "\e[2J"<< std::endl << g.gaze_msg << std::endl;
            if(printed){
                msgpack::object_handle oh = msgpack::unpack((const char*)msg_raw.data(),msg_raw.size());
                msgpack::object deserialized = oh.get();
                deserialized.convert<ros_msg::Gaze>(g);

                // // std::cout << "SIZE: " << deserialized.via.array.size << std::endl;
                // for(int ii=0; ii < 2*deserialized.via.array.size; ii+=2){
                //     std::cout << deserialized.via.array.ptr[ii] << " : " << deserialized.via.array.ptr[ii+1] << std::endl;
                // }

                //msgpack::object pupil_deserialized = deserialized.via.array.ptr[3];
                //std::cout << pupil_deserialized << std::endl;

                //std::cout << deserialized.via.array.ptr[0] << std::endl;
                //std::cout << deserialized.as<ros_msg::Gaze>() << std::endl;
                //printed = false;
            }
        }
        else if( strstr(static_cast<char*>(msg_topic.data()),"gaze") != NULL){

        }
        return true;
    }


};

int main(int argc, char** argv){

    std::cout << "Testing PupilVisitor class" << std::endl;
    PupilComms comms;

    while(comms.processIncomming()){}

    return 0;
}
