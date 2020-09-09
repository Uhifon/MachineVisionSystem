#pragma once
#include <QWidget>
#include "ui_FormMorphological.h"
#include  <opencv2\opencv.hpp>

class FormMorphological :public QWidget
{
	Q_OBJECT
public:
	FormMorphological(QWidget *parent = Q_NULLPTR);

private:
	Ui::FormMorphologicalClass ui;
	cv::Mat srcImage;
	cv::Mat dstImage;


private slots :
	void btnReadImageClick();
    void btnMorphologicClick();  
};

