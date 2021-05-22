#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

// object detection and tracking, primarily facial detection and recognition.
#include <opencv2/objdetect.hpp>


using namespace std;
using namespace cv;

///// Face Detection  /////


class FaceDetect {

	Mat img;

	//importing images
	void importImages() {
		//defining the path of the image stored in the project
		String path = "Resources/test.png";

		//read the image on the matrix from the path provided
		//Mat : matrix data type in open cv to handle all the images
		img = imread(path);

		//show the image 
		//imshow(nameOfTheImage,imageMatrix)
		imshow("Image", img);
	}

	void cascadeImage() {
		//cascade the image and detect the face 
		CascadeClassifier faceCascade;

		//xml 
		faceCascade.load("Resources/haarcascade_frontalface_default.xml");

		//check if loaded 
		if (faceCascade.empty()) {
			cout << "\nXml not loaded ! \n";
		}
		else cout << "\nXml loaded !\n";

		//face boundary to display face is detected 
		vector<Rect> faceBoundary;

		//detect the face using cascading 
		faceCascade.detectMultiScale(img, faceBoundary, 1.1, 10);

		//detecting all the images 
		for (int i = 0; i < faceBoundary.size(); i++) {
			rectangle(img, faceBoundary[i].tl(), faceBoundary[i].br(), Scalar(90, 100, 255), 3);
		}

		//displaying the image 
		imshow("Face detection", img);
	}
public:
	void init() {
		importImages();
		cascadeImage();

		waitKey(0);
	}
};

int main() {
	FaceDetect detect;
	detect.init();
	return 0;
}
