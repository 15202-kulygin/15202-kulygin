#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
//g++ petya.cpp -lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11

int main(int argc,char *argv[]) {
    double cpu_Hz = 2800000000;

    CvCapture *capture = cvCreateCameraCapture(0);
    if (!capture) return 0;
    int counter = 0;
    std::time_t current_second = 0;
    int fps = 0;
    while(1) {
        uint32_t hi, lo,hi2,lo2;

        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  uint64_t start2 = ( (uint64_t) lo) | ( ((uint64_t) hi) << 32 );

        uint32_t hi_2, lo_2, hi2_2, lo2_2;
        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi_2));
  uint64_t start2_2 = ( (uint64_t) lo_2) | ( ((uint64_t) hi_2) << 32 );

        IplImage *frame = cvQueryFrame(capture);
        __asm__ __volatile__ ("rdtsc" : "=a" (lo2), "=d" (hi2_2)); //4
        uint64_t end2_2 = ( (uint64_t) lo2) | ( ((uint64_t) hi2_2) << 32 ); //4
        std::cout << "Time spent, image capture " << (end2_2-start2_2)/cpu_Hz << "sec.\n";

        IplImage *image = cvCloneImage(frame);
        for (int y=0; y<image->height; y++) {
            int x = 0;
            uchar *ptr = (uchar*)(image->imageData + y*image->widthStep);
            for (x=0; x<image->width/3; x++) {
                ptr[3*x+1] = 0;
                ptr[3*x] = 0;
            }
            for (x; x<2*image->width/3; x++) {
                ptr[3*x] = 0;
                ptr[3*x+2] = 0;
            }
            for (x; x<image->width; x++) {
                ptr[3*x+1] = 0;
                ptr[3*x+2] = 0;
            }
        }
        if(!frame) break;
        cvFlip(image, image, 1);
        cvSmooth(frame, frame, 1, 3, 15);
        uint32_t hi_3, lo_3, hi2_3, lo2_3;
        __asm__ __volatile__ ("rdtsc" : "=a" (lo_3), "=d" (hi_3));
  uint64_t start2_3 = ( (uint64_t) lo_3) | ( ((uint64_t) hi_3) << 32 );

        cvShowImage("smooth", frame);

        __asm__ __volatile__ ("rdtsc" : "=a" (lo2_3), "=d" (hi2_3)); //4
        uint64_t end2_3 = ( (uint64_t) lo2_3) | ( ((uint64_t) hi2_3) << 32 ); //4
        std::cout << "Time spent, ShowImage" << (end2_3-start2_3)/cpu_Hz << "sec.\n";

        cvShowImage("123", image);
        __asm__ __volatile__ ("rdtsc" : "=a" (lo2), "=d" (hi2)); //4
        uint64_t end2 = ( (uint64_t) lo2) | ( ((uint64_t) hi2) << 32 ); //4
        std::cout << "Time spent, overall " << (end2-start2)/cpu_Hz << "sec.\n";

        std::time_t result = std::time(nullptr);
        if (result == current_second) {
            fps++;
        } else {
            std::cout << fps << "\n";
            current_second = result;
            fps = 0;
        }
        char c = cvWaitKey(33);
        if (c == 27) break;
        if (c == 10) {
            
            std::ostringstream name;
            name << "image" << counter << ".jpg";
            cvSaveImage(name.str().c_str(), frame);
            counter++;
        }
    }

    cvReleaseCapture(&capture);
    cvDestroyWindow("123");
    cvDestroyWindow("smooth");

}
