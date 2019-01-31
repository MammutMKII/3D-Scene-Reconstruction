#include "calibration.h"
#include "camera.h"
#include "display.h"

#include <opencv2/calib3d.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

std::vector<std::vector<Vec3f>> generatePattern(int views, int height, int width, float squareSize) {
	std::vector<std::vector<Vec3f>> patternCollection{};

	std::vector<Vec3f> pattern{};
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			pattern.push_back(Vec3f(col * squareSize, row*squareSize, 0.0f));
		}
	}
	for (int i = 0; i < views; i++)
		patternCollection.push_back(pattern);

	return patternCollection;
}

StereoCalibrationParams computeStereoCalibrationParams() {
	const int VIEWS = 10;
	const int PT_HEIGHT = 6;
	const int PT_WIDTH = 7;
	const float PT_SIZE = 2.4;
	Size ptSize{ PT_WIDTH, PT_HEIGHT };
	Size imgSize{ 480, 640 };
	auto pattern = generatePattern(VIEWS, PT_HEIGHT, PT_WIDTH, PT_SIZE);

	std::vector<std::vector<Point2f>> leftImgPoints;
	std::vector<std::vector<Point2f>> rightImgPoints;

	VideoCapture leftCapture, rightCapture;
	openStereoVideo(leftCapture, rightCapture);
	for (int i = 0; i < VIEWS;) {
		std::cout << "taking calib image #" << i << std::endl;
		Mat leftImage, rightImage;
		captureStereo(leftImage, rightImage, leftCapture, rightCapture);

		std::vector<Point2f> leftCorners{};
		std::vector<Point2f> rightCorners{};
		bool success = findChessboardCorners(leftImage, ptSize, leftCorners);
		success = success && findChessboardCorners(rightImage, ptSize, rightCorners);
		if (success) {
			//std::vector<Point2f> corners2{};
			//cornerSubPix(leftImage, corners2, Size(5, 5), Size(-1, -1), TermCriteria(2, 30, 0.001));
			leftImgPoints.push_back(leftCorners);
			rightImgPoints.push_back(rightCorners);
			//Draw and display the corners
			drawChessboardCorners(leftImage, ptSize, leftCorners, success);
			drawChessboardCorners(rightImage, ptSize, rightCorners, success);

			displayStereo(leftImage, rightImage);
			i++;
		}
	}

	Mat leftCameraMatrix, rightCameraMatrix;
	Mat leftDistCoeffs, rightDistCoeffs;
	std::vector<Mat> leftRVecs{};
	std::vector<Mat> rightRVecs{};
	std::vector<Mat> leftTVecs{};
	std::vector<Mat> rightTVecs{};
	calibrateCamera(pattern, leftImgPoints, imgSize, leftCameraMatrix, leftDistCoeffs, leftRVecs, leftTVecs);
	calibrateCamera(pattern, rightImgPoints, imgSize, rightCameraMatrix, rightDistCoeffs, rightRVecs, rightTVecs);

	Mat R, T, E, F;
	stereoCalibrate(pattern, leftImgPoints, rightImgPoints, leftCameraMatrix, leftDistCoeffs, rightCameraMatrix, rightDistCoeffs, imgSize, R, T, E, F, CALIB_FIX_INTRINSIC);
	
	Mat R1, R2, P1, P2, Q;
	stereoRectify(leftCameraMatrix, leftDistCoeffs, rightCameraMatrix, rightDistCoeffs, imgSize, R, T, R1, R2, P1, P2, Q, CALIB_ZERO_DISPARITY, 0.5);

	Mat leftMap1, leftMap2, rightMap1, rightMap2;
	initUndistortRectifyMap(leftCameraMatrix, leftDistCoeffs, R1, P1, imgSize, CV_32FC1, leftMap1, leftMap2);
	initUndistortRectifyMap(rightCameraMatrix, rightDistCoeffs, R2, P2, imgSize, CV_32FC1, rightMap1, rightMap2);

	std::cout << "successfully computed calibration params" << std::endl;

	return { leftCameraMatrix, rightCameraMatrix, leftDistCoeffs, rightDistCoeffs, R, T, E, F, R1, R2, P1, P2, Q, leftMap1, leftMap2, rightMap1, rightMap2 };
}


void undistortRectifyStereo(cv::Mat rawLeftImage, cv::Mat rawRightImage, cv::Mat &calibratedLeftImage, cv::Mat &calibratedRightImage, StereoCalibrationParams calibrationParams) {
	remap(rawLeftImage, calibratedLeftImage, calibrationParams.leftMap1, calibrationParams.leftMap2, INTER_LINEAR);
	remap(rawRightImage, calibratedRightImage, calibrationParams.rightMap1, calibrationParams.rightMap2, INTER_LINEAR);
	//undistort(rawLeftImage, calibratedLeftImage, calibrationParams.leftCameraMatrix, calibrationParams.leftDistCoeffs);
	//undistort(rawRightImage, calibratedRightImage, calibrationParams.rightCameraMatrix, calibrationParams.rightDistCoeffs);
}