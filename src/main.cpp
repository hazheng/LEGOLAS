#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace std;

cv::Mat threshIm(cv::Mat image_in){
	cv::Mat hsv;
	cv::cvtColor(image_in,hsv,cv::CV_BGR2HSV);
	return hsv;
}

int main(int argc, char** argv)
{ 
	if (argc!=2)
	{
		printf("%s\n","Usage: ./binary imagePath" );
		return -1;
	}
	cv::Mat image;
	image = cv::imread(argv[1], cv::IMREAD_COLOR); // reads file in path provided

	if (!image.data)
	{
		printf("%s\n","image not found" );
		return -1;
	}
	//image proc section
	cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE ); // Create a window for display.
    cv::imshow( "Display window", image );                // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
	return 0;
}
