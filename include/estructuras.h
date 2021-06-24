/**
 * @file estructuras.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Descripcion de distintas estructuras de datos usadas por la clase
 * @version 0.1
 * @date 2021-06-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(ESTRUCTURAS_H)
#define ESTRUCTURAS_H

#include <vector>
#include <opencv2/core/types.hpp>

using namespace std;
using namespace cv;

struct Landmarks
{
	bool vacio = 0;
	float escala = 1;
	float rotacion = 0;
	std::vector<Point2f> menton;
	std::vector<Point2f> ojoIzq;
	std::vector<Point2f> ojoDer;
	std::vector<Point2f> cejaIzq;
	std::vector<Point2f> cejaDer;
	std::vector<Point2f> boca;
	std::vector<Point2f> nariz;
	inline const bool empty() { return vacio; };
};

#endif // ESTRUCTURAS_H
