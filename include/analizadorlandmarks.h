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
#include "estructuras.h"

using namespace std;
using namespace cv;

/**
 * @brief Clase que maneja los metodos para analizar los landmarks
 * @todo calcular asimetria
 */
class AnalizadorLandmarks
{
private:
/**
 * @brief Vector de estructuras de tipo Landmarks, 
 * 
 */
	std::vector<Landmarks> landmarks;
	/**
	 * @brief Vector de estructura de tipo Landmarks, pero normalizada
	 * 
	 */
	std::vector<Landmarks> landmarksNorm;

public:
	/**
	 * @brief Construye un nuevo objeto de la clase Analizador Landmarks
	 * 
	 */
	AnalizadorLandmarks();

	/**
	 * @brief Destruye el objeto de la clase Analizador Landmarks
	 * 
	 */
	~AnalizadorLandmarks();

	/**
	 * @brief Setea la propiedad Landmarks del objeto
	 * 
	 */
	void setLandmarks(const std::vector<Landmarks> &);

	/**
	 * @brief Devuelve la propiedad Landmarks 
	 * 
	 * @return const std::vector<Landmarks> 
	 */
	const std::vector<Landmarks> getLandmarks() { return this->landmarks; };

	/**
	 * @brief Devuelve la propiedad Norm Landmarks 
	 * 
	 * @return std::vector<Landmarks> 
	 */
	std::vector<Landmarks> getNormLandmarks() { return this->landmarksNorm; };

	/**
	 * @brief Método que devuelve el angulo entre dos puntos
	 * 
	 * @return const float 
	 */
	inline const float calcularAngulo(const Point2f &, const Point2f &);

	/**
	 * @brief Metodo que devuelve la pendiente entre dos puntos
	 * 
	 * @return const float 
	 */
	inline const float calcularPendiente(const Point2f &, const Point2f &);

	/**
	 * @brief Método que devuelve el máximo valor entre dos puntos
	 * 
	 * @return const float 
	 */
	inline const float calcularMax(const float &, const float &);

	/**
	 * @brief Método principal de la clase, analiza la asimetria de un rostro
	 * 
	 * @return const float 
	 */
	const float calcularAsimetria();

	/**
	 * @brief Funcion que normaliza los landmarks, eliminando la posible rotacion del rostro
	 * 
	 */
	void normalizarLandmarks();
};

#endif // ANALIZADORLANDMARKS_H
