#pragma once

#include <opencv2/core.hpp>

using namespace cv;

void computeStereoCalibrationParams(Mat rawLeftChessboard, Mat rawRightChessboard, int &leftCalibrationParams, int &rightCalibrationParams);