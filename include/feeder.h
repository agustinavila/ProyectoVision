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
	Mat frame;

public:
	Feeder(){};

	virtual ~Feeder(){};

	virtual const FeederType get_feeder_type() = 0;

	/**
	 * @brief Devuelve el frame actual
	 *
	 * @return const Mat
	 */
	virtual const Mat get_frame() = 0;
};

#endif // FEEDER_H
