#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int main(void){
	Mat currimg, graysc, edgmap;
	VideoCapture vid("visiontraffic.avi");
	namedWindow("win", CV_WINDOW_AUTOSIZE);
	while(true){
		vid >> currimg;
		if(currimg.rows == 0){
			destroyWindow("win");
			break;
		}
		cvtColor(currimg , graysc, CV_BGR2GRAY);
		Canny(graysc , edgmap,50, 200, 3);
		vector<Vec4i> lines;
		HoughLinesP(edgmap, lines, 1, CV_PI/180, 50, 50, 1);
		for( size_t i = 0; i < lines.size(); i++ )
			{
				Vec4i l = lines[i];
				line( currimg, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
			}
		imshow("win", currimg);
		waitKey(22);
	}
}