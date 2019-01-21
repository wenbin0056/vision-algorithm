#include<stdio.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//#include <opencv2\opencv.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
#include "cv.h"  
#include "highgui.h"  
#include "cxcore.h"
#include<iostream>

using namespace std;
using namespace cv;
using namespace std;

#if 0
//全局变量声明
Mat g_srcImage,g_dstImage,g_grayImage,g_grayImage1,g_grayImage2,g_tmpImage,g_tempImage,g_tmpImage1,g_tempImage1;
int g_nModeValue=1;//0为原图像，1为canny，2为sobel，3位Scharr，4为Laplacian，5为Laplacian增强对比度
int g_nCannyLowThreshold=1;//canny边缘检测低阈值
int g_nSobelKernelSize=1;//sobel算子内核大小

//全局函数声明
void on_ModeType(int ,void *);
void on_CannyType(int ,void *);
void on_SobelType(int ,void *);
void Process();


//主函数
int main()
{
    system("COLOR 2F");//改变字体颜色

    //载入源图像
    g_srcImage=imread("/Users/new/Desktop/1.jpg");
    if(!g_srcImage.data){printf("读取源图像srcImage错误～！\n");return false;}

    //创建显示窗口
    namedWindow("[Edge Detector]");

    g_dstImage.create(g_srcImage.size(),g_srcImage.type());

    //创建模式转换、canny参数，sobel参数滚动条
    createTrackbar("Mode Switch: ", "[Edge Detector]", &g_nModeValue,5, on_ModeType);
    createTrackbar("Canny Parameters: ", "[Edge Detector]",&g_nCannyLowThreshold ,120,on_CannyType);
    createTrackbar("Sobel/Laplacian Parameters", "[Edge Detector]", &g_nSobelKernelSize,3, on_SobelType);
    //初始化回调函数
    on_ModeType(0,0);

    //轮询获取按键信息，按下ESC退出
    while(1)
    {
        int key;
        key=waitKey(9);
        if((char)key == 27)
            break;
    }
    return 0;
}

//定义回调函数
void Process()
{
    switch(g_nModeValue)
    {
        case 0://源图像
            g_srcImage.copyTo(g_dstImage);
            break;
        case 1://canny边缘检测算法
            cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
            blur(g_grayImage, g_tmpImage, Size(3,3));//先用均值滤波器进行平滑去噪
            Canny(g_tmpImage, g_tmpImage, g_nCannyLowThreshold, g_nCannyLowThreshold*3);
            g_dstImage=Scalar::all(0);
            g_srcImage.copyTo(g_dstImage, g_tmpImage);//将g_tmpImage作为掩码，来将原图像拷贝到输出图像中
            break;
        case 2://sobel边缘检测算法
            Sobel(g_srcImage, g_tmpImage, CV_16S, 1, 0,(2*g_nSobelKernelSize+1),1,1,BORDER_DEFAULT);//求x方向梯度
            convertScaleAbs(g_tmpImage, g_tmpImage1);//计算绝对值，并将结果转换成8位
            Sobel(g_srcImage, g_tempImage, CV_16S, 0, 1,(2*g_nSobelKernelSize+1),1,1,BORDER_DEFAULT);//求y方向梯度
            convertScaleAbs(g_tempImage, g_tempImage1);//计算绝对值，并将结果转换成8位
            addWeighted(g_tmpImage1, 0.5, g_tempImage1, 0.5, 0, g_dstImage);
            break;
        case 3://Scharr函数
            Scharr(g_srcImage, g_tmpImage, CV_16S, 1, 0,1,0,BORDER_DEFAULT);//求x方向梯度
            convertScaleAbs(g_tmpImage, g_tmpImage1);//计算绝对值，并将结果转换成8位
            Sobel(g_srcImage, g_tempImage, CV_16S, 0, 1,1,0,BORDER_DEFAULT);//求y方向梯度
            convertScaleAbs(g_tempImage, g_tempImage1);//计算绝对值，并将结果转换成8位
            addWeighted(g_tmpImage1, 0.5, g_tempImage1, 0.5, 0, g_dstImage);
            break;
        case 4://Laplacian边缘检测算法
            GaussianBlur(g_srcImage, g_srcImage, Size(3,3), 0,0,BORDER_DEFAULT);//高斯滤波消除噪声
            cvtColor(g_srcImage, g_grayImage1, COLOR_RGB2GRAY);
            Laplacian(g_grayImage1, g_tmpImage, CV_16S,(g_nSobelKernelSize*2+1),1,0,BORDER_DEFAULT);
            convertScaleAbs(g_tmpImage, g_dstImage);
            break;
        case 5://利用原图像减去拉普拉斯图像增强对比度
            GaussianBlur(g_srcImage, g_srcImage, Size(3,3), 0,0,BORDER_DEFAULT);//高斯滤波消除噪声
            cvtColor(g_srcImage, g_grayImage2, COLOR_RGB2GRAY);
            Laplacian(g_grayImage2, g_tmpImage, CV_16S,(g_nSobelKernelSize*2+1),1,0,BORDER_DEFAULT);
            convertScaleAbs(g_tmpImage, g_tmpImage1);
            g_dstImage=g_grayImage2-g_tmpImage1;
            break;
    }
      imshow("[Edge Detector]",g_dstImage);
}
void on_ModeType(int ,void *)
{
    Process();
}
void on_CannyType(int ,void *)
{
    Process();
}
void on_SobelType(int ,void *)
{
    Process();
}

