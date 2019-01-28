#pragma once

#include <opencv2/core.hpp>

void matchStereo(cv::Mat calibratedLeftImage, cv::Mat calibratedRightImage, std::vector<std::tuple<cv::KeyPoint,cv::KeyPoint>> &keyPointMatches);