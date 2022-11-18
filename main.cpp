#ifdef _WIN32
// Windows
#else
// Unix
#include </usr/local/include/opencv4/opencv2/opencv.hpp>
#include </usr/local/include/opencv4/opencv2/imgcodecs.hpp>
#include </usr/local/include/opencv4/opencv2/highgui.hpp>
#include </usr/local/include/opencv4/opencv2/highgui/highgui.hpp>
#include </usr/local/include/opencv4/opencv2/imgproc.hpp>
#include <iostream>
#endif

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////
int main() {
    string path = "~/MEGA/CODES/C-Cpp/cpp-image-processing/resources/paper.png";
    Mat img = imread(path);
    Mat gray;
    bilateralFilter(img, gray, 10, 50, 0);
    imwrite("~/Documents", gray);
    //imshow("Image", img);
    //waitKey(0);
    return 0;
}


///////////////  Video  //////////////////////
//void main() {
//
//	string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//	while (true) {
//
//		cap.read(img);
//		imshow("Image", img);
//		waitKey(20);
//	}
//}


/////////////////  Webcam  //////////////////////
//void main() {
//
//	VideoCapture cap(0);
//	Mat img;
//
//	while (true) {
//
//		cap.read(img);
//		imshow("Image", img);
//		waitKey(1);
//	}
//}