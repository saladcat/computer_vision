#include <cstdio>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// write down your warping function here

void onMouse(int event, int x, int y, int flags, void* param) {
	vector<Point2f>* ptr = (vector<Point2f>*) param;
	if (event == CV_EVENT_LBUTTONDOWN) {
		ptr->push_back(Point2f(x, y));
	}
}

int main() {
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		return -1;
	}
	Mat image;
	image = imread("warping.jpg");

	Mat frame;
	cap >> frame;

	vector<Point2f> cap_corner;
	vector<Point2f> img_corner;

	// add the corner of frame into cap_corner	

	namedWindow("img", CV_WINDOW_AUTOSIZE);
	setMouseCallback("img", onMouse, &img_corner);

	while (img_corner.size()<4) {
		imshow("img", image);
		if (waitKey(1) == 27) break;
	}


	Mat img_out = image.clone();
	Mat img_temp = image.clone();
	Mat h = findHomography(cap_corner, img_corner);
	// call your warping function

	Point poly[4];
	for (int i = 0; i < img_corner.size(); i++) {
		poly[i] = img_corner[i];
	}

	while (1) {
		cap >> frame;
		// call your warping function 	
		fillConvexPoly(img_out, poly, 4, Scalar(0), CV_AA);
		img_out = img_out + img_temp;
		imshow("img", img_out);
		if (waitKey(1) == 27) break;
	}
	return 0;
}

