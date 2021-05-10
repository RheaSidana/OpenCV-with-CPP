#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

///// Image : Basic Functions /////

class ImageBasicFunctions {
	//read the image on the matrix from the path provided
	//Mat : matrix data type in open cv to handle all the images
	Mat img;

	//store the gray scale image
	Mat imgGray;

	//img matrix to store blur image 
	Mat imgBlur;

	//stores the edges fromed in the image 
	Mat imgCanny;

	//store dilated image
	Mat imgDilate;

	//store the erode image 
	Mat imgErode;

	//store structuringElement
	//getStructuringElement(shape,size)
	//size :  greater : more dilation (always use odd numbers as parameters
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

	//importing images
	void importImage() {
		//defining the path of the image stored in the project
		String path = "Resources/test.png";

		//read the image on the matrix from the path provided
		//Mat : matrix data type in open cv to handle all the images
		img = imread(path);
	}

	//converting image to gray scale
	void convertToGray() {
		//converting the RGB image to gray scale image 
		cvtColor(img, imgGray, COLOR_BGR2GRAY);
	}

	//converting image blur
	void convertToBlur() {
		//type of blur
		//GaussianBlu(imageToConvert,convertedImage,kernelSize,blurSigmaX,blurSigmaY=0.0,borderSize=4)
		GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
	}

	//edge detector : after making the image blur
	void convertToCanny() {
		//Converting blur image to edge image 
		//Canny(blurImageToConvert, convertedImage, densityOfEdge1,densityOfEdge2)
		//densityOfImage: less : more edges visible
		Canny(imgBlur, imgCanny, 25, 75);
	}

	//Dilate the edges of the canny Image
	void convertToDilate() {
		//store structuringElement
		//getStructuringElement(shape,size)
		//size :  greater : more dilation (always use odd numbers as parameters
		kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

		//dilate the edges
		dilate(imgCanny, imgDilate, kernel);
	}

	//Erode Image
	void convertToErode() {
		//convert the dilate image to erode image 
		//can have different kernel : structuredImage 
		erode(imgDilate, imgErode, kernel);
	}
public:
	//initializing the images
	void initImageFunctions() {
		//importing image 
		importImage();

		//convert to Gray 
		convertToGray();

		//convert to Blur
		convertToBlur();

		//edge detector : after making the image blur
		//convert to Canny
		convertToCanny();

		//dilate and erode the image 
		//dilate : thickens the image edges 
		//		   as edges are too thin to detect
		//errode : decrease the thickness of the edges
		//dilate the canny image 
		convertToDilate();

		//convert to Erode
		convertToErode();
	}

	//display all the images 
	void displayImage() {
		//show the image 
		//imshow(nameOfTheImage,imageMatrix)
		imshow("Image", img);

		//display the gray image
		imshow("Gray Image", imgGray);

		//display the blur images
		imshow("Blur Image", imgBlur);

		//display the edge image 
		imshow("Canny Image", imgCanny);

		//display the dilated edges 
		imshow("Dilate Image", imgDilate);

		//display the eroded image
		imshow("Erode Image", imgErode);

		//add delay to view the output
		//parameter: 0 for infinity
		waitKey(0);
	}
};

int main() {
	//importing image
	//
	// Basic Functions: detecting the shape of the image 
	// 1. Convert to Gray Scale Image 
	// 2. Convert to Blur Image
	// 3. Edge Detector : Convert to Canny Image
	// 4. Dilate the edges of the Canny Image
	// 5. Erode the image of the dilated image 
	//
	ImageBasicFunctions basicFn;
	basicFn.initImageFunctions();
	basicFn.displayImage();

	return 0;
}
