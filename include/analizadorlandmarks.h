/**
 * @file analizadorlandmarks.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase AnalizadorLandmarks
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(ANALIZADORLANDMARKS_H)
#define ANALIZADORLANDMARKS_H

#include <iostream>
#include <vector>
//#include <math.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

/**
 * @brief Clase que maneja los metodos para analizar los landmarks
 * @todo calcular asimetria
 */
class AnalizadorLandmarks
{
private:
	std::vector<Point2f> landmarks;
	std::vector<Point2f> landmarksNorm;
	/**
 	* @brief Landmarks sectorizador por region de la cara.
 	* @details Los distintos vectores son:
 	* 0: Quijada
 	* 1: ceja izquierda
 	* 2: ceja derecha
 	* 3: nariz
 	* 4: ojo izq
 	* 5: ojo derecho
 	* 6: boca
 	*/
	std::vector<std::vector<Point2f>> landmarksRegion;
	float rotacion;
	float asimetria;

public:
	AnalizadorLandmarks(/* args */);
	~AnalizadorLandmarks();
	void setLandmarks(const std::vector<Point2f> &);
	const std::vector<Point2f> getLandmarks() { return this->landmarks; };
	std::vector<Point2f> getNormLandmarks() { return this->landmarksNorm; };
	inline const float calcularAngulo(const Point2f &, const Point2f &);
	inline const float calcularPendiente(const Point2f &, const Point2f &);
	inline const float calcularMax(const float &, const float &);
	const float calcularAsimetria();
	void normalizarLandmarks();
};

#endif // ANALIZADORLANDMARKS_H
