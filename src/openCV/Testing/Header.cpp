#include <iostream>
#include <opencv2/opencv.hpp>
#include "Gpio.cpp"

using namespace cv;
using namespace std;

void applyThreshold(unsigned char, unsigned char, unsigned char, unsigned char, Mat, Mat&);
bool determineHot(Mat input, Mat output);
double distance2(Point, Point);

//hueLower = lowerbound for hue filter
//hueYpper = upperbound for hue filter
//sat = lower bound for saturation filter
//lum = lower bound for luminousity filter
//src = source Mat
//out = Mat that the thresholded image will be output to
void applyThreshold(unsigned char hueLower, unsigned char hueUpper, unsigned char sat, unsigned char lum, Mat src, Mat& out)
{
	Mat hueVal;
	Mat satVal;
	Mat lumVal;
	Mat HSV[3] = {hueVal, satVal, lumVal};

	Mat temp;
	Mat temp2;

	split(src, HSV);

	//threshold(input, output, lower bound, upper bound)
	//80 = lower bound of green
	//150 = upper bound of green
	//1 as lo
	threshold(HSV[0], temp2, hueLower, 255, THRESH_BINARY);
	threshold(HSV[0], temp, hueUpper, 255, THRESH_BINARY_INV);

	bitwise_and(temp, temp2, HSV[0]);

	threshold(HSV[1], HSV[1], sat, 255, THRESH_BINARY);
	threshold(HSV[2], HSV[2], lum, 255, THRESH_BINARY);

	bitwise_and(HSV[0], HSV[1], out);
	bitwise_and(HSV[2], out, out);
}

bool determineHot(Mat input, Mat output)
{
	bool isHot = false;

	//finds the contours
	vector< vector<Point> > contours;
	findContours(input, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

	vector<Rect> boundRect(contours.size());

	//goes through every contour and determine if it is part of what we want
	for(int i=0; i < contours.size(); i++)
	{
		Rect rect(boundingRect(contours[i]));

		//calculate rectangular score
		double particleArea = contourArea(contours[i]);
		double boundBoxArea = rect.width * rect.height;
		double score		= (particleArea / boundBoxArea) * 100;

		//if the score is above certain amount, keep rectangle
		if(score > 60)
			boundRect[i] = rect;

		//compare every rectangle with eachother to see if they are close enough to form a target pair
		for(int j=0; j < i; j++)
		{
			//if one rectangle is horizontal and the other is vertical
			//(if its width is > its height)
			//then check to see how far away their corners are
			if(	boundRect[i].width > boundRect[i].height &&
				boundRect[j].width < boundRect[j].height)
			{
				//calc score for distance (from center of the rectangles)
				double dist;

				//if the horizontal rectangle is on the right of the vertical use top left and top left
				//if it's on the left, use bottom right and top left
				if(boundRect[i].tl().x > boundRect[j].tl().x)
				{
					dist = distance2(boundRect[i].tl(), boundRect[j].tl());

					double shouldBe = 2 * boundRect[j].width;
					double distScore = 100 * (shouldBe/dist);


					//if the score meets requirements, draw a rectangle around pair
					if( distScore > 85)
					{
						//calc bottom right corner
						int brY = boundRect[i].br().y + boundRect[j].height;
						int brX = boundRect[i].br().x;

						//calc top left corner
						int tlY = boundRect[i].tl().y;
						int tlX = boundRect[j].tl().x;
						rectangle(output, Point(tlX, tlY), Point(brX, brY), Scalar( 0,255,0), 4);
						isHot = true;
					}//endif
				}
				else
				{
					dist = distance2(boundRect[i].br(), boundRect[j].tl());

					double shouldBe = 2 * boundRect[j].width;
					double distScore = 100 * (shouldBe/dist);

					//if the score meets requirements, draw a rectangle around pair
					if( distScore > 85)
					{
						//calc bottom right corner
						int brY = boundRect[i].br().y + boundRect[j].height;
						int brX = boundRect[j].br().x;

						//calc top left corner
						int tlY = boundRect[i].tl().y;
						int tlX = boundRect[i].tl().x;
						rectangle(output, Point(tlX, tlY), Point(brX, brY), Scalar( 0,255,0), 4);
						isHot = true;
					}//endif
				}//end if
			}//end if
		}//end for
	}//end for

	return isHot;
}

double distance2(Point first, Point second)
{
	double distance = sqrt(pow(second.x - first.x,2) + pow(second.y - first.y,2));

	return distance;
}