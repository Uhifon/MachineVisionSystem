#include "FormCheckScratch.h"
#include "CommonHelper.h"

FormCheckScratch::FormCheckScratch(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}


void FormCheckScratch::btnReadImageClick()
{
	string path = CommonHelper::selectImage();
	if (path == "")
		return;
	srcImage = cv::imread(path);
	CommonHelper::showImage(ui.labelPicIn, srcImage);
}

 
void FormCheckScratch::btnCheckClick()
{
	//均值模糊
	Mat dstImage,diffImage, Mask;
	blur(srcImage, dstImage, Size(13, 13));

	//图像差分
	subtract(dstImage, srcImage, diffImage);

	//同动态阈值分割dyn_threshold
	threshold(diffImage, Mask, 50, 255, THRESH_BINARY_INV);
	imshow("imagemean", dstImage);
	waitKey(0);
	imshow("diffImage", diffImage);
	waitKey(0);
	imshow("Mask", Mask);
	waitKey(0);
	Mat imagegray;
	cvtColor(Mask, imagegray, COLOR_RGB2GRAY);
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	/*函数原型
		findContours(InputOutputArray image, OutputArrayOfArrays contours,OutputArray hierarchy, int mode, int method, Point offset = Point());
	    参数1：单通道图像矩阵，可以是灰度图，但更常用的是二值图像，一般是经过Canny、拉普拉斯等边缘检测算子处理过的二值图像；
		参数2：contours定义为“vector<vector<Point>> contours”，是一个双重向量（向量内每个元素保存了一组由连续的Point构成的点的集合的向量），每一组点集就是一个轮廓，有多少轮廓，contours就有多少元素；
		参数3：hierarchy定义为“vector<Vec4i> hierarchy”，Vec4i的定义：typedef Vec<int, 4> Vec4i;（向量内每个元素都包含了4个int型变量），所以从定义上看，hierarchy是一个向量，向量内每个元素都是一个包含4个int型的数组。向量hierarchy内的元素和轮廓向量contours内的元素是一一对应的，向量的容量相同。hierarchy内每个元素的4个int型变量是hierarchy[i][0] ~hierarchy[i][3]，分别表示当前轮廓 i 的后一个轮廓、前一个轮廓、父轮廓和内嵌轮廓的编号索引。如果当前轮廓没有对应的后一个轮廓、前一个轮廓、父轮廓和内嵌轮廓，则相应的hierarchy[i][*]被置为 - 1。
		参数4：定义轮廓的检索模式，取值如下：
		CV_RETR_EXTERNAL：只检测最外围轮廓，包含在外围轮廓内的内围轮廓被忽略；
		CV_RETR_LIST：检测所有的轮廓，包括内围、外围轮廓，但是检测到的轮廓不建立等级关系，彼此之间独立，没有等级关系，这就意味着这个检索模式下不存在父轮廓或内嵌轮廓，所以hierarchy向量内所有元素的第3、第4个分量都会被置为 - 1，具体下文会讲到；
		CV_RETR_CCOMP : 检测所有的轮廓，但所有轮廓只建立两个等级关系，外围为顶层，若外围内的内围轮廓还包含了其他的轮廓信息，则内围内的所有轮廓均归属于顶层；
		CV_RETR_TREE : 检测所有轮廓，所有轮廓建立一个等级树结构。外层轮廓包含内层轮廓，内层轮廓还可以继续包含内嵌轮廓。
		参数5：定义轮廓的近似方法，取值如下：
		CV_CHAIN_APPROX_NONE：保存物体边界上所有连续的轮廓点到contours向量内；
		CV_CHAIN_APPROX_SIMPLE：仅保存轮廓的拐点信息，把所有轮廓拐点处的点保存入contours向量内，拐点与拐点之间直线段上的信息点不予保留；
		CV_CHAIN_APPROX_TC89_L1：使用teh - Chinl chain 近似算法;
	    CV_CHAIN_APPROX_TC89_KCOS：使用teh - Chinl chain 近似算法。
		参数6：Point偏移量，所有的轮廓信息相对于原始图像对应点的偏移量，相当于在每一个检测出的轮廓点上加上该偏移量，并且Point还可以是负值！
    */
	findContours(imagegray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat drawing = Mat::zeros(Mask.size(), CV_8U);
	int j = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		Moments moms = moments(Mat(contours[i]));
		double area = moms.m00;//零阶矩即为二值图像的面积  double area = moms.m00;零阶距.m00表示轮廓的面积，.m10为轮廓重心

		//如果面积超出了设定的范围，则不再考虑该斑点 
		if (area > 20 && area < 1000)
		{
			drawContours(drawing, contours, i, Scalar(255), FILLED, 8, hierarchy, 0, Point());
			j = j + 1;

		}
	}
	//
	Mat element15(3, 3, CV_8U, Scalar::all(1));
	Mat close;
	//闭运算
	morphologyEx(drawing, close, MORPH_CLOSE, element15); 
	imshow("drawing", drawing);
	waitKey(0);
	vector<vector<Point> > contours1;
	vector<Vec4i> hierarchy1;
	findContours(close, contours1, hierarchy1, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	imshow("close", close);
	waitKey(0);
	j = 0;
	int m = 0;
	for (int i = 0; i < contours1.size(); i++)
	{
		Moments moms = moments(Mat(contours1[i]));
		double area = moms.m00;//零阶矩即为二值图像的面积  double area = moms.m00;
		//如果面积超出了设定的范围，则不再考虑该斑点  

		double area1 = contourArea(contours1[i]);
		if (area > 50 && area < 100000)
		{
			drawContours(srcImage, contours1, i, Scalar(0, 0, 255), FILLED, 8, hierarchy1, 0, Point());
			j = j + 1;

		}
		else if (area >= 0 && area <= 50)
		{
			drawContours(srcImage, contours1, i, Scalar(255, 0, 0), FILLED, 8, hierarchy1, 0, Point());
			m = m + 1;

		}
	}

	char t[256];
	sprintf_s(t, "%01d", j);
	string s = t;
	string txt = "Long NG : " + s;
	putText(srcImage, txt, Point(20, 30), FONT_HERSHEY_COMPLEX, 1,
		Scalar(0, 0, 255), 2, 8);

	sprintf_s(t, "%01d", m);
	s = t;
	txt = "Short NG : " + s;
	putText(srcImage, txt, Point(20, 60), FONT_HERSHEY_COMPLEX, 1,
		Scalar(255, 0, 0), 2, 8);
	imwrite("C:\\Users\\Tony\\Desktop\\result.bmp", srcImage);

}
