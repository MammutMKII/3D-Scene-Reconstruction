#include <iostream>
#include "camera.h"
#include "display.h"
#include "match.h"
#include "reconstruction.h"

using namespace cv;

int capture_and_store()
{
	Mat leftImage, rightImage;
	if (int status = capture_images(leftImage, rightImage) < 0)
		return status;

	imwrite("../images/testL.png", leftImage);
	imwrite("../images/testR.png", rightImage);
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
	if (int status = capture_images(leftImage, rightImage) < 0)
		return status;

	Mat result;
	reconstructV1(leftImage, rightImage, result);

	waitKey(30000);

	return 0;
}

void present()
{
	//show distorted chessboard
	Mat rawLeftChessboard, rawRightChessboard;
	takeStereo(rawLeftImage, rawRightImage);

	//get calibration params
	int leftCalibrationParams, rightCalibrationParams;
	computeStereoCalibrationParams(leftCalibrationParams, rightCalibrationParams);

	//calibrate chessboard
	Mat calibratedLeftChessboard, calibratedRightChessboard;
	calibrateStereo(rawLeftChessboard, rawRightChessboard, calibratedLeftChessboard, calibratedRightChessboard, leftCalibrationParams, rightCalibrationParams);
	
	//show calibrated chessboard
	displayStereo(calibratedLeftChessboard, calibratedRightChessboard);
	
	//take a snap
	Mat rawLeftImage, rawRightImage;
	takeStereo(rawLeftImage, rawRightImage);

	//show distorted snap
	displayStereo(rawLeftImage, rawRightImage);

	//calibrate snap
	Mat calibratedLeftImage, calibratedRightImage;
	calibrateStereo(rawLeftImage, rawRightImage, calibratedLeftImage, calibratedRightImage, leftCalibrationParams, rightCalibrationParams);

	//show calibrated snap
	displayStereo(calibratedLeftImage, calibratedRightImage);

	//match
	std::vector<std::tuple<KeyPoint, KeyPoint>> keyPointMatches;
	matchStereo(calibratedLeftImage, calibratedRightImage, keyPointMatches);

	//reconstruct
	std::vector<float> X, Y, Z;
	reconstructV2(keyPointMatches, X, Y, Z);

	//display reconstruction
	display3D(X, Y, Z);
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
