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
}

//现实图像
void CommonHelper::showImage(QLabel* label, Mat mat)
{
	QImage image = MatImageToQt(mat);
	label->setPixmap(QPixmap::fromImage(image).scaled(label->size()));
	label->show();
}


//Mat转成QImage
QImage CommonHelper::MatImageToQt(Mat &src)
{
	//CV_8UC1 8位无符号的单通道---灰度图片
	if (src.type() == CV_8UC1)  
	{
		//使用给定的大小和格式构造图像
		//QImage(int width, int height, Format format)
		QImage qImage(src.cols, src.rows, QImage::Format_Indexed8);
		//扩展颜色表的颜色数目
		qImage.setColorCount(256);

		//在给定的索引设置颜色
		for (int i = 0; i < 256; i++)
		{
			//得到一个黑白图
			qImage.setColor(i, qRgb(i, i, i));
		}
		//复制输入图像,data数据段的首地址
		uchar *pSrc = src.data;
		//
		for (int row = 0; row < src.rows; row++)
		{
			//遍历像素指针
			uchar *pDest = qImage.scanLine(row);
			//从源src所指的内存地址的起始位置开始拷贝n个
			//字节到目标dest所指的内存地址的起始位置中
			memcmp(pDest, pSrc, src.cols);
			//图像层像素地址
			pSrc += src.step;
		}
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