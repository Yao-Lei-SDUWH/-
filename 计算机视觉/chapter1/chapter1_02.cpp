﻿// chapter1_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>




//测试函数，它创建一幅图像
cv::Mat getImg()
{
	//创建图像
	cv::Mat ima(500, 500, CV_8U, 50);
	//返回图像
	return ima;
}

int main()
{
#pragma region 图像的创建

	/*灰度图像的创建*/

	//创建一个240行×320列的新灰度图像
	cv::Mat imagel(240, 320, CV_8U, 100);
		//或者
		//cv::Mat imagel(240,320,CV_8U,100);
	    //或者
	    //cv::Mat imagel(240,320,CV_8U,cv::Scalar(100));
	    //imagel=100;


	cv::namedWindow("Image");   //定义窗口
	cv::imshow("Image", imagel); //显示图像
	cv::waitKey(0);              //等待按键
	

	/*彩色图像的创建*/

	//创建一个红色的彩色图像，用cv::Size(320,240)以提供图像的尺寸信息
	cv::Mat image2(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 0, 255)); //通道次序为BGR
	//或者
	//cv::Mat image2(cv::Size(320,240),CV_8UC3);
	//image2=cv::Scalar(0,0,255);

	cv::imshow("Image", image2);//显示图像
	cv::waitKey(0);//等待按键
	cv::destroyAllWindows();//销毁所有窗口

	

#pragma endregion

#pragma region图像类型

	//U:表示无符号整数 unsigned int
	//S:表示有符号的整数 signed int
	//F:表示浮点数 float


	//C:表示通道数 channel
	//无C/C1:单通道，灰度图像
	//C3：三通道，彩色图像（BGR）

	//8bit （位）=1Byte(字节）
	//8bit:char
	//16/32bit:int
	//32/64bit:float

    //例子:
	//CV_8U:     8位无字符，uchar,灰度（channel=1)
	//CV_16SC3:  16位有符号，int，彩色(channel=3)
	//CV_32FC1:  32位浮点数，float,灰度（channel=1）

#pragma endregion

#pragma region 图像的重分配
	//重新分配一个新图像（原来的内容会先被释放）
	//如果新的尺寸和类型与原来的相同，就不会重新分配内存
	//相当于修改原图大小或类型
	imagel.create(200, 200, CV_8U);
	imagel = 200;//初始化图像

	cv::namedWindow("Image");//定义窗口
	cv::imshow("Image", imagel);//显示图像
	cv::waitKey(0);//等待按键
	cv::destroyWindow("Image");//销毁"Image"窗口

#pragma endregion

#pragma region 图像的浅拷贝与深拷贝
	//读入图像
	cv::Mat image3 = cv::imread("puppy.bmp");

	//所有这些图像都指向同一个数据块（浅拷贝)
	cv::Mat image4(image3);
	imagel = image3;

		//这些图像是原图像的副本图像
		image3.copyTo(image2);
	cv::Mat image5 = image3.clone();

	//转换图像进行测试，水平翻转image3
	cv::flip(image3, image3, 1);

	//定义窗口
	cv::namedWindow("Image 1");
	cv::namedWindow("Image 2");
	cv::namedWindow("Image 3");
	cv::namedWindow("Image 4");
	cv::namedWindow("Image 5");

	cv::imshow("Image 3", image3);//受影响

	//检查那些图像在处理过程中受到了影响
	cv::imshow("Image 1", imagel);//受影响
	cv::imshow("Image 4", image4);//受影响

	cv::imshow("Image 2", image2);//不受影响
	cv::imshow("Image 5", image5);//不受影响
	cv::waitKey(0);//等待按键
	cv::destroyAllWindows();//销毁所有窗口

#pragma endregion

#pragma region 从函数中获取图像
	//从函数中获取一个灰度图像
	cv::Mat gray = getImg();//调用我们自己定义的函数
	
	//显示图像
	cv::namedWindow("Image from function");//定义窗口
	cv::imshow("Image from function", gray);
	cv::waitKey(0);//等待按键
	cv::destroyWindow("Image from function");//销毁"Image from function"窗口
#pragma endregion

#pragma region 图像的转换
	
											 
	//作为灰度图像读入
	cv::Mat image6 = cv::imread("puppy.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat image7;

	//转换成浮点型图像，像素强度范围[0,1]，两幅图像的通道数量必须相同
	image6.convertTo(
		image7,          //输出图像
		CV_32F,          //图像类型 Type
		1 / 255.0,       //缩放比例 α
		0.0);            //偏移量β
	//image7(x,y)=saturate_cast<rType>(α*image6(x,y)+β)

	cv::namedWindow("Image 7");//定义窗口
	cv::imshow("Image 7", image7);//显示图像
	cv::waitKey(0);//等待按键
	cv::destroyWindow("Image 7");//销毁"Image 7"窗口

#pragma endregion

#pragma region 处理小矩阵
	//3×3 双精度型矩阵
	cv::Matx33d matrix( //cv::Matx<double,3,3>
		3.0, 2.0, 1.0,
		2.0, 1.0, 3.0,
		1.0, 2.0, 3.0);
	//3×1矩阵（即列向量）
	cv::Matx31d vector(5.0, 1.0, 3.0);//Matx<double,3,1>
	//矩阵相乘
	cv::Matx31d result = matrix * vector;//(3×3）*（3×1）

	std::cout << result;

#pragma endregion

	return 0;

}


