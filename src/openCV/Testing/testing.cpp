#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{


	VideoCapture webCam(0);
	if(!webCam.isOpened())
		return -1;

	Mat thresholded;
	Mat imageFrame;
	Mat hsvImage;

	namedWindow("webCam", WINDOW_AUTOSIZE);
	namedWindow("hueVal", WINDOW_AUTOSIZE);
	namedWindow("satVal", WINDOW_AUTOSIZE);
	namedWindow("lumVal", WINDOW_AUTOSIZE);

	for(;;)
	{
		webCam >> imageFrame;
 
		cvtColor(imageFrame, hsvImage, CV_RGB2HSV);

		//applyThreshold(hueLower,hueUpper,sat,lum, hsvImage, thresholded);

		int something1 = 125;
		unsigned char something = something1;

		std::cout << (int)something << std::endl;
		

		Mat hueVal;
		Mat satVal;
		Mat lumVal;
		Mat HSV[3] = {hueVal, satVal, lumVal};

		Mat temp;
		Mat temp2;

		split(hsvImage, HSV);
		//threshold(input, output, lower bound, upper bound)
		//80 = lower bound of green
		//150 = upper bound of green
		threshold(HSV[0], temp, 80, 255, THRESH_BINARY);
		threshold(HSV[0], temp2, 128, 255, THRESH_BINARY_INV);

		bitwise_and(temp, temp2, HSV[0]);

		threshold(HSV[1], HSV[1], 100, 255, THRESH_BINARY);
		threshold(HSV[2], HSV[2], 100, 255, THRESH_BINARY);

		imshow("hueVal", HSV[0]);
		imshow("satVal", HSV[1]);
		imshow("lumVal", HSV[2]);

		//spacebar key code = 32
		if(waitKey(10) == 32)
			break;
	}//end for

}//end main
