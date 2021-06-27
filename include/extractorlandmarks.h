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

#include <opencv2/core/core.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <array>
#include "estructuras.h"

using namespace std;


/**
 * @brief Clase abstracta para extraer landmarks de un Mat
 * 
 */
class ExtractorLandmarks
{
private:

/**
 * @brief Propiedad de las clases, vector de landmarks obtenidos
 * 
 */
	std::vector<Landmarks> landmarks;
public:

/**
 * @brief Construye un nuevo objeto de la clase abstracta Extractor Landmarks
 * 
 */
	ExtractorLandmarks(const std::vector<string> &);
	ExtractorLandmarks();

	/**
	 * @brief Destruye el objeto de la clase Extractor Landmarks
	 * 
	 */
	virtual ~ExtractorLandmarks();

	/**
	 * @brief Método para convertir los landmarks "crudos" a una estructura con distintos rasgos
	 * 
	 * @return const std::vector<Landmarks> 
	 */
	const std::vector<Landmarks> parseLandmarks(const std::vector<std::vector<cv::Point2f>> &);

	virtual const TipoExtractor getExtractor() = 0;

	/**
	 * @brief Devuelve la propiedad Landmarks 
	 * 
	 * @return const std::vector<Landmarks> 
	 */
	virtual const std::vector<Landmarks> getLandmarks(const cv::Mat &) = 0;
};

#endif // EXTRACTORLANDMARKS_H