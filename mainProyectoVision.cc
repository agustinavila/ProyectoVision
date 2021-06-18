/**
 * @file mainProyectoVision.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// includes
#include <iostream>
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

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	//Definiciones de propiedades
	char ch = 0;
	Mat frame;
	std::vector<Point2f> landmarks;
	//parseo de argumentos

	//instanciacion de objetos
	Feeder *ptrFeeder;
	WebcamFeeder webcamFeeder;
	ptrFeeder = &webcamFeeder;
	FrameLogger logger;
	ExtractorLandmarks *ptrExtractor;
	ExtractorLandmarks extractorDlib; //No está funcionando ExtractorDlib.getLandmarks(), genera una violacion de segmento
	ptrExtractor = &extractorDlib;

	//ejecutar las acciones / bucle
	cout << "Presione q para finalizar" << endl;
	while (ch != 'q' && ch != 'Q')
	{
		frame = ptrFeeder->getFrame();
		logger.log(frame); //Guarda frames, segun parametros podria desactivarse o no
		imshow("feeder", frame);
		landmarks = ptrExtractor->getLandmarks(frame);
		if (landmarks.size() > 1)
		{
			cout << "Detectados " << landmarks.size() << " puntos!" << endl;
		}
		ch = waitKey(1);
	}
	return 0;
}