#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Timer.h"
//-----------------------------------【命名空间声明部分】--------------------------------------
//		描述：包含程序所使用的命名空间
//-----------------------------------------------------------------------------------------------
using namespace std;
using namespace cv;
//-----------------------------------【全局变量声明部分】--------------------------------------
//		描述：全局变量声明
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage,g_midImage;//原始图、中间图和效果图
vector<Vec4i> g_lines;//定义一个矢量结构g_lines用于存放得到的线段矢量集合
//变量接收的TrackBar位置参数
int g_nthreshold=100;
int minLineLength=50;
int maxLineGap = 10;
int threshold1=300;
int threshold2=300;
//-----------------------------------【全局函数声明部分】--------------------------------------
//		描述：全局函数声明
//-----------------------------------------------------------------------------------------------
static void on_HoughLines(int,void*);//回调函数
//static void on_Canny(int, void*);
static void ShowHelpText();
//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
int main( int argc,char **argv)
{
    ShowHelpText();
    cv::Mat image;
    //载入原始图和Mat变量定义
    g_srcImage = cv::imread(argv[1]);  //手动输入一张图片路径

    //显示原始图
    imshow("【原始图】", g_srcImage);

    //创建滚动条
    namedWindow("【效果图】",1);
    createTrackbar("值", "【效果图】",&g_nthreshold,200,on_HoughLines);
    createTrackbar("minLineLength", "【效果图】",&minLineLength,200,on_HoughLines);
    createTrackbar("maxLineGap", "【效果图】",&maxLineGap,200,on_HoughLines);
    createTrackbar("threshold1", "【效果图】",&threshold1,500,on_HoughLines);
    createTrackbar("threshold2", "【效果图】",&threshold2,500,on_HoughLines);
//    double start= clock()/CLOCKS_PER_SEC;
//    //进行边缘检测和转化为灰度图
//    Canny(g_srcImage, g_midImage, 10, 20, 3);//进行一次canny边缘检测
//
//    cvtColor(g_midImage, g_dstImage, 8);//转化边缘检测后的图为灰度图
//        //调用一次回调函数，调用一次HoughLinesP函数
     on_HoughLines(0, nullptr);#调用一次函数
//    HoughLinesP(g_midImage, g_lines, 1, CV_PI/180, 80, 50, 10 );
////    //显示效果图
//    imshow("【效果图】", g_dstImage);
    waitKey(0);
    return 0;
}
//-----------------------------------【on_HoughLines( )函数】--------------------------------
//窗口的回调函数
//----------------------------------------------------------------------------------------------
static void on_HoughLines(int, void*)
{
    //定义局部变量储存全局变量
    Mat srcImage=g_srcImage.clone();
    Mat midImage;
    Mat dstImage;
    Canny(srcImage,midImage, threshold1, threshold2, 3);//进行一次canny边缘检测
    cvtColor(midImage, dstImage, 8);//转化边缘检测后的图为灰度图
    //调用HoughLinesP函数
    vector<Vec4i> mylines;
    {
        TIMER_PROCESS("HLP");#调用时钟函数记录括号里函数处理时间
        HoughLinesP(midImage, mylines, 1, CV_PI/180, g_nthreshold+1, minLineLength, maxLineGap );
    }
    //循环遍历绘制每一条线段
    for( size_t i = 0; i < mylines.size(); i++ )
    {
        Vec4i l = mylines[i];
        line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 4);
    }
    //显示图像
    imshow("【效果图】",dstImage);
}
//static void on_Canny(int, void*)
//{
//    //定义局部变量储存全局变量
//    Canny(g_srcImage, g_midImage, threshold1, threshold2, 3);
//    }

//-----------------------------------【ShowHelpText( )函数】----------------------------------
//		描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
    //输出一些帮助信息
    printf("\n\n\n\t调整滚动条观察图像效果~\n\n");
    printf("\n\n\t\t\t\t\t\t\t\t "
    );
}