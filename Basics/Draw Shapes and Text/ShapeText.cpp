#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

/////  Drawing Shapes and Text    /////

class DrawShapeText {
	Mat imgBlankBlack;
	Mat imgBlankBlue;
	Mat imgBlankPurple;
	Mat imgBlankWhite;

	//creating coloured blank images 
	void initBlankImages() {
		//store the blank image 
		//parameters : size, 8-bit color, Scalar=color(BGR)
		imgBlankBlue = Mat(512, 512, CV_8UC3, Scalar(255, 0, 0));

		//blank purple image 
		//scalar(BGR) : Purple : blue + red
		imgBlankPurple = Mat(512, 512, CV_8UC3, Scalar(255, 0, 200));

		//blank white image 
		imgBlankWhite = Mat(512, 512, CV_8UC3, Scalar(255, 255, 255));

		//blank black image 
		imgBlankBlack = Mat(512, 512, CV_8UC3, Scalar(0, 0, 0));
	}

	//displaying coloured blank images 
	void showBlankImages() {
		//display a blank blue image 
		imshow("Blue Image", imgBlankBlue);

		//display a blank purple image 
		imshow("Purple Image", imgBlankPurple);

		//display a blank white image 
		imshow("White Image", imgBlankWhite);

		//display a blank black image 
		imshow("Black Image", imgBlankBlack);
	}

	//drawing Circle 
	void drawCircle() {
		//img: to draw the circle in the image 
		//Point : centre point of the circle 
		//radius 
		//Scalar: Orange : colour of the circle 
		//width of the circle 
		Mat img = imgBlankBlack;
		circle(img, Point(256, 256), 155, Scalar(0, 115, 255), 10);

		//displaying the image with circle drawn
		imshow("Circle Drawing", img);
	}

	//drawing filled circle 
	void drawFilledCircle() {
		Mat img = imgBlankBlack;
		//img: to draw the circle in the image 
		//Point : centre point of the circle 
		//radius 
		//Scalar: Orange : colour of the circle 
		//filled : fully coloured circle 
		circle(img, Point(256, 256), 155, Scalar(0, 115, 255), FILLED);

		//displaying the image with circle drawn
		imshow("Filled Circle Drawing", img);

	}

	//drawing rectangle 
	void drawRectangle() {
		Mat img = imgBlankBlack;
		//rectangle 
		//img : draw rectangle on 
		//Point1 : top left corner 
		//Point2 : bottom right corner 
		//Scalar : black : (BGR)
		//width of the rectangle 
		rectangle(img, Point(170, 150), Point(350, 350), Scalar(0, 0, 0), 5);

		//displaying the image 
		imshow("Rectangle Drawing", img);

		//drawing the rectangle using rect data type 
		//top left corner and width and height
		Rect myRectangle(180, 170, 160, 155);

		//rectangle using rect data type
		//img : draw rectangle on 
		//myRectangle : object of rect data type
		//Scalar : white : (BGR)
		//width of the rectangle 
		rectangle(img, myRectangle, Scalar(255, 255, 255), 5);

		//display img2 
		imshow("Rect Rectangle Drawing", img);
	}

	//draw filled rectangle 
	void drawFilledRectangle() {
		Mat img = imgBlankBlack;
		//drawing the rectangle using rect data type 
		//top left corner and width and height
		Rect myRectangle(200, 190, 120, 115);

		//rectangle using rect data type
		//img : draw rectangle on 
		//myRectangle : object of rect data type
		//Scalar : white : (BGR)
		//fill the rectangle 
		rectangle(img, myRectangle, Scalar(255, 255, 255), FILLED);

		//displaying the image 
		imshow("Filled Rectangle Drawing ", img);
	}

	//draw a line 
	void drawLine() {

		Mat img = imgBlankBlack;

		//img : draw line on
		//Point1 : starting point of line 
		//Point2 : ending point of the line 
		//Scalar : Red :BGR
		//thickness of the line 
		line(img, Point(180, 340), Point(340, 340), Scalar(0, 0, 200), 3);

		imshow("Line Drawing", img);
	}

	//add text
	void addText() {
		Mat img = imgBlankBlack;

		//text that we need to display 
		String text = "Rhea";

		//adding text to the image
		//text :  String to display
		//Point : starting point 
		//Font : Font face
		//Font Size
		//Text colour
		//width of the text
		putText(img, text, Point(220, 260), FONT_HERSHEY_TRIPLEX, 0.95, Scalar(0, 155, 200), 3);

		//display the image 
		imshow("Text Added", img);
	}

public :

	void init() {
		initBlankImages();
		showBlankImages();
		drawCircle();
		drawFilledCircle();
		drawRectangle();
		drawFilledRectangle();
		drawLine();
		addText();

		waitKey(0);
	}
};

int main() {
	DrawShapeText shape;
	shape.init();
	return 0;
}
