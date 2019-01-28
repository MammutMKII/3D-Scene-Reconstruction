#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int captureStereo(cv::Mat &leftImage, cv::Mat &rightImage, cv::VideoCapture leftCapture, cv::VideoCapture rightCapture);
void openStereoVideo(cv::VideoCapture &leftCapture, cv::VideoCapture &rightCapture);
void takeStereo(cv::Mat &leftImage, cv::Mat &rightImage);