#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>

using namespace std;
using namespace cv;

int getThreshold(double *histogram);

int main() {
	double histogram[256];
	memset(histogram, 0, sizeof(histogram));
	Mat input = imread(R"(C:\code\DIP\lab3\input1.jpg)");
	cvtColor(input, input, COLOR_BGR2GRAY);
	Mat output = input.clone();
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			histogram[input.at<uchar>(i, j)]++;
		}
	}

	int index = getThreshold(histogram);

	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			output.at<uchar>(i, j) = static_cast<uchar>((output.at<uchar>(i, j) > index)
				? 255 : 0);
		}
	}
	imshow("input", input);
	imshow("output", output);
	waitKey(0);
	return 0;
}

int getThreshold(double *histogram) {
	int T = 0;
	double maxBetween = -1;
	for (int index = 1; index < 256; index++) {
		double sumLeft = accumulate(histogram, histogram + index, 0.0);
		double sumRight = accumulate(histogram + index, histogram + 256, 0.0);
		double aveLeft = 0;
		double aveRight = 0;
		for (int i = 0; i < index; i++) {
			aveLeft += histogram[i] * i;
		}
		aveLeft /= sumLeft;
		for (int i = index; i < 256; i++) {
			aveRight += histogram[i] * i;
		}
		aveRight /= sumRight;
		if (maxBetween <
			sumLeft * sumRight * (aveLeft - aveRight) * (aveLeft - aveRight)) {
			maxBetween = sumLeft * sumRight * (aveLeft - aveRight) * (aveLeft - aveRight);
			T = index;
		}
	}
	return T;
}

