#pragma once
#include <QWidget>
#include "ui_FormFiltering.h"
#include  <opencv2\opencv.hpp>
 

class FormFiltering :public QWidget
{
	Q_OBJECT
public:
	FormFiltering(QWidget *parent = Q_NULLPTR);

private:
	Ui::FormFilteringClass ui;
	cv::Mat srcImage;
	cv::Mat dstImage;

private slots :
	void btnReadImageClick();
	void btnBoxFilterClick();
	void btnBlurClick();
	void btnGaussianBlurClick();

	void btnMedianBlurClick();
	void btnBilateralFilterClick();
};

