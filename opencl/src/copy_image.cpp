/**
Copies an opencv image
*/

// STANDARD C++ INCLUDES
#include<iostream>
#include<iomanip>
#include<chrono>

// Local Includes
#include<cl_utils.hpp>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std::chrono;
using mclock = std::chrono::steady_clock;

using ulong = unsigned long int;
using uint = unsigned int;

int main()
{
    // Initialization of GPU device
    ClUtil gpu;
    if(!gpu.initCl()){
        return -1;
    }

    // GPU openCl Kernel (NAIVE APPROACH ?)
    std::string source_str = {
        "#define LOCAL_SIZE 254\n"
        "const sampler_t smp = CLK_NORMALIZED_COORDS_FALSE |"
		"   CLK_ADDRESS_CLAMP_TO_EDGE |"
        "   CLK_FILTER_NEAREST;\n"
        "__kernel void copy_image(__read_only image2d_t in, __write_only image2d_t out) {"
        "   const int2 coord = {get_global_id(0), get_global_id(1)};"
        "   const uint4 pixel = read_imageui(in,coord);"
        "   write_imageui(out, coord, pixel);"
        "}"
    };

    // Build Kernel
    if(!gpu.buildKernel("copy_image",source_str)){
        return -1;
    }

    for(uint im_size=500; im_size <= 5000; im_size+=500 )
    {
        std::cout << "Image Size: " << im_size << "x" << im_size << '\n';

        // Generation of random noise
        cv::Mat cv_image(im_size,im_size,CV_8UC4);
        cv::Mat cv_output(im_size,im_size,CV_8UC4);
        cv::randu(cv_image,0,255);

        // Run Image Copy on GPU
        try{
            // OpenCL Queue
            cl::CommandQueue queue(gpu.context, gpu.device);


            cl::ImageFormat format({CL_RGBA,CL_UNSIGNED_INT8});
            cl::Image2D image_in = cl::Image2D(gpu.context, CL_MEM_READ_ONLY, format, cv_image.cols ,cv_image.rows);
            cl::Image2D image_out = cl::Image2D(gpu.context, CL_MEM_WRITE_ONLY, format, cv_image.cols, cv_image.rows);


            // Link Kernel Arguments to respective Buffers
            gpu.kernel["copy_image"].setArg(0,image_in);
            gpu.kernel["copy_image"].setArg(1,image_out);

            // START TIMER
            mclock::time_point t1_gpu = mclock::now();

            // Copy image
            queue.enqueueWriteImage(image_in, CL_TRUE, {0,0,0}, {(ulong)cv_image.cols,(ulong)cv_image.rows,(ulong)1}, 0, 0, (void*)cv_image.data);

            // // RUN KERNEL!
            cl::NDRange global_size(cv_image.cols,cv_image.rows);
            cl::NDRange local_size(16,16);  // 16*16 = 256   NOTE: MAX_LOCAL_SIZE = sqrt(CL_DEVICE_MAX_WORK_GROUP_SIZE)
            queue.enqueueNDRangeKernel(gpu.kernel["copy_image"],cl::NDRange(),global_size,local_size);

            // Get 1D Matrix from GPU
            queue.enqueueReadImage(image_out, CL_TRUE, {0,0,0}, {(ulong)cv_image.cols,(ulong)cv_image.rows,(ulong)1}, 0, 0,(void*)cv_output.data);

            // GET GPU TIMING RESULTS
            mclock::time_point t2_gpu = mclock::now();
            auto duration_gpu = duration_cast<microseconds>( t2_gpu - t1_gpu ).count();
            std::cout << "  GPU: "<< duration_gpu << " us\n";

        }catch(cl::Error& e){
            parseError(e.err());
            return -1;
        }

        // Run Image Copy on CPU (should be faster)
        mclock::time_point t1_cpu = mclock::now();
        memcpy(cv_output.data,cv_image.data,cv_image.cols*cv_image.rows*cv_image.channels());
        mclock::time_point t2_cpu = mclock::now();
        auto duration_cpu = duration_cast<microseconds>(t2_cpu - t1_cpu).count();
        std::cout << "  CPU: " << duration_cpu << " us" << std::endl;

        // // Show Matrix
        // cv::namedWindow("image");
        // cv::imshow("image",cv_output);
        // cv::waitKey(0);
        //
        // cv::destroyAllWindows();
    }
    return 0;
}
