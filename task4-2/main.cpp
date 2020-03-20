#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{

	cv::Mat srcMat = imread("coin.png", 0);
	cv::Mat binaryMat;
	cv::Mat labels;
	cv::Mat stats;
	cv::Mat centroids;

	//二值化
	cv::threshold(srcMat, binaryMat, 0, 255, THRESH_OTSU);
	//创建结构元素
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//闭运算
	morphologyEx(binaryMat, binaryMat, MORPH_CLOSE, kernel);
//获得连通域
	int liantongyu =connectedComponentsWithStats(binaryMat,
		labels,
		stats,
		centroids,
		8,
		CV_32S);

	//输出连通域信息

	for (int i = 0; i < liantongyu; i++)
	{
		cout << "连通域序号： " << i << endl;
		cout << "width = " << stats.at<int>(i, 2) << endl;
		cout << "height = " << stats.at<int>(i, 3) << endl;
		cout << "pixels = " << stats.at<int>(i, 4) << endl;
		
	}
	cout << "sum = " << liantongyu - 1 << endl;


	//绘制bounding box
	for (int i = 1; i < liantongyu; i++)
	{

		char num[10];
		sprintf_s(num, "%d", i);

		Rect boundingbox;
		//bounding box左上角坐标
		boundingbox.x = stats.at<int>(i, 0);
		boundingbox.y = stats.at<int>(i, 1);
		//bouding box的宽和长 
		boundingbox.width = stats.at<int>(i, 2);
		boundingbox.height = stats.at<int>(i, 3);
		//绘制
		rectangle(binaryMat, boundingbox, CV_RGB(255, 255, 255), 2, 8, 0);
	}

	imshow("binaryMat", binaryMat);
	
	imshow("frame", srcMat);
	waitKey(0);
	return 0;
}
