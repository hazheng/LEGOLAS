#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <stdio.h>

/**
is supposed to be thresholding code
*/
cv::Mat threshIm(cv::Mat* image_in){
	cv::Mat hsv;
	cv::cvtColor(*image_in,hsv,CV_BGR2HSV);
	return hsv;
}

int main(int argc, char** argv)
{ 
	if (argc!=2)
	{
		printf("%s\n","Usage: ./binary imagePath" );
		return -1;
	}
	cv::Mat src;
	cv::Mat proc;
	src = cv::imread(argv[1], cv::IMREAD_COLOR); // reads file in path provided

	if (!src.data)
	{
		printf("%s\n","image not found" );
		return -1;
	}
	//image proc section
	proc = threshIm(&src);

	cv::namedWindow( "Source_Image", cv::WINDOW_AUTOSIZE ); // Create a window for display.
    cv::imshow( "Source_Image", src );                // Show our image inside it.

    cv::namedWindow( "Processed_Image", cv::WINDOW_AUTOSIZE ); // Create a window for processed image.
    cv::imshow( "Processed_Image", proc );                

    cv::waitKey(0); // Wait for a keystroke in the window
	return 0;
}
