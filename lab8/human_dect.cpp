#include <opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <iostream>  


using namespace std;
using namespace cv;

int main() {
	VideoCapture capture("pedestrian.mp4");
	Mat input_img=imread("4.png");
	Mat gray;
	HOGDescriptor myHOG;
	myHOG.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
/*	std::vector<cv::Rect> regions;

	myHOG.detectMultiScale(input_img, regions, 0.8, cv::Size(6, 6), cv::Size(16, 16), 1.05, 0.2, true);
	//myHOG.detectMultiScale(input_img, regions, 0, cv::Size(6, 6), cv::Size(16, 16), 1.05, 1, true);

	for (size_t i = 0; i < regions.size(); i++) {
		cv::rectangle(input_img, regions[i], cv::Scalar(0, 0, 255), 2);
	}

	cv::imshow("hog", input_img);
	cv::waitKey(0);

	*/


	while (true) {
		capture >> input_img;
		if (input_img.empty()) {
			break;
		}
		std::vector<cv::Rect> regions;	
		myHOG.detectMultiScale(input_img, regions, 0.5, cv::Size(6, 6), cv::Size(16, 16), 1.05, 0.85, true);
		for (size_t i = 0; i < regions.size(); i++) {
			cv::rectangle(input_img, regions[i], cv::Scalar(0, 0, 255), 2);
		}
		
		cv::imshow("hog", input_img);
		cv::waitKey(33);
	}

	return 0;
}