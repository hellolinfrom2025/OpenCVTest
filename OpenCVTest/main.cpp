#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "putText.h"

using namespace cv;
using namespace std;
using namespace chrono;

static vector< cv::Point> _getPtsByLine(cv::Point pt1, cv::Point pt2, int div)
{
	vector< cv::Point> vecPtRet;
	if (pt1 == pt2) {
		return vecPtRet;
	}
	double distance_percentage = 1.0 / div;
	double gap_x = pt2.x - pt1.x;
	double gap_y = pt2.y - pt1.y;
	for (int ii = 1; ii < div; ii++) {
		cv::Point ptNew;
		ptNew.x = pt1.x + gap_x * distance_percentage*ii;
		ptNew.y = pt1.y + gap_y * distance_percentage*ii;
		vecPtRet.push_back(ptNew);
	}
	return vecPtRet;
}

template <typename T>
static void _vectorAdd(const vector<T>&src, vector<T>&des)
{
	for (const auto &val : src) {
		des.push_back(val);
	}
}
//ͼƬ��Mat��ת�������������
void test1() 
{
	//���ļ���ȡͼƬ��MAT
	Mat img = cv::imread("./Res/absolute1.png");
	if (img.empty())
	{
		cout << "Can not load image." << endl;
		return;
	}
	Mat grayImg;
	//ͼƬ��ʽת��
	cv::cvtColor(img, grayImg, CV_BGR2GRAY);
	Mat result;
	cv::Canny(img, result, 50, 150);
	//��ȡ����ֵ
	cout << grayImg.at<uchar>(5, 5) << endl;
	//д������ֵ
	grayImg.at<uchar>(12, 13) = 0;
	//���洦�����ͼƬ��png
	cv::imwrite("./Res/absolute_outPut.png", grayImg);
	cv::imwrite("./Res/absolute_canny.png", result);
}
//����Mat���ʽ�����
void test2()
{
	//����MAT
	Mat img(3, 2, CV_8UC3);
	randu(img, Scalar::all(0), Scalar::all(255));
	cout << "img(default) = " << endl << " " << img << endl;
	cout << "img(python) = " << endl  << cv::format( img, Formatter::FMT_PYTHON) << endl;
	cout << "img(numpy) = " << endl << cv::format(img, Formatter::FMT_NUMPY) << endl;
	
}
//����Mat����
void test3() 
{
	Mat grayim(600, 800, CV_8UC1);
	Mat colorim(600, 800, CV_8UC3);
	//1.�����������أ�����������ֵ
	//for (int ii = 0; ii < grayim.rows; ++ii)
	//	for (int jj = 0; jj < grayim.cols; ++jj)
	//		grayim.at<uchar>(ii, jj) = (ii + jj) % 255;

	//for (size_t ii = 0; ii < colorim.rows; ii++)
	//{
	//	for (size_t jj = 0; jj < colorim.cols; jj++)
	//	{
	//		Vec3b pixel;
	//		pixel[0] = ii % 255;
	//		pixel[1] = jj % 255;
	//		pixel[2] = 0;
	//		colorim.at<Vec3b>(ii, jj) = pixel;
	//	}
	//}

	//2.ʹ�õ���������
	//MatIterator_<uchar> grayIt, grayEnd;
	//for (grayIt=grayim.begin<uchar>(), grayEnd=grayim.end<uchar>();grayIt!=grayEnd;++grayIt)
	//	*grayIt = rand() % 255;

	//MatIterator_<Vec3b> colorIt, colorEnd;
	//for (colorIt=colorim.begin<Vec3b>(),colorEnd=colorim.end<Vec3b>();colorIt!=colorEnd;++colorIt)
	//{
	//	(*colorIt)[0] = rand() % 255;
	//	(*colorIt)[1] = rand() % 255;
	//	(*colorIt)[2] = rand() % 255;
	//}

	//3.ʹ��ָ��������� ��Ч����ָ��Խ�����
	for (size_t ii = 0; ii < grayim.rows; ii++)
	{
		//��ȡĳ�����ص�ָ��
		uchar* pRow = grayim.ptr<uchar>(ii);
		for (size_t jj = 0; jj < grayim.cols; jj++)
		{
			pRow[jj] = (ii + jj) % 255;
		}
	}
	for (size_t ii = 0; ii < colorim.rows; ii++)
	{
		Vec3b* pRow = colorim.ptr<Vec3b>(ii);
		for (size_t jj = 0; jj < colorim.cols; jj++)
		{
			pRow[jj][0] = ii % 255;
			pRow[jj][1] = 255;
			pRow[jj][2] = jj % 255;
		}
	}

	//��ʾ���
	cv::imshow("grayim", grayim);
	cv::imshow("colorim", colorim);
	cv::waitKey(0);
}

