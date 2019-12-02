#include "CommonHelper.h"



/****************************************
* Qt中使用文件选择对话框步骤如下：
* 1. 定义一个QFileDialog对象
* 2. 设置路径、过滤器等属性
*****************************************/
string CommonHelper::selectFile()
{
	//定义文件对话框类
	QFileDialog *fileDialog = new QFileDialog();
	//定义文件对话框标题
	fileDialog->setWindowTitle("打开图片");
	//设置默认文件路径
	fileDialog->setDirectory(".");
	//设置文件过滤器
	fileDialog->setNameFilter("Images(*.png *.jpg *.jpeg *.bmp)");
	//设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//设置视图模式
	fileDialog->setViewMode(QFileDialog::Detail);
	//打印所有选择的文件的路径
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames)
		return tmp.toLocal8Bit();
}


void CommonHelper::showImage(QLabel* label, cv::Mat mat)
{
	cv::Mat temp;
	cv::cvtColor(mat, temp, cv::COLOR_BGR2RGB);//BGR convert to RGB
	QImage Qtemp = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	label->setPixmap(QPixmap::fromImage(Qtemp));
	label->show();
}