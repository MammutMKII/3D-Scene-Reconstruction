#include "camera.h"
#include "calibration.h"
#include "display.h"
#include "match.h"
#include "reconstruction.h"

using namespace cv;

#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/highgui.hpp>

int capture_and_store()
{
	Mat leftImage, rightImage;
	for (int i = 0; i < 10; i++) {
		takeStereo(leftImage, rightImage);

		std::stringstream ls;
		ls << "../images/chessboardL_" << i << ".png";
		imwrite(ls.str(), leftImage);
		std::stringstream rs;
		rs << "../images/chessboardR_" << i << ".png";
		imwrite(rs.str(), rightImage);
	}
	return 0;
}

int load_and_reconstruct()
{
	Mat leftImage = imread("../images/motorcycle_left.png", IMREAD_GRAYSCALE);
	Mat rightImage = imread("../images/motorcycle_right.png", IMREAD_GRAYSCALE);

	Mat result;
	reconstructV1(leftImage, rightImage, result);

	waitKey(30000);

	return 0;
}

int capture_and_reconstruct()
{
	Mat leftImage, rightImage;
	takeStereo(leftImage, rightImage);

	Mat result;
	reconstructV1(leftImage, rightImage, result);

	waitKey(30000);

	return 0;
}

void present()
{
	//show distorted chessboard
	Mat rawLeftChessboard, rawRightChessboard;
	takeStereo(rawLeftChessboard, rawRightChessboard);
	displayStereo(rawLeftChessboard, rawRightChessboard);

	//get calibration params
	StereoCalibrationParams calibrationParams = computeStereoCalibrationParams();

	//calibrate chessboard
	Mat calibratedLeftChessboard, calibratedRightChessboard;
	undistortRectifyStereo(rawLeftChessboard, rawRightChessboard, calibratedLeftChessboard, calibratedRightChessboard, calibrationParams);
	
	//show calibrated chessboard
	displayStereo(calibratedLeftChessboard, calibratedRightChessboard);
	waitKey(1000000);
	
	while (true) {
		//take a snap
		Mat rawLeftImage, rawRightImage;
		takeStereo(rawLeftImage, rawRightImage);

		//show distorted snap
		displayStereo(rawLeftImage, rawRightImage);

		//calibrate snap
		Mat calibratedLeftImage, calibratedRightImage;
		undistortRectifyStereo(rawLeftImage, rawRightImage, calibratedLeftImage, calibratedRightImage, calibrationParams);

		//show calibrated snap
		displayStereo(calibratedLeftImage, calibratedRightImage);
		waitKey(1000000);

		//match
		std::vector<std::tuple<KeyPoint, KeyPoint>> keyPointMatches;
		matchStereo(calibratedLeftImage, calibratedRightImage, keyPointMatches);
		waitKey(1000000);

		//reconstruct
		std::vector<float> X, Y, Z;
		reconstructV2(keyPointMatches, X, Y, Z, calibrationParams);

		//display reconstruction
		display3D(X, Y, Z);
	}
}

int main()
{
	//capture_and_store();

	//load_and_reconstruct();

	//while(true)
	//	capture_and_reconstruct();

	present();

	return 0;
}
