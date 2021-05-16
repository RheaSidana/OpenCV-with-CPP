#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

///// Wrap Perspective  /////

//K Card Dimensions = P1(527,140) , P2(774,188) , P3(399,396) , P4(678,461)
//Q Card Dimensions = P1(58,318) , P2(344,275) , P3(86,639) , P4(408,578)
//J Card Dimensions = P1(773,102) , P2(1024,79) , P3(836,360) , P4(1120,334)
//9 Card Dimensions = P1(735,382) , P2(1026,432) , P3(642,714) , P4(976,768)
//Card Dimensions = P1(0.0f,0.0f) , P2(w,0.0f) , P3(0.0f,h) , P4(w,h)
//w=250,h=350

class WrapPerspective {
	Mat img;

	void importImage() {
		//defining the path of the image stored in the project
		String path = "Resources/cards.jpg";

		//read the image on the matrix from the path provided
		//Mat : matrix data type in open cv to handle all the images
		img = imread(path);
	}

	void displayImportedImage() {
		//show the image 
		//imshow(nameOfTheImage,imageMatrix)
		imshow("Image", img);
	}

	//our card dimensions
	void resultantCard(Mat img, Point2f src[4], String text) {
		//width and height of our card
		float w = 250, h = 350;
		//Plotting points of our card
		Point2f destination[4] = { {0.0f,0.0f} , {w,0.0f} , {0.0f,h} , {w,h} };

		//store the image of our card
		Mat imgWarp;

		//map the perspective points to the plotting points of the card
		Mat matrix = getPerspectiveTransform(src, destination);

		//warp perspective in accordance to the width and height of our card
		warpPerspective(img, imgWarp, matrix, Point(w, h));

		//display resultant card
		imshow(text, imgWarp);
	}

	//K Card Dimension
	void kCardTransformation() {
		//dimension of k card in the image 
		Point2f src[4] = { {527,140} , {774,188} , {399,396} , {678,461} };

		//mapping or transfroming the card to our card
		resultantCard(img, src, "K  Card");

		//mapping the points selected from the original image 
		img = drawFilledCircle(img, src, "Selecting K Card");
	}

	//Q Card Dimension 
	void qCardTransformation() {
		//dimension of q card in the image 
		Point2f src[4] = { {58,318} , {344,275} , {86,639} , {408,578} };

		//mapping or transfroming the card to our card
		resultantCard(img, src, "Q Card");

		//mapping the points selected from the original image 
		img = drawFilledCircle(img, src, "Selecting Q Card");
	}

	//J card dimension
	void jCardTransformation() {
		//dimension of j card in the image 
		Point2f src[4] = { {773,102} , {1024,79} , {836,360} , {1120,334} };

		//mapping or transfroming the card to our card
		resultantCard(img, src, "J Card");

		//mapping the points selected from the original image 
		img = drawFilledCircle(img, src, "Selecting J Card");
	}

	//9 card dimension
	void nineCardTransformation() {
		//dimension of 9 card in the image 
		Point2f src[4] = { {735,382} , {1026,432} , {642,714} , {976,768} };

		//mapping or transfroming the card to our card
		resultantCard(img, src, "9 Card");

		//mapping the points selected from the original image 
		img = drawFilledCircle(img, src, "Selecting 9 Card");
	}

	//draw filled circle on the points selected
	Mat drawFilledCircle(Mat img, Point2f src[4], String text) {
		for (int i = 0; i < 4; i++) {
			//img: to draw the circle in the image 
			//Point : centre point of the circle 
			//radius 
			//Scalar: Red : colour of the circle 
			//filled : fully coloured circle 
			circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
		}

		//displaying the image with circle drawn
		imshow(text, img);

		//returning image with fully filled circle
		return img;
	}

public:

	void init() {
		importImage();
		displayImportedImage();

		//transforming k card 
		kCardTransformation();

		//transforming q card
		qCardTransformation();

		//transforming j card
		jCardTransformation();

		//transforming 9 card
		nineCardTransformation();

		waitKey(0);
	}
};

int main() {
	WrapPerspective wrapImage;
	wrapImage.init();
	return 0;
}
