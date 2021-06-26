/**
 * @file feeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief header de la clase abstracta Feeder
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

using namespace std;
using namespace cv;


/**
 * @brief Clase abstracta para proveer Mats
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
	Feeder();

	/**
	 * @brief Destruye el objeto de la clase virtual Feeder
	 * 
	 */
	virtual ~Feeder();

	/**
	 * @brief Devuelve el frame actual 
	 * 
	 * @return const Mat 
	 */
	virtual const Mat getFrame() = 0;
};

#endif // FEEDER_H
