#include"debug_time.hh"

void DebugTime::startTime(void){
    t1=std::chrono::high_resolution_clock::now();
}

void DebugTime::endTime(void){
    t2=std::chrono::high_resolution_clock::now();
}

void DebugTime::updateData(void){
    duration = 0.000001*(double)std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    total = total + duration;
    ++times_executed;
    mean = total/(double)times_executed;
}

void DebugTime::printData(void){
    std::cout << "Mean (ms): " << mean << std::endl;
}

void DebugTime::printAll(void){
    std::cout << "===========================" << std::endl;
    for(const auto& it : debug_time_data){
        std::cout << "----" << std::endl;
        std::cout << "[" << it.first << "] Duration: " << it.second.duration << std::endl;
        std::cout << "[" << it.first << "] Mean: " << it.second.mean << std::endl;
        std::cout << "[" << it.first << "] Total: " << it.second.total << std::endl;
        std::cout << "[" << it.first << "] Times: " << it.second.times_executed << std::endl;
        std::cout << "----" << std::endl;
    }
}

// Map of every function currently being timed and current FUNCTION ID
std::map<std::size_t, DebugTime> debug_time_data;
DebugTime* debug_time_ptr=nullptr;
