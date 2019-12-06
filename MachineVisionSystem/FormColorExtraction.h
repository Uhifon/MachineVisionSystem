#pragma once
#include <QWidget>
#include "ui_FormColorExtraction.h"
#include  <opencv2\opencv.hpp>

class FormColorExtraction :public QWidget
{
	Q_OBJECT
public:
	FormColorExtraction(QWidget *parent = Q_NULLPTR);

private:
	Ui::FormColorExtractionClass ui;
	cv::Mat srcImage;
	cv::Mat dstImage;

private slots :
	void btnReadImageClick();
	void LabelPicInClick();
};

