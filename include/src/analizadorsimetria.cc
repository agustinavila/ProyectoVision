/**
 * @file analizadorsimetria.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../analizadorsimetria.h"

AnalizadorSimetria::AnalizadorSimetria(/* args */)
{
	cout << "En el constructor del objeto de analizadorSimetria"<<endl;
	// WebcamFeeder webcamFeeder;
	// this->ptrFeeder = &webcamFeeder;
	// ExtractorLandmarksOpenCV extractorOpencv;
	// ptrExtractor = &extractorOpencv;
	// ExtractorLandmarksDlib extractorDlib;
	// this->ptrExtractor = &extractorDlib;
}

AnalizadorSimetria::~AnalizadorSimetria()
{
cout<<"destructor del analizador?"<<endl;
}

void AnalizadorSimetria::step()
{
		frame = feeder.getFrame();
		logger.log(frame); //Guarda frames, segun parametros podria desactivarse o no
		landmarks = extractor.getLandmarks(frame);
		if (!landmarks[0].empty())
		{
			cout << "Detectados " << landmarks.size() << " rostros!" << endl;
			analizadorLandmarks.setLandmarks(landmarks);
			analizadorLandmarks.normalizarLandmarks();
			asimetria=analizadorLandmarks.calcularAsimetria();
			cout << "Asimetria: "<< asimetria << endl;
			putText(frame, "Rostro detectado!",*landmarks[0].menton.end(),1,1,Scalar(255,0,0));
			drawContours(frame,landmarks[0].ojoDer,-1,Scalar(255,0,0));
		}
		else
		{
			cout << "no se detecto ninguna cara"<<endl;
 		}	
}