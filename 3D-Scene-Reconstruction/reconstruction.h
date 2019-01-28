#pragma once

#include "calibration.h"

#include <opencv2/core.hpp>
#include <vector>

void reconstructV1(cv::Mat &leftImage, cv::Mat &rightImage, cv::Mat &result);
void reconstructV2(std::vector<std::tuple<cv::KeyPoint, cv::KeyPoint>> keyPointMatches, std::vector<float> &X, std::vector<float> &Y, std::vector<float> &Z, StereoCalibrationParams calibrationParams);