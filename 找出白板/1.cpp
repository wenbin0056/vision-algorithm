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
//ȫ�ֱ�������
Mat g_srcImage,g_dstImage,g_grayImage,g_grayImage1,g_grayImage2,g_tmpImage,g_tempImage,g_tmpImage1,g_tempImage1;
int g_nModeValue=1;//0Ϊԭͼ��1Ϊcanny��2Ϊsobel��3λScharr��4ΪLaplacian��5ΪLaplacian��ǿ�Աȶ�
int g_nCannyLowThreshold=1;//canny��Ե������ֵ
int g_nSobelKernelSize=1;//sobel�����ں˴�С

//ȫ�ֺ�������
void on_ModeType(int ,void *);
void on_CannyType(int ,void *);
void on_SobelType(int ,void *);
void Process();


//������
int main()
{
    system("COLOR 2F");//�ı�������ɫ

    //����Դͼ��
    g_srcImage=imread("/Users/new/Desktop/1.jpg");
    if(!g_srcImage.data){printf("��ȡԴͼ��srcImage���󡫣�\n");return false;}

    //������ʾ����
    namedWindow("[Edge Detector]");

    g_dstImage.create(g_srcImage.size(),g_srcImage.type());

    //����ģʽת����canny������sobel����������
    createTrackbar("Mode Switch: ", "[Edge Detector]", &g_nModeValue,5, on_ModeType);
    createTrackbar("Canny Parameters: ", "[Edge Detector]",&g_nCannyLowThreshold ,120,on_CannyType);
    createTrackbar("Sobel/Laplacian Parameters", "[Edge Detector]", &g_nSobelKernelSize,3, on_SobelType);
    //��ʼ���ص�����
    on_ModeType(0,0);

    //��ѯ��ȡ������Ϣ������ESC�˳�
    while(1)
    {
        int key;
        key=waitKey(9);
        if((char)key == 27)
            break;
    }
    return 0;
}

