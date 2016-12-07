#include <iostream>
#include <time.h>

#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


//g++ -std=c++11 true.cpp -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -o true.out

#define ITERATIONS_CHECK 33

int main(int argc,char *argv[])
{ 
	CvCapture *capture = cvCreateCameraCapture(0);
	if (!capture) 
		return 0;
	struct timespec start;
	struct timespec end;
	struct timespec start_fps;
	struct timespec end_fps;
 	IplImage * frame;
 	IplImage * destination; 

 	int counter = 0;	
 	int iterations = 0;

 	clock_gettime(CLOCK_MONOTONIC_RAW, &start_fps);
 	while (true) 
 	{
 		clock_gettime(CLOCK_MONOTONIC_RAW, &end_fps);
 		if (1.0 <= end_fps.tv_sec - start_fps.tv_sec + 0.000000001 * (end_fps.tv_nsec - start_fps.tv_nsec))
 		{
 			printf("fps %d\n", counter);
 			counter = 0;
 			clock_gettime(CLOCK_MONOTONIC_RAW, &start_fps);
 		}

 		clock_gettime(CLOCK_MONOTONIC_RAW, &start); // input
 		frame = cvQueryFrame(capture); // ******
 		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
 		if (0 == iterations % ITERATIONS_CHECK)
 			printf("State %d\nInput : %lf sec\n", iterations/ITERATIONS_CHECK + 1, end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));


 		if(!frame) 
 			break;
 		

 		clock_gettime(CLOCK_MONOTONIC_RAW, &start); //showing
 		cvShowImage("original", frame); // ******
 		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
 		if (0 == iterations % ITERATIONS_CHECK)
 			printf("Output : %lf sec\n", end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));



 		destination = cvCloneImage(frame); 
 		clock_gettime(CLOCK_MONOTONIC_RAW, &start); // changing
 		cvThreshold(frame, destination, 50, 255, CV_THRESH_BINARY); // ******
 		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
 		if (0 == iterations % ITERATIONS_CHECK)
 			printf("Changing : %lf sec\n\n", end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));
 		

 		cvShowImage("threshold", destination);
 		char c = cvWaitKey(33);
 		if(c == 27) 
 			break;
 		counter++;
 		iterations++;
 	}
 	cvReleaseImage(&frame);
 	cvReleaseImage(&destination);
 	cvDestroyWindow("original");
 	cvDestroyWindow("threshold");
 	cvReleaseCapture(&capture);
}

