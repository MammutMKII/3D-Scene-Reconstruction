#include <iostream>
#include "camera.h"
#include "reconstruction.h"

using namespace cv;

int capture_and_store()
{
	Mat leftImage, rightImage;
	if (int status = capture_images(leftImage, rightImage) < 0)
		return status;

	imwrite("../images/test.png", leftImage);
	imwrite("../images/test.png", rightImage);
	return 0;
}

int load_and_reconstruct()
{
	Mat leftImage = imread("../images/motorcycle_left.png", IMREAD_GRAYSCALE);
	Mat rightImage = imread("../images/motorcycle_right.png", IMREAD_GRAYSCALE);

	Mat result;
	reconstruct(leftImage, rightImage, result);

	waitKey(30000);

	return 0;
}

int capture_and_reconstruct()
{
	Mat leftImage, rightImage;
	if (int status = capture_images(leftImage, rightImage) < 0)
		return status;

	Mat result;
	reconstruct(leftImage, rightImage, result);

	waitKey(30000);

	return 0;
}

int main()
{
	//capture_and_store();

	load_and_reconstruct();

	//while(true)
	//	capture_and_reconstruct();

	return 0;
}
