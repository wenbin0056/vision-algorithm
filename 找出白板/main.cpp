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

int img_threshold()
{
	IplImage* src = NULL;  
	IplImage* img = NULL;  


	src = cvLoadImage ("whitePanle.jpg", 1);  
	img = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);  

	cvCvtColor (src, img, CV_BGR2GRAY);  
	
	cvThreshold (img, img, 150, 300, CV_THRESH_BINARY);

	cvSaveImage("whitePanle_threshold.jpg",  img );

	return 0;
}

int detect_draw_Contours() 
{
	IplImage* src = NULL;  
	IplImage* img = NULL;  
	IplImage* dst = NULL;

	CvMemStorage* storage = cvCreateMemStorage (0);  
	CvMemStorage* storage1 = cvCreateMemStorage (0);  
	CvSeq* contour = 0;  
	CvSeq* cont;  
	CvSeq* mcont;

	src = cvLoadImage ("whitePanle.jpg", 1);  
	img = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);  
	dst = cvCreateImage (cvGetSize(src), src->depth, src->nChannels);

	cvCvtColor (src, img, CV_BGR2GRAY);  
	
	cvThreshold (img, img, 190, 200, CV_THRESH_BINARY);

	cvFindContours (img, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	if (contour)  
	{   
		CvTreeNodeIterator iterator;
		cvInitTreeNodeIterator (&iterator, contour,  1);
		while (0 != (cont = (CvSeq*)cvNextTreeNode (&iterator)))  
		{    
			mcont = cvApproxPoly (cont, sizeof(CvContour), storage1, CV_POLY_APPROX_DP, cvContourPerimeter(cont)*0.02,0);   
			cvDrawContours (dst, mcont, CV_RGB(255,0,0),CV_RGB(0,0,100),1,2,8,cvPoint(0,0));   
		}
	}

	//cvNamedWindow ("Contour", 1);  cvShowImage ("Contour", dst);

	//cvWaitKey (0);

	cvSaveImage("whitePanle_contours.jpg",  dst );

	cvReleaseMemStorage (&storage);  
	cvReleaseMemStorage (&storage1);  	
	cvReleaseImage (&src);
	cvReleaseImage (&img);
	cvReleaseImage (&dst);

	return 0; 
}

int img_filter()
{
	Mat img = imread("whitePanle.jpg");
	Mat out;

	//medianBlur(img, out, 7);//中值滤波，第三个参数表示孔径的线性尺寸，它的值必须是大于1的奇数

	//bilateralFilter(img, out, 25, 25 * 2, 25 / 2);//双边滤波

	//GaussianBlur(img, out, Size(3, 3), 0, 0); // 高斯滤波

	//blur(img, out,Size(5, 5));//-1指原图深度 ，均值滤波

	boxFilter(img, out, -1, Size(5, 5));//-1指原图深度，方框滤波
	
	cv::imwrite("whitePanle_filter.jpg", out);

	return 0;
}

int detect_white_panel()
{
	IplImage* src = NULL;  
	IplImage* img = NULL;  
	IplImage* dst = NULL;

	CvMemStorage* storage = cvCreateMemStorage (0);  
	CvMemStorage* storage1 = cvCreateMemStorage (0);  
	CvSeq* contour = 0;  
	CvSeq* cont;  
	CvSeq* mcont;

	src = cvLoadImage ("whitePanle.jpg", 1);  

	
	img = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);  
	dst = cvCreateImage (cvGetSize(src), src->depth, src->nChannels);

	cvCvtColor (src, img, CV_BGR2GRAY);  
	
	cvThreshold (img, img, 150, 300, CV_THRESH_BINARY);

	cvCanny(img, img, 50, 200, 3);

	//cvSmooth( img, img, CV_GAUSSIAN, 5,5 );

	cvFindContours (img, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	if (contour)  
	{   
		CvTreeNodeIterator iterator;
		cvInitTreeNodeIterator (&iterator, contour,  1);
		while (0 != (cont = (CvSeq*)cvNextTreeNode (&iterator)))  
		{    
			mcont = cvApproxPoly (cont, sizeof(CvContour), storage1, CV_POLY_APPROX_DP, cvContourPerimeter(cont)*0.02,0);   
			if(mcont->total != 4)
				continue;


			if(fabs(cvContourArea(mcont,CV_WHOLE_SEQ)) < 5000)
			{
				continue;
			}

			
			#if 1
			static int j = 0;
			int s_max = 0, s_min = 180, t = 0;
			j++;
			for(int i = 0; i < mcont->total; i++)
			{
				if(i >= 2)
				{
					t = fabs(angle( (CvPoint*)cvGetSeqElem( mcont, i ),(CvPoint*)cvGetSeqElem( mcont, i-2 ),(CvPoint*)cvGetSeqElem( mcont, i-1 )));   	
					s_max = s_max > t ? s_max : t; 
					s_min = s_min < t ? s_min : t; 					
					//CvPoint *p  =  (CvPoint*)cvGetSeqElem( mcont, i );
					//printf("[%d],%d/total=%d, x=%d,y=%d\n", j,i,mcont->total, p->x, p->y);
				}
			}
			//if(s_max > 100 || s_min < 90)
				//continue;
			
			#endif


			{
				double w, h =0.0;
				CvPoint *p  =  (CvPoint*)cvGetSeqElem( mcont, 0 );
				CvPoint *p1  =  (CvPoint*)cvGetSeqElem( mcont, 1 );
				h = fabs(p->y - p1->y);
				p1  =  (CvPoint*)cvGetSeqElem( mcont, 2 );				
				w = fabs(p->x - p1->x);				

				//printf("%f\n",w/h);
				if(w/h > 2.5)
				{
					continue;
				}
				
			}

			

			for(int i = 0; i < mcont->total; i++)
			{
				CvPoint *p  =  (CvPoint*)cvGetSeqElem( mcont, i );
				//printf("[%d],%d/total=%d, x=%d,y=%d\n", j,i,mcont->total, p->x, p->y);
			}			
			
			//cvDrawContours (dst, mcont, CV_RGB(255,0,0),CV_RGB(0,0,100),1,2,8,cvPoint(0,0));   
			cvDrawContours (src, mcont, CV_RGB(255,0,0),CV_RGB(0,0,100),1,2,8,cvPoint(0,0));   			





		}
	}

	//cvNamedWindow ("Contour", 1);  cvShowImage ("Contour", dst);

	//cvWaitKey (0);

	cvSaveImage("whitePanle_out.jpg",  dst );
	cvSaveImage("whitePanle_src_out.jpg",  src );	

	cvReleaseMemStorage (&storage);  
	cvReleaseMemStorage (&storage1);  	
	cvReleaseImage (&src);
	cvReleaseImage (&img);
	cvReleaseImage (&dst);

	return 0;	
}

int main()
{

	detect_white_panel();
	

	return 0;


	//sample
	char c = 0;
	
	while(1)
	{
		c = getchar();
		switch(c)
		{
			case '1':
				drawLine();
				break;
			case '2':
				detectEdge_Canny();				
				break;
			case '3':
				dect_Edge_Line();			
				break;
			case '4':
				//detect_rect();
				detect_rect1();						
				break;
			case '5':
				img_threshold();
				break;
			case '6':
				img_filter();
				break;		
			case '7':
				detect_draw_Contours();
				break;				
			case 'q':
			case 'Q':
				return 0;
		}

	}

	return 0;
}




