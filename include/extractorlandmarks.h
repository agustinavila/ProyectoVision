/**
 * @file extractorlandmarks.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase abstracta ExtractorLandmarks
 * @version 0.1
 * @date 2021-06-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#if !defined(EXTRACTORLANDMARKS_H)
#define EXTRACTORLANDMARKS_H

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "estructuras.h"
#include <opencv2/core/core.hpp>

using namespace std;

/**
 * @brief Clase abstracta para extraer landmarks de un Mat
 */
class ExtractorLandmarks {
private:
    std::vector<Landmarks> landmarks; ///< Propiedad de las clases, vector de landmarks obtenidos

public:
    ExtractorLandmarks(const std::vector<string>&);

    ExtractorLandmarks();

    virtual ~ExtractorLandmarks();

    /**
	 * @brief Método para convertir los landmarks "crudos" a una estructura con distintos rasgos
	 *
	 * @return const std::vector<Landmarks>
	 */
    const std::vector<Landmarks> parseLandmarks(const std::vector<std::vector<cv::Point2f>>&);

    virtual const ExtractorType get_extractor_type() = 0;

    /**
	 * @brief Devuelve la propiedad Landmarks
	 *
	 * @param frame
	 * @return const std::vector<Landmarks>
	 */
    virtual const std::vector<Landmarks> get_landmarks(const cv::Mat& frame) = 0;
};

#endif // EXTRACTORLANDMARKS_H