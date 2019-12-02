#pragma once

#include <cstring>
#include <qlabel.h>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>
#include <QFileDialog>


using namespace std;

class CommonHelper
{
public:
	static void showImage(QLabel* label, cv::Mat mat);

	static string selectImage();
};

