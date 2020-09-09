#include "FormMorphological.h"
#include "CommonHelper.h"
 

FormMorphological::FormMorphological(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

//��ȡͼ��
void FormMorphological::btnReadImageClick()
{
	string path = CommonHelper::selectImage();
	if (path == "")
		return;
	srcImage = cv::imread(path);
	CommonHelper::showImage(ui.labelPicIn, srcImage);
}

//��̬ѧ����
void FormMorphological::btnMorphologicClick()
{
	cv::MorphTypes type = (cv::MorphTypes)ui.cmbMorphologicalMethod->currentIndex();
	int kernel = ui.lineEditKernel->text().toInt();      //�ں� �ṹԪ�� 
	cv::Point2i ancho =  cv::Point2i(ui.lineEditAncho_x->text().toInt(), ui.lineEditAncho_y->text().toInt()); //ê���λ�ã���Ĭ��ֵΪ(-1, -1)˵��λ��kernel������λ�á�
	int iterations = ui.lineEditIterations->text().toInt();;  //��������
	cv::BorderTypes borderType = (cv::BorderTypes)ui.cmbBorderType->currentIndex();  //�����ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ��ע������Ĭ��ֵBORDER_CONSTANT��
	//borderValue  //���߽�Ϊ����ʱ�ı߽�ֵ����Ĭ��ֵmorphologyDefaultBorderValue()��һ�����ǲ���ȥ����

	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, cv::COLOR_BGR2GRAY);
    //����ͼ�����������ģ� �����Ӧ����CV_8U��CV_16U��CV_16S��CV_32F��CV_64F֮һ��
	cv::morphologyEx(srcGray, dstImage,type, kernel, ancho, iterations, borderType);
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
 
}