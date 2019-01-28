#pragma once

#include <opencv2/core.hpp>

struct StereoCalibrationParams {
	cv::Mat leftCameraMatrix, rightCameraMatrix;
	cv::Mat leftDistCoeffs, rightDistCoeffs;
	cv::Mat R, T, E, F;
	cv::Mat R1, R2, P1, P2, Q;
	cv::Mat leftMap1, leftMap2, rightMap1, rightMap2;
};

StereoCalibrationParams computeStereoCalibrationParams();
void undistortRectifyStereo(cv::Mat rawLeftChessboard, cv::Mat rawRightChessboard, cv::Mat &calibratedLeftChessboard, cv::Mat &calibratedRightChessboard, StereoCalibrationParams calibrationParams);