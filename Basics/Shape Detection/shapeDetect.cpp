#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

///// Shapes / Contour Detection  /////


class shapeDetect {
	//Original Image 
	Mat img, imgOriginal;

	//store the gray scale image
	Mat imgGray;

	//img matrix to store blur image 
	Mat imgBlur;

	//stores the edges fromed in the image 
	Mat imgCanny;

	//store dilated image
	Mat imgDilate;

	//Pre-processing 
	//importing images
	void importImages() {
		//defining the path of the image stored in the project
		String path = "Resources/shapes.png";

		//read the image on the matrix from the path provided
		//Mat : matrix data type in open cv to handle all the images
		img = imread(path);
		imgOriginal = imread(path);

		//show the image 
		//imshow(nameOfTheImage,imageMatrix)
		imshow("Image", img);
	}

	//converting image to gray scale and displaying it
	void showGrayImage() {
		//converting the RGB image to gray scale image 
		cvtColor(img, imgGray, COLOR_BGR2GRAY);

		//display the gray image
		imshow("Gray Image", imgGray);
	}

	//converting image blur
	void showBlurImage() {
		//type of blur
		//GaussianBlu(imageToConvert,convertedImage,kernelSize,blurSigmaX,blurSigmaY=0.0,borderSize=4)
		GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);

		//display the blur image 
		imshow("Blur Image", imgBlur);
	}

	//detect shape by finding the edges : canny edges 
	//find contour points 
	void edgeDetecting() {
		//Converting blur image to edge image 
		//Canny(blurImageToConvert, convertedImage, densityOfEdge1,densityOfEdge2)
		//densityOfImage: less : more edges visible
		Canny(imgBlur, imgCanny, 25, 75);

		//display the edge image 
		imshow("Canny Image", imgCanny);
	}

	//dilate the canny image 
	void showDilateImage() {

		//store structuringElement
		//getStructuringElement(shape,size)
		//size :  greater : more dilation (always use odd numbers as parameters
		Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

		//dilate the edges
		dilate(imgCanny, imgDilate, kernel);

		//display the dilated edges 
		imshow("Dilate Image", imgDilate);
	}

	//after processing 
	//vectors of vectors<Point>
	vector<vector<Point>> contours;

	//vector of 4 integers
	vector<Vec4i> hierarcy;

	//contour polygon values 
	vector<vector<Point>> contourPoly;

	//perimeter of each shape 
	double perimeter;

	//rectangular point for boundary around the shape 
	vector<Rect> rectangularBoundary;

	//assigning the shape name
	string objectType;

	//count the corner points 
	int cornerPointCount;

	//point to display the shape name 
	Point displayTextPoint;

	//differentiate between square and rectangle 
	float aspectRatio;

	//determining the boundary of the shapes
	void getContours() {
		//finding contours : retrieves contours from the binary image
		//for the shape analysis and object detection and recognition
		//imgDilate : finding contours on
		findContours(imgDilate, contours, hierarcy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		//drawing contours on our original image 
		//-1 : draw contours on all the shapes present in the image 
		//Scalar : colour to depict the the shape is recognised : bgr
		// 3 : thickness 
		drawContours(imgOriginal, contours, -1, Scalar(150, 255, 60), 3);

		//displaying the image 
		imshow("Contour Image", imgOriginal);
	}

	//removing un-wanted shapes or objects from the image considering them as "noise"
	void removeUselessPartOfImage() {
		for (int i = 0; i < contours.size(); i++) {
			//find area of the contour/boundary of each shape
			int area = contourArea(contours[i]);

			//finding the smallest shape
			//cout << area << endl;
			//after finding out the image contains a small shape which can be removed from detection 
			//Output : 36445   38807  5469   11644   33991  248   22111   11845   8678   7919

			//remove the contour on smallest useless part of image 
			if (area > 1000) {
				drawContours(imgOriginal, contours, i, Scalar(0, 200, 240), 3);
			}
		}

		//displaying after removing 
		imshow("Removed Contour from Noise", imgOriginal);

		//finding number of corners of the shapes recognised to determine the shape
		//determineCornerPoints(contours, imgOriginal);
	}

	//finding corner points of the shapes
	void determineCornerPoints() {
		contourPoly = vector<vector<Point>>(contours.size());
		for (int i = 0; i < contours.size(); i++) {
			int area = contourArea(contours[i]);
			if (area > 1000) {
				perimeter = arcLength(contours[i], true);

				//determint the polygo points
				approxPolyDP(contours[i], contourPoly[i], 0.03 * perimeter, true);

				//drawing contour using contour poly points
				drawContours(imgOriginal, contourPoly, i, Scalar(80, 100, 90), 3);

				//determinning number points in each shape
				//if (i == 0)cout << endl;
				//cout << contourPoly[i].size() << endl;
				//output : 4  8  3  4  4  3  4  3  8
			}
		}

		//displaying the image 
		imshow("Contour Poly", imgOriginal);

		//draw rectangle bounding around the shapes
		//boundaryRectangle(contourPoly, imgOriginal);

	}

	//drawing a boundary rectangle around the shapes with the help of corner points(contourPoly)
	void boundaryRectangle() {
		//rectangular point for boundary around the shape 
		rectangularBoundary = vector<Rect>(contourPoly.size());

		for (int i = 0; i < contourPoly.size(); i++) {
			//assigning the 4 values of the rectangle 
			rectangularBoundary[i] = boundingRect(contourPoly[i]);

			//drawing the rectangle around the shapes 
			//img : draw rectangle on 
			//Point1 : top left corner 
			//Point2 : bottom right corner 
			//Scalar : black : (BGR)
			//width of the rectangle 
			rectangle(imgOriginal, rectangularBoundary[i].tl(), rectangularBoundary[i].br(), Scalar(30, 125, 170), 3);
		}

		//displaying the image 
		imshow("Rectangular Boundary", imgOriginal);

		//determining shape by corner points
		//determineShape(contourPoly, imgOriginal, rectangularBoundary);
	}

	//displaying the shape name 
	void determineShape() {
		for (int i = 0; i < contourPoly.size(); i++) {
			cornerPointCount = int(contourPoly[i].size());

			if (cornerPointCount == 3) {
				objectType = "Triangle";
			}
			else if (cornerPointCount == 4) {
				aspectRatio = float(rectangularBoundary[i].width / rectangularBoundary[i].height);
				if (aspectRatio > 0.95 && aspectRatio < 1.05) {
					objectType = "Square";
				}
				else objectType = "Rectangle";
			}
			else if (cornerPointCount > 4) {
				objectType = "Circle";
			}

			displayTextPoint = Point(rectangularBoundary[i].x, rectangularBoundary[i].y - 5);

			//adding text to the image
			//objectType :  String to display
			//Point : starting point (should be above the image)
			//Font : Font face
			//Font Size
			//Text colour : bgr
			//width of the text
			putText(imgOriginal, objectType, displayTextPoint, FONT_HERSHEY_TRIPLEX, 0.75, Scalar(60, 20, 200), 1);
		}

		//displaying the image 
		imshow("Text Display", imgOriginal);
	}


public:
	void initClass() {
		importImages();
		showGrayImage();
		showBlurImage();
		edgeDetecting();
		showDilateImage();

		//after processing 
		getContours();
		removeUselessPartOfImage();
		determineCornerPoints();
		boundaryRectangle();
		determineShape();

		waitKey(0);
	}
};

int main() {
	shapeDetect detect;
	detect.initClass();
	return 0;
}

