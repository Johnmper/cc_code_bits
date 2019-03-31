#include<map>
#include<vector>

// OPENCL
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_TARGET_OPENCL_VERSION 120
#include<CL/cl2.hpp>

#undef VERBOSE

const std::map<int, std::string> cl_error_type = {
    {CL_DEVICE_NOT_FOUND,"CL_DEVICE_NOT_FOUND"},
    {CL_DEVICE_NOT_AVAILABLE,"CL_DEVICE_NOT_AVAILABLE"},
    {CL_COMPILER_NOT_AVAILABLE,"CL_COMPILER_NOT_AVAILABLE"},
    {CL_MEM_OBJECT_ALLOCATION_FAILURE,"CL_MEM_OBJECT_ALLOCATION_FAILURE"},
    {CL_OUT_OF_RESOURCES,"CL_OUT_OF_RESOURCES"},
    {CL_OUT_OF_HOST_MEMORY,"CL_OUT_OF_HOST_MEMORY"},
    {CL_PROFILING_INFO_NOT_AVAILABLE,"CL_PROFILING_INFO_NOT_AVAILABLE"},
    {CL_MEM_COPY_OVERLAP,"CL_MEM_COPY_OVERLAP"},
    {CL_IMAGE_FORMAT_MISMATCH,"CL_IMAGE_FORMAT_MISMATCH"},
    {CL_IMAGE_FORMAT_NOT_SUPPORTED,"CL_IMAGE_FORMAT_NOT_SUPPORTED"},
    {CL_BUILD_PROGRAM_FAILURE,"CL_BUILD_PROGRAM_FAILURE"},
    {CL_MAP_FAILURE,"CL_MAP_FAILURE"},
    {CL_MISALIGNED_SUB_BUFFER_OFFSET,"CL_MISALIGNED_SUB_BUFFER_OFFSET"},
    {CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST,"CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST"},
    {CL_COMPILE_PROGRAM_FAILURE,"CL_COMPILE_PROGRAM_FAILURE"},
    {CL_LINKER_NOT_AVAILABLE,"CL_LINKER_NOT_AVAILABLE"},
    {CL_LINK_PROGRAM_FAILURE,"CL_LINK_PROGRAM_FAILURE"},
    {CL_DEVICE_PARTITION_FAILED,"CL_DEVICE_PARTITION_FAILED"},
    {CL_KERNEL_ARG_INFO_NOT_AVAILABLE,"CL_KERNEL_ARG_INFO_NOT_AVAILABLE"},
    {CL_INVALID_VALUE,"CL_INVALID_VALUE"},
    {CL_INVALID_DEVICE_TYPE,"CL_INVALID_DEVICE_TYPE"},
    {CL_INVALID_PLATFORM,"CL_INVALID_PLATFORM"},
    {CL_INVALID_DEVICE,"CL_INVALID_DEVICE"},
    {CL_INVALID_CONTEXT,"CL_INVALID_CONTEXT"},
    {CL_INVALID_QUEUE_PROPERTIES,"CL_INVALID_QUEUE_PROPERTIES"},
    {CL_INVALID_COMMAND_QUEUE,"CL_INVALID_COMMAND_QUEUE"},
    {CL_INVALID_HOST_PTR,"CL_INVALID_HOST_PTR"},
    {CL_INVALID_MEM_OBJECT,"CL_INVALID_MEM_OBJECT"},
    {CL_INVALID_IMAGE_FORMAT_DESCRIPTOR,"CL_INVALID_IMAGE_FORMAT_DESCRIPTOR"},
    {CL_INVALID_IMAGE_SIZE,"CL_INVALID_IMAGE_SIZE"},
    {CL_INVALID_SAMPLER,"CL_INVALID_SAMPLER"},
    {CL_INVALID_BINARY,"CL_INVALID_BINARY"},
    {CL_INVALID_BUILD_OPTIONS,"CL_INVALID_BUILD_OPTIONS"},
    {CL_INVALID_PROGRAM,"CL_INVALID_PROGRAM"},
    {CL_INVALID_PROGRAM_EXECUTABLE,"CL_INVALID_PROGRAM_EXECUTABLE"},
    {CL_INVALID_KERNEL_NAME,"CL_INVALID_KERNEL_NAME"},
    {CL_INVALID_KERNEL_DEFINITION,"CL_INVALID_KERNEL_DEFINITION"},
    {CL_INVALID_KERNEL,"CL_INVALID_KERNEL"},
    {CL_INVALID_ARG_INDEX,"CL_INVALID_ARG_INDEX"},
    {CL_INVALID_ARG_VALUE,"CL_INVALID_ARG_VALUE"},
    {CL_INVALID_ARG_SIZE,"CL_INVALID_ARG_SIZE"},
    {CL_INVALID_KERNEL_ARGS,"CL_INVALID_KERNEL_ARGS"},
    {CL_INVALID_WORK_DIMENSION,"CL_INVALID_WORK_DIMENSION"},
    {CL_INVALID_WORK_GROUP_SIZE,"CL_INVALID_WORK_GROUP_SIZE"},
    {CL_INVALID_WORK_ITEM_SIZE,"CL_INVALID_WORK_ITEM_SIZE"},
    {CL_INVALID_GLOBAL_OFFSET,"CL_INVALID_GLOBAL_OFFSET"},
    {CL_INVALID_EVENT_WAIT_LIST,"CL_INVALID_EVENT_WAIT_LIST"},
    {CL_INVALID_EVENT,"CL_INVALID_EVENT"},
    {CL_INVALID_OPERATION,"CL_INVALID_OPERATION"},
    {CL_INVALID_GL_OBJECT,"CL_INVALID_GL_OBJECT"},
    {CL_INVALID_BUFFER_SIZE,"CL_INVALID_BUFFER_SIZE"},
    {CL_INVALID_MIP_LEVEL,"CL_INVALID_MIP_LEVEL"},
    {CL_INVALID_GLOBAL_WORK_SIZE,"CL_INVALID_GLOBAL_WORK_SIZE"},
    {CL_INVALID_PROPERTY,"CL_INVALID_PROPERTY"},
    {CL_INVALID_IMAGE_DESCRIPTOR,"CL_INVALID_IMAGE_DESCRIPTOR"},
    {CL_INVALID_COMPILER_OPTIONS,"CL_INVALID_COMPILER_OPTIONS"},
    {CL_INVALID_LINKER_OPTIONS,"CL_INVALID_LINKER_OPTIONS"},
    {CL_INVALID_DEVICE_PARTITION_COUNT,"CL_INVALID_DEVICE_PARTITION_COUNT"}
};

