#include "match.h"

#include <opencv2/highgui.hpp>

void matchStereo(Mat calibratedLeftImage, Mat calibratedRightImage, std::vector<std::tuple<KeyPoint, KeyPoint>> &keyPointMatches) {
	const bool CROSS_CHECKING = false;
	//auto sift = SIFT::create(10000, 3, 0.001, 100000, 0.4);
	auto sift = SIFT::create();

	std::vector<KeyPoint> leftKeypoints{};
	Mat leftDescriptors{};
	sift->detectAndCompute(calibratedLeftImage, noArray(), leftKeypoints, leftDescriptors);
	std::vector<KeyPoint> rightKeypoints{};
	Mat rightDescriptors{};
	sift->detectAndCompute(calibratedRightImage, noArray(), rightKeypoints, rightDescriptors);

	auto brute = BFMatcher(NORM_L2, CROSS_CHECKING);
	std::vector<std::vector<DMatch>> matches{};
	brute.knnMatch(leftDescriptors, rightDescriptors, matches, CROSS_CHECKING ? 1 : 2);

	std::vector<std::vector<DMatch>> filteredMatches{};
	keyPointMatches = std::vector<std::tuple<KeyPoint, KeyPoint>>{};

	for (auto match : matches) {
		if (match.size() > 0) {
			auto leftKP = leftKeypoints[match[0].queryIdx];
			auto rightKP = rightKeypoints[match[0].trainIdx];

			if(CROSS_CHECKING || (match.size() > 1 && match[0].distance < 0.75*match[1].distance)) {
				std::vector<DMatch> m{ match[0] };
				filteredMatches.push_back(m);
				keyPointMatches.push_back(std::tuple(leftKP, rightKP));
			}
		}
	}

	Mat matchImage;
	drawMatches(calibratedLeftImage, leftKeypoints, calibratedRightImage, rightKeypoints, filteredMatches, matchImage);
	imshow("matches", matchImage);
}