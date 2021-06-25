/**
 * @file analizadorlandmarks.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase AnalizadorLandmarks
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../analizadorlandmarks.h"

/**
 * @brief Construye un nuevo objeto de la clase Analizador Landmarks:: Analizador Landmarks
 * 
 */
AnalizadorLandmarks::AnalizadorLandmarks()
{
	cout << "Construyendo el analizador de landmarks..." << endl;
}

/**
 * @brief Destruye el objeto de la clase Analizador Landmarks:: Analizador Landmarks
 * 
 */
AnalizadorLandmarks::~AnalizadorLandmarks()
{
	cout << "destructor del analizador" << endl;
	// Deberia eliminar los vectores?
}

/**
 * @brief Actualiza los landmarks
 * 
 * @param vector<Point2f>lm 
 */
void AnalizadorLandmarks::setLandmarks(const vector<Landmarks> &lm)
{
	this->landmarks = lm;
}

/**
 * @brief Calcula el angulo entre dos puntos a y b
 * 
 * @param a 
 * @param b 
 * @return float 
 */
inline const float AnalizadorLandmarks::calcularAngulo(const Point2f &a, const Point2f &b)
{
	if ((a.x - b.x) != 0)
	{
		return atan((a.y - b.y) / (a.x - b.x)) * 180 / CV_PI;
	}
	else
		return 0;
}

/**
 * @brief Calcula la pendiente entre dos puntos
 * 
 * @param a 
 * @param b 
 * @return float 
 */
inline const float AnalizadorLandmarks::calcularPendiente(const Point2f &a, const Point2f &b)
{
	return abs((a.x - b.x) / (a.y - b.y));
}

/**
 * @brief Normaliza los landmarks, leyendo 'landmarks' y actualizando 'landmarksNorm'
 * 
 */
void AnalizadorLandmarks::normalizarLandmarks()
{
	Mat matrizRotacion;
	landmarksNorm.clear();
	if (!landmarks.front().empty())
	{
		std::vector<Landmarks>::const_iterator cii;
		Landmarks l, lNorm;
		for (cii = landmarks.begin(); cii != landmarks.end(); cii++)
		{
			l = *cii;
			lNorm.rotacion = calcularAngulo(l.menton.front(), l.menton.back());
			matrizRotacion = getRotationMatrix2D(l.menton.front(), lNorm.rotacion, l.escala);
			transform(l.menton, lNorm.menton, matrizRotacion);
			transform(l.cejaIzq, lNorm.cejaIzq, matrizRotacion);
			transform(l.cejaDer, lNorm.cejaDer, matrizRotacion);
			transform(l.ojoIzq, lNorm.ojoIzq, matrizRotacion);
			transform(l.ojoDer, lNorm.ojoDer, matrizRotacion);
			transform(l.nariz, lNorm.nariz, matrizRotacion);
			transform(l.boca, lNorm.boca, matrizRotacion);
			landmarksNorm.push_back(lNorm);
		}
	}
	else
		landmarksNorm.front().vacio = 1;
}

/**
 * @brief Funcion que calcula la asimetria entre ambos lados de la cara
 * 
 * @return const float 
 */
const float AnalizadorLandmarks::calcularAsimetria()
{
	//Estoy usando un float, podria ser un vector y luego sumar los puntos
	//Los valores estan elegidos un poco "a ojo"
	float asimetria = 1;
	if (!landmarksNorm.front().empty())
	{
		//aca deberia calcular la asimetria
	}

	return asimetria;
}

/**
 * @brief Devuelve el maximo entre dos valores
 * 
 * @param a 
 * @param b 
 * @return const float 
 */
inline const float AnalizadorLandmarks::calcularMax(const float &a, const float &b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}