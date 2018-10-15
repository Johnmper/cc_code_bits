#ifndef __DETECTORS_COLORED_MARKER_HEADER
#define __DETECTORS_COLORED_MARKER_HEADER

#include <opencv2/opencv.hpp>

//=================================================================================================
//   #####  ###### ##### ######  ####  #####  ####  #####   ####
//   #    # #        #   #      #    #   #   #    # #    # #
//   #    # #####    #   #####  #        #   #    # #    #  ####
//   #    # #        #   #      #        #   #    # #####       #
//   #    # #        #   #      #    #   #   #    # #   #  #    #
//   #####  ######   #   ######  ####    #    ####  #    #  ####
//=================================================================================================
namespace detectors{

//=================================================================================================
//   #     #  #####  #     # #######
//   #     # #     # #     #    #    #    # #####  ######  ####  #    #  ####  #      #####   ####
//   #     # #       #     #    #    #    # #    # #      #      #    # #    # #      #    # #
//   #######  #####  #     #    #    ###### #    # #####   ####  ###### #    # #      #    #  ####
//   #     #       #  #   #     #    #    # #####  #           # #    # #    # #      #    #      #
//   #     # #     #   # #      #    #    # #   #  #      #    # #    # #    # #      #    # #    #
//   #     #  #####     #       #    #    # #    # ######  ####  #    #  ####  ###### #####   ####
//=================================================================================================
struct HSVThresholds{
    cv::Scalar mins;
    cv::Scalar maxs;
    HSVThresholds(cv::Scalar _mins, cv::Scalar _maxs) : mins(_mins),maxs(_maxs){};
};


//=================================================================================================
//    #####                              #######        ######
//   #     #  ####  #       ####  #####     #     ####  #     # ###### ##### ######  ####  #####
//   #       #    # #      #    # #    #    #    #    # #     # #        #   #      #    #   #
//   #       #    # #      #    # #    #    #    #    # #     # #####    #   #####  #        #
//   #       #    # #      #    # #####     #    #    # #     # #        #   #      #        #
//   #     # #    # #      #    # #   #     #    #    # #     # #        #   #      #    #   #
//    #####   ####  ######  ####  #    #    #     ####  ######  ######   #   ######  ####    #
//=================================================================================================
struct ColorToDetect{
    std::string name;
    struct HSVThresholds lims;
    ColorToDetect(std::string _name, cv::Scalar _mins, cv::Scalar _maxs) : name(_name), lims(HSVThresholds(_mins,_maxs)){};
    ColorToDetect(std::string _name, struct HSVThresholds _lims) : name(_name), lims(_lims){};
};


//=================================================================================================
//    #####                                            #     #
//   #     #  ####  #       ####  #####  ###### #####  ##   ##   ##   #####  #    # ###### #####
//   #       #    # #      #    # #    # #      #    # # # # #  #  #  #    # #   #  #      #    #
//   #       #    # #      #    # #    # #####  #    # #  #  # #    # #    # ####   #####  #    #
//   #       #    # #      #    # #####  #      #    # #     # ###### #####  #  #   #      #####
//   #     # #    # #      #    # #   #  #      #    # #     # #    # #   #  #   #  #      #   #
//    #####   ####  ######  ####  #    # ###### #####  #     # #    # #    # #    # ###### #    #
//=================================================================================================
class ColoredMarker{
public:

    cv::Mat detect_img;

    ColoredMarker(const std::string _name, const cv::Scalar _mins, const cv::Scalar _maxs) : color(_name,_mins,_maxs) {

    }
    ~ColoredMarker(){

    }

    int coloredCorner(cv::Mat& original){

        if(detect_img.empty()){
            detect_img = cv::Mat::zeros(original.rows,original.cols, CV_8U);
        }

        const int ch = original.channels();
        uint8_t* ptr = original.data;
        const int rows=original.rows;
        const int cols=original.cols;
        for(int ii=0; ii < rows-1; ++ii){
            for(int jj=0; jj < cols-1; ++jj){

                float tmp = (((float)ptr[ch*((ii+1)*cols+jj+1)+2]-(float)ptr[ch*(ii*cols+jj)+2])+1.0)/ ((float)ptr[ch*((ii+1)*cols+jj+1)+1]-(float)ptr[ch*(ii*cols+jj)+1]);
                if( tmp > 0.9 && tmp < 1.1 ){
                    detect_img.data[ii*cols+jj] = 255;
                }
                else{
                    detect_img.data[ii*cols+jj] = 0;
                }
            }
        }

        return 0;
    }

    /// Detects the configured markers
    /// @return number of detected markers
    int detect(cv::Mat& original){
        cv::cvtColor(original,img_hsv,cv::COLOR_BGR2HSV);
        cv::inRange(img_hsv, color.lims.mins, color.lims.maxs, img_hsv);

        return 0;
    }

private:

    cv::Mat img_hsv;
    struct ColorToDetect color;

    /// @brief      Instead of converting and applying the thresholds individually do it at the same time
    /// @details    Instead of converting and applying the HSV thresholds individually do it at the same
    /// time and make the necessary optimizations! :)
    /// Normally the RGB -> HSV conversion is:
    ///
    ///     // R,G,B in range [0,1]
    ///     if( MAX == R) then
    ///         H = 60*(G - B)/(MAX-MIN)
    ///     elif( MAX == G) then
    ///         H = 120 + 60*(B-R)/(MAX-MIN)
    ///     elif( MAX == B) then
    ///         H = 240 + 60*(R-G)/(MAX-MIN)
    ///     elif( MAX == MIN ) then
    ///         H = 0
    ///     endif
    ///
    ///     if( MAX == 0 ) then
    ///         S = 0
    ///     else then
    ///         S = (MAX - MIN)/MAX
    ///     endif
    ///
    ///     V = MAX
    ///
    /// But this conversion can be optimized for instance if we know beforehand that we want to detect
    /// a certain range of HUE!
    ///
    void detect_custom_hsv(){



    }



};



}


#endif