//����ص�����
void Process()
{
    switch(g_nModeValue)
    {
        case 0://Դͼ��
            g_srcImage.copyTo(g_dstImage);
            break;
        case 1://canny��Ե����㷨
            cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
            blur(g_grayImage, g_tmpImage, Size(3,3));//���þ�ֵ�˲�������ƽ��ȥ��
            Canny(g_tmpImage, g_tmpImage, g_nCannyLowThreshold, g_nCannyLowThreshold*3);
            g_dstImage=Scalar::all(0);
            g_srcImage.copyTo(g_dstImage, g_tmpImage);//��g_tmpImage��Ϊ���룬����ԭͼ�񿽱������ͼ����
            break;
        case 2://sobel��Ե����㷨
            Sobel(g_srcImage, g_tmpImage, CV_16S, 1, 0,(2*g_nSobelKernelSize+1),1,1,BORDER_DEFAULT);//��x�����ݶ�
            convertScaleAbs(g_tmpImage, g_tmpImage1);//�������ֵ���������ת����8λ
            Sobel(g_srcImage, g_tempImage, CV_16S, 0, 1,(2*g_nSobelKernelSize+1),1,1,BORDER_DEFAULT);//��y�����ݶ�
            convertScaleAbs(g_tempImage, g_tempImage1);//�������ֵ���������ת����8λ
            addWeighted(g_tmpImage1, 0.5, g_tempImage1, 0.5, 0, g_dstImage);
            break;
        case 3://Scharr����
            Scharr(g_srcImage, g_tmpImage, CV_16S, 1, 0,1,0,BORDER_DEFAULT);//��x�����ݶ�
            convertScaleAbs(g_tmpImage, g_tmpImage1);//�������ֵ���������ת����8λ
            Sobel(g_srcImage, g_tempImage, CV_16S, 0, 1,1,0,BORDER_DEFAULT);//��y�����ݶ�
            convertScaleAbs(g_tempImage, g_tempImage1);//�������ֵ���������ת����8λ
            addWeighted(g_tmpImage1, 0.5, g_tempImage1, 0.5, 0, g_dstImage);
            break;
        case 4://Laplacian��Ե����㷨
            GaussianBlur(g_srcImage, g_srcImage, Size(3,3), 0,0,BORDER_DEFAULT);//��˹�˲���������
            cvtColor(g_srcImage, g_grayImage1, COLOR_RGB2GRAY);
            Laplacian(g_grayImage1, g_tmpImage, CV_16S,(g_nSobelKernelSize*2+1),1,0,BORDER_DEFAULT);
            convertScaleAbs(g_tmpImage, g_dstImage);
            break;
        case 5://����ԭͼ���ȥ������˹ͼ����ǿ�Աȶ�
            GaussianBlur(g_srcImage, g_srcImage, Size(3,3), 0,0,BORDER_DEFAULT);//��˹�˲���������
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
					//�������ܣ�����������COS��=������֮��/������ģ�ĳ˻��������߶μн�
					//���룺   �߶�3��������pt1,pt2,pt0,���һ������Ϊ������
					//�����   �߶μнǣ���λΪ�Ƕ�
					//////////////////////////////////////////////////////////////////
double angle(CvPoint* pt1, CvPoint* pt2, CvPoint* pt0)
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;
	double dx2 = pt2->x - pt0->x;
	double dy2 = pt2->y - pt0->y;
	double angle_line = (dx1*dx2 + dy1 * dy2) / sqrt((dx1*dx1 + dy1 * dy1)*(dx2*dx2 + dy2 * dy2) + 1e-10);//����ֵ
	return acos(angle_line) * 180 / 3.141592653;
}
//////////////////////////////////////////////////////////////////
//�������ܣ����ö���μ�⣬ͨ��Լ������Ѱ�Ҿ���
//���룺   img ԭͼ��
//          storage �洢
//          minarea��maxarea �����ε���С/������
//          minangle,maxangle �����α߼нǷ�Χ����λΪ�Ƕ�
//�����   ��������
//////////////////////////////////////////////////////////////////
CvSeq* findSquares4(IplImage* img, CvMemStorage* storage, int minarea, int maxarea, int minangle, int maxangle, int(&temp)[30])
{
	CvSeq* contours;//��Ե
	int N = 6;  //��ֵ�ּ�
	CvSize sz = cvSize(img->width & -2, img->height & -2);
	IplImage* timg = cvCloneImage(img);//����һ��img
	IplImage* gray = cvCreateImage(sz, 8, 1); //img�Ҷ�ͼ
	IplImage* pyr = cvCreateImage(cvSize(sz.width / 2, sz.height / 2), 8, 3);  //�������˲�3ͨ��ͼ���м����
	IplImage* tgray = cvCreateImage(sz, 8, 1); ;
	CvSeq* result;
	double s, t;
	int sk = 0;
	CvSeq* squares = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvPoint), storage);
 
	cvSetImageROI(timg, cvRect(0, 0, sz.width, sz.height));
	//�������˲� 
	cvPyrDown(timg, pyr, 7);
	cvPyrUp(pyr, timg, 7);
	//��3��ͨ����Ѱ�Ҿ��� 
	for (int c = 0; c < 3; c++) //��3��ͨ���ֱ���д��� 
	{
		cvSetImageCOI(timg, c + 1);
		cvCopy(timg, tgray, 0);  //���ν�BGRͨ������tgray         
		for (int l = 0; l < N; l++)
		{
			//��ͬ��ֵ�¶�ֵ��
			cvThreshold(tgray, gray, 75, 250, CV_THRESH_BINARY);
			cvShowImage("111", gray);
			cvFindContours(gray, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
			while (contours)
			{ //����αƽ�             
				result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
 
				//�����͹�ı��β�������ڷ�Χ�� 
				if (result->total == 4 && fabs(cvContourArea(result, CV_WHOLE_SEQ)) > minarea  && fabs(cvContourArea(result, CV_WHOLE_SEQ)) < maxarea &&  cvCheckContourConvexity(result))
				{
 
					s = 0;
					//�ж�ÿһ����
					for (int i = 0; i < 5; i++)
					{
						if (i >= 2)
						{   //�Ƕ�            
							t = fabs(angle((CvPoint*)cvGetSeqElem(result, i), (CvPoint*)cvGetSeqElem(result, i - 2), (CvPoint*)cvGetSeqElem(result, i - 1)));
							s = s > t ? s : t;
						}
					}
					//�����SΪֱ���ж����� ��λΪ�Ƕ�
					if (s > minangle && s < maxangle)
					{
						for (int i = 0; i < 4; i++)
							cvSeqPush(squares, (CvPoint*)cvGetSeqElem(result, i));
						CvRect rect = cvBoundingRect(contours, 1);       // ��ȡ���α߽�� 
						CvPoint p1;
						p1 = cvPoint(rect.x + rect.width / 2, rect.y + rect.height / 2);   //������������  
						std::cout << "X:" << p1.x << "Y��" << p1.y << std::endl;
					}
				}
				contours = contours->h_next;
			}
		}
		std::cout << "Բ��������"<<sk << std::endl;
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
//�������ܣ��������о���
//���룺   img ԭͼ��
//          squares ��������
//          wndname ��������
//�����   ͼ���б�Ǿ���
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
		cvPolyLine(cpy, &rect, &count, 1, 1, CV_RGB(rand() & 255, rand() & 255, rand() & 255), 1, CV_AA, 0);//��ɫ����
	}
	cvShowImage("22", cpy);
	cvReleaseImage(&cpy);
}
 