const std::map<int,std::string> cl_device_type_str = {
    {CL_DEVICE_TYPE_GPU,"CL_DEVICE_TYPE_GPU"},
    {CL_DEVICE_TYPE_CPU,"CL_DEVICE_TYPE_CPU"},
    {CL_DEVICE_TYPE_ACCELERATOR,"CL_DEVICE_TYPE_ACCELERATOR"}
};

void parseError(int err){
    std::cerr << " [\e[31;1mERROR\e[0m] \e[33;1m" << cl_error_type.at(err) << "\e[0m" << std::endl;
}

class ClUtil{
public:

    cl::Platform platform;
    cl::Device device;
    cl::Context context;

    std::map<std::string, cl::Kernel> kernel;

    ClUtil(){};
    ~ClUtil(){};

    bool initCl(){

        try{
            // Get all available CL Platforms
            std::vector<cl::Platform> all_platforms;
            cl::Platform::get(&all_platforms);
#ifdef VERBOSE
            std::cout << " Detected platforms:" << std::endl;
            for(auto& it : all_platforms){
                std::cout << "    \e[34;1m" <<it.getInfo<CL_PLATFORM_NAME>() << "\e[0m: " << it.getInfo<CL_PLATFORM_VERSION>() << std::endl;
            }
#endif
            platform = all_platforms[0];    // Default platform

            // Get all available CL devices in chosen platform
            std::vector<cl::Device> all_devices;
            platform.getDevices(CL_DEVICE_TYPE_GPU, &all_devices);

#ifdef VERBOSE
            // Info about detect Devices
            std::cout << "----------------------------------------------------------------------" << std::endl;
            std::cout << " Detected Devices:" << std::endl;
            for(auto& it : all_devices){
                std::cout << "    \e[34;1m" << cl_device_type_str.at(it.getInfo<CL_DEVICE_TYPE>()) << "\e[0m: " << it.getInfo<CL_DEVICE_NAME>() << std::endl;
            }
#endif
            device = all_devices[0];    // Default device

#ifdef VERBOSE
            std::cout << " Default device info:" << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_MAX_CLOCK_FREQUENCY\e[0m : " << device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << " Hz" <<std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_MAX_MEM_ALLOC_SIZE\e[0m : " << device.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>()/1048576 << " MB" <<std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_GLOBAL_MEM_SIZE\e[0m : " << device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>()/1048576 << " MB" <<  std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_MAX_PARAMETER_SIZE\e[0m : " << device.getInfo<CL_DEVICE_MAX_PARAMETER_SIZE>() << " B" << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_MAX_COMPUTE_UNITS\e[0m : " << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS\e[0m : " << device.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>() << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_MAX_WORK_ITEM_SIZES\e[0m : " << "(";
            for(auto& it : device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>()){ std::cout << " " << it; };
            std::cout << " )"<<std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_MAX_WORK_GROUP_SIZE\e[0m : " << device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>() << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR\e[0m : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR>() << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT\e[0m : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT>() << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT\e[0m : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT>() << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG\e[0m : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG>() << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT\e[0m : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT>() << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE\e[0m : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE>() << std::endl;
            std::cout << std::setw(60) << "\e[34;1m CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF\e[0m : " << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF>() << std::endl;
#endif
            // OpenCL Context creation, link with GPU
            context = cl::Context({device});
        }
        catch(cl::Error& e){
            parseError(e.err());
            return false;
        }
        return true;
    }

    bool buildKernel(std::string name, std::string source_str){
        int err=0;

        cl::Program::Sources source;
        source.push_back(source_str);

#ifdef VERBOSE
        // Build OpenCL Program
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << " Building kernels" << std::endl;
#endif
        cl::Program program = cl::Program(context, source);
        try{
            program.build({device});
            kernel.insert({name,cl::Kernel(program, name.c_str(), &err)});
        }
        catch (cl::Error& e){
            parseError(e.err());
            if (e.err() == CL_BUILD_PROGRAM_FAILURE){
                // Get the build log
                std::string name = device.getInfo<CL_DEVICE_NAME>();
                std::string buildlog = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
                std::cerr << "Build log for " << name << ":" << std::endl << buildlog << std::endl;
            }
            return false;
        }

#ifdef VERBOSE
        std::cout << " Kernel [\e[34;1m" << name << "\e[0m] created!" << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
#endif
        return true;
    }
};