#endif
#if 0
int main()





#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <WINSOCK2.H>
#include<iostream>
#include<thread>
#include <winsock2.h>
#include <stdio.h>
#include<string>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
#include<vector>
 
using namespace cv;
 
 
					//////////////////////////////////////////////////////////////////
					//函数功能：用向量来做COSα=两向量之积/两向量模的乘积求两条线段夹角
					//输入：   线段3个点坐标pt1,pt2,pt0,最后一个参数为公共点
					//输出：   线段夹角，单位为角度
					//////////////////////////////////////////////////////////////////
double angle(CvPoint* pt1, CvPoint* pt2, CvPoint* pt0)
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;
	double dx2 = pt2->x - pt0->x;
	double dy2 = pt2->y - pt0->y;
	double angle_line = (dx1*dx2 + dy1 * dy2) / sqrt((dx1*dx1 + dy1 * dy1)*(dx2*dx2 + dy2 * dy2) + 1e-10);//余弦值
	return acos(angle_line) * 180 / 3.141592653;
}
//////////////////////////////////////////////////////////////////
//函数功能：采用多边形检测，通过约束条件寻找矩形
//输入：   img 原图像
//          storage 存储
//          minarea，maxarea 检测矩形的最小/最大面积
//          minangle,maxangle 检测矩形边夹角范围，单位为角度
//输出：   矩形序列
//////////////////////////////////////////////////////////////////
CvSeq* findSquares4(IplImage* img, CvMemStorage* storage, int minarea, int maxarea, int minangle, int maxangle, int(&temp)[30])
{
	CvSeq* contours;//边缘
	int N = 6;  //阈值分级
	CvSize sz = cvSize(img->width & -2, img->height & -2);
	IplImage* timg = cvCloneImage(img);//拷贝一次img
	IplImage* gray = cvCreateImage(sz, 8, 1); //img灰度图
	IplImage* pyr = cvCreateImage(cvSize(sz.width / 2, sz.height / 2), 8, 3);  //金字塔滤波3通道图像中间变量
	IplImage* tgray = cvCreateImage(sz, 8, 1); ;
	CvSeq* result;
	double s, t;
	int sk = 0;
	CvSeq* squares = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvPoint), storage);
 
	cvSetImageROI(timg, cvRect(0, 0, sz.width, sz.height));
	//金字塔滤波 
	cvPyrDown(timg, pyr, 7);
	cvPyrUp(pyr, timg, 7);
	//在3个通道中寻找矩形 
	for (int c = 0; c < 3; c++) //对3个通道分别进行处理 
	{
		cvSetImageCOI(timg, c + 1);
		cvCopy(timg, tgray, 0);  //依次将BGR通道送入tgray         
		for (int l = 0; l < N; l++)
		{
			//不同阈值下二值化
			cvThreshold(tgray, gray, 75, 250, CV_THRESH_BINARY);
			cvShowImage("111", gray);
			cvFindContours(gray, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
			while (contours)
			{ //多边形逼近             
				result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
 
				//如果是凸四边形并且面积在范围内 
				if (result->total == 4 && fabs(cvContourArea(result, CV_WHOLE_SEQ)) > minarea  && fabs(cvContourArea(result, CV_WHOLE_SEQ)) < maxarea &&  cvCheckContourConvexity(result))
				{
 
					s = 0;
					//判断每一条边
					for (int i = 0; i < 5; i++)
					{
						if (i >= 2)
						{   //角度            
							t = fabs(angle((CvPoint*)cvGetSeqElem(result, i), (CvPoint*)cvGetSeqElem(result, i - 2), (CvPoint*)cvGetSeqElem(result, i - 1)));
							s = s > t ? s : t;
						}
					}
					//这里的S为直角判定条件 单位为角度
					if (s > minangle && s < maxangle)
					{
						for (int i = 0; i < 4; i++)
							cvSeqPush(squares, (CvPoint*)cvGetSeqElem(result, i));
						CvRect rect = cvBoundingRect(contours, 1);       // 获取矩形边界框 
						CvPoint p1;
						p1 = cvPoint(rect.x + rect.width / 2, rect.y + rect.height / 2);   //矩形中心坐标  
						std::cout << "X:" << p1.x << "Y：" << p1.y << std::endl;
					}
				}
				contours = contours->h_next;
			}
		}
		std::cout << "圆的数量是"<<sk << std::endl;
		temp[26] = sk;
 
	
		sk = 0;
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&pyr);
	cvReleaseImage(&tgray);
	cvReleaseImage(&timg);
 
	return squares;
}
//////////////////////////////////////////////////////////////////
//函数功能：画出所有矩形
//输入：   img 原图像
//          squares 矩形序列
//          wndname 窗口名称
//输出：   图像中标记矩形
//////////////////////////////////////////////////////////////////
void drawSquares(IplImage* img, CvSeq* squares, const char* wndname)
{
	CvSeqReader reader;
	IplImage* cpy = cvCloneImage(img);
	CvPoint pt[4];
	int i;
	cvStartReadSeq(squares, &reader, 0);
	for (i = 0; i < squares->total; i += 4)
	{
		CvPoint* rect = pt;
		int count = 4;
		memcpy(pt, reader.ptr, squares->elem_size);
		CV_NEXT_SEQ_ELEM(squares->elem_size, reader);
		memcpy(pt + 1, reader.ptr, squares->elem_size);
		CV_NEXT_SEQ_ELEM(squares->elem_size, reader);
		memcpy(pt + 2, reader.ptr, squares->elem_size);
		CV_NEXT_SEQ_ELEM(squares->elem_size, reader);
		memcpy(pt + 3, reader.ptr, squares->elem_size);
		CV_NEXT_SEQ_ELEM(squares->elem_size, reader);
		//cvPolyLine( cpy, &rect, &count, 1, 1, CV_RGB(0,255,0), 3, CV_AA, 0 );
		cvPolyLine(cpy, &rect, &count, 1, 1, CV_RGB(rand() & 255, rand() & 255, rand() & 255), 1, CV_AA, 0);//彩色绘制
	}
	cvShowImage("22", cpy);
	cvReleaseImage(&cpy);
}
 
void SendMessageOne()
{
	//开起摄像头
	VideoCapture capture;
	capture.open(0);
	Mat edges;  //定义转化的灰度图
	if (!capture.isOpened())
		namedWindow("【效果图】", CV_WINDOW_NORMAL);
	const char* winn = "1111";
	if (!capture.isOpened())
		//namedWindow(winn, CV_WINDOW_NORMAL);
		CvMemStorage* storage = 0;
	CvMemStorage* storage = 0;
	storage = cvCreateMemStorage(0);
	while (1)
	{
		int Y=0, J=0;
		Mat frame;
		capture >> frame;
		IplImage img0 = frame;
		//drawSquares(&img0, findSquares4(&img0, storage, 100, 2000, 80, 100, a), winn);
		//cvClearMemStorage(storage);  //清空存储
		Mat E = frame(Range(1, 320), Range(1, 240));
		cvtColor(frame, edges, CV_BGR2GRAY);
		//高斯滤波
		GaussianBlur(edges, edges, Size(7, 7), 2, 2);
		std::vector<Vec3f> circles;//存储每个圆的位置信息
								   //霍夫圆
		HoughCircles(edges, circles, CV_HOUGH_GRADIENT, 1.5, 10, 100, 100, 0, 50);
		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			//std::cout << "圆的X是" << circles[i][0] << "圆的Y是" << circles[i][1] << std:: endl;
			//绘制圆轮廓  
			circle(frame, center, radius, Scalar(155, 50, 255), 3, 8, 0);
			int R = frame.at<Vec3b>(cvRound(circles[i][1]), cvRound(circles[i][0]))[2];//R
			int G = frame.at<Vec3b>(cvRound(circles[i][1]), cvRound(circles[i][0]))[1];//G
			int B = frame.at<Vec3b>(cvRound(circles[i][1]), cvRound(circles[i][0]))[0];//B
			int num = R + G + B;
			std::cout << "圆心颜色是" << num << std::endl;
                }
 
		imshow("【效果图】", frame);
		waitKey(30);
	}
}
#endif

 

int drawLine()
{
	#define SRC_FILENAME	"whitePanle.jpg"

	
 	Mat mat = imread(SRC_FILENAME);
	if(mat.empty())
	{
		printf("open file failed!\n");
		return -1;
	}




	int x0 = mat.cols / 4;
	int x1 = mat.cols * 3 / 4;
	int y0 = mat.rows / 4;
	int y1 = mat.rows * 3 / 4;

	cv::Point p0 = cv::Point(x0,y0);
	cv::Point p1 = cv::Point(x1, y1);
	cv::line(mat, p0, p1, cv::Scalar(0, 0, 255), 3, 4);


	p0.y = y1;
	p1.y = y0;
	cv::line(mat,p0,p1,cv::Scalar(255,0,0),3,4);


	cv::imwrite("whitePanle_line.jpg", mat);

 	return 0;
 }

int detectEdge_Canny()
{
	Mat srcImage, midImage, dstImage;
	
	srcImage = imread("whitePanle.jpg");
	if(srcImage.empty())
	{
		printf("open file failed!\n");
		return -1;
	}
	
	Canny(srcImage, midImage, 50, 200, 3);
	
	cvtColor(midImage, dstImage, CV_GRAY2BGR);
	
	cv::imwrite("whitePanle_canny.jpg", dstImage);
	
	return 0;
}




int main()
{
	//drawLine();
	//detectEdge_Canny();
	
#if 0
	//read jpg
	Mat src, src_gray;
	Mat dst;


	int p[3];	

	IplImage *img = cvLoadImage("whitePanle.jpg");	

	p[0] = CV_IMWRITE_JPEG_QUALITY;	
	p[1] = 10;	
	p[2] = 0;	





	Canny(img, edge, 3, 9, 3);

	cvSaveImage("out_canny.jpg", img);

	return 0;
#endif	

	//cvSaveImage("out1.jpg", img, p);
/*
//  Mat srcImage = imread("whitePanle.jpg");

   // imshow("Src Pic", srcImage);

    Mat midImage, dstImage,dstImage1;
    //边缘检测
    Canny(srcImage, midImage, 50, 200, 3);
	
    //灰度化
    cvtColor(midImage, dstImage, CV_GRAY2BGR);

/*	
    // 定义矢量结构存放检测出来的直线
    vector<Vec2f> lines;
    //通过这个函数，我们就可以得到检测出来的直线集合了
    HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
	
    //这里注意第五个参数，表示阈值，阈值越大，表明检测的越精准，速度越快，得到的直线越少（得到的直线都是很有把握的直线）
    //这里得到的lines是包含rho和theta的，而不包括直线上的点，所以下面需要根据得到的rho和theta来建立一条直线

    //依次画出每条线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0]; //就是圆的半径r
        float theta = lines[i][1]; //就是直线的角度
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000 * (a));
//LINE_AA
        line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 0); //Scalar函数用于调节线段颜色，就是你想检测到的线段显示的是什么颜色

//        imshow("边缘检测后的图", midImage);
//        imshow("最终效果图", dstImage);
    }
*/
	//IplImage img = IplImage(dstImage1);

//cvThreshold(&img, &img, 75, 250, CV_THRESH_BINARY);



//	IplImage img1 = IplImage(midImage);

	
//	cvSaveImage("out.jpg", &img);
//	cvSaveImage("out_canny.jpg", &img1);	
	
	//src = imread("whitePanle.jpg");
	
	//dst.create( src.size(), src.type() );

	//cvtColor( src, src_gray, CV_BGR2GRAY );

	//	detected_edges: 原灰度图像
	//detected_edges: 输出图像 (支持原地计算，可为输入图像)
	//lowThreshold: 用户通过 trackbar设定的值。
	//highThreshold: 设定为低阈值的3倍 (根据Canny算法的推荐)
	//kernel_size: 设定为 3 (Sobel内核大小，内部使用)
	//Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

//	cvSaveImage("out.jpg", &src);

//	return 0;
}

