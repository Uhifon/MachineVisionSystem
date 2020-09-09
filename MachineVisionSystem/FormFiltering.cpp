#include "FormFiltering.h"
#include "CommonHelper.h"

FormFiltering::FormFiltering(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}


void FormFiltering::btnReadImageClick()
{
	string path = CommonHelper::selectImage();
	if (path == "")
		return;
	srcImage = cv::imread(path);
	CommonHelper::showImage(ui.labelPicIn, srcImage);
}

//方框滤波
void FormFiltering::btnBoxFilterClick()
{
	  /* void boxFilter(InputArray src,OutputArray dst,int ddepth,Size ksize,Point anchor=Point(-1,-1),boolnormalize=true,int borderType=BORDER_DEFAULT)
	    第一个参数，InputArray类型的src，输入图像，即图像源，填Mat类对象即可，该函数对通道是独立处理的，且可以处理任意通道数的图片，处理图片深度应该是CV_8U, CV_16U, CV_16S, CV_32F, CV_64F之一；
		第二个参数，OutputArray类型的dst，即目标图像，需要和原图像有一样的尺寸和类型；
		第三个参数，int类型的ddepth，输入图像的深度， -1代表用原图像深度，即src.depth();
	    第四个参数，Size类型的ksize，内核的大小，一般用Size(w, h)的写法来表示内核的大小，例如Size(3, 3)就是3×3的核大小；
		第五个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意有默认值Point(-1, -1)，如果这个点坐标是负值的话就表示取核中心为锚点；
		第六个参数，bool类型的normalize，默认值为true，一个标识符，表示内核是否被其区域归一化了；
		第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式，有默认值BORDER_DEFAULT，一般不去管它。*/
	//int blocksize = ui.lineEditBolckSize->text().toDouble();
	//cv::Point2i ancho = cv::Point2i(ui.lineEditAncho_x->text().toInt(), ui.lineEditAncho_y->text().toInt()); //锚点的位置，其默认值为(-1, -1)说明位于kernel的中心位置。
	cv::boxFilter(srcImage, dstImage,-1,Size(3,3), cv::Point2i(-1,-1));
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
}

//均值滤波
void FormFiltering::btnBlurClick()
{
	/*void blur(InputArray src, OutputArray, dst, Size ksize, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
		第一个参数，InputArray类型的src，输入图像，即图像源，填Mat类对象即可，该函数对通道是独立处理的，且可以处理任意通道数的图片，处理图片深度应该是CV_8U, CV_16U, CV_16S, CV_32F, CV_64F之一；
		第二个参数，OutputArray类型的dst，即目标图像，需要和原图像有一样的尺寸和类型；比如可以用Mat::clone, 以源图片为模板来初始化得到如假包换的目标图；
		第三个参数，Size类型的ksize，内核的大小，一般用Size(w, h)的写法来表示内核的大小，例如Size(3, 3)就是3×3的核大小；
		第四个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意有默认值Point(-1, -1)，如果这个点坐标是负值的话就表示取核中心为锚点；
		第五个参数，int类型的borderType，用于推断图像外部像素的某种边界模式，有默认值BORDER_DEFAULT，一般不去管它。*/
	cv::blur(srcImage, dstImage, Size(3, 3));
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
}

//高斯滤波
void FormFiltering::btnGaussianBlurClick()
{
	//void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double, sigmaY = 0, int borderType = BORDER_DEFAULT)
	//	第一个参数，InputArray类型的src，输入图像，即图像源，填Mat类对象即可，该函数对通道是独立处理的，且可以处理任意通道数的图片，处理图片深度应该是CV_8U, CV_16U, CV_16S, CV_32F, CV_64F之一；
	//	第二个参数，OutputArray类型的dst，即目标图像，需要和原图像有一样的尺寸和类型；比如可以用Mat::clone, 以源图片为模板来初始化得到如假包换的目标图；
	//	第三个参数，Size类型的ksize，内核的大小，一般用Size(w, h)的写法来表示内核的大小，ksize.width和ksize.height可以不同，但必须是正数&&奇数！！
	//	第四个参数，double类型的sigmaX，表示高斯核函数在X方向上的标准差；
	//	第五个参数，double类型的sigmaY，表示高斯核函数在Y方向上的标准差。若sigmaY为零，就将它设为sigmaX，如果sigmaX和sigmaY都为零，那就由ksize.width和ksize.hight计算出来。为了结果的正确性着想，最好把第三个参数Size，第四个参数sigmaX，第五个参数sigmaY全部制定好；
	//	第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式，有默认值BORDER_DEFAULT，一般不去管它。
	double sigmaX = 0;
	double sigmaY = 0;
	cv::GaussianBlur(srcImage, dstImage, Size(3, 3), sigmaX, sigmaY);
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
}


//中值滤波
void FormFiltering::btnMedianBlurClick()
{
	//void medianBlur(InputArray src, OutputArray dst, int ksize);
	//第一个参数，InputArray类型的src，函数的输入参数，填1、3或者4通道的Mat类型的图像；当ksize为3或者5的时候，图像深度需为CV_8U，CV_16U，或CV_32F其中之一，而对于较大孔径尺寸的图片，它只能是CV_8U。
    //第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。我们可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
    //第三个参数，int类型的ksize，孔径的线性尺寸（aperture linear size），注意这个参数必须是大于1的奇数，比如：3，5，7，9
	int ksize = 3;
	cv::medianBlur(srcImage, dstImage, ksize);
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
}

//双边滤波
void FormFiltering::btnBilateralFilterClick()
{
	/*void bilateralFilter(InputArray src, OutputArray dst, int d,double sigmaColor, double sigmaSpace,int borderType = BORDER_DEFAULT);
	第一个参数，InputArray类型的src，输入图像，可以是Mat类型，图像必须是8位或浮点型单通道、三通道的图像。
    第二个参数，OutputArray类型的dst，输出图像，和原图像有相同的尺寸和类型。
	第三个参数，int类型的d，表示在过滤过程中每个像素邻域的直径范围。如果这个值是非正数，则函数会从第五个参数sigmaSpace计算该值。
	第四个参数，double类型的sigmaColor，颜色空间过滤器的sigma值，这个参数的值月大，表明该像素邻域内有月宽广的颜色会被混合到一起，产生较大的半相等颜色区域。
	第五个参数，double类型的sigmaSpace，坐标空间中滤波器的sigma值，如果该值较大，则意味着颜色相近的较远的像素将相互影响，从而使更大的区域中足够相似的颜色获取相同的颜色。当d>0时，d指定了邻域大小且与sigmaSpace五官，否则d正比于sigmaSpace.
	第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式，有默认值BORDER_DEFAULT.*/
	int d = 25;
	double sigmaColor = 25 * 2;
	double sigmaSpace = 25 / 2;
	cv::bilateralFilter(srcImage, dstImage, d, sigmaColor, sigmaSpace);
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);

}