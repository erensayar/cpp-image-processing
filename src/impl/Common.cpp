#ifdef _WIN32 // Windows Dependencies
#include <iostream>
#include <opencv2/opencv.hpp>

#else // Unix Dependencies
#include <iostream>
#include <opencv2/core.hpp>
#endif

#include "../interface/Common.hpp"

using namespace cv;
using namespace std;


Mat preProcessing(Mat img, int size, double sigmaX, bool isShowEveryStepProcessedImg) {
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(size, size), sigmaX, 0);
 // GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
 //	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgErode, kernel);

    if (isShowEveryStepProcessedImg) {
        imshow("Image", img);
	    imshow("Image Gray", imgGray);
	    imshow("Image Blur", imgBlur);
	    imshow("Image Canny", imgCanny);
	    imshow("Image Dil", imgDil);
	    imshow("Image Erode", imgErode);
        waitKey(0);
    }

	return imgDil;
}


Mat readImage(string path) {
    Mat image = imread(path, 1);
    if (!image.data) {
        cout << ("No image data");
        return Mat();
    }
    return image;
}

void clearTerminalOutput() {
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}