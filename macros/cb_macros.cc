///
///  MACROS TESTING
///

#include<iostream>

// USEFULL C++ MACROS:
// __FILE__ : Name of the file the macro is expanded
// __LINE__ : Number of the line where the macro is expanded
// __DATE__ : Date when the macro was expanded
// __TIME__ : Time when the macro was expanded
// __func__ : (Since C++11) Name o the function where the macro is expanded

/// USEFULL MACROS FOR DEBUGGING

#define CRIT_STR    "\e[1m" << __FILE__ << ":" << __LINE__ << ":\e[31m critical:\e[0m "
#define NOTE_STR    "\e[1m" << __FILE__ << ":" << __LINE__ << ":\e[32m note:\e[0m "
#define WARN_STR    "\e[1m" << __FILE__ << ":" << __LINE__ << ":\e[33m warning:\e[0m "
#define DEBUG_STR   "\e[1m" << __FILE__ << ":" << __LINE__ << ":\e[34m debug:\e[0m "

int main(int argc, char** argv){
    std::cout << NOTE_STR << "MACRO TESTING STARTING\n";

    int var_int = 4;

    std::cout << CRIT_STR << "asdasd" << std::endl;
    std::cout << WARN_STR << "asdasd" << std::endl;
    std::cout << DEBUG_STR << "asdasd" << std::endl;
    std::cout << NOTE_STR << "asdasd" << std::endl;

    return 0;
}
