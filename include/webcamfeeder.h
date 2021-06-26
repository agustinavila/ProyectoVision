/**
 * @file webcamfeeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase concreta WebcamFeeder
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#if !defined(WEBCAMFEEDER_H)
#define WEBCAMFEEDER_H

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
/**
 * @brief 
 * 
 */
	Mat frame;
	int idx;
	cv::VideoCapture cap;

public:
/**
 * @brief Construye un nuevo objeto de la clase Webcam Feeder
 * 
 * @param idx 
 */
	WebcamFeeder(int idx = 0);

	/**
	 * @brief Destruye el objeto de la clase Webcam Feeder
	 * 
	 */
	virtual ~WebcamFeeder();
	
	/**
	 * @brief Devuelve la propiedad Frame 
	 * 
	 * @return const Mat 
	 */
	virtual const Mat getFrame();
};

#endif // WEBCAMFEEDER_H