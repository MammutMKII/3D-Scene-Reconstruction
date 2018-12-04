#include "reconstruction.h"

#include <opencv2/highgui.hpp>
void reconstruct(Mat &leftImage, Mat &rightImage, Mat &result) {
	auto sift = SIFT::create(1000);
	std::vector<KeyPoint> keypoints{};
	sift->detect(leftImage, keypoints);
	drawKeypoints(leftImage, keypoints, result);

	imshow("with kp", result);
	waitKey(0);
}