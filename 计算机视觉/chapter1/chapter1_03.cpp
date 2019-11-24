// chapter1_03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>

int main()
{
#pragma region 定义感兴趣区域(Region of Interest,ROI)

	/*要把一个小图像复制到一个大图像上，例如要把一个logo插入到测试图像中*/
	
	//读入图像
	cv::Mat image = cv::imread("puppy.bmp");
	//读入logo图像
	cv::Mat logo = cv::imread("smalllogo.png");

	//在图像的右下角定义一个ROI（初始化），放logo位置
	cv::Mat imageROI(image,
		cv::Rect(image.cols - logo.cols, image.rows - logo.rows,    //ROI左上角坐标
			logo.cols, logo.rows));                                 //ROI大小（宽度和高度）
	/*ORI实际上是一个cv::Mat对象，它与它的父图像指向同一个数据缓冲区，并且在头部指明了ROI的坐标*/

    //插入logo，将logo这幅图像拷贝到image上定义的一个ROI（imageROI)中去
	logo.copyTo(imageROI);

	cv::namedWindow("Image");//define an image window
	cv::imshow("Image", image);//show the image
	cv::waitKey(0);//wait for a key password

#pragma endregion

#pragma endregion 使用图像掩码

	//重新输入原始图像
	image = cv::imread("puppy.bmp");

	//在图像的右下角定义一个ROI（赋值）
	imageROI = image(
		cv::Rect(image.cols - logo.cols, image.rows - logo.rows,     //ROI左上角坐标
			logo.cols, logo.rows));                                  //ROI大小（宽度和高度）
	//ROI还可以用行和列的值域来描述
	//imageROI=image(cv::Range(image.rows-logo.rows,image.rows),     //ROI行（高度）范围
	//               cv::Range(image.cols - logo.cols, image.cols)); //ROI列（宽度）范围

	//把标志作为掩码（必须是灰度图像）
	cv::Mat mask(logo);//浅拷贝，mask和logo指向同一副图像

	//插入标志，只复制掩码mask中不为0的位置
	logo.copyTo(imageROI, mask);
	//logo/mask是同一副图像，都是二值图像，即像素值不是0就是255，只由黑色和白色构成
	//这里相当于只复制logo中值为255的像素

	cv::imshow("Image", image);//show the image
	cv::waitKey(0);//wait for a key password

#pragma endregion


      return 0;
	
}




