#pragma once
#include <QWidget>
#include "ui_FormBinaryzation.h"
#include  <opencv2\core.hpp>
#include  <opencv2\opencv.hpp>

 

class FormBinaryzation:public QWidget
{
	Q_OBJECT
public:
	FormBinaryzation(QWidget *parent = Q_NULLPTR);



private:
	Ui::FormBinaryzationClass ui;
	
	cv::Mat srcImage;
	cv::Mat dstImage;
private slots:
	void ReadImage();
	void Threshold();
	void AdaptiveThreshold();

};

