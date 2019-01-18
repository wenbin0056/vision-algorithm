#include<stdio.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

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
