#include<iostream>
#include<vector>

#include<zmq.hpp>
#include<msgpack.hpp>

namespace pupil{

class Remote{
public:

    zmq::context_t ctx;
    zmq::socket_t remote;
    zmq::socket_t sub;

    Remote(std::vector<std::string> topic_names) :  ctx(1),
                remote(ctx, ZMQ_REQ),
                sub(ctx,ZMQ_SUB){

        // Connect to Pupil Remote Plugin!
        remote.connect("tcp://localhost:50020");

        subscribe2PupilIPC();
        subscribe2PupilTopics(topic_names);

    }
    ~Remote(){
        sub.close();
        remote.close();
    }

    bool subscribe2PupilIPC(){
        // Asks Pupil Remote Plugin for the Pupil IPC_SUB_URL
        const std::string ipc_sub_command = {"SUB_PORT"};
        zmq::message_t request(ipc_sub_command.size());
        zmq::message_t response;

        memcpy(request.data(), ipc_sub_command.c_str(), ipc_sub_command.size());
        remote.send(request);
        remote.recv(&response);

        // Subscribe to Pupil ICP_SUB_URL
        std::string sub_url = "tcp://localhost:" + std::string(static_cast<char*>(response.data()),response.size());
        std::cout << "Connecting to: " << sub_url << std::endl;
        sub.connect(sub_url.c_str());
        return true;
    }

    bool subscribe2PupilTopics(const std::vector<std::string> topic_names){
        for(const auto& it : topic_names){
            std::cout << "Subscribing to " << it << "("<<it.size()<<")" <<std::endl;
            sub.setsockopt(ZMQ_SUBSCRIBE, it.c_str(), it.size());
        }
        return true;
    }
};


class Comms : public Remote{
public:

    zmq::message_t msg_topic;
    zmq::message_t msg_gaze;
    zmq::message_t msg_frame1;
    zmq::message_t msg_frame2;

    Comms(const std::vector<std::string> topic_names) : Remote(topic_names),
        msg_topic(512), msg_gaze(4096), msg_frame1(4096), msg_frame2(8388608){
        std::cout << "Initialization complete" << std::endl;
    }

    bool processMsg(){

        sub.recv(&msg_topic);
        std::string ss = std::string(static_cast<char*>(msg_topic.data()),msg_topic.size());
        std::size_t hashed_topic = std::hash<std::string>{}(ss);

        switch(hashed_topic){
            case 15309918034564606150U:   // gaze.2d.0.
                std::cout << "recv: gaze.2d.0." << std::endl;
                sub.recv(&msg_gaze);
                break;
            case 17475305093489470139U:   // frame.eye.0
                std::cout << "recv: frame.eye.0" << std::endl;
                sub.recv(&msg_gaze);
                sub.recv(&msg_gaze);
                break;
            case 14183506048178478110U:  // frame.world
                std::cout << "recv: frame.world" << std::endl;
                sub.recv(&msg_gaze);
                sub.recv(&msg_gaze);
                break;
            case 383410510582886379U:  // frame.depth
                std::cout << "recv: frame.depth" << std::endl;
                sub.recv(&msg_gaze);
                sub.recv(&msg_gaze);
                break;
        }

        return true;
    }

};
}

int main(){

    const std::vector<std::string> topic_names = {"gaze."};
    pupil::Comms comms(topic_names);

    while(comms.processMsg()){}

    return 0;
}
