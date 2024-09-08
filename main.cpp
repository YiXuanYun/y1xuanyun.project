#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

    Mat frame;
    Mat blurImg;

    VideoCapture capture(0);


    Mat backImg = imread("d:/你的背景地址.jpg");

    while(capture.read(frame))
    {
        imshow("video",frame);

        blur(frame,blurImg,Size(50,50));
        imshow("blur",blurImg);

        Mat hsv;
        cvtColor(frame,hsv,COLOR_BGR2HSV);
        imshow("hsv",hsv);

        Mat mask,mask1;
        inRange(hsv,Scalar(0,120,100),Scalar(10,255,255),mask);
        inRange(hsv,Scalar(170,120,100),Scalar(180,255,255),mask1);

        mask = mask+mask1;
        imshow("mask",mask);

        Mat hideImg = frame;

        Mat uMask;
        bitwise_not(mask,uMask);
        imshow("uMask",uMask);

        Mat bkMask;
        bitwise_and(backImg,backImg,bkMask,mask);
        imshow("bkMask",bkMask);

        Mat bkUmask;
        bitwise_and(hideImg,hideImg,bkUmask,uMask);
        imshow("bkUmask",bkUmask);

        Mat final;
        add(bkMask,bkUmask,final);
        imshow("final",final);

         waitKey(30);
    }
    return 0;
}

