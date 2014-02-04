#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include "Header.cpp"

using namespace cv;

void exitHandler(int s)
{
	std::cout << "Ctrl-c pressed!" << std::endl;
	exit(1);
}

int main(int argc, char *argv[])
{
	VideoCapture webCam(1);
	if(!webCam.isOpened())
		return -1;

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

	namedWindow("webCam", WINDOW_AUTOSIZE);
	namedWindow("raw", WINDOW_AUTOSIZE);
	createTrackbar("hueLower:", "webCam", &hueLower, 255);
	createTrackbar("hueUpper:", "webCam", &hueUpper, 255);
	createTrackbar("sat:", "webCam", &sat, 255);
	createTrackbar("lum:", "webCam", &lum, 255);

	//fps stuff
	time_t start, end;
	int counter = 0;
	double sec, fps;
	for(;;)
	{

		if(counter == 0)
			//record start
			time(&start);

		webCam >> imageFrame;

		cvtColor(imageFrame, hsvImage, CV_RGB2HSV);

		applyThreshold(hueLower,hueUpper,sat,lum, hsvImage, thresholded);
		determineHot(thresholded, imageFrame);

		imshow("webCam", thresholded);
		imshow("raw", imageFrame);

		//record end and calculate
		time(&end);
		counter++;
		sec = difftime(end, start);
		fps = counter/sec;
		if(counter > 30)
		{
			printf("%.2f fps\n", sec);
			counter = 0;
		}


		//spacebar key code = 32
		if(waitKey(10) == 32)
			break;
	}//end for

}//end main

