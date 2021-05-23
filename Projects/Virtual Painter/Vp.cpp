#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

// object detection and tracking, primarily facial detection and recognition.
#include <opencv2/objdetect.hpp>


using namespace std;
using namespace cv;

///// Project 1 : Virtual Painter   /////
Mat convertToHSV(Mat img);

//convert the image to hsv space 
//easier to detect the color 
//alternative to rgb colour model 
//parts: saturation hue and value 
Mat convertToHSV(Mat img) {
	//store the converted image 
	Mat imgHSV;

	//convert the RGB image to HSV image 
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	//display the HSV image 
	//imshow("HSV Image", imgHSV);

	return imgHSV;
}


class ColourPicker {
	//capture webcam 
	//parameter : 0 : camera id (can be 1,2,3...)
	VideoCapture webcamVideo;

	//stores the captured image in the image matrix
	Mat img;

	Mat mask;
public:
	//Preprocessing 
	void findSketchPenColour() {
		//finding the colour range to detect
		trackBarToDetectColour();

		//Sketch Pen Colour
		//		   hMin << hMax << sMin << sMax << vMin << vMax
		//Black  : 51 130 31 116 14 215
		//Blue   : 107 155 146 227 87 175
		//Pink   : 135 174 108 175 106 201
		//Purple : 97 129 114 189 73 220
		//Orange : 4 24 128 205 146 245
		//Red	 : 0 179 137 226 127 222
		//Green	 : 43 100 121 229 78 180
		//White  : 69 128 0 66 134 253
		//Yellow : 21 49 95 196 139 253
		//Brown  : 0 71 0 128 59 144
		//Grey   : 71 116 21 82 88 224

		//finding out which colour to display in corresponding to the colours detected 
		//parameters : size, 8-bit color, Scalar=color(BGR)
		//Mat imgBlankBlue(512, 512, CV_8UC3, Scalar(140, 140, 140));

		//display a blank blue image 
		//imshow("Blue Image", imgBlankBlue);

		//waitKey(0);

		//Display Colour when sketch pen detected 
		//Black  : Scalar(0, 0, 0)
		//Blue   : Scalar(255, 0, 90)
		//Pink   : Scalar(120, 0, 190)
		//Purple : Scalar(255, 0, 190)
		//Orange : Scalar(115, 170, 255)
		//Red	 : Scalar(75, 40, 220)
		//Green	 : Scalar(55, 110, 20)
		//White  : Scalar(255, 255, 255)
		//Yellow : Scalar(90, 230, 255)
		//Brown  : Scalar(85, 110, 200)
		//Grey   : Scalar(136, 136, 136)

		////vector of colours to detect
		////hMin << hMax << sMin << sMax << vMin << vMax
		//vector<vector<int>> detectColours = { {51, 130, 31, 116, 14, 215}, //black
		//									  {107, 155, 146, 227, 87, 175 }, //blue
		//									  {135, 174, 108, 175, 106, 201},//Pink
		//									   { 142 , 179 , 142 , 234 , 83 , 210 } // Pink 
		//									  {97, 129, 114, 189, 73, 220}, //Purple
		//									   { 93 , 132 , 118 , 194 , 31 , 125 } // Purple
		//									  {4, 24, 128, 205, 146, 245}, //Orange
		//									  { 0 , 17 , 187 , 255 , 135 , 220 } //Orange
		//									  {0, 179, 137, 226, 127, 222}, //Red
		//									  {43, 100, 121, 229, 78, 180}, //Green
		//									  {69, 128, 0, 66, 134, 253}, //White 
		//									  {21, 49, 95, 196, 139, 253}, //Yellow
		//									  { 21 , 50 , 102 , 255 , 108 , 205 } //Yellow
		//									  {0, 71, 0, 128, 59, 144}, //brown
		//									  {71, 116, 21, 82, 88, 224} //Grey
		//}; 
		////bgr
		//vector<Scalar> displayColors = { {0, 0, 0}, //Black
		//								 {255, 0, 90},//Blue
		//								 {120, 0, 190},//Pink
		//								 {255, 0, 190},//Purple
		//								 {115, 170, 255},//Orange
		//								 {75, 40, 220},//Red
		//								 {55, 110, 20},//Green
		//								 {255, 255, 255},//White
		//								 {90, 230, 255},//Yellow
		//								 {85, 110, 200}, //Brown
		//								 {136, 136, 136} //Grey
		//};
	}

