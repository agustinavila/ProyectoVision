/**
 * @file videofeeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo de cabecera de la clase concreta VideoFeeder
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
#include <unistd.h>

using namespace std;
using namespace cv;

/**
 * @brief Sobrecarga de la clase Feeder para abrir un archivo de video
 *
 * @details Abre un archivo de video, cuyo nombre se pasa a la hora de construir el feeder.
 * Por ahora, cuando llega al final del video, se corta la ejecucion.
 */
class VideoFeeder : public Feeder
{
private:
	Mat frame_;

	cv::VideoCapture cap_;

	string video_file_name_;

public:
	/**
	 * @brief Construye un nuevo objeto de la clase VideoFeeder
	 *
	 * @param nombre - nombre del video a abrir
	 */
	VideoFeeder(string &nombre);

	/**
	 * @brief Construye un nuevo objeto de la clase VideoFeeder, tomando un nombre por defecto
	 *
	 * @details Intenta abrir el archivo "video.avi"
	 */
	VideoFeeder();

	virtual ~VideoFeeder();

	virtual const FeederType get_feeder_type() { return FeederType::video_feeder; };

	virtual const Mat get_frame();
};

#endif // VIDEOFEEDER_H