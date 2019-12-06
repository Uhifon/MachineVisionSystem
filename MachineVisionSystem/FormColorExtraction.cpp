#include "FormColorExtraction.h"
#include "CommonHelper.h"
#include "QLabelEx.h"

FormColorExtraction::FormColorExtraction(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.labelPicIn = (QLabelEx*)(ui.labelPicIn);
    connect(ui.labelPicIn, SIGNAL(clicked()), this, SLOT(LabelPicInClick()));


}

void FormColorExtraction::btnReadImageClick()
{
	string path = CommonHelper::selectImage();
	if (path=="")
		return;
	srcImage = cv::imread(path);
	CommonHelper::showImage((QLabelEx*)ui.labelPicIn, srcImage);
}
 

void FormColorExtraction::LabelPicInClick()
{
	 
}