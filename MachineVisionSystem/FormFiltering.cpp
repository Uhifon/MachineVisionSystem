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

//�����˲�
void FormFiltering::btnBoxFilterClick()
{
	  /* void boxFilter(InputArray src,OutputArray dst,int ddepth,Size ksize,Point anchor=Point(-1,-1),boolnormalize=true,int borderType=BORDER_DEFAULT)
	    ��һ��������InputArray���͵�src������ͼ�񣬼�ͼ��Դ����Mat����󼴿ɣ��ú�����ͨ���Ƕ�������ģ��ҿ��Դ�������ͨ������ͼƬ������ͼƬ���Ӧ����CV_8U, CV_16U, CV_16S, CV_32F, CV_64F֮һ��
		�ڶ���������OutputArray���͵�dst����Ŀ��ͼ����Ҫ��ԭͼ����һ���ĳߴ�����ͣ�
		������������int���͵�ddepth������ͼ�����ȣ� -1������ԭͼ����ȣ���src.depth();
	    ���ĸ�������Size���͵�ksize���ں˵Ĵ�С��һ����Size(w, h)��д������ʾ�ں˵Ĵ�С������Size(3, 3)����3��3�ĺ˴�С��
		�����������Point���͵�anchor����ʾê�㣨����ƽ�����Ǹ��㣩��ע����Ĭ��ֵPoint(-1, -1)���������������Ǹ�ֵ�Ļ��ͱ�ʾȡ������Ϊê�㣻
		������������bool���͵�normalize��Ĭ��ֵΪtrue��һ����ʶ������ʾ�ں��Ƿ��������һ���ˣ�
		���߸�������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ����Ĭ��ֵBORDER_DEFAULT��һ�㲻ȥ������*/
	//int blocksize = ui.lineEditBolckSize->text().toDouble();
	//cv::Point2i ancho = cv::Point2i(ui.lineEditAncho_x->text().toInt(), ui.lineEditAncho_y->text().toInt()); //ê���λ�ã���Ĭ��ֵΪ(-1, -1)˵��λ��kernel������λ�á�
	cv::boxFilter(srcImage, dstImage,-1,Size(3,3), cv::Point2i(-1,-1));
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
}

//��ֵ�˲�
void FormFiltering::btnBlurClick()
{
	/*void blur(InputArray src, OutputArray, dst, Size ksize, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
		��һ��������InputArray���͵�src������ͼ�񣬼�ͼ��Դ����Mat����󼴿ɣ��ú�����ͨ���Ƕ�������ģ��ҿ��Դ�������ͨ������ͼƬ������ͼƬ���Ӧ����CV_8U, CV_16U, CV_16S, CV_32F, CV_64F֮һ��
		�ڶ���������OutputArray���͵�dst����Ŀ��ͼ����Ҫ��ԭͼ����һ���ĳߴ�����ͣ����������Mat::clone, ��ԴͼƬΪģ������ʼ���õ���ٰ�����Ŀ��ͼ��
		������������Size���͵�ksize���ں˵Ĵ�С��һ����Size(w, h)��д������ʾ�ں˵Ĵ�С������Size(3, 3)����3��3�ĺ˴�С��
		���ĸ�������Point���͵�anchor����ʾê�㣨����ƽ�����Ǹ��㣩��ע����Ĭ��ֵPoint(-1, -1)���������������Ǹ�ֵ�Ļ��ͱ�ʾȡ������Ϊê�㣻
		�����������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ����Ĭ��ֵBORDER_DEFAULT��һ�㲻ȥ������*/
	cv::blur(srcImage, dstImage, Size(3, 3));
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
}

