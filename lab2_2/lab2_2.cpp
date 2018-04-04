//
// Created by zhu on 2018/3/8.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void doMask(Mat &output, Mat &input, int i, int j);

const int maxNum = 256;

int main() {
	Mat input = imread(R"(C:\Users\zhu\Desktop\mj.tif)");
	cvtColor(input, input, COLOR_BGR2GRAY);
	Mat output = input.clone();
	for (int i = 1; i < output.rows - 1; i++) {
		for (int j = 1; j < output.cols - 1; j++) {
			doMask(output, input, i, j);
		}
	}
	imshow("output", output);
	imshow("input", input);
	waitKey(0);
	return 0;
}

void doMask(Mat &output, Mat &input, int i, int j) {
	int tem = input.at<uchar>(i - 1, j) +
		input.at<uchar>(i + 1, j) +
		input.at<uchar>(i, j - 1) +
		input.at<uchar>(i, j + 1) -
		4 * input.at<uchar>(i, j);
	if (tem > 255) {
		output.at<uchar>(i, j) = 255;
	} else if (tem < 0) {
		output.at<uchar>(i, j) = 0;
	} else {
		output.at<uchar>(i, j) = static_cast<uchar>(tem);
	}
}

