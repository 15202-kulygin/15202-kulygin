#include <opencv2/highgui/highgui.hpp>


//gcc lab5.c –lopencv_core –lopencv_highgui

int main(int argc,char *argv[])
{ CvCapture *capture = cvCreateCameraCapture(0);
 if (!capture) return 0;
 while(1) {
 IplImage *frame = cvQueryFrame(capture);
 if(!frame) break;
 cvShowImage("test", frame);
 char c = cvWaitKey(33);
 if(c == 27) break;
 }
 cvReleaseCapture(&capture);
 cvDestroyWindow("test");
}
