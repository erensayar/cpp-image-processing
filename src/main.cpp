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

void basicImageProcess(string path) {
    Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
 
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
	Canny(imgBlur, imgCanny, 25,75);
 
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgErode, kernel);
 
	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDil);
	imshow("Image Erode", imgErode);
	waitKey(0);
}

void resizeAndCorp(string path){
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
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
 
	// Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
 
	getContours(imgDil,img);
 
	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	//imshow("Image Canny", imgCanny);
	//imshow("Image Dil", imgDil);
 
	waitKey(0);
}

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


// MAIN
// <====================================================================================>

int main(int argc, char **argv) {

    int input;
    string path = "../resources/test.png";
    Mat img;
    bool loopVal = true;
    string changePathAnswer;

    //cout << "Enter image path according to app path: ";
    //cin >> path;

    while (loopVal) {
        cout << "Choose Process" << endl;
        cout << "1. Show Image" << endl;
        cout << "2. Video Capture" << endl;
        cout << "3. Show Video" << endl;
        cout << "4. Basic Image Processes" << endl;
        cout << "5. Resize And Corp" << endl;
        cout << "6. Draw Shapes & Text" << endl;
        cout << "7. Warp Image" << endl;
        cout << "8. Color Detection" << endl;
        cout << "9. Shape And Contour Detection" << endl;
        cout << "10. Face Detection" << endl;

        cout << "INPUT: ";
        cin >> input; 

        switch(input) {
            case 1:
                img = readImage(path);
                showImage(img);
                break;

            case 2:
                /*
                cout << "Do you want to change the file path?(Y/N) " << endl;
                cin >> changePathAnswer;
                if(changePathAnswer.compare("Y")){
                    cout << "Enter video path according to your path: ";
                    cin >> path;
                }
                */
                videoCapture("../resources/shapes.png");
                break;

            case 3:
                webcamCapture();
                break;

            case 4:
                basicImageProcess(path);
                break;
            
            case 5:
                resizeAndCorp(path);
                break;

            case 6:
                drawsShapeAndText();
                break;

            case 7:
                warpImage("../resources/cards.jpg");
                break;

            case 8:
                colorDetection(path);
                break;

            case 9:
                shapeAndContourDetection("../resources/shapes.png");
                break;        

            case 10:
                faceDetection("../resources/presidents.jpg");
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