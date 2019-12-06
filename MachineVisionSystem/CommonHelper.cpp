#include "CommonHelper.h"

/****************************************
* Qt中使用文件选择对话框步骤如下：
* 1. 定义一个QFileDialog对象
* 2. 设置路径、过滤器等属性
*****************************************/
string CommonHelper::selectImage()
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
	return "";

}

//显示图像
void CommonHelper::showImage(QLabelEx* label, Mat mat)
{
	 
	QImage image = MatImageToQt(mat);
	label->setPixmap(QPixmap::fromImage(image).scaled(label->size()));  //以label的大小显示图像
	label->show();
}


//Mat转成QImage
QImage CommonHelper::MatImageToQt(Mat &src)
{
	//CV_8UC1 8位无符号的单通道---灰度图片
	if (src.type() == CV_8UC1)  
	{
		//得到图像的的首地址
		const uchar *pSrc = (const uchar*)src.data;
		//以src构造图片
		QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_Grayscale8);
		//在不改变实际图像数据的条件下，交换红蓝通道
		return qImage;
	}

	//为3通道的彩色图片
	else if (src.type() == CV_8UC3)
	{
		//得到图像的的首地址
		const uchar *pSrc = (const uchar*)src.data;
		//以src构造图片
		QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_RGB888);
		//在不改变实际图像数据的条件下，交换红蓝通道
		return qImage.rgbSwapped();
	}
	//四通道图片，带Alpha通道的RGB彩色图像
	else if (src.type() == CV_8UC4)
	{
		const uchar *pSrc = (const uchar*)src.data;
		QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
		//返回图像的子区域作为一个新图像
		return qImage.copy();
	}
	else
	{
		return QImage();
	}
}