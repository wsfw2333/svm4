#include <opencv4/opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
  Mat src, srcGray, dst;
  src = imread("1.jpg");
  //imshow("src",src);
  cvtColor(src, srcGray, COLOR_BGR2GRAY);
  //imshow("srcGray",srcGray);

  threshold(srcGray, dst, 150, 255, THRESH_BINARY);
  // imshow("dst", dst);
  Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
  erode(dst, dst, element);
  dilate(dst, dst, element);
  

  //imshow("dst", dst);
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  findContours(dst, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
  if( !contours.empty() && !hierarchy.empty() ){    
        vector<vector<Point> >::iterator it;
        for( it = contours.begin(); it != contours.end(); ){  
            //按轮廓长度筛选
            if( arcLength(*it, true) < 450)
                contours.erase(it);
            else it ++;
        }
    }


  Mat lunkuo = Mat::zeros(srcGray.rows, srcGray.cols, CV_8UC3);
  drawContours(lunkuo, contours, -1, Scalar(0,255,0), 1);
  //imshow("lunkuo",lunkuo);

 cv::Ptr<cv::ml::SVM> svm = cv::ml::StatModel::load<cv::ml::SVM>("mnist_svm.xml");
  vector<Rect> boundRect(contours.size());
  for(int i=0;i<contours.size();i++)
  {
    
    boundRect[i] = boundingRect(contours[i]);
    if(contourArea(contours[i])>15000||contourArea(contours[i])<2000)
    {continue;}

    rectangle(src, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 0), 1);
    Mat roi = src(boundRect[i]);
    Mat roi2,roi3;
    
     int len = max(roi.cols,roi.rows);
     Mat drawing= Mat::zeros(Size(len,len), CV_8UC3);
     
    // //  threshold(roi,drawing2, 150, 255, THRESH_BINARY_INV);s
      Mat mask ,drawing2;
     // mask = roi ;
      threshold(roi,mask, 150, 255, THRESH_BINARY_INV);
       imshow("mask",mask);
     // threshold(roi,mask, 150, 255, THRESH_BINARY_INV);
     imshow("drawing",drawing);
      int a = (drawing.cols/2)-(roi.cols/2);
      int  b = (drawing.rows/2)-(roi.rows/2);
      Mat imageROI = drawing(Rect(a,b, roi.cols, roi.rows));
    // cout << imageROI.cols << endl;
    // cout << mask.cols << endl;
    
    // cout << imageROI.rows << endl;
    // cout << mask.rows << endl;
      addWeighted(imageROI,0.5,mask,1.0,0, imageROI);
     //drawing.copyTo(imageROI,mask);
    //  bitwise_or(drawing,roi,drawing2);
     imshow("dd",drawing);
     threshold(drawing,drawing2, 150, 255, THRESH_BINARY_INV);
    imshow("rrr",drawing2);
    
     resize(drawing2,roi2,Size(28,28));
     imshow("rrr2",roi2);
     vector<Mat> channels;
     Mat aChannels[3];
     split(roi2, aChannels);
     split(roi2, channels);
    
    threshold(channels[2],roi3, 150, 255, THRESH_BINARY_INV);
    
   
     roi3 = roi3.reshape(1, 1);
    roi3.convertTo(roi3, CV_32F);
    
  
   
    // cout << roi3.cols << endl;
    // cout << svm->getVarCount() << endl;
    int ret = svm->predict(roi3);
    putText(src,to_string(ret),boundRect[i].br(),cv::FONT_HERSHEY_COMPLEX,1,Scalar(0, 255, 255),1, 5, 0);
   
  }
  imshow("src", src);

  waitKey(0);
}
