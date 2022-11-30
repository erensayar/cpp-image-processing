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

#include "LicensePlateRecognition.hpp"

using namespace cv;
using namespace std;

void licensePlateRecognition() {
    Mat img;
	VideoCapture cap(0);
 
	CascadeClassifier plateCascade;
	plateCascade.load("../resources/haarcascade_russian_plate_number.xml");
 	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }
 
	vector<Rect> plates;
	while (true) {
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);
 
		for (int i = 0; i < plates.size(); i++) {
			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("../resources/Plates/" + to_string(i) + ".png", imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
		}
 
		imshow("Image", img);
		waitKey(1);
	}
}