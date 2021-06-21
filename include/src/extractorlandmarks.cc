/**
 * @file extractorlandmarks.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief implementacion de la clase abstracta ExtractorLandmarks
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../extractorlandmarks.h"

ExtractorLandmarks::ExtractorLandmarks()
{
	cout << "Constructor abstracto de ExtractorLandmarks..." << endl;
	this->landmarks.push_back(cv::Point2f(1,2));
}

ExtractorLandmarks::~ExtractorLandmarks()
{
	cout << "Destructor abstracto de ExtractorLandmarks..." << endl;
}

std::vector<cv::Point2f> ExtractorLandmarks::getLandmarks(cv::Mat)
{
	//cout << "funcion prototipo";
	return this->landmarks;
}