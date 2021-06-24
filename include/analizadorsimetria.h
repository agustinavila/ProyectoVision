/**
 * @file analizadorsimetria.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Clase maestra del proyecto
 * @version 0.1
 * @date 2021-06-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(ANALIZADORSIMETRIA_H)
#define ANALIZADORSIMETRIA_H

#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/video.hpp>
#include <opencv2/core/core.hpp>
#include "feeder.h"
#include "webcamfeeder.h"
#include "framelogger.h"
#include "extractorlandmarks.h"
#include "extractorlandmarks_dlib.h"
#include "extractorlandmarks_opencv.h"
#include "analizadorlandmarks.h"
#include "estructuras.h"

using namespace std;
using namespace cv;

class AnalizadorSimetria
{
private:
	float asimetria;
	Mat frame;
	Feeder *ptrFeeder;
	ExtractorLandmarks *ptrExtractor;
	AnalizadorLandmarks analizadorLandmarks;
	FrameLogger logger;
	std::vector<Landmarks> landmarks;
	std::vector<Landmarks> landmarksNorm;

public:
	AnalizadorSimetria(Feeder *, ExtractorLandmarks *);
	AnalizadorSimetria();
	~AnalizadorSimetria();
	Mat getFrame() { return frame; };
	const float getAsimetria() { return asimetria; };
	const std::vector<Landmarks> getLandmarks() { return landmarks; };
	const std::vector<Landmarks> getLandmarksNorm() { return landmarks; };
	void setFeeder(Feeder *);
	void setExtractor(ExtractorLandmarks *);
	void step();
};

#endif // ANALIZADORSIMETRIA_H
