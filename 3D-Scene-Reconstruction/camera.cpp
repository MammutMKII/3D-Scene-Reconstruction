#include "camera.h"

int capture_images(Mat &leftImage, Mat &rightImage) {
	int camIdx1 = 0;
	int camIdx2 = 1;
	VideoCapture captInputVideo1(camIdx1);
	VideoCapture captInputVideo2(camIdx2);
	if(!captInputVideo1.isOpened() || !captInputVideo1.isOpened()) {
		std::cout << "Could not open video " << std::endl;
		return -1;
	}

	//then request the size
	int videoWidth1 = (int)captInputVideo1.get(CAP_PROP_FRAME_WIDTH);
	int videoHeight1 = (int)captInputVideo1.get(CAP_PROP_FRAME_HEIGHT);
	int numOfFrames1 = (int)captInputVideo1.get(CAP_PROP_FRAME_COUNT);
	std::cout << "video opened, w=" << videoWidth1 << " h=" << videoHeight1 << " #frames=" << numOfFrames1 << std::endl;
	int videoWidth2 = (int)captInputVideo2.get(CAP_PROP_FRAME_WIDTH);
	int videoHeight2 = (int)captInputVideo2.get(CAP_PROP_FRAME_HEIGHT);
	int numOfFrames2 = (int)captInputVideo2.get(CAP_PROP_FRAME_COUNT);
	std::cout << "video opened, w=" << videoWidth2 << " h=" << videoHeight2 << " #frames=" << numOfFrames2 << std::endl;

	const char* WIN_ORIG1 = "orig frame1";
	const char* WIN_ORIG2 = "orig frame2";

	int delayInMs = 100;

	// Windows
	namedWindow(WIN_ORIG1, WINDOW_AUTOSIZE);
	moveWindow(WIN_ORIG1, videoWidth1, 0);
	namedWindow(WIN_ORIG2, WINDOW_AUTOSIZE);
	moveWindow(WIN_ORIG2, videoWidth1+videoWidth2, 0);

	int idx = 0;
	for (;;) //Show the image captured in the window and repeat
	{
		captInputVideo1 >> leftImage;
		captInputVideo2 >> rightImage;
		rotate(leftImage, leftImage, RotateFlags::ROTATE_90_CLOCKWISE);
		rotate(rightImage, rightImage, RotateFlags::ROTATE_90_COUNTERCLOCKWISE);

		if (leftImage.empty() || rightImage.empty()) {
			std::cout << "end of video reached" << std::endl;
		}

		cvtColor(leftImage, leftImage, COLOR_BGR2GRAY);
		cvtColor(rightImage, rightImage, COLOR_BGR2GRAY);

		imshow(WIN_ORIG1, leftImage);
		imshow(WIN_ORIG2, rightImage);
		waitKey(delayInMs);

		if (GetAsyncKeyState(VK_SPACE     ) & 0x8000)
		{
			std::cout << "key press" << std::endl;
			break;
		}
	}

	return 0;
}

