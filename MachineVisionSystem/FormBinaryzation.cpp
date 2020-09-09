#include "FormBinaryzation.h"
#include "CommonHelper.h"

FormBinaryzation::FormBinaryzation(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
}


void FormBinaryzation::btnReadImageClick()
{
	 string path = CommonHelper::selectImage();
	 if (path == "")
		 return;
	 srcImage = cv::imread(path);
	 CommonHelper::showImage(ui.labelPicIn, srcImage);
}
 

//二值化处理
void FormBinaryzation::btnThresholdClick()
{
	if (!srcImage.data)
		return ;
	double thresh = ui.spinBoxThresh->value();
	double maxThresh = ui.spinBoxMaxThresh->value();
	cv::ThresholdTypes thresholdType = (cv::ThresholdTypes)ui.cmbThresholdType->currentIndex();
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, cv::COLOR_BGR2GRAY);
	double res = cv::threshold(srcGray, dstImage, thresh, maxThresh, thresholdType);

	CommonHelper::showImage((QLabelEx*)ui.labelPicOut1, dstImage);
}

//自适应二值化
void FormBinaryzation::btnAdaptiveThresholdClick()
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
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut2, dstImage);
}