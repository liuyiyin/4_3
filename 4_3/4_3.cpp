// 4_3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("D:\\IMG_1989.jpg",0);
	cv::Mat src;
	cv::Mat src1;
	cv::Mat src2;
	cv::Mat labelMat;
	cv::Mat statsMat;
	cv::Mat centrMat;

	threshold(srcMat, src, 100, 255, THRESH_BINARY);
    int height = src.rows;
	int width = src.cols;
	for (int i = 1; i < height; i++)
	{
		for (int j = 1; j < width; j++)
		{
			if (src.at<uchar>(i, j) < 255) 
			{
				src.at<uchar>(i, j) = 255;
			}
			else
			{
				src.at<uchar>(i, j) = 0;
			}

		}
	}

	Mat kernel1 = getStructuringElement(MORPH_RECT, Size(10, 10));
	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(src, src1, 2, kernel1);
	morphologyEx(src1, src2, 3, kernel2);

	int nComp = cv::connectedComponentsWithStats(src2, labelMat, statsMat, centrMat, 8, CV_32S);

	for (int i = 1; i < nComp; i++)
	{
		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);
		rectangle(src2, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}

	cout << "圆的个数：" << nComp - 1 << endl;
	imshow("连通域标记", src2);
	waitKey(0);
    return 0;
}

