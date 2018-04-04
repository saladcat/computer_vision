#include<iostream>
#include<opencv2/opencv.hpp>
#include<cstdlib>

using namespace cv;
using namespace std;

int sett[2000][2000] = { 0 };
int num_of_set;
Mat input_img;
int cols, rows;

int getThreshold(double *histogram);

void bfs(int i, int j, int s, int T) {
	if (i > 0) {
		if (input_img.at<uchar>(i - 1, j) > T && sett[i - 1][j] == 0) {
			sett[i - 1][j] = s;
			bfs(i - 1, j, s, T);
		}
	}
	if (i < rows - 1) {
		if (input_img.at<uchar>(i + 1, j) > T && sett[i + 1][j] == 0) {
			sett[i + 1][j] = s;
			bfs(i + 1, j, s, T);
		}
	}
	if (j > 0) {
		if (input_img.at<uchar>(i, j - 1) > T && sett[i][j - 1] == 0) {
			sett[i][j - 1] = s;
			bfs(i, j - 1, s, T);
		}
	}
	if (j < cols - 1) {
		if (input_img.at<uchar>(i, j + 1) > T && sett[i][j + 1] == 0) {
			sett[i][j + 1] = s;
			bfs(i, j + 1, s, T);
		}
	}

	if (i > 0 && j > 0) {
		if (input_img.at<uchar>(i - 1, j - 1) == T && sett[i - 1][j - 1] == 0) {
			sett[i - 1][j - 1] = s;
			bfs(i - 1, j - 1, s, T);
		}
	}
	if (i < rows - 1 && j > 0) {
		if (input_img.at<uchar>(i + 1, j - 1) == T && sett[i + 1][j - 1] == 0) {
			sett[i + 1][j - 1] = s;
			bfs(i + 1, j - 1, s, T);
		}
	}
	if (i < rows - 1 && j < cols - 1) {
		if (input_img.at<uchar>(i + 1, j + 1) == T && sett[i + 1][j + 1] == 0) {
			sett[i + 1][j + 1] = s;
			bfs(i + 1, j + 1, s, T);
		}
	}
	if (i > 0 && j < cols - 1) {
		if (input_img.at<uchar>(i - 1, j + 1) == T && sett[i - 1][j + 1] == 0) {
			sett[i - 1][j + 1] = s;
			bfs(i - 1, j + 1, s, T);
		}
	}
}

class rgb {
public:
	int r;
	int g;
	int b;
};

int main() {
	double histogram[256];
	memset(histogram, 0, sizeof(histogram));
	input_img = imread(R"(C:\code\DIP\lab3\input1.jpg)");
	Mat output_img = input_img.clone();

	cvtColor(input_img, input_img, COLOR_BGR2GRAY);

	cols = input_img.cols;
	rows = input_img.rows;

	num_of_set = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			histogram[input_img.at<uchar>(i, j)]++;
		}
	}
	int T = getThreshold(histogram);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (input_img.at<uchar>(i, j) > T) {
				if (sett[i][j] == 0) {
					sett[i][j] = num_of_set + 1;
					bfs(i, j, num_of_set + 1, T);
					num_of_set++;
				}

			}

		}
	}
	rgb *color = new rgb[num_of_set + 1];
	for (int i = 0; i < num_of_set + 1; i++) {
		color[i].r = rand() % 256;
		color[i].g = rand() % 256;
		color[i].b = rand() % 256;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (sett[i][j] != 0) {
				output_img.at<Vec3b>(i, j)[0] = color[sett[i][j]].b;
				output_img.at<Vec3b>(i, j)[1] = color[sett[i][j]].g;
				output_img.at<Vec3b>(i, j)[2] = color[sett[i][j]].r;
			}
		}
	}
	imshow("input", input_img);
	imshow("output_img", output_img);
	waitKey(0);
	return 0;

}

int getThreshold(double *histogram) {
	int T = 0;
	double maxBetween = -1;
	for (int index = 1; index < 256; index++) {
		double sumLeft = std::accumulate(histogram, histogram + index, 0.0);
		double sumRight = std::accumulate(histogram + index, histogram + 256, 0.0);
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
