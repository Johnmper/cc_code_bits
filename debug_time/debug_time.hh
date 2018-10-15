#ifndef DEBUG_TIME_HEADER
#define DEBUG_TIME_HEADER

#include<iostream>
#include<vector>
#include<functional>
#include<map>
#include<chrono>

// DebugTime Information about specific function
struct DebugTime{
    double mean=0.0;
    double duration=0.0;
    double total=0.0;       // Total seconds spent executing the respective fuction
    unsigned int times_executed=0; // Number of times the function was executed

    void startTime(void);
    void endTime(void);

    void updateData(void);
    void printData(void);
    void printAll(void);
    std::chrono::high_resolution_clock::time_point t1,t2;
};

// Map of every function currently being timed and current FUNCTION ID
extern std::map<std::size_t, DebugTime> debug_time_data;
extern DebugTime* debug_time_ptr;


#ifdef DEBUG_TIME
// Actual macros
#define DEBUG_TIME_PRINT if(debug_time_ptr != nullptr){debug_time_ptr->printData();};
#define DEBUG_TIME_FUNC(a) \
    debug_time_ptr=&debug_time_data[std::hash<std::string>{}(std::string(__FILE__)+"::"+std::string(__func__)+"("+std::to_string(__LINE__)+")")];\
    debug_time_ptr->startTime();\
    a;\
    debug_time_ptr->endTime();\
    debug_time_ptr->updateData();
#else

#define DEBUG_TIME_FUNC(a)
#define DEBUG_TIME_PRINT

#endif

#endif // DEBUG_TIME_HEADER
