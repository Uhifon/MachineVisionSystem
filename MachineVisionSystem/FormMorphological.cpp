#include "FormMorphological.h"
#include "CommonHelper.h"
 

FormMorphological::FormMorphological(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

//获取图像
void FormMorphological::btnReadImageClick()
{
	string path = CommonHelper::selectImage();
	if (path == "")
		return;
	srcImage = cv::imread(path);
	CommonHelper::showImage(ui.labelPicIn, srcImage);
}

//形态学运算
void FormMorphological::btnMorphologicClick()
{
	cv::MorphTypes type = (cv::MorphTypes)ui.cmbMorphologicalMethod->currentIndex();
	int kernel = ui.lineEditKernel->text().toInt();      //内核 结构元素 
	cv::Point2i ancho =  cv::Point2i(ui.lineEditAncho_x->text().toInt(), ui.lineEditAncho_y->text().toInt()); //锚点的位置，其默认值为(-1, -1)说明位于kernel的中心位置。
	int iterations = ui.lineEditIterations->text().toInt();;  //迭代次数
	cv::BorderTypes borderType = (cv::BorderTypes)ui.cmbBorderType->currentIndex();  //用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_CONSTANT。
	//borderValue  //当边界为常数时的边界值，有默认值morphologyDefaultBorderValue()，一般我们不用去管他

	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, cv::COLOR_BGR2GRAY);
    //输入图像可以是任意的， 但深度应该是CV_8U，CV_16U，CV_16S，CV_32F或CV_64F之一。
	cv::morphologyEx(srcGray, dstImage,type, kernel, ancho, iterations, borderType);
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
 
}