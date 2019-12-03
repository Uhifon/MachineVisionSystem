#pragma once
#include <QWidget>
#include "ui_FormMorphological.h"
#include  <opencv2\core.hpp>
#include  <opencv2\opencv.hpp>
#include  <opencv2\imgproc.hpp> 
#include  <opencv2\world.hpp>
#include <opencv2\highgui.hpp>


class FormMorphological :public QWidget
{
	Q_OBJECT
public:
	FormMorphological(QWidget *parent = Q_NULLPTR);

private:
	Ui::FormMorphologicalClass ui;
	cv::Mat srcImage;
	cv::Mat dstImage;

signals:


private slots :
	void ReadImage();
    void MorphologicalOperate();
};

