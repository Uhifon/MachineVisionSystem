#pragma once
#include <QWidget>
#include "ui_FormCheckScratch.h"
#include  <opencv2\opencv.hpp>

class FormCheckScratch :public QWidget
{
	Q_OBJECT
public:
	FormCheckScratch(QWidget *parent = Q_NULLPTR);

private:
	Ui::FormCheckScratchClass ui;
	cv::Mat srcImage;
	cv::Mat dstImage;
private slots:
	void btnReadImageClick();
	void btnCheckClick();
};

