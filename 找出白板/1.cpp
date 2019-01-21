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
	detect_rect();
	
	return 0;
}

