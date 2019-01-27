#pragma once

#include <opencv2/core.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace xfeatures2d;

void matchStereo(Mat calibratedLeftImage, Mat calibratedRightImage, std::vector<std::tuple<KeyPoint,KeyPoint>> &keyPointMatches);