	//detecting the sketch pen colours
	//track-bars to find the min and max values of hsv colour model
	void trackBarToDetectColour() {
		webcamVideo = VideoCapture(0);

		//window to track the value of HSV min and max
		namedWindow("TrackBars", (640, 200));

		//variables to store the min and max values
		int hMin = 0, sMin = 0, vMin = 0;
		int hMax = 179, sMax = 255, vMax = 255;

		//vlaues got with the help of trackbars
		//hMin = 0, sMin = 114, vMin = 165;
		//hMax = 21, sMax = 255, vMax = 255;

		//creating 6 track bars
		createTrackbar("Hue min", "TrackBars", &hMin, 179);
		createTrackbar("Hue max", "TrackBars", &hMax, 179);
		createTrackbar("Sat min", "TrackBars", &sMin, 255);
		createTrackbar("Sat max", "TrackBars", &sMax, 255);
		createTrackbar("Val min", "TrackBars", &vMin, 255);
		createTrackbar("Val max", "TrackBars", &vMax, 255);

		while (true) {
			//storing the image in image matrix
			webcamVideo.read(img);

			Mat imgHSV = convertToHSV(img);

			//HSV : hue saturation value
			//min :  light and max : bright
			Scalar lower(hMin, sMin, vMin);
			Scalar upper(hMax, sMax, vMax);

			//searching the colour belonging to the particular range and assigning to mask image 
			//everything will become black and white portion depicts the colour in the image 
			inRange(imgHSV, lower, upper, mask);

			cout << endl <<" { " << hMin << " , " << hMax << " , " << sMin << " , " << sMax << " , " << vMin << " , " << vMax <<" } ";

			//displaying the mask image 
			imshow("Mask Imaging", mask);

			//display the captured image 
			imshow("Image", img);

			waitKey(1);
		}
	}

};

class VirtualPianter {
	//stores the captured image in the image matrix
	Mat img;

	//store the converted image 
	Mat imgHSV;

	//capture webcam 
	//parameter : 0 : camera id (can be 1,2,3...)
	VideoCapture webcamVideo;

	vector<vector<int>> detectedPoints;

	//vector of colours to detect
	//hMin << hMax << sMin << sMax << vMin << vMax
	vector<vector<int>> detectColours;

	void assignColoursToDetect() {
		detectColours = {	//{51, 130, 31, 116, 14, 215}, //black
							//{107, 155, 146, 227, 87, 175 }, //blue
							{ 142 , 179 , 142 , 234 , 83 , 210 },//Pink
							{ 93 , 132 , 118 , 194 , 31 , 125 }, //Purple
							{ 0 , 17 , 187 , 255 , 135 , 220 }, //Orange
							//{0, 179, 137, 226, 127, 222}, //Red
							//{43, 100, 121, 229, 78, 180}, //Green
							//{69, 128, 0, 66, 134, 253}, //White 
							{ 21 , 50 , 102 , 255 , 108 , 205 } //Yellow
							//{0, 71, 0, 128, 59, 144}, //brown
							//{71, 116, 21, 82, 88, 224} //Grey
		};
	}

	//vector to colours to display the colour virtually
		//bgr
	vector<Scalar> displayColors;

