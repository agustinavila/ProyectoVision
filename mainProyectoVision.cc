/**
 * @file mainProyectoVision.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo main del proyecto
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
#include "extractorlandmarks_opencv.h"
#include "analizadorlandmarks.h"

using namespace std;
using namespace cv;

/**
 * @brief Funcion main del proyecto
 * @todo Manejar argumentos de entrada
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
	//Definiciones de propiedades
	char ch = 0;
	Mat frame;
	std::vector<Point2f> landmarks;
	float asimetria;
	//TODO: parseo de argumentos

	//instanciacion de objetos
	Feeder *ptrFeeder;
	WebcamFeeder webcamFeeder;
	ptrFeeder = &webcamFeeder;
	FrameLogger logger;
	ExtractorLandmarks *ptrExtractor;
	// ExtractorLandmarksOpenCV extractorOpencv;
	// ptrExtractor = &extractorOpencv;
	ExtractorLandmarksDlib extractorDlib;
	ptrExtractor = &extractorDlib;
	AnalizadorLandmarks analizadorLandmarks;

	cout << "Presione q para finalizar" << endl;
	while (ch != 'q' && ch != 'Q')
	{ 
		frame = ptrFeeder->getFrame();
		logger.log(frame); //Guarda frames, segun parametros podria desactivarse o no
		landmarks = ptrExtractor->getLandmarks(frame);
		if (landmarks.size() > 1)
		{
			cout << "Detectados " << landmarks.size() << " puntos!" << endl;
			analizadorLandmarks.setLandmarks(landmarks);
			analizadorLandmarks.normalizarLandmarks();
			asimetria=analizadorLandmarks.calcularAsimetria();
			cout << "Asimetria: "<< asimetria << endl;
			putText(frame, "Rostro detectado!",landmarks[16],1,1,Scalar(255,0,0));
		}
		else
		{
			cout << "no se detecto ninguna cara"<<endl;
 		}
		imshow("feeder", frame);
		ch = waitKey(1);
	}
	return 0;
}