//��ȡROI
void test4()
{
	Mat img(400, 300, CV_8UC3);
	cout << img.rows << endl;
	for (size_t ii = 0; ii < img.rows; ii++)
	{
		Vec3b* pRow = img.ptr<Vec3b>(ii);
		for (size_t jj = 0; jj < img.cols; jj++)
		{
			pRow[jj][0] = ii % 255;
			pRow[jj][1] = 255;
			pRow[jj][2] = jj % 255;
		}
	}
	Mat roi1(img, Rect(20, 20, 200, 200));
	Mat roi2 = img(Rect(20, 20, 200, 200));
	Mat roi3(img, Range(20, 200), Range(20, 200));
	Mat roi4 = img(Range(20, 200), Range(20, 200));
	cv::imshow("img", img);
	cv::imshow("roi1", roi1);
	cv::imshow("roi2", roi2);
	cv::imshow("roi3", roi3);
	cv::imshow("roi4", roi4);
	cv::waitKey(0);
}
//ȡ�Խ��� 45��
void test5()
{
	Mat img = (Mat_<uchar>(4, 3) <<
		1, 2, 3,
		4, 5, 6,
		7, 8, 9,
		10,11,12);
	Mat d0 = img.diag(0);
	Mat d1 = img.diag(1);
	Mat d_1 = img.diag(-1);
	cout << "d0:" << endl << format(d0, Formatter::FMT_NUMPY);
	cout << "d1:" << endl << format(d1, Formatter::FMT_NUMPY);
	cout << "d_1:" << endl << format(d_1, Formatter::FMT_NUMPY);
}
//ʹ��Mat_��װģ������
void test6()
{
	Mat m(300, 300, CV_8UC3);
	Mat_<Vec3b> img = static_cast<Mat_<Vec3b>>(m);
	for (size_t ii = 0; ii < img.rows; ii++)
	{
		for (size_t jj = 0; jj < img.cols; jj++)
		{
			Vec3b pixel;
			pixel[0] = ii % 255;
			pixel[1] = jj % 255;
			pixel[2] = 255;
			img(ii, jj) = pixel;
		}
	}
	imshow("Mat", m);
	imshow("Mat_", img);
	waitKey(0);
}
//��ʾ����
void test7()
{
	Mat m(300, 300, CV_8UC3);

	putTextZH(m,"��ð���",cv::Point(0,0),cv::Scalar(254,0,127),25);
	imshow("Mat", m);
	waitKey(0);

}

void test8()
{
	cv::Rect rc(100, 100, 100, 100);
	vector<cv::Point> vecCvPt;
	cv::Point ptTl = rc.tl();
	cv::Point ptTr = rc.tl() + cv::Point(rc.width, 0);
	cv::Point ptBr = rc.br();
	cv::Point ptBl = rc.tl() + cv::Point(0, rc.height);
	_vectorAdd<cv::Point>(_getPtsByLine(ptTl, ptTr, 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptTl, ptBl, 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptBr, ptBl, 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptBr, ptTr, 5), vecCvPt);
	int nOffsetX = rc.width / 10;
	int nOffsetY = rc.height / 10;
	_vectorAdd<cv::Point>(_getPtsByLine(ptTl, cv::Point(ptTl.x + nOffsetX, ptTl.y), 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptTl, cv::Point(ptTl.x, ptTl.y + nOffsetY), 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptTr, cv::Point(ptTr.x - nOffsetX, ptTr.y), 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptTr, cv::Point(ptTr.x, ptTr.y + nOffsetY), 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptBl, cv::Point(ptBl.x + nOffsetX, ptBl.y), 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptBl, cv::Point(ptBl.x, ptBl.y - nOffsetY), 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptBr, cv::Point(ptBr.x - nOffsetX, ptBr.y), 5), vecCvPt);
	_vectorAdd<cv::Point>(_getPtsByLine(ptBr, cv::Point(ptBr.x, ptBr.y - nOffsetY), 5), vecCvPt);



}
int main()
{
	printf("Hello, OpenCV!\n");
	auto begin = system_clock::now();
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	for (int ii = 0; ii < 100000;ii++) {
		test8();
	}

	auto end = system_clock::now();
	auto elapsedTime =duration_cast<std::chrono::milliseconds>(end - begin);
	printf("\r\n ##time: %d",elapsedTime.count());
	system("pause");
	return 0;
}
