#pragma once

#include <vector>
#include <opencv2/core.hpp>

void displayStereo(cv::Mat leftImage, cv::Mat rightImage, std::string win1Name = "display stereo left", std::string win2Name = "display stereo right", int wait = 100);
void display3D(std::vector<float> X, std::vector<float> Y, std::vector<float> Z);