/**
 * @file framelogger.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase FrameLogger
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

//TODO: generar constructor para trabajar con secuencias de imagenes.
//TODO: Aceptar argumentos para el constructor
//TODO:Eventualmente ver el tema de los codecs, segun la carga que representen para el cpu

#if !defined(FRAMELOGGER_H)
#define FRAMELOGGER_H

#include "feeder.h"
#include <opencv2/video/video.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

/**
 * @brief Clase para guardar los frames. Por defecto genera un video
 * @todo generar constructor para trabajar con secuencias de imagenes.
 * Aceptar argumentos para el constructor.
 * Eventualmente ver el tema de los codecs, segun la carga que representen para el cpu.
 */
class FrameLogger
{
private:
	Mat frame;
	string nombre;
	double numero = 0;
	VideoWriter video;

public:
	FrameLogger();
	~FrameLogger();
	void log(const Mat &);
};

#endif // FRAMELOGGER_H