/**
 * @file feeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo de cabecera de la clase abstracta Feeder
 * @version 0.1
 * @date 2021-06-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(FEEDER_H)
#define FEEDER_H

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "estructuras.h"

using namespace std;
using namespace cv;


/**
 * @brief Clase abstracta para proveer obtener nuevos mats
 * 
 * @details Clase abstracta para utilizar como interfaz a las implementaciones concretas.
 * Provee dos métodos básicos que todas las clases utilizarán.
 * 
 */
class Feeder
{
private:

	/**
	 * @brief Estructura que contiene el frame actual
	 * 
	 */
	Mat frame;

public:

	/**
	 * @brief Construye un nuevo objeto de la clase abstracta Feeder
	 * 
	 */
	Feeder(){};

	/**
	 * @brief Destruye el objeto de la clase abstracta Feeder
	 * 
	 */
	virtual ~Feeder(){};

	/**
	 * @brief Devuelve el TipoFeeder del feeder implementado.
	 * 
	 * @return const TipoFeeder 
	 */
	virtual const TipoFeeder getFeeder() = 0;

	/**
	 * @brief Devuelve el frame actual 
	 * 
	 * @return const Mat 
	 */
	virtual const Mat getFrame() = 0;
};

#endif // FEEDER_H
