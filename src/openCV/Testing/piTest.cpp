#include <iostream>
#include <signal.h>
#include "Header.cpp"

using namespace cv;

void exitHandler(int s)
{
	std::cout << "Ctrl-c pressed!" << std::endl;
	exit(1);
}


int main(int argc, char *argv[])
{
	std::cout << "started" << std::endl;

	VideoCapture webCam(0);
	if(!webCam.isOpened())
		return -1;

	std::cout << "webcam opened" << std::endl;

	Mat thresholded;
	Mat imageFrame;
	Mat hsvImage;

	int hueLower = 25;
	int hueUpper = 50;
	int sat = 90;
	int lum = 100;

	//establish ctrl-c listener
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = exitHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	for(;;)
	{
		webCam >> imageFrame;

		cvtColor(imageFrame, hsvImage, CV_RGB2HSV);

		applyThreshold(hueLower,hueUpper,sat,lum, hsvImage, thresholded);
		std::cout << determineHot(thresholded, imageFrame)<< std::endl;


	}//end for

}//end main
