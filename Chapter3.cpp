#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

/////  Resize and Crop Images   /////

class ImageResizeCrop {
	//read the image on the matrix from the path provided
	//Mat : matrix data type in open cv to handle all the images
	Mat img;

	//store the resized image 
	Mat imgResize;

	//store the resized image by percentage
	Mat imgResizePercentage;

	//store thr cropped Image 
	Mat imgCrop;

	//importing images
	void importImages() {
		//defining the path of the image stored in the project
		String path = "Resources/test.png";

		//read the image on the matrix from the path provided
		//Mat : matrix data type in open cv to handle all the images
		img = imread(path);
	}

	//Finding the original size of the Image
	void imageSize() {
		cout << endl << "Size of image : " << img.size() << endl << endl;
		//Output:
		//Size of image : [400 x 500]
	}

	//Resizing the Image 
	void resizeImage() {
		//function to resie the image 
		resize(img, imgResize, Size(340, 480));
	}

	//Resize the image : defining scaling on x and y directions
	void resizeImagePercentage() {
		//function to resie the image 
		//Size is not defined 
		//Percentage : fx,fy :0.5,0.5
		resize(img, imgResizePercentage, Size(), 0.5, 0.5);
	}

	//Crop the particular portion of the Image 
	// croped region is know as Region of Interest (ROI)
	void cropImage() {
		//selecting a rectangular region
		//upper left corner  and width and height 
		Rect roi(120, 60, 200, 350);

		//cropping the image according to the ROI
		imgCrop = img(roi);
	}

public:
	void initFunction() {
		//import image 
		importImages();

		//finding the size of image 
		imageSize();

		//resiging the image 
		resizeImage();

		//resizing the image by percentage
		resizeImagePercentage();

		//cropping the image 
		cropImage();
	}

	void displayImages() {
		//show the image 
		//imshow(nameOfTheImage,imageMatrix)
		imshow("Image", img);

		//display the resized image 
		imshow("Resized Image", imgResize);

		//display the resized image 
		imshow("Resized Image by Percentage", imgResizePercentage);

		//displaying the image 
		imshow("Cropped Image", imgCrop);

		//add delay to view the output
		//parameter: 0 for infinity
		waitKey(0);
	}
};

int main() {
	//Resize or Crop the image 
	//Functions 
	//1. Size of the Image 
	//2. Resize the Image by Size
	//3. Resize the Image by Percentage
	//4. Crop the particular portion of the Image 
	ImageResizeCrop imgResizeCrop;
	imgResizeCrop.initFunction();
	imgResizeCrop.displayImages();
	return 0;
}