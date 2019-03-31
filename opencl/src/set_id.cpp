// STANDARD C++ INCLUDES
#include<iostream>
#include<iomanip>
#include<chrono>
#include<algorithm>

// Local Includes
#include<cl_utils.hpp>

using namespace std;
using namespace std::chrono;

// Image Information
#define IMAGE_WIDTH     2048
#define IMAGE_HEIGHT    2048
#define IMAGE_STEP      IMAGE_WIDTH
#define IMAGE_TYPE      unsigned char
#define IMAGE_SIZE      (IMAGE_WIDTH*IMAGE_HEIGHT*sizeof(IMAGE_TYPE))

template<typename T>
void show(T* buf, std::size_t width, std::size_t height){
    for(std::size_t ii=0; ii < height; ++ii){
        for(std::size_t jj=0; jj < width; ++jj){
            std::cout << " " << std::setw(2) << std::setfill(' ') << (int)buf[ii*width+jj];
        }
        std::cout << std::endl;
    }
}

int main(){
    // Initialize image
    IMAGE_TYPE* image = new IMAGE_TYPE[IMAGE_WIDTH*IMAGE_HEIGHT];

    // Initialization of GPU device
    ClUtil gpu;
    if(!gpu.initCl()){
        return -1;
    }

    // GPU openCl Kernel
    std::string source_str = {
        "#define GLOBAL_STEP 512\n"
        "__kernel void set_id(__global unsigned char* out) {"
        "   const int2 coord = {get_global_id(0),get_global_id(1)};"
        // Map 2D coord to 1D index
        "   int id = coord.s1*GLOBAL_STEP + coord.s0;"

        // Get Group ID
        "   int id_g = get_group_id(1)*get_num_groups(0) + get_group_id(0);"
        //"   int id_l = get_local_id(1)*get_local_size(0) + get_local_id(0);"

        "   out[id] = id_g;"
        //"   printf(\"(%03i , %03i) => (%03i , %03i)\\n\",id_x,id_y,id_g,id_l);"
        "}"
    };

    // Build Kernel
    if(!gpu.buildKernel("set_id",source_str)){
        return -1;
    }

    // OpenCL Queue
    cl::CommandQueue queue(gpu.context, gpu.device);

    // Create Kernel Argument buffers
    cl::Buffer image_buf = cl::Buffer(gpu.context, CL_MEM_WRITE_ONLY, IMAGE_SIZE);
    // Copy array A to memory buffers
    //queue.enqueueWriteBuffer(image_buf, CL_TRUE, 0, IMAGE_SIZE, image);
    // Link Kernel Arguments to respective Buffers
    gpu.kernel["set_id"].setArg(0,image_buf);

    // RUN KERNEL!
    cl::NDRange global_size(IMAGE_WIDTH,IMAGE_HEIGHT);
    cl::NDRange local_size(16,16);  // 8*8 = 64   NOTE: MAX_LOCAL_SIZE = sqrt(CL_DEVICE_MAX_WORK_GROUP_SIZE)

    std::vector<int> timed;
    for(int ii=0; ii < 1000; ++ii){
        high_resolution_clock::time_point t1_gpu = high_resolution_clock::now();
        queue.enqueueNDRangeKernel(gpu.kernel["set_id"],cl::NDRange(),global_size,local_size);
        high_resolution_clock::time_point t2_gpu = high_resolution_clock::now();
        int duration_gpu = duration_cast<microseconds>( t2_gpu - t1_gpu ).count();
        timed.push_back(duration_gpu);
    }

    // std::for_each(timed.begin(),timed.end(), [](const int& n){ std::cout << n << std::endl;});
    std::cout << "Mean: " << std::accumulate(timed.begin(),timed.end(),0)/timed.size() << std::endl;

    // Get 1D Matrix from GPU
    queue.enqueueReadBuffer(image_buf, CL_TRUE,0, IMAGE_SIZE, (void*)image);

    // Show Matrix
    //show<unsigned char>(image,IMAGE_WIDTH,IMAGE_HEIGHT);


    return 0;
}
