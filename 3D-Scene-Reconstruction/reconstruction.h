#pragma once

#include <opencv2/core.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <vector>

using namespace cv;
using namespace xfeatures2d;

void reconstructV1(Mat &leftImage, Mat &rightImage, Mat &result);
void reconstructV2(std::vector<std::tuple<KeyPoint, KeyPoint>> keyPointMatches, std::vector<float> &X, std::vector<float> &Y, std::vector<float> &Z);