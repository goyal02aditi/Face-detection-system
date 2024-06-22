#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/*void main() {
	string path = "rishin.jpg";
	Mat	img = imread(path);
	imshow("Frame", img);
	waitKey(0);
}*/

void main() {
    VideoCapture video(0);  // Change to 0 if you have only one camera
    if (!video.isOpened()) {
        cerr << "Error: Could not open video capture" << endl;
        return;
    }

    CascadeClassifier facedetect;
    if (!facedetect.load("haarcascade_frontalface_default.xml")) {
        cerr << "Error: Could not load Haar cascade file" << endl;
        return;
    }

    Mat img;

    while (true) {
        video.read(img);
        if (img.empty()) {
            cerr << "Error: Could not read frame from video" << endl;
            break;
        }

        vector<Rect> faces;
        try {
            facedetect.detectMultiScale(img, faces, 1.3, 5);
        }
        catch (cv::Exception& e) {
            cerr << "Error during face detection: " << e.what() << endl;
            break;
        }

        cout << faces.size() << endl;

        for (int i = 0; i < faces.size(); i++) {
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 3);
            rectangle(img, Point(0, 0), Point(250, 70), Scalar(50, 50, 255), FILLED);
            putText(img, to_string(faces.size()) + " Face Found", Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);
        }

        imshow("Frame", img);
        if (waitKey(1) >= 0) break;  // Exit loop if any key is pressed
    }
}