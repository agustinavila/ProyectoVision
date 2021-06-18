/**
 * @file webcamfeeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "feeder.h"
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


/**
 * @brief Sobrecarga de la clase Feeder para abrir una webcam
 * 
 */
class WebcamFeeder : public Feeder
{
private:
    Mat frame;
    int idx;
    cv::VideoCapture cap;
public:
	Mat getFrame();
	WebcamFeeder(int idx = 0);
	virtual ~WebcamFeeder();
};
