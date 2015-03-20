
//Fisheye Image correction

#include "cv.h"
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class FisheyeImgCorrect
{
public:
	int w;
	int h;
	double wRatio;
	double hRatio;
	double cx;
	double cy;
	double f;
	double r;
	double phi0;
	double sita0;
	double gama0;
	double phi1;
	double sita1;
	double gama1;
	double phi2;
	double sita2;
	double gama2;
	double phi3;
	double sita3;
	double gama3;
	/*�ķ�չ��ͼ�����ϳɵĴ���������*/
	Mat ImgIndex;
	/*�ķ�չ��ͼ����*/
	Mat ImgIndex1;
	Mat ImgIndex2;
	Mat ImgIndex3;
	Mat ImgIndex4;
	/*Mat ImgIndex1;
	Mat ImgIndex2;
	Mat ImgIndex3;*/
	//Mat dstImg;
	Mat orgImg;
	/*�ķ�չ��ͼ�ϲ�Ϊһ����ͼ����һ�����ģ��������£���������*/
	Mat dstImg;
	int Flag;
	int *position;
	long *positionShift;
	void FisheyeImgCorrectInit();
	void FishCalculate(Mat& fishImage);
	void FishImgIndex(const Mat &orgImg);
	void Fix(int &u,int &v,double &x,double &y,double phi0,double sita0,double gama0);
	void ImageCorrect(Mat& fishImage,Mat& dstImg1,Mat& dstImg2,Mat& dstImg3);
	void ImageCorrect( );
};