	void assignColoursToDisplay() {
		displayColors = { //{0, 0, 0}, //Black
										 //{255, 0, 90},//Blue
										 {120, 0, 190},//Pink
										 {255, 0, 190},//Purple
										 {115, 170, 255},//Orange
										 //{75, 40, 220},//Red
										 //{55, 110, 20},//Green
										 //{255, 255, 255},//White
										 {90, 230, 255} //Yellow
										 //{85, 110, 200}, //Brown
										 //{136, 136, 136} //Grey
		};
	}

	void findColour() {
		//convert image to HSV
		imgHSV = convertToHSV(img);

		//vector of colours to detect
		//hMin << hMax << sMin << sMax << vMin << vMax
		/*vector<vector<int>> detectColours = { //{51, 130, 31, 116, 14, 215}, //black
											  //{107, 155, 146, 227, 87, 175 }, //blue
											  {135, 174, 108, 175, 106, 201},//Pink
											  {97, 129, 114, 189, 73, 220}, //Purple
											  {4, 24, 128, 205, 146, 245}, //Orange
											  //{0, 179, 137, 226, 127, 222}, //Red
											  //{43, 100, 121, 229, 78, 180}, //Green
											  //{69, 128, 0, 66, 134, 253}, //White 
											  {21, 49, 95, 196, 139, 253} //Yellow
											  //{0, 71, 0, 128, 59, 144}, //brown
											  //{71, 116, 21, 82, 88, 224} //Grey
		};*/
		assignColoursToDetect();

		//vector to colours to display the colour virtually
		//bgr
		/*vector<Scalar> displayColors = { //{0, 0, 0}, //Black
										 //{255, 0, 90},//Blue
										 {120, 0, 190},//Pink
										 {255, 0, 190},//Purple
										 {115, 170, 255},//Orange
										 //{75, 40, 220},//Red
										 //{55, 110, 20},//Green
										 //{255, 255, 255},//White
										 {90, 230, 255} //Yellow
										 //{85, 110, 200}, //Brown
										 //{136, 136, 136} //Grey
		};*/
		assignColoursToDisplay();
	}

	vector<vector<int>> pointsDetected;

	void detectColour() {
		//detect these colours 
		pointsDetected = detectPenColour();

		drawOnCanvas();
	}

	//inRange function : collect the colour 
	//because of the shadow the colours in the image will be within a range 
	vector<vector<int>> detectPenColour() {
		Mat imgOriginal = img;
		
		Mat mask;

		for (int i = 0; i < detectColours.size(); i++) {
			////hMin << hMax << sMin << sMax << vMin << vMax
			//searching Colour 
			int hMin = detectColours[i][0], sMin = detectColours[i][2], vMin = detectColours[i][4];
			int hMax = detectColours[i][1], sMax = detectColours[i][3], vMax = detectColours[i][5];

			//HSV : hue saturation value
			//min :  light and max : bright
			Scalar lower(hMin, sMin, vMin);
			Scalar upper(hMax, sMax, vMax);

			//searching the colour belonging to the particular range and assigning to mask image 
			//everything will become black and white portion depicts the colour in the image 
			inRange(imgHSV, lower, upper, mask);

			int colourId = i;

			//String myMaskString = "Mask Image" + to_string(i);
			//displaying the mask image 
			//imshow(myMaskString, mask);
			Point dotPoint = getContours(mask, imgOriginal);

			if (dotPoint.x != 0 && dotPoint.y != 0) {
				detectedPoints.push_back({ dotPoint.x,dotPoint.y,colourId });
			}

			//cout << endl << detectedPoints.size();
		}

		return detectedPoints;
	}

