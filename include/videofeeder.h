/**
 * @file videofeeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase concreta VideoFeeder
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#if !defined(VIDEOFEEDER_H)
#define VIDEOFEEDER_H


#include "feeder.h"
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;


/**
 * @brief Sobrecarga de la clase Feeder para abrir un archivo de video
 * @todo Todavia no esta terminado, abre la webcam...
 */
class VideoFeeder : public Feeder
{
private:
/**
 * @brief 
 * 
 */
	Mat frame;
	cv::VideoCapture cap;
	string nombreVideo;

public:
	VideoFeeder(string nombre = "output");
	virtual ~VideoFeeder();
	virtual const Mat getFrame();
};

#endif // VIDEOFEEDER_H