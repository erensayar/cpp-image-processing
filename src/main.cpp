#ifdef _WIN32 // Windows Dependencies
#include <iostream>
#include <opencv2/opencv.hpp>

#else // Unix Dependencies
#include <iostream>
#include <opencv2/opencv.hpp>
#endif

#include "./interface/VirtualPaint.hpp"
#include "./interface/DocumentScanner.hpp"
#include "./interface/LicensePlateRecognition.hpp"
#include "./interface/Other.hpp"
#include "./interface/Common.hpp"

using namespace cv;
using namespace std;

string path = "../resources/test.png";

int main(int argc, char **argv) {

    int input;
    Mat img;
    bool loopVal = true;

    //cout << "Enter image path according to app path: ";
    //cin >> path;

    while (loopVal) {
        clearTerminalOutput();
        cout << "\nChoose Process" << endl;
        cout << "01. Show Image" << endl;
        cout << "02. Video Capture" << endl;
        cout << "03. Webcam Capture" << endl;
        cout << "04. Basic Image Processes" << endl;
        cout << "05. Resize And Corp" << endl;
        cout << "06. Draw Shapes & Text" << endl;
        cout << "07. Warp Image" << endl;
        cout << "08. Color Detection" << endl;
        cout << "09. Shape And Contour Detection" << endl;
        cout << "10. Face Detection" << endl;
        cout << "11. Color Picker" << endl;
        cout << "12. Virtual Paint" << endl;
        cout << "13. Document Scanner" << endl;  
        cout << "14. License Plate Recognition" << endl;              

        cout << "\nINPUT: ";
        cin >> input; 

        switch(input) {
            case 1:
                img = readImage(path);
                namedWindow("Display Image", WINDOW_AUTOSIZE);
                imshow("Display Image", img);
                waitKey(0);
                break;

            case 2:
                //changeSourcePathQuestion();
                videoCapture("../resources/test_video.mp4");
                break;

            case 3:
                webcamCapture();
                break;

            case 4:
                preProcessing(readImage(path), 7, 5, true);
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

            case 11:
                colorPicker();
                break;     

            case 12:
                virtualPaint();
                break;     

            case 13:
                documentScanner("../resources/paper.jpg");
                break;     
                
            case 14:
                licensePlateRecognition();
                break;     

            default:
                cout << "Enter valid value\n";
        }
    }
    
    return 0;
}

/*
void changeSourcePathQuestion() {
    string changePathAnswer;
    cout << "Do you want to change the file path?(Y/N) " << endl;
    cin >> changePathAnswer;
    if(changePathAnswer.compare("Y")){
        cout << "Enter video path according to your path: ";
        cin >> path;
    }          
}
*/

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