	//contours to draw points 
	Point getContours(Mat imgDilate, Mat imgOriginal) {
		//vectors of vectors<Point>
		vector<vector<Point>> contours;

		//vector of 4 integers
		vector<Vec4i> hierarcy;

		//finding contours : retrieves contours from the binary image
		//for the shape analysis and object detection and recognition
		//imgDilate : finding contours on
		findContours(imgDilate, contours, hierarcy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		//drawing contours on our original image 
		//-1 : draw contours on all the shapes present in the image 
		//Scalar : colour to depict the the shape is recognised : bgr
		// 3 : thickness 
		//drawContours(imgOriginal, contours, -1, Scalar(150, 255, 60), 3);

		//displaying the image 
		//imshow("Contour Image", imgOriginal);

		Point dotPoint = determineCornerPoints(contours, imgOriginal);

		return dotPoint;
	}

	//finding corner points of the shapes
	Point determineCornerPoints(vector<vector<Point>> contour, Mat imgOriginal) {
		//contour polygon values 
		vector<vector<Point>> contourPoly(contour.size());
		//perimeter of each shape 
		double perimeter;

		for (int i = 0; i < contour.size(); i++) {
			int area = contourArea(contour[i]);
			if (area > 1000) {
				perimeter = arcLength(contour[i], true);

				//determint the polygo points
				approxPolyDP(contour[i], contourPoly[i], 0.03 * perimeter, true);

				//drawing contour using contour poly points
				//drawContours(imgOriginal, contourPoly, i, Scalar(80, 100, 90), 3);

				//determinning number points in each shape
				//if (i == 0)cout << endl;
				//cout << contourPoly[i].size() << endl;
				//output : 4  8  3  4  4  3  4  3  8
			}
		}

		//displaying the image 
		//imshow("Contour Poly", imgOriginal);

		//draw rectangle bounding around the shapes
		Point dotPoint = boundaryRectangle(contourPoly, imgOriginal);

		return dotPoint;

	}

	//drawing a boundary rectangle around the shapes with the help of corner points(contourPoly)
	Point boundaryRectangle(vector<vector<Point>> contourPoly, Mat imgOriginal) {
		//rectangular point for boundary around the shape 
		vector<Rect> rectangularBoundary(contourPoly.size());
		Point dotPoint(0, 0);

		for (int i = 0; i < contourPoly.size(); i++) {
			//assigning the 4 values of the rectangle 
			rectangularBoundary[i] = boundingRect(contourPoly[i]);

			//find point(x,y) to draw colour
			dotPoint = getPoint(rectangularBoundary[i]);

			//drawing the rectangle around the shapes 
			//img : draw rectangle on 
			//Point1 : top left corner 
			//Point2 : bottom right corner 
			//Scalar : red : (BGR)
			//width of the rectangle 
			//rectangle(imgOriginal, rectangularBoundary[i].tl(), rectangularBoundary[i].br(), Scalar(0, 0, 255), 3);
		}

		/*if(dotPoint.x != 0 && dotPoint.y != 0)
		detectedPoints.push_back({ dotPoint.x,dotPoint.y,colourId});*/

		//displaying the image 
		//imshow("Rectangular Boundary", imgOriginal);

		return dotPoint;
	}

	//Point to draw the displayColour
	Point getPoint(Rect rectangularBoundary) {
		Point dotPoint(0, 0);
		dotPoint.x = rectangularBoundary.x + rectangularBoundary.width / 2;
		dotPoint.y = rectangularBoundary.y;
		return dotPoint;
	}

	void drawOnCanvas() {
		for (int i = 0; i < detectedPoints.size(); i++) {
			circle(img, (Point(pointsDetected[i][0], pointsDetected[i][1])), 13, displayColors[pointsDetected[i][2]], FILLED);
		}
	}
public:
	void importVideoWebcam() {
		webcamVideo = VideoCapture(0);

		while (true) {
			//storing the image in image matrix
			webcamVideo.read(img);

			//finding the colour 
			findColour();

			detectColour();

			//display the captured image 
			imshow("Image", img);

			//delay should not be infinity in this case
			//parameter :  20 ms
			waitKey(1);

		}
	}
};


int main() {
	/*
	ColourPicker pick;
	pick.findSketchPenColour();
	*/

	/**/
	VirtualPianter paint;
	paint.importVideoWebcam();
	/**/
	return 0;
}
