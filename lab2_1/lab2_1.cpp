#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
const int maxNum = 256;

int main() {
	int gray[maxNum];
	double histogram[maxNum];
	memset(gray, 0, sizeof(gray));
	Mat input = imread(R"(C:\Users\zhu\Desktop\mj.tif)");
	cvtColor(input, input, COLOR_BGR2GRAY);
	Mat output = input.clone();
	int count = input.rows * input.cols;
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			gray[static_cast<int> (input.at<uchar>(i, j))]++;
		}
	}
	for (int i = 0; i < maxNum; i++) {
		histogram[i] = gray[i];
	}
	for (int i = 1; i < maxNum; i++) {
		histogram[i] += histogram[i - 1];
	}
	for (double &item : histogram) {
		item = static_cast<int>(item / count * (maxNum - 1));
	}
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			uchar usedGray = input.at<uchar>(i, j);
			output.at<uchar>(i, j) = static_cast<uchar>(histogram[usedGray]);
			//            output.at<uchar>(i, j) = 0;
		}
	}
	imshow("input", input);
	imshow("output", output);
	waitKey(0);
	return 0;
}