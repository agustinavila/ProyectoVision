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
	 * @brief Fotograma actual
	 * 
	 */
	Mat frame;

	/**
	 * @brief Índice de la Webcama abrir. Por defecto es 0
	 * 
	 */
	int idx;

	/**
	 * @brief Objeto de openCV encargado de manejar la webcam
	 * 
	 */
	cv::VideoCapture cap;

public:
	/**
	 * @brief Construye un nuevo objeto de la clase WebcamFeeder
	 * 
	 * @details Se encarga de inicializar la webcam 
	 * a través del objeto de la clase VideoCapture
	 * 
	 * @param idx - índice de la webcam a abrir
	 */
	WebcamFeeder(int idx = 0);

	/**
	 * @brief Destruye el objeto de la clase WebcamFeeder
	 * 
	 */
	virtual ~WebcamFeeder();
	
	/**
	 * @brief Devuelve el TipoFeeder (en este caso WEBCAMFEEDER)
	 * 
	 * @return const TipoFeeder 
	 */
	virtual const TipoFeeder getFeeder() {return WEBCAMFEEDER;};

	/**
	 * @brief Devuelve el fotograma actual.
	 * 
	 * @return const Mat 
	 */
	virtual const Mat getFrame();
};

#endif // WEBCAMFEEDER_H