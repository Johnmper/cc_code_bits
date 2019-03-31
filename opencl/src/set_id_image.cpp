/**
Creates a checkerboard image that represents the divisions in work_groups, similar to set_id
*/

// STANDARD C++ INCLUDES
#include<iostream>
#include<iomanip>
#include<chrono>

// Local Includes
#include<cl_utils.hpp>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

// Image Information
#define IMAGE_CHANNELS  1
#define IMAGE_WIDTH     640
#define IMAGE_HEIGHT    480
#define IMAGE_STEP      IMAGE_WIDTH
#define IMAGE_TYPE      unsigned char
#define IMAGE_SIZE      (IMAGE_WIDTH*IMAGE_HEIGHT*IMAGE_CHANNELS*sizeof(IMAGE_TYPE))

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
    cv::Mat cv_image(IMAGE_HEIGHT,IMAGE_WIDTH, CV_8U, cv::Scalar::all(100));
    IMAGE_TYPE* image = new IMAGE_TYPE[IMAGE_WIDTH*IMAGE_HEIGHT*IMAGE_CHANNELS];

    // Initialization of GPU device
    ClUtil gpu;
    if(!gpu.initCl()){
        return -1;
    }

    // GPU openCl Kernel
    std::string source_str = {
        "__kernel void set_id_image(__write_only image2d_t out) {"

        "   const sampler_t smp = CLK_NORMALIZED_COORDS_FALSE |"
        "   CLK_ADDRESS_CLAMP_TO_EDGE |"
        "   CLK_FILTER_NEAREST;"

        // Get 2D indexes
        "   int2 coord = (int2)(get_global_id(0),get_global_id(1));"

        "   int2 ids = (int2)(get_group_id(0),get_group_id(1));"
        // Print black or white
        "   if((ids[0]+ids[1])%2==0){"
        "       write_imageui(out,(int2)coord, 2*(ids[0]+ids[1]));"
        "   }else{"
        "       write_imageui(out, (int2)coord, 256-2*(ids[0]+ids[1]));"
        "   }"
        "}"
    };

    // Build Kernel
    if(!gpu.buildKernel("set_id_image",source_str)){
        return -1;
    }


    try{
        // OpenCL Queue
        cl::CommandQueue queue(gpu.context, gpu.device);

        cl::ImageFormat format = cl::ImageFormat(CL_R, CL_UNSIGNED_INT8);
        cl::Image2D image_out = cl::Image2D(gpu.context, CL_MEM_WRITE_ONLY, format,
            IMAGE_WIDTH, IMAGE_HEIGHT, 0, (unsigned char*)image);

        // // Copy array A to memory buffers
        // //queue.enqueueWriteBuffer(image_buf, CL_TRUE, 0, IMAGE_SIZE, image);
        // // Link Kernel Arguments to respective Buffers
        gpu.kernel["set_id_image"].setArg(0,image_out);

        // // RUN KERNEL!
        cl::NDRange global_size(IMAGE_WIDTH,IMAGE_HEIGHT);
        cl::NDRange local_size(20,20);  // 16*16 = 256   NOTE: MAX_LOCAL_SIZE = sqrt(CL_DEVICE_MAX_WORK_GROUP_SIZE)
        queue.enqueueNDRangeKernel(gpu.kernel["set_id_image"],cl::NDRange(),global_size,local_size);

        // // Get 1D Matrix from GPU
        queue.enqueueReadImage(image_out, CL_TRUE, {0,0,0}, {IMAGE_WIDTH,IMAGE_HEIGHT,1}, 0, 0, (void*)image);

    }catch(cl::Error& e){
        parseError(e.err());
        return -1;
    }

    memcpy(cv_image.data,image,IMAGE_SIZE);

    // Show Matrix
    cv::namedWindow("image");
    cv::imshow("image",cv_image);
    cv::waitKey(0);

    cv::destroyAllWindows();
    delete [] image;
    return 0;
}
