// chapter1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>



///<summury>
///处理鼠标事件的回调函数
///</summury>
///<param name="event">触发回调函数的鼠标事件的类型</param>
///<param name="x">事件发生时鼠标x的位置</param>
///<param name="y">事件发生时鼠标y的位置</param>
///<param name="flags">事件发生时按下了鼠标的哪个键</param>
///<param name="param">指向任意对象的指针，作为附加的参数发送给函数</param>
///<returns>无</returns>
void onMouse(int event, int x, int y, int flags, void* param)
{
	//viod*类型指针强制转换为cv::Mat*类型
	cv::Mat* im = reinterpret_cast<cv::Mat*>(param);

	switch (event)   //调度事件
	{
	case cv::EVENT_LBUTTONDOWN://鼠标左键按下事件
			//display pixel vaule at (x,y)
		std::cout << "At(" << x << "," << y << ") vaule is:"
			<< static_cast<int>(im->at<uchar>(cv::Point(x, y)))
			<< std::endl;
		break;
	case cv::EVENT_RBUTTONDOWN:  //鼠标右键按下事件
			std::cout << "The right button is clicked." << std::endl;
			break;
	/*
	case cv::EVENT_MOUSEMOVE://鼠标移动事件
	     //display pixel vaule at(x,y)
		 std::cout<<"At("<<x<<","<<y<<") vaule is:"
		     <<static_cast<int>(im->at<uchar>(cv::Point(x,y)))
			 <<std::endl;
			 break;   */
	}
}

int main()
{
#pragma region 装载图像

	//创建一个空图像
	cv::Mat image;
	//检查图像尺寸
	std::cout << "This empty image is" << image.rows << "x" << image.cols << std::endl;
	std::cout << "=========================================================" << std::endl;

	//读取输入图想
	image = cv::imread("puppy.bmp", cv::IMREAD_GRAYSCALE);//读入为单通道灰度图像
	//image = cv::imread("puppy.bmp",cv::IMREAD_COLOR);//读入为三通道彩色图像
	//第二个参数为空的话，就按图像的原本情况读入
	//图像的默认路径就是源代码所在的位置

	//错误处理
	if (image.empty())//图像为空，读入失败
	{
		//未创建图像
		//可能显示一个错误消息并退出程序
		std::cout << "Error reading image..." << std::endl;
		return 0;
	}

	//检查图像的尺寸
	std::cout << "This image is" << image.rows << "x" << image.cols << std::endl;
	//检查图像的通道数
	std::cout << "This image has" << image.channels() << "channel(s)" << std::endl;
	std::cout << "========================================================" << std::endl;


#pragma endregion
#pragma region 显示，存储图像

	//定义窗口
	cv::namedWindow("Original Image");//窗口名字是为了区分不同的窗口
	//显示图像
	cv::imshow("Original Image", image);

	//创建另一个空的图像（用作输出图像）
	cv::Mat result;

	//翻转图像
	cv::flip(image, result,//image:输入图像，result:输出图像
		1);//正数表示水平翻转，0表示垂直翻转，负数表示水平和垂直都翻转

	//输出窗口
	cv::namedWindow("Output Image");
	cv::imshow("Output Image", result);

	//保存图像到本地磁盘，默认路径就是源代码所在的位置
	cv::imwrite("output.bmp", result);

	//控制台窗口，会在main函数结束前关闭，下面的函数可以等待用户按下键盘任意键后再结束程序
	cv::waitKey(0);//0表示永远地等待按键（默认值），直到用户按下键盘任意键
				   //键入的正数表示等待的毫秒数
#pragma endregion

	//装载图像

	//显示、存储图像

#pragma region 在图像上点击
	//回调函数
	//注册鼠标点击的回调函数
	cv::setMouseCallback(
		"Original Image",                   //与名为“Original Image”的图像窗口建立关系
		onMouse,                            //处理鼠标事件的回调函数
		reinterpret_cast<void*>(&image));   //cv::Mat*类型指针强制转换为void*类型
	cv::waitKey();
#pragma endregion


#pragma region 在图像上绘图
	//创建一个窗口
	cv::namedWindow("Drawing on an Image");
	//画图
	cv::circle(
		image,                //目标图像
		cv::Point(155, 110),   //圆心坐标
		65,                   //半径
		0,                    //颜色（这里用黑色）
		3);                  //厚度
	//图像上标注文本
	cv::putText(
		image,                 //目标图像
		"This is a dog.",      //文本
		cv::Point(40, 200),     //文本位置（左上角）
		cv::FONT_HERSHEY_PLAIN,//字体类型
		2.0,                   //字体大小
		255,                   //字体颜色（这里用白色）
		2);                    //文本厚度

	//显示图像
	cv::imshow("Drawing on an Image", image);

	cv::waitKey(0);
	

#pragma endregion


	return 0;

   }
   



