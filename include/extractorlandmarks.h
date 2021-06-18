/**
 * @file extractorlandmarks.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Clase abstracta para la obtencion de landmarks
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

using namespace std;

class ExtractorLandmarks
{
private:
	std::vector<cv::Point2f> landmarks;
	/* data */
public:
	ExtractorLandmarks();
	virtual ~ExtractorLandmarks();
	virtual std::vector<cv::Point2f> getLandmarks(cv::Mat &);
};

#endif // EXTRACTORLANDMARKS_H