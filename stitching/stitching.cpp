


#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/stitching/stitcher.hpp>

using namespace std;
using namespace cv;

bool try_use_gpu = false;
vector<Mat> imgs;
string result_name = "dst1.jpg";




int detect_feature_points_surf()
{
	//提取特征点    
	SurfFeatureDetector Detector(2000);  
	vector<KeyPoint> keyPoint1, keyPoint2;
	Detector.detect(image1, keyPoint1);
	Detector.detect(image2, keyPoint2);

	//特征点描述，为下边的特征点匹配做准备    
	SurfDescriptorExtractor Descriptor;
	Mat imageDesc1, imageDesc2;
	Descriptor.compute(image1, keyPoint1, imageDesc1);
	Descriptor.compute(image2, keyPoint2, imageDesc2);

	FlannBasedMatcher matcher;
	vector<vector<DMatch> > matchePoints;
	vector<DMatch> GoodMatchePoints;

	vector<Mat> train_desc(1, imageDesc1);
	matcher.add(train_desc);
	matcher.train();

	matcher.knnMatch(imageDesc2, matchePoints, 2);
	cout << "total match points: " << matchePoints.size() << endl;

	// Lowe's algorithm,获取优秀匹配点
	for (int i = 0; i < matchePoints.size(); i++)
	{
		if (matchePoints[i][0].distance < 0.4 * matchePoints[i][1].distance)
		{
			GoodMatchePoints.push_back(matchePoints[i][0]);
		}
	}

	Mat first_match;
	drawMatches(image02, keyPoint2, image01, keyPoint1, GoodMatchePoints, first_match);
	imshow("first_match ", first_match);
	
	return 0;
}


int stitch_opencv()
{
	Mat img1 = imread("34.jpg");
	Mat img2 = imread("35.jpg");

	imshow("p1", img1);
	imshow("p2", img2);

	if (img1.empty() || img2.empty())
	{
		cout << "Can't read image" << endl;
		return -1;
	}
	imgs.push_back(img1);
	imgs.push_back(img2);


	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	// 使用stitch函数进行拼接
	Mat pano;
	Stitcher::Status status = stitcher.stitch(imgs, pano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}
	imwrite(result_name, pano);
	Mat pano2 = pano.clone();
	// 显示源图像，和结果图像
	imshow("全景图像", pano);
	if (waitKey() == 27)
		return 0;
}


int main()
{
	return 0;
}


