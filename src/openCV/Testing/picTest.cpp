#include <iostream>
#include <opencv2/opencv.hpp>
#include "Header.cpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{

	Mat image = imread(argv[1]);
	if(image.data == NULL)
		return 0;

	Mat thresholded;
	Mat hsvImage;

	int hueUpper = 50;
	int hueLower = 25;
	int sat = 90;
	int lum = 60;
	

	namedWindow("webCam", WINDOW_AUTOSIZE);
	namedWindow("raw", WINDOW_AUTOSIZE);
	createTrackbar("hueLower:", "webCam", &hueLower, 255);
	createTrackbar("hueUpper:", "webCam", &hueUpper, 255);
	createTrackbar("sat:", "webCam", &sat, 255);
	createTrackbar("lum:", "webCam", &lum, 255);

	for(;;)
	{
		cvtColor(image, hsvImage, CV_RGB2HSV);

		//lower hue seems like ~25 - 30 good range
		//upper hue seems like ~35 - 50 good range
		//sat unknown
		//lum ~60 looks really nice
		applyThreshold(hueLower,hueUpper,sat,lum, hsvImage, thresholded);
		determineHot(thresholded, image);

		imshow("webCam", thresholded);
		imshow("raw", image);
		//spacebar key code = 32
		if(waitKey(10) == 32)
			break;
	}//end for

}//end main
