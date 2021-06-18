/**
 * @file feeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief header de la clase abstracta feeder
 * @version 0.1
 * @date 2021-06-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(FEEDER_H)
#define FEEDER_H

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class Feeder
{
	private:
	Mat frame;

	public:
	Feeder();
	virtual ~Feeder();
	virtual Mat getFrame();

};


#endif // FEEDER_H

