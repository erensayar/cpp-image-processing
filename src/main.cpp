#ifdef _WIN32 // Windows Dependencies
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#else // Unix Dependencies
#include <iostream>
#include <opencv2/opencv.hpp>
#endif

using namespace cv;
using namespace std;

// METHODS
// <====================================================================================>
Mat readImage(string path) {
    Mat image = imread(path, 1);
    if (!image.data) {
        cout << ("No image data");
        return Mat();
    }
    return image;
}

void showImage(Mat image){
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
}

void videoCapture(string path){
   VideoCapture cap(path);
   Mat img;
   while (true) {
       cap.read(img);
       imshow("Image", img);
       waitKey(20);
   }
}

void webcamCapture() {
    VideoCapture cap(0);
    Mat img;
    while (true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(1);
    }
}

// MAIN
// <====================================================================================>

int main(int argc, char **argv) {

    int input;
    string path;
    Mat img;
    bool loopVal = true;

    while (loopVal) {
        cout << "Choose Process" << endl;
        cout << "1. Show Image" << endl;
        cout << "2. Video Capture" << endl;
        cout << "3. Show Video" << endl;

        cout << "INPUT: ";
        cin >> input; 

        switch(input) {
            case 1:
                cout << "Enter image path according to your path: ";
                cin >> path;
                img = readImage(path);
                showImage(img);
                break;
            case 2:
                cout << "Enter video path according to your path: ";
                cin >> path;
                videoCapture(path);
                break;
            case 3:
                webcamCapture();
                break;
            default:
                cout << "Enter valid value\n";
        }
    }
    
    return 0;
}

// NOTES
// <====================================================================================>

// EXAMPLE : Image path take as argument
/*
int main(int argc, char **argv) {
    if (argc != 2) {
        cout << ("USAGE: app.exe <Image_Or_Video_Path>");
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
}
*/