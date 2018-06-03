#include <cstdio>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
int main(int argc, char** argv) {
	/* VideoCapture cap(0);
	if (!cap.isOpened()) {
		return -1;
	}
    */
	Mat image;
	image = imread(argv[1]);

    String face_cascade_name = "/home/jeff/opencv/data/haarcascades/haarcascade_frontalface_alt.xml";
    //String face_cascade_name = "/home/jeff/opencv/data/haarcascades/haarcascade_frontalface_default.xml";
    //String face_cascade_name = "/home/jeff/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml";
    CascadeClassifier face_cascade;
    if(!face_cascade.load(face_cascade_name))
        printf("load classifier error\n");
    

    Mat img_gray;

    cvtColor( image, img_gray, CV_BGR2GRAY );
    equalizeHist( img_gray, img_gray );

    vector<Rect> faces;
    face_cascade.detectMultiScale( img_gray, faces, 1.1, 3, 0, Size(20, 20) );

    for( size_t i = 0; i < faces.size(); i++ ) {
        if(faces[i].height > 0 && faces[i].width > 0)
            rectangle(image, faces[i], Scalar(0, 0, 255),3,8,0);
    }
    imshow("imgg", image);
    printf("%ld\n", faces.size());
    imwrite("output.jpg", image);
    waitKey(0);




	return 0;
}

