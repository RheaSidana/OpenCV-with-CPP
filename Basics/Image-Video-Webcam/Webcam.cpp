#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

//importing video from webcam
void importVideoWebcam() {
	//capture webcam 
	//parameter : 0 : camera id (can be 1,2,3...)
	VideoCapture webcamVideo(0);

	//stores the captured image in the image matrix
	Mat img;

	while (true) {
		//storing the image in image matrix
		webcamVideo.read(img);

		//display the captured image 
		imshow("Webcam", img);

		//delay should not be infinity in this case
		//parameter :  20 ms
		waitKey(2);

	}
}

//main function

int main() {
  
	//import video from webcam 
	importVideoWebcam();

	return 0;
}
