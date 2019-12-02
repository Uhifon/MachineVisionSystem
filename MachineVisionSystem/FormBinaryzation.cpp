#include "FormBinaryzation.h"
#include  <opencv2\imgproc.hpp> 
#include  <opencv2\world.hpp>
#include "CommonHelper.h"

FormBinaryzation::FormBinaryzation(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnReadImage, SIGNAL(clicked()), this, SLOT(ReadImage()));
	connect(ui.btnThreshold, SIGNAL(clicked()), this, SLOT(Threshold()));
	connect(ui.btnAdaptiveThreshold, SIGNAL(clicked()), this, SLOT(AdaptiveThreshold()));
}


void FormBinaryzation::ReadImage()
{
	 string path = CommonHelper::selectFile();
	 srcImage = cv::imread(path);
	 CommonHelper::showImage(ui.labelPicIn, srcImage);
}
 

//二值化处理
void FormBinaryzation::Threshold()
{
	if (!srcImage.data)
		return ;
	double thresh = ui.spinBoxThresh->value();
	double maxThresh = ui.spinBoxMaxThresh->value();
	cv::ThresholdTypes thresholdType = (cv::ThresholdTypes)ui.cmbThresholdType->currentIndex();
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, cv::COLOR_BGR2GRAY);
	double res = cv::threshold(srcGray, dstImage, thresh, maxThresh, thresholdType);
	CommonHelper::showImage(ui.labelPicOut1, dstImage);
}

//自适应二值化
void FormBinaryzation::AdaptiveThreshold()
{
	if (!srcImage.data)
		return;
	double maxThresh = ui.spinBoxMaxThresh_2->value();
	int blocksize = ui.lineEditBolckSize->text().toDouble();
	double c = ui.lineEditConst->text().toDouble() ;
	
	cv::ThresholdTypes thresholdType = (cv::ThresholdTypes)ui.cmbThresholdType_2->currentIndex();
	cv::AdaptiveThresholdTypes adaptiveThresholdType = (cv::AdaptiveThresholdTypes)ui.cmbAdaptiveThresholdType->currentIndex();
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, cv::COLOR_BGR2GRAY);
    cv::adaptiveThreshold(srcGray, dstImage, maxThresh, adaptiveThresholdType, thresholdType, blocksize,c);
	CommonHelper::showImage(ui.labelPicOut2, dstImage);
}