//
// Created by zhu on 2018/3/3.
//

#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>

using namespace std;
using namespace cv;

void bilinear_interpolation(Mat &input, Mat &output, float scalingFactor);

int main(int argc, char **argv) {

	Mat inputImg = imread(argv[1]);
	float scalingFactor = atof(argv[2]);

	int scaledWidth = static_cast<int>(round(1. * inputImg.cols * scalingFactor));
	int scaledHeight = static_cast<int>(round(1. * inputImg.rows * scalingFactor));

	Mat outputImg1 = Mat(scaledHeight, scaledWidth, inputImg.type());
	Mat outputImg2; // for opencv build-in function

	bilinear_interpolation(inputImg, outputImg1, scalingFactor);
	resize(inputImg, outputImg2, Size(), scalingFactor, scalingFactor, INTER_LINEAR);

	imshow("My Interpolation", outputImg1);
	imshow("openCV build-in function", outputImg2);
	waitKey(0);

	imwrite("output.jpg", outputImg1);

	return 0;
}


void bilinear_interpolation(Mat &input, Mat &output, float scalingFactor) {

	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {
			double rRow = i / scalingFactor;
			double rCol = j / scalingFactor;
			for (int k = 0; k < 3; k++) {
				auto ld = input.at<Vec3b>(floor(rRow) + 1, floor(rCol))[k];
				auto rd = input.at<Vec3b>(floor(rRow) + 1, floor(rCol) + 1)[k];
				auto lu = input.at<Vec3b>(floor(rRow), floor(rCol))[k];
				auto ru = input.at<Vec3b>(floor(rRow), floor(rCol) + 1)[k];
				auto upTemp = (rCol - floor(rCol)) * ru + (floor(rCol) + 1 - rCol) * lu;
				auto downTemp = (rCol - floor(rCol)) * rd + (floor(rCol) + 1 - rCol) * ld;
				output.at<Vec3b>(i, j)[k] = (rRow - floor(rRow)) * downTemp +
					(floor(rRow) + 1 - rRow) * upTemp;
			}
		}
	}
}

