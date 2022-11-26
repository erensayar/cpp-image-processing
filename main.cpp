#ifdef _WIN32 // Windows Dependencies
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#else // Unix Dependencies
#include <iostream>
#include <opencv2/opencv.hpp>
#endif

using namespace cv;
using namespace std;

// <================== Image =================>
int main(int argc, char **argv) {
    if (argc != 2) {
        cout << ("USAGE: App <Image_Path>");
        return -1;
    }
    Mat image = imread(argv[1], 1);
    if (!image.data) {
        cout << ("No image data");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}

// <================== Video =================>
/*
int main() {
   string path = "../resources/test_video.mp4";
   VideoCapture cap(path);
   Mat img;
   while (true) {
       cap.read(img);
       imshow("Image", img);
       waitKey(20);
   }
   return 0;
}
*/

// <================= Webcam =================>
/*
int main() {
    VideoCapture cap(0);
    Mat img;
    while (true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(1);
    }
    return 0;
}
*/