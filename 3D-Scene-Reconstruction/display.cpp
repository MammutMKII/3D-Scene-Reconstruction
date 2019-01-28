#include "display.h"

#include <fstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

void displayStereo(Mat leftImage, Mat rightImage, std::string win1Name, std::string win2Name, int wait) {
	namedWindow(win1Name, WINDOW_AUTOSIZE);
	moveWindow(win1Name, 0, 300);
	namedWindow(win2Name, WINDOW_AUTOSIZE);
	moveWindow(win2Name, 480, 300);

	imshow(win1Name, leftImage);
	imshow(win2Name, rightImage);
	waitKey(wait);
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