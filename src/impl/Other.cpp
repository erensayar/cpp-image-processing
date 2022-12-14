#ifdef _WIN32 // Windows Dependencies
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#else // Unix Dependencies
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#endif

#include "../interface/Other.hpp"
#include "../interface/Common.hpp"

using namespace cv;
using namespace std;


// <=====================================================================================>
void videoCapture(string path) {
   VideoCapture cap(path);
   Mat img;
   while (true) {
       cap.read(img);
       imshow("Image", img);
       waitKey(20);
   }
}

// <=====================================================================================>
void webcamCapture() {
    VideoCapture cap(0);
    Mat img;
    while (true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(1);
    }
}

// <=====================================================================================>
void resizeAndCorp(string path) {
	Mat img = imread(path);
	Mat imgResize, imgCrop;
 
	cout << "Image Size: " << img.size() << endl;
	resize(img, imgResize, Size(),0.5,0.5);
 
	Rect roi(200, 100, 300, 300);
	imgCrop = img(roi);
 
	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);
	waitKey(0);
}

// <=====================================================================================>
void drawsShapeAndText() {
    // Blank Image
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
 
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255),FILLED);
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);
	
	putText(img, "Hello World", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255),2);
 
	imshow("Image", img);
	waitKey(0);
}

// <=====================================================================================>
void warpImage(string path) {
	Mat img = imread(path);
	Mat matrix, imgWarp;
	float w = 250, h = 350;
	
	Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
 
	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
 
	for (int i = 0; i < 4; i++) {
		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	}
 
	imshow("Image", img);
	imshow("Image Warp", imgWarp);
	waitKey(0);
}

// <=====================================================================================>
void colorDetection(string path) {
    Mat img = imread(path);
	Mat imgHSV, mask;
	int hmin = 0, smin = 110, vmin = 153;
	int hmax = 19, smax = 240, vmax = 255;
 
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
 
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);
 
	while (true) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
 
		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image Mask", mask);
		waitKey(1);
	}
}

// shapeAndContourDetection
// <=====================================================================================>
void getContours(Mat imgDil, Mat img) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
 
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	 
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;
		string objectType;
 
		if (area > 1000) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            
            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);
            int objCor = (int)conPoly[i].size();
            if (objCor == 3) { 
                objectType = "Tri";
            }
            else if (objCor == 4) {
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                cout << aspRatio << endl;
                if (aspRatio > 0.95 && aspRatio < 1.05) {
                    objectType = "Square";
                }
                else {
                    objectType = "Rect";
                }
            } 
            else if (objCor > 4) {
                objectType = "Circle";
            }

            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
            putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
        }
	}
}

void shapeAndContourDetection(string path) {
    Mat img = imread(path);
	Mat processedImg = preProcessing(img, 3, 3, false);
	getContours(processedImg,img);
	imshow("Image", img);
	waitKey(0);
}

// <=====================================================================================>
void faceDetection(string path) {
    Mat img = imread(path);
 
	CascadeClassifier faceCascade;
	faceCascade.load("../resources/haarcascade_frontalface_default.xml");
	if (faceCascade.empty()) { cout << "XML file not loaded" << endl;}
 
	vector<Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);
 
	for (int i = 0; i < faces.size(); i++) {
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}
 
	imshow("Image", img);
	waitKey(0);
}

// <=====================================================================================>
void colorPicker() {
    VideoCapture cap(0);
    Mat img;
    Mat imgHSV, mask, imgColor;
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;
 
    namedWindow("Trackbars", (640, 200)); // Create Window
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);
 
    while (true) {
        cap.read(img);
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
 
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
 
        inRange(imgHSV, lower, upper, mask);
        // hmin, smin, vmin, hmax, smax, vmax;
        cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;
        imshow("Image", img);
        imshow("Mask", mask);
        waitKey(1);
    }
}