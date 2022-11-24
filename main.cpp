#ifdef _WIN32 // Windows Dependencies
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#else // Unix Dependencies
#include <iostream>
#include </usr/local/include/opencv4/opencv2/opencv.hpp>
#include </usr/local/include/opencv4/opencv2/imgcodecs.hpp>
#include </usr/local/include/opencv4/opencv2/highgui.hpp>
#include </usr/local/include/opencv4/opencv2/highgui/highgui.hpp>
#include </usr/local/include/opencv4/opencv2/imgproc.hpp>
#endif

using namespace cv;
using namespace std;

#if defined(_GLIBCXX_HAS_GTHREADS) && defined(_GLIBCXX_USE_C99_STDINT_TR1)
#endif

/////////////////  Images  //////////////////////
int main() {
    //string path = "~/MEGA/CODES/C-Cpp/cpp-image-processing/resources/paper.jpg";
    string path = "C:/Users/xresayar/Desktop/Codes/Codes-Personal/C++/cpp-image-processing/resources/paper.jpg";
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);
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