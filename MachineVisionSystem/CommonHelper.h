#pragma once

#include <cstring>
#include <qlabel.h>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>
#include <QFileDialog>


using namespace std;
using namespace cv;

class CommonHelper
{
public:
	static void showImage(QLabel* label, Mat mat);
	static string selectImage();
	static QImage MatImageToQt(Mat &src);
};

