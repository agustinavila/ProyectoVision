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

#include "estructuras.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

/**
 * @brief Clase que maneja los metodos para analizar los landmarks
 * @todo calcular asimetria
 */
class AnalizadorLandmarks {
private:
    std::vector<Landmarks> landmarks; ///< Vector de estructuras de tipo Landmarks
    std::vector<Landmarks>
            landmarksNorm; ///< Vector de estructura de tipo Landmarks, pero normalizada(sin rotacion del rostro)

public:
    AnalizadorLandmarks();

    ~AnalizadorLandmarks();

    /**
	 * @brief Actualiza los landmarks del objeto
	 *
	 * @param lm landmarks nuevos.
	 */
    void setLandmarks(const std::vector<Landmarks>& lm);

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

    inline const float calcularAngulo(const Point2f&, const Point2f&);

    inline const float calcularPendiente(const Point2f&, const Point2f&);

    inline const float calcularMax(const float&, const float&);

    /**
	 * @brief Método principal de la clase, analiza la asimetria de un rostro
	 *
	 * @details No está completamente desarrollada, pero debería devolver
	 * una asimetría de un rostro. Lo ideal en realidad sería que devuelva
	 * una estructura con diferentes parámetros, para luego alimentar a una
	 * red neuronal y discernir la asimetria.
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
