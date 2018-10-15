#include <iostream>
#include <detectors/detectors.hh>
#include <opencv2/opencv.hpp>


int main(int argc, char** argv ){

    cv::Mat frame;
    cv::VideoCapture stream(0);

    //detectors::ColoredMarker object("Green",cv::Scalar(35,0,0),cv::Scalar(80,255,255));
    detectors::ColoredMarker object("Green",cv::Scalar(35,65,100),cv::Scalar(80,160,255));

    cv::namedWindow("Color Detected", cv::WINDOW_AUTOSIZE );

    bool should_exit = false;
    while(!should_exit){
        stream.read(frame);

        //object.detect(frame);
        object.coloredCorner(frame);

        // Show image and process key events
        cv::imshow("Color Detected", object.detect_img);
        if(cv::waitKey(10) >=0)
            break;
    }

    return EXIT_SUCCESS;
}
