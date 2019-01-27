#pragma once

#include <vector>
#include <opencv2/core.hpp>

using namespace cv;

void displayStereo(Mat leftImage, Mat rightImage);
void display3D(std::vector<float> X, std::vector<float> Y, std::vector<float> Z);