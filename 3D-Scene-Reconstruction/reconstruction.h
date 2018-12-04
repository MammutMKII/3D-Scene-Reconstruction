#pragma once

#include <opencv2/core.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace xfeatures2d;

void reconstruct(Mat &leftImage, Mat &rightImage, Mat &result);