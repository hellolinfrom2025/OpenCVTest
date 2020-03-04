#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma  comment(lib, "opencv_core341d.lib")
#pragma  comment(lib, "opencv_imgcodecs341d.lib")
#pragma  comment(lib, "opencv_highgui341d.lib")
#pragma  comment(lib, "opencv_imgproc341d.lib")
#pragma  comment(lib, "opencv_calib3d341d.lib")
#else
#pragma  comment(lib, "opencv_core341.lib")
#pragma  comment(lib, "opencv_imgcodecs341.lib")
#pragma  comment(lib, "opencv_highgui341.lib")
#pragma  comment(lib, "opencv_imgproc341.lib")
#pragma  comment(lib, "opencv_calib3d341.lib")
#endif

using namespace cv;
using namespace std;
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
	cout << "img(python) = " << endl  << cv::format(img, 3) << endl;
	cout << "img(numpy) = " << endl << cv::format(img, 4) << endl;
	
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
	cout << "d0:" << endl << format(d0, 4);
	cout << "d1:" << endl << format(d1, 4);
	cout << "d_1:" << endl << format(d_1, 4);
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

int main()
{
	printf("Hello, OpenCV!\n");
	time_t start = clock();
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	test6();

	time_t end = clock();
	printf("\r\n ##time: %d", end - start);
	system("pause");
	return 0;
}
