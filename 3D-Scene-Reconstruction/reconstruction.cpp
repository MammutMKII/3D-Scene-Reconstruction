#include "reconstruction.h"

#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>

#include <opencv2/xfeatures2d.hpp>

using namespace cv;

void reconstructV1(Mat &leftImage, Mat &rightImage, Mat &result) {
	const bool CROSS_CHECKING = false;
	//auto sift = SIFT::create(10000, 3, 0.001, 100000, 0.4);
	auto sift = xfeatures2d::SIFT::create();

	std::vector<KeyPoint> leftKeypoints{};
	Mat leftDescriptors{};
	sift->detectAndCompute(leftImage, noArray(), leftKeypoints, leftDescriptors);
	std::vector<KeyPoint> rightKeypoints{};
	Mat rightDescriptors{};
	sift->detectAndCompute(rightImage, noArray(), rightKeypoints, rightDescriptors);

	auto flann = FlannBasedMatcher();
	auto brute = BFMatcher(NORM_L2, CROSS_CHECKING);
	std::vector<std::vector<DMatch>> matches{};
	brute.knnMatch(leftDescriptors, rightDescriptors, matches, CROSS_CHECKING ? 1 : 2);

	std::vector<std::vector<DMatch>> filteredMatches{};

	std::vector<float> X{};
	std::vector<float> Y{};
	std::vector<float> Z{};

	for (auto match : matches) {
		if (match.size() > 0) {
			auto leftKP = leftKeypoints[match[0].queryIdx];
			auto rightKP = rightKeypoints[match[0].trainIdx];
			double xdiff = abs(leftKP.pt.x - rightKP.pt.x);
			if ((CROSS_CHECKING || (match.size() > 1 && match[0].distance < 0.75*match[1].distance))
				&& xdiff < 0.25*leftImage.cols) {
				std::vector<DMatch> m{ match[0] };
				filteredMatches.push_back(m);
				X.push_back(leftKP.pt.x);
				Y.push_back(leftKP.pt.y);
				Z.push_back(xdiff);
			}
		}
	}

	Mat matchImage;
	drawMatches(leftImage, leftKeypoints, rightImage, rightKeypoints, filteredMatches, matchImage);
	imshow("result", matchImage);

	std::ofstream myfile;
	myfile.open("../import_pc_data.m");
	myfile << "function [x,y,z] = import_pc_data()\n";
	myfile << "\tx = [";
	for (auto x : X)
		myfile << x << " ";
	myfile << "];\n";
	myfile << "\ty = [";
	for (auto y : Y)
		myfile << y << " ";
	myfile << "];\n";
	myfile << "\tz = [";
	for (auto z : Z)
		myfile << z << " ";
	myfile << "];\n";

	myfile << "end";
	myfile.close();
}


void reconstructV2(std::vector<std::tuple<KeyPoint,KeyPoint>> keyPointMatches, std::vector<float> &X, std::vector<float> &Y, std::vector<float> &Z, StereoCalibrationParams calibrationParams) {
	std::vector<Point3f> disparityPoints{};

	for (auto match : keyPointMatches) {
		auto leftKP = std::get<0>(match);
		auto rightKP = std::get<1>(match);
		float posX = (leftKP.pt.x + rightKP.pt.x) / 2.0;
		float posY = (leftKP.pt.y + rightKP.pt.y) / 2.0;
		float xdiff = leftKP.pt.x - rightKP.pt.x;

		disparityPoints.push_back(Point3f(posX, posY, xdiff));
	}

	std::vector<Point3f> depthPoints{};
	perspectiveTransform(disparityPoints, depthPoints, calibrationParams.Q);

	X = std::vector<float>{};
	Y = std::vector<float>{};
	Z = std::vector<float>{};

	for (auto point : depthPoints) {
		X.push_back(point.x);
		Y.push_back(point.y);
		Z.push_back(point.z);
	}
}