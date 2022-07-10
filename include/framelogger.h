/**
 * @file framelogger.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo de cabecera de la clase FrameLogger
 * @version 0.1
 * @date 2021-06-17
 * @copyright Copyright (c) 2021
 *
 */

#if !defined(FRAMELOGGER_H)
#define FRAMELOGGER_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "feeder.h"
#include <opencv2/video/video.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

/**
 * @brief Clase para guardar los frames. Por defecto genera un video.
 * @todo generar constructor para trabajar con secuencias de imagenes.
 * @details Clase encargada de guardar el los fotogramas obtenidos.
 * Toma un nombre por defecto para el archivo de video, al cual le inserta
 * el feeder del que se proveen los fotogramas, y la fecha y hora del comienzo del registro.
 * Por lo pronto solo trabaja con videos, pero eventualmetne podria guardar secuencias de imagenes.
 */
class FrameLogger {
private:
    VideoWriter video_; ///< Objeto Videowriter de Opencv, encargado de manejar la escritura y codificacion del video
    string video_file_name_ = "Salida"; ///< Nombre base para utilizar con el archivo
    double frame_counter_ = 0;          ///< contador para tener un registro de fotogramas

public:
    /**
	 * @brief Construye un nuevo objeto de la clase Frame Logger.
	 *
	 * @details Constructor a utilizar generalmente, se le pasa como argumentos
	 * el nombre base del video y el tipo de feeder utilizado.
	 */
    FrameLogger(const string&, const FeederType&);

    /**
	 * @brief Constructor por defecto, genera un nombre por defecto.
	 * @bug Puede tener problemas segun el tipo de feeder que provee los frames.
	 */
    FrameLogger();

    ~FrameLogger();

    double get_frame_counter() { return frame_counter_; };

    void log(const Mat&);
};

#endif // FRAMELOGGER_H