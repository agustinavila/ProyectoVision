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
	std::vector<Landmarks> landmarks;
	/* data */
public:
	ExtractorLandmarks();
	virtual ~ExtractorLandmarks();
	const std::vector<Landmarks> parseLandmarks(const std::vector<std::vector<cv::Point2f>> &);
	virtual const std::vector<Landmarks> getLandmarks(const cv::Mat &);
};

#endif // EXTRACTORLANDMARKS_H