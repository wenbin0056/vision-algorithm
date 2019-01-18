#include<stdio.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

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
