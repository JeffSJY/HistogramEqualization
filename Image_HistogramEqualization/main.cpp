#include<highgui.h>
#include<cv.h>
#include<vector>
#include<string>

using namespace std;
using namespace cv;

void main()
{
//--------------------------------------------------------計算前
	string imgPath;
	vector<int> imgHig_o(256);

	cout << "Image: ";
	cin >> imgPath;

	Mat imgMat_o = imread(imgPath, 0);

	if (imgMat_o.empty())
	{
		cout << "Image Error!!";
		return;
	}

	for (int i = 0; i < imgMat_o.rows; i++)
	{
		for (int j = 0; j < imgMat_o.cols; j++)
		{
			imgHig_o[imgMat_o.at<uchar>(i, j)]++;//直方圖統計
		}
	}

	Mat higImg_o = Mat(512, 256, CV_8UC1);//直方圖陣列

	for (int i = 0; i < higImg_o.rows; i++)
	{
		for (int j = 0; j < higImg_o.cols; j++)
		{
			if (512 - int(imgHig_o[j] / 75 + 0.5) < i) higImg_o.at<uchar>(i, j) = 0;
			else higImg_o.at<uchar>(i, j) = 255;
		}
	}

//------------------------------------------------------------------------ 計算後
	vector<int>imgHig_n(imgHig_o.size());
	double pixel_count = 0.0, C = (double)255 / (imgMat_o.rows * imgMat_o.cols);

	for (int i = 0; i < imgHig_o.size(); i++)
	{
		pixel_count += imgHig_o[i];
		imgHig_n[int(C * pixel_count + 0.5)] += imgHig_o[i];
		imgHig_o[i] = int(C * pixel_count + 0.5);
	}
	
	Mat imgMat_n = Mat(imgMat_o.rows, imgMat_o.cols, CV_8UC1);
	for (int i = 0; i < imgMat_n.rows; i++)
	{
		for (int j = 0; j < imgMat_n.cols; j++)
		{
			imgMat_n.at<uchar>(i, j) = imgHig_o[imgMat_o.at<uchar>(i, j)];
		}
	}

	Mat higImg_n = Mat(512, 256, CV_8UC1);
	for (int i = 0; i < higImg_n.rows; i++)
	{
		for (int j = 0; j < higImg_n.cols; j++)
		{
			if (512 - int(imgHig_n[j] / 75 + 0.5) < i) higImg_n.at<uchar>(i, j) = 0;
			else higImg_n.at<uchar>(i, j) = 255;
		}
	}

	imshow("image", imgMat_o);
	imshow("Histogram", higImg_o);
	imshow("new image", imgMat_n);
	imshow("new Histogram", higImg_n);
	cvWaitKey(0);

	vector<int>(imgHig_o).swap(imgHig_o);
	vector<int>(imgHig_n).swap(imgHig_n);

	system("pause");
}