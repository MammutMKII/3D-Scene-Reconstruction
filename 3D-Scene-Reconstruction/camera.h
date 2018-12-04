#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <string>
#include <iostream>

#include "Windows.h"

using namespace cv;

int capture_images(Mat &leftImage, Mat &rightImage);