//��˹�˲�
void FormFiltering::btnGaussianBlurClick()
{
	//void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double, sigmaY = 0, int borderType = BORDER_DEFAULT)
	//	��һ��������InputArray���͵�src������ͼ�񣬼�ͼ��Դ����Mat����󼴿ɣ��ú�����ͨ���Ƕ�������ģ��ҿ��Դ�������ͨ������ͼƬ������ͼƬ���Ӧ����CV_8U, CV_16U, CV_16S, CV_32F, CV_64F֮һ��
	//	�ڶ���������OutputArray���͵�dst����Ŀ��ͼ����Ҫ��ԭͼ����һ���ĳߴ�����ͣ����������Mat::clone, ��ԴͼƬΪģ������ʼ���õ���ٰ�����Ŀ��ͼ��
	//	������������Size���͵�ksize���ں˵Ĵ�С��һ����Size(w, h)��д������ʾ�ں˵Ĵ�С��ksize.width��ksize.height���Բ�ͬ��������������&&��������
	//	���ĸ�������double���͵�sigmaX����ʾ��˹�˺�����X�����ϵı�׼�
	//	�����������double���͵�sigmaY����ʾ��˹�˺�����Y�����ϵı�׼���sigmaYΪ�㣬�ͽ�����ΪsigmaX�����sigmaX��sigmaY��Ϊ�㣬�Ǿ���ksize.width��ksize.hight���������Ϊ�˽������ȷ�����룬��ðѵ���������Size�����ĸ�����sigmaX�����������sigmaYȫ���ƶ��ã�
	//	������������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ����Ĭ��ֵBORDER_DEFAULT��һ�㲻ȥ������
	double sigmaX = 0;
	double sigmaY = 0;
	cv::GaussianBlur(srcImage, dstImage, Size(3, 3), sigmaX, sigmaY);
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
}


//��ֵ�˲�
void FormFiltering::btnMedianBlurClick()
{
	//void medianBlur(InputArray src, OutputArray dst, int ksize);
	//��һ��������InputArray���͵�src�������������������1��3����4ͨ����Mat���͵�ͼ�񣻵�ksizeΪ3����5��ʱ��ͼ�������ΪCV_8U��CV_16U����CV_32F����֮һ�������ڽϴ�׾��ߴ��ͼƬ����ֻ����CV_8U��
    //�ڶ���������OutputArray���͵�dst����Ŀ��ͼ�񣬺����������������Ҫ��ԴͼƬ��һ���ĳߴ�����͡����ǿ�����Mat::Clone����ԴͼƬΪģ�壬����ʼ���õ���ٰ�����Ŀ��ͼ��
    //������������int���͵�ksize���׾������Գߴ磨aperture linear size����ע��������������Ǵ���1�����������磺3��5��7��9
	int ksize = 3;
	cv::medianBlur(srcImage, dstImage, ksize);
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);
}

//˫���˲�
void FormFiltering::btnBilateralFilterClick()
{
	/*void bilateralFilter(InputArray src, OutputArray dst, int d,double sigmaColor, double sigmaSpace,int borderType = BORDER_DEFAULT);
	��һ��������InputArray���͵�src������ͼ�񣬿�����Mat���ͣ�ͼ�������8λ�򸡵��͵�ͨ������ͨ����ͼ��
    �ڶ���������OutputArray���͵�dst�����ͼ�񣬺�ԭͼ������ͬ�ĳߴ�����͡�
	������������int���͵�d����ʾ�ڹ��˹�����ÿ�����������ֱ����Χ��������ֵ�Ƿ�������������ӵ��������sigmaSpace�����ֵ��
	���ĸ�������double���͵�sigmaColor����ɫ�ռ��������sigmaֵ�����������ֵ�´󣬱������������������¿�����ɫ�ᱻ��ϵ�һ�𣬲����ϴ�İ������ɫ����
	�����������double���͵�sigmaSpace������ռ����˲�����sigmaֵ�������ֵ�ϴ�����ζ����ɫ����Ľ�Զ�����ؽ��໥Ӱ�죬�Ӷ�ʹ������������㹻���Ƶ���ɫ��ȡ��ͬ����ɫ����d>0ʱ��dָ���������С����sigmaSpace��٣�����d������sigmaSpace.
	������������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ����Ĭ��ֵBORDER_DEFAULT.*/
	int d = 25;
	double sigmaColor = 25 * 2;
	double sigmaSpace = 25 / 2;
	cv::bilateralFilter(srcImage, dstImage, d, sigmaColor, sigmaSpace);
	CommonHelper::showImage((QLabelEx*)ui.labelPicOut, dstImage);

}