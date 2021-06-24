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

AnalizadorSimetria::AnalizadorSimetria(Feeder *feeder = new WebcamFeeder, ExtractorLandmarks *extractor = new ExtractorLandmarksDlib): ptrFeeder(feeder), ptrExtractor(extractor)
{
	cout << "En el constructor del objeto de analizadorSimetria por defecto" << endl;

}
AnalizadorSimetria::AnalizadorSimetria()
{
	cout << "En el constructor del objeto de analizadorSimetria por defecto" << endl;
	this->ptrFeeder=new WebcamFeeder;
	this->ptrExtractor=new ExtractorLandmarksDlib;

}
AnalizadorSimetria::~AnalizadorSimetria()
{
	delete this->ptrExtractor;
	delete this->ptrFeeder;

	cout << "destructor del analizador?" << endl;
}

void AnalizadorSimetria::step()
{
	frame = ptrFeeder->getFrame();
	logger.log(frame); //Guarda frames, segun parametros podria desactivarse o no
	landmarks = ptrExtractor->getLandmarks(frame);
	if (!landmarks[0].vacio)
	{
		cout << "Detectados " << landmarks.size() << " rostros!" << endl;
		analizadorLandmarks.setLandmarks(landmarks);
		analizadorLandmarks.normalizarLandmarks();
		asimetria = analizadorLandmarks.calcularAsimetria();
		cout << "Asimetria: " << asimetria << endl;

	}
	else
	{
		cout << "no se detecto ninguna cara" << endl;
	}
}

void AnalizadorSimetria::setExtractor(ExtractorLandmarks *extractor)
{
	delete this->ptrExtractor;
	this->ptrExtractor = extractor;
}

void AnalizadorSimetria::setFeeder(Feeder *feeder)
{
	delete this->ptrFeeder;
	this->ptrFeeder = feeder;
}