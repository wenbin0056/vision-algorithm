#include<stdio.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//#include <opencv2\opencv.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
#include "cv.h"  
#include "highgui.h"  
#include "cxcore.h"
#include<iostream>
#include <cv.h>
#include <highgui.h>
#include <math.h>

using namespace std;
using namespace cv;
using namespace std;




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


int dect_Edge_Line()
{
	Mat src, dst, color_dst;
	if(  !(src=imread("whitePanle.jpg", 0)).data)
		return -1;

	Canny( src, dst, 350, 400, 3 );//Canny( src, dst, 50, 200, 3 );
	cvtColor( dst, color_dst, CV_GRAY2BGR );


#if 0
	vector<Vec2f> lines;
	HoughLines( dst, lines, 1, CV_PI/180, 100 );

	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		Point pt1(cvRound(x0 + 1000*(-b)),
				cvRound(y0 + 1000*(a)));
		Point pt2(cvRound(x0 - 1000*(-b)),
				cvRound(y0 - 1000*(a)));
		line( color_dst, pt1, pt2, Scalar(0,0,255), 3, 8 );
	}
#else
	vector<Vec4i> lines;
	HoughLinesP( dst, lines, 1, CV_PI/180, 80, 30, 10 );
	for( size_t i = 0; i < lines.size(); i++ )
	{
		line( color_dst, Point(lines[i][0], lines[i][1]),
				Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
	}
#endif

	//    namedWindow( "Source", 1 );
	//    imshow( "Source", src );

	//    namedWindow( "Detected Lines", 1 );
	//    imshow( "Detected Lines", color_dst );

	cv::imwrite("whitePanle_detectRect.jpg", color_dst);

	return 0;
}

static double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 )
{    
    double dx1 = pt1->x - pt0->x; 
    double dy1 = pt1->y - pt0->y;  
    double dx2 = pt2->x - pt0->x;  
    double dy2 = pt2->y - pt0->y;    
    double angle_line = (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);//余弦值
    return acos(angle_line)*180/3.141592653; 
}


int detect_rect1()
{
	CvSeq* contours;//边缘
	int N = 6;  //阈值分级
	CvMemStorage* storage = 0;
	storage = cvCreateMemStorage(0);
	
	IplImage* img = cvLoadImage("whitePanle.jpg");
	CvSize sz = cvSize( img->width & -2, img->height & -2 );
	IplImage* timg = cvCloneImage( img );//拷贝一次img
	IplImage* gray = cvCreateImage( sz, 8, 1 ); //img灰度图
	IplImage* pyr = cvCreateImage( cvSize(sz.width/2, sz.height/2), 8, 3 );  //金字塔滤波3通道图像中间变量
	IplImage* tgray = cvCreateImage( sz, 8, 1 ); ;   
	CvSeq* result;  
	double s, t;  
	int minarea = 100;
	int maxarea = 2000;
	int minangle = 80;
	int maxangle = 100;
	CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );   

	cvSetImageROI( timg, cvRect( 0, 0, sz.width, sz.height ));   
	//金字塔滤波 
	cvPyrDown( timg, pyr, 7 );  
	cvPyrUp( pyr, timg, 7 );   
	//在3个通道中寻找矩形 
	for( int c = 0; c < 3; c++ ) //对3个通道分别进行处理 
	{       
		cvSetImageCOI( timg, c+1 );     
		cvCopy( timg, tgray, 0 );  //依次将BGR通道送入tgray         
		for( int l = 0; l < N; l++ )     
		{         
			//不同阈值下二值化
			cvThreshold( tgray, gray, (l+1)*255/N, 255, CV_THRESH_BINARY );

			cvFindContours( gray, storage, &contours, sizeof(CvContour),CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );          
			while( contours )    
			{ //多边形逼近             
				result = cvApproxPoly( contours, sizeof(CvContour), storage,CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0 ); 
				//如果是凸四边形并且面积在范围内
				if( result->total == 4 && fabs(cvContourArea(result,CV_WHOLE_SEQ)) > minarea  && fabs(cvContourArea(result,CV_WHOLE_SEQ)) < maxarea &&  cvCheckContourConvexity(result) )  
				{               
					s = 0;      
					//判断每一条边
					for( int i = 0; i < 5; i++ )  
					{                   
						if( i >= 2 )           
						{   //角度            
							t = fabs(angle( (CvPoint*)cvGetSeqElem( result, i ),(CvPoint*)cvGetSeqElem( result, i-2 ),(CvPoint*)cvGetSeqElem( result, i-1 )));   
							s = s > t ? s : t;     
						}         
					}   
					//这里的S为直角判定条件 单位为角度
					if( s > minangle && s < maxangle )                      
						for( int i = 0; i < 4; i++ )              
							cvSeqPush( squares,(CvPoint*)cvGetSeqElem( result, i ));     
				}                                      
				contours = contours->h_next;      
			}   
		} 
	}

	
	cvReleaseImage( &gray );   
	cvReleaseImage( &pyr );  
	cvReleaseImage( &tgray );  
	cvReleaseImage( &timg );   

	return 0;

}
int detect_rect()
{
	Mat src, dst, color_dst;
	if(  !(src=imread("whitePanle.jpg", 0)).data)
		return -1;

	Canny( src, dst, 350, 400, 3 );//Canny( src, dst, 50, 200, 3 );
	cvtColor( dst, color_dst, CV_GRAY2BGR );


#if 0
	vector<Vec2f> lines;
	HoughLines( dst, lines, 1, CV_PI/180, 100 );

	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		Point pt1(cvRound(x0 + 1000*(-b)),
				cvRound(y0 + 1000*(a)));
		Point pt2(cvRound(x0 - 1000*(-b)),
				cvRound(y0 - 1000*(a)));
		line( color_dst, pt1, pt2, Scalar(0,0,255), 3, 8 );
	}
#else
	vector<Vec4i> lines;
	HoughLinesP( dst, lines, 1, CV_PI/180, 80, 30, 10 );
	for( size_t i = 0; i < lines.size(); i++ )
	{
		line( color_dst, Point(lines[i][0], lines[i][1]),
				Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
	}
#endif

	//    namedWindow( "Source", 1 );
	//    imshow( "Source", src );

	//    namedWindow( "Detected Lines", 1 );
	//    imshow( "Detected Lines", color_dst );

	cv::imwrite("whitePanle_detectRect.jpg", color_dst);

	return 0;	
}
int main()
{
	//drawLine();
	//detectEdge_Canny();
	//dect_Edge_Line();
	//detect_rect();
	detect_rect1();
	return 0;
}

