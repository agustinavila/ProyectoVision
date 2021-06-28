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
	/**
	 * @brief Fotograma actual.
	 * 
	 */
	Mat frame;

	/**
	 * @brief Objeto de openCV para manejar el video.
	 * 
	 */
	cv::VideoCapture cap;

	/**
	 * @brief Nombre del video abierto / a abrir.
	 * 
	 */
	string nombreVideo;

public:
	/**
	 * @brief Construye un nuevo objeto de la clase VideoFeeder
	 * 
	 * @param nombre - nombre del video a abrir
	 */
	VideoFeeder(string &);

	/**
	 * @brief Construye un nuevo objeto de la clase VideoFeeder, tomando un nombre por defecto
	 * 
	 * @details Intenta abrir el archivo "video.avi"
	 */
	VideoFeeder();

	/**
	 * @brief Destruye el objeto de la clase VideoFeeder
	 * 
	 */
	virtual ~VideoFeeder();

	/**
	 * @brief Devuelve un valor de TipoFeeder (En este caso VIDEOFEEDER) 
	 * 
	 * @return const TipoFeeder 
	 */
	virtual const TipoFeeder getFeeder() { return VIDEOFEEDER; };

	/**
	 * @brief Devuelve el ultimo frame procesado
	 * 
	 * @return const Mat 
	 */
	virtual const Mat getFrame();
};

#endif // VIDEOFEEDER_H