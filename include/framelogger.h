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
/**
 * @brief Nombre base para utilizar con el archivo
 * 
 */
	string nombre_;
	/**
	 * @brief flag para indicar si se esta logeando o no
	 * 
	 */
	bool rec = 0;

	/**
	 * @brief contador para tener un registro de fotogramas
	 * 
	 */
	double numero = 0;

	/**
	 * @brief Objeto Videowriter de Opencv
	 * 
	 */
	VideoWriter video;

public:
/**
 * @brief Construye un nuevo objeto de la clase Frame Logger
 * 
 */
	FrameLogger();

/**
 * @brief Construye un nuevo objeto de la clase Frame Logger
 * 
 */
	FrameLogger(string);

/**
 * @brief Destruye el objeto de la clase Frame Logger
 * 
 */
	~FrameLogger();

/**
 * @brief Metodo para empezar a grabar video
 * 
 */
	void startVideoLog();

/**
 * @brief Metodo para detener la grabacion
 * 
 */
	void stopVideoLog();

/**
 * @brief Agrega un frame al video
 * 
 */
	void log(const Mat &);
};

#endif // FRAMELOGGER_H