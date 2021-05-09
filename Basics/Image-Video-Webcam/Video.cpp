#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;


//importing videos
void importVideos() {
	//video is a series of images or frames
	//we will need while loop 

	//defining the path of the video
	string path = "Resources/test_video.mp4";

	//capturing the images of the video 
	VideoCapture videoCapture(path);

	//stores the captured image in the image matrix
	Mat img;

	while (true) {
		//storing the image in image matrix
		videoCapture.read(img);

		//when no image to display : end of loop
		if (img.empty()) {
			cout << " --- END -- OF -- IMAGE --- ";
			break;
		}

		//display the captured image 
		imshow("Image", img);

		//delay should not be infinity in this case
		//parameter :  20 ms
		waitKey(2);

	}
}


//main function

int main() {

	//import videos
	importVideos();

	return 0;
}
