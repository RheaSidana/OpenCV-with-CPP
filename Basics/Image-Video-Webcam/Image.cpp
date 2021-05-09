#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

//importing images
void importImages() {
	//defining the path of the image stored in the project
	String path = "Resources/test.png";

	//read the image on the matrix from the path provided
	//Mat : matrix data type in open cv to handle all the images
	Mat img = imread(path);

	//show the image 
	//imshow(nameOfTheImage,imageMatrix)
	imshow("Image", img);

	//add delay to view the output
	//parameter: 0 for infinity
	waitKey(0);
}


//main function

int main() {
	//importing images 
	importImages();

	return 0;
}
