/**
 * @file analizadorlandmarks.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo de cabecera de la clase AnalizadorLandmarks
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
	 * @brief Vector de estructuras de tipo Landmarks
	 * 
	 */
	std::vector<Landmarks> landmarks;

	/**
	 * @brief Vector de estructura de tipo Landmarks, pero normalizada(sin rotacion del rostro)
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
	 * @brief Actualiza los landmarks del objeto
	 * 
	 * @param lm landmarks nuevos.
	 */
	void setLandmarks(const std::vector<Landmarks> &);

	/**
	 * @brief Devuelve los landmarks del objeto
	 * 
	 * @return const std::vector<Landmarks> 
	 */
	const std::vector<Landmarks> getLandmarks() { return this->landmarks; };

	/**
	 * @brief Devuelve los landmarks normalizados del objeto
	 * 
	 * @return std::vector<Landmarks> 
	 */
	std::vector<Landmarks> getNormLandmarks() { return this->landmarksNorm; };

	/**
	 * @brief Método que devuelve el angulo entre dos puntos a y b
	 * 
	 * @param a - punto a 
	 * @param b - punto b
	 * @return const float - angulo en grandos
	 */
	inline const float calcularAngulo(const Point2f &, const Point2f &);

	/**
	 * @brief Metodo que devuelve la pendiente entre dos puntos a y b
	 * 
	 * @param a - punto a
	 * @param b - punto b
	 * @return const float - pendiente entre los dos puntos
	 */
	inline const float calcularPendiente(const Point2f &, const Point2f &);

	/**
	 * @brief Método que devuelve el máximo valor entre dos puntos
	 * @param a - punto a
	 * @param b - punto b
	 * @return const float - valor máximo
	 */
	inline const float calcularMax(const float &, const float &);

	/**
	 * @brief Método principal de la clase, analiza la asimetria de un rostro
	 * 
	 * @details No está completamente desarrollada, pero debería devolver
	 * una asimetría de un rostro. Lo ideal en realidad sería que devuelva
	 * una estructura con diferentes parámetros, para luego alimentar a una 
	 * red neuronal y discernir la asimetria.
	 * 
	 * @todo Una implementación útil del cálculo.
	 * 
	 * @return const float 
	 */
	const float calcularAsimetria();

	/**
	 * @brief Funcion que normaliza los landmarks, eliminando la posible rotacion del rostro
	 * 
	 * @details La normalización cobra relevancia si se toma como parámetros
	 * la pendiente o el angulo entre distintos landmarks en el rostro.
	 * Por el momento no tiene utilidad, pero en el caso de alimentar una RN
	 * cobraría relevancia.
	 */
	void normalizarLandmarks();
};

#endif // ANALIZADORLANDMARKS_H