void SendMessageOne()
{
	//��������ͷ
	VideoCapture capture;
	capture.open(0);
	Mat edges;  //����ת���ĻҶ�ͼ
	if (!capture.isOpened())
		namedWindow("��Ч��ͼ��", CV_WINDOW_NORMAL);
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
		//cvClearMemStorage(storage);  //��մ洢
		Mat E = frame(Range(1, 320), Range(1, 240));
		cvtColor(frame, edges, CV_BGR2GRAY);
		//��˹�˲�
		GaussianBlur(edges, edges, Size(7, 7), 2, 2);
		std::vector<Vec3f> circles;//�洢ÿ��Բ��λ����Ϣ
								   //����Բ
		HoughCircles(edges, circles, CV_HOUGH_GRADIENT, 1.5, 10, 100, 100, 0, 50);
		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			//std::cout << "Բ��X��" << circles[i][0] << "Բ��Y��" << circles[i][1] << std:: endl;
			//����Բ����  
			circle(frame, center, radius, Scalar(155, 50, 255), 3, 8, 0);
			int R = frame.at<Vec3b>(cvRound(circles[i][1]), cvRound(circles[i][0]))[2];//R
			int G = frame.at<Vec3b>(cvRound(circles[i][1]), cvRound(circles[i][0]))[1];//G
			int B = frame.at<Vec3b>(cvRound(circles[i][1]), cvRound(circles[i][0]))[0];//B
			int num = R + G + B;
			std::cout << "Բ����ɫ��" << num << std::endl;
                }
 
		imshow("��Ч��ͼ��", frame);
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
    //��Ե���
    Canny(srcImage, midImage, 50, 200, 3);
	
    //�ҶȻ�
    cvtColor(midImage, dstImage, CV_GRAY2BGR);

/*	
    // ����ʸ���ṹ��ż�������ֱ��
    vector<Vec2f> lines;
    //ͨ��������������ǾͿ��Եõ���������ֱ�߼�����
    HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
	
    //����ע��������������ʾ��ֵ����ֵԽ�󣬱�������Խ��׼���ٶ�Խ�죬�õ���ֱ��Խ�٣��õ���ֱ�߶��Ǻ��а��յ�ֱ�ߣ�
    //����õ���lines�ǰ���rho��theta�ģ���������ֱ���ϵĵ㣬����������Ҫ���ݵõ���rho��theta������һ��ֱ��

    //���λ���ÿ���߶�
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0]; //����Բ�İ뾶r
        float theta = lines[i][1]; //����ֱ�ߵĽǶ�
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000 * (a));
//LINE_AA
        line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 0); //Scalar�������ڵ����߶���ɫ�����������⵽���߶���ʾ����ʲô��ɫ

//        imshow("��Ե�����ͼ", midImage);
//        imshow("����Ч��ͼ", dstImage);
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

	//	detected_edges: ԭ�Ҷ�ͼ��
	//detected_edges: ���ͼ�� (֧��ԭ�ؼ��㣬��Ϊ����ͼ��)
	//lowThreshold: �û�ͨ�� trackbar�趨��ֵ��
	//highThreshold: �趨Ϊ����ֵ��3�� (����Canny�㷨���Ƽ�)
	//kernel_size: �趨Ϊ 3 (Sobel�ں˴�С���ڲ�ʹ��)
	//Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

//	cvSaveImage("out.jpg", &src);

//	return 0;
}

