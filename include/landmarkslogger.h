/**
 * @file landmarkslogger.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo de cabecera de la clase LandmarksLogger
 * @version 0.1
 * @date 2021-06-28
 *
 * @copyright Copyright (c) 2021
 *
 */

#if !defined(LANDMARKSLOGGER_H)
#define LANDMARKSLOGGER_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "estructuras.h"
#include "feeder.h"
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

/**
 * @brief Clase para guardar los landmarks. Por defecto genera un video.
 * @todo generar constructor para trabajar con secuencias de imagenes.
 * @details Clase encargada de guardar el los fotogramas obtenidos.
 * Toma un nombre por defecto para el archivo de video, al cual le inserta
 * el feeder del que se proveen los fotogramas, y la fecha y hora del comienzo del registro.
 * Por lo pronto solo trabaja con videos, pero eventualmetne podria guardar secuencias de imagenes.
 */
class LandmarksLogger {
private:
    FileStorage fs_;                    ///< Objeto FileStorage de Opencv, encargado de manejar la escritura del archivo
    string log_file_name_ = "log.yaml"; ///< Nombre base para utilizar con el archivo
    double landmarks_counter_ = 0;      ///< contador para tener un registro de landmarks guardados

public:
    /**
	 * @brief Construye un nuevo objeto de la clase Landmark Logger.
	 *
	 * @details Constructor a utilizar generalmente, se le pasa como argumentos
	 * el nombre base del video y el tipo de feeder utilizado.
	 */
    LandmarksLogger(const string&, const FeederType&);

    /**
	 * @brief Constructor por defecto, genera un nombre por defecto.
	 * @bug Puede tener problemas segun el tipo de feeder que provee los landmarks.
	 */
    LandmarksLogger();

    ~LandmarksLogger();

    double get_landmarks_counter() { return landmarks_counter_; };

    void log(const std::vector<Landmarks>& landmarks);
};

#endif // LANDMARKSLOGGER_H