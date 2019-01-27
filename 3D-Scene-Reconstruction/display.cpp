#include "display.h"

#include <fstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

void displayStereo(Mat leftImage, Mat rightImage) {
	const char* WIN_ORIG1 = "display stereo left";
	const char* WIN_ORIG2 = "display stereo right";

	namedWindow(WIN_ORIG1, WINDOW_AUTOSIZE);
	//moveWindow(WIN_ORIG1, videoWidth1, 0);
	namedWindow(WIN_ORIG2, WINDOW_AUTOSIZE);
	//moveWindow(WIN_ORIG2, videoWidth1+videoWidth2, 0);

	imshow(WIN_ORIG1, leftImage);
	imshow(WIN_ORIG2, rightImage);
	waitKey(100);
}

void display3D(std::vector<float> X, std::vector<float> Y, std::vector<float> Z) {
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