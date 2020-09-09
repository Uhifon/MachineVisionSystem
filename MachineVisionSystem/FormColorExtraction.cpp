#include "FormColorExtraction.h"
#include "CommonHelper.h"
#include "QLabelEx.h"

FormColorExtraction::FormColorExtraction(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	 
	
	/*connect(ui.labelPicIn, SIGNAL(linkActivated(QString)), this, SLOT(LabelPicInClick(QString)));*/
}

void FormColorExtraction::btnReadImageClick()
{
	string path = CommonHelper::selectImage();
	if (path=="")
		return;
	srcImage = cv::imread(path);
	CommonHelper::showImage(ui.labelPicIn, srcImage);
}
 

void FormColorExtraction::LabelPicInClick()
{
	 
}