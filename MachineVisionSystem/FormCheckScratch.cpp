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
	//��ֵģ��
	Mat dstImage,diffImage, Mask;
	blur(srcImage, dstImage, Size(13, 13));

	//ͼ����
	subtract(dstImage, srcImage, diffImage);

	//ͬ��̬��ֵ�ָ�dyn_threshold
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

	/*����ԭ��
		findContours(InputOutputArray image, OutputArrayOfArrays contours,OutputArray hierarchy, int mode, int method, Point offset = Point());
	    ����1����ͨ��ͼ����󣬿����ǻҶ�ͼ���������õ��Ƕ�ֵͼ��һ���Ǿ���Canny��������˹�ȱ�Ե������Ӵ�����Ķ�ֵͼ��
		����2��contours����Ϊ��vector<vector<Point>> contours������һ��˫��������������ÿ��Ԫ�ر�����һ����������Point���ɵĵ�ļ��ϵ���������ÿһ��㼯����һ���������ж���������contours���ж���Ԫ�أ�
		����3��hierarchy����Ϊ��vector<Vec4i> hierarchy����Vec4i�Ķ��壺typedef Vec<int, 4> Vec4i;��������ÿ��Ԫ�ض�������4��int�ͱ����������ԴӶ����Ͽ���hierarchy��һ��������������ÿ��Ԫ�ض���һ������4��int�͵����顣����hierarchy�ڵ�Ԫ�غ���������contours�ڵ�Ԫ����һһ��Ӧ�ģ�������������ͬ��hierarchy��ÿ��Ԫ�ص�4��int�ͱ�����hierarchy[i][0] ~hierarchy[i][3]���ֱ��ʾ��ǰ���� i �ĺ�һ��������ǰһ������������������Ƕ�����ı�������������ǰ����û�ж�Ӧ�ĺ�һ��������ǰһ������������������Ƕ����������Ӧ��hierarchy[i][*]����Ϊ - 1��
		����4�����������ļ���ģʽ��ȡֵ���£�
		CV_RETR_EXTERNAL��ֻ�������Χ��������������Χ�����ڵ���Χ���������ԣ�
		CV_RETR_LIST��������е�������������Χ����Χ���������Ǽ�⵽�������������ȼ���ϵ���˴�֮�������û�еȼ���ϵ�������ζ���������ģʽ�²����ڸ���������Ƕ����������hierarchy����������Ԫ�صĵ�3����4���������ᱻ��Ϊ - 1���������Ļὲ����
		CV_RETR_CCOMP : ������е�����������������ֻ���������ȼ���ϵ����ΧΪ���㣬����Χ�ڵ���Χ������������������������Ϣ������Χ�ڵ����������������ڶ��㣻
		CV_RETR_TREE : �������������������������һ���ȼ����ṹ��������������ڲ��������ڲ����������Լ���������Ƕ������
		����5�����������Ľ��Ʒ�����ȡֵ���£�
		CV_CHAIN_APPROX_NONE����������߽������������������㵽contours�����ڣ�
		CV_CHAIN_APPROX_SIMPLE�������������Ĺյ���Ϣ�������������յ㴦�ĵ㱣����contours�����ڣ��յ���յ�֮��ֱ�߶��ϵ���Ϣ�㲻�豣����
		CV_CHAIN_APPROX_TC89_L1��ʹ��teh - Chinl chain �����㷨;
	    CV_CHAIN_APPROX_TC89_KCOS��ʹ��teh - Chinl chain �����㷨��
		����6��Pointƫ���������е�������Ϣ�����ԭʼͼ���Ӧ���ƫ�������൱����ÿһ���������������ϼ��ϸ�ƫ����������Point�������Ǹ�ֵ��
    */
	findContours(imagegray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat drawing = Mat::zeros(Mask.size(), CV_8U);
	int j = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		Moments moms = moments(Mat(contours[i]));
		double area = moms.m00;//��׾ؼ�Ϊ��ֵͼ������  double area = moms.m00;��׾�.m00��ʾ�����������.m10Ϊ��������

		//�������������趨�ķ�Χ�����ٿ��Ǹðߵ� 
		if (area > 20 && area < 1000)
		{
			drawContours(drawing, contours, i, Scalar(255), FILLED, 8, hierarchy, 0, Point());
			j = j + 1;

		}
	}
	//
	Mat element15(3, 3, CV_8U, Scalar::all(1));
	Mat close;
	//������
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
		double area = moms.m00;//��׾ؼ�Ϊ��ֵͼ������  double area = moms.m00;
		//�������������趨�ķ�Χ�����ٿ��Ǹðߵ�  

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
