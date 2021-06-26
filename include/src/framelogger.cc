/**
 * @file framelogger.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase FrameLogger
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../framelogger.h"

FrameLogger::FrameLogger()
{
	nombre_="out.avi";
	//el nombre esta hardcodeado por ahora, tendria que tomar un nombre como parametro
	//y ademas adjuntarle un timestamp por si acaso
}

FrameLogger::FrameLogger(string nombre="outcpp.avi") : nombre_(nombre)
{
	//el nombre esta hardcodeado por ahora, tendria que tomar un nombre como parametro
	//y ademas adjuntarle un timestamp por si acaso
}

FrameLogger::~FrameLogger()
{
	cout << "Cerrando video...";
	video.release();
	cout << "Video cerrado!" << endl;
}

void FrameLogger::startVideoLog()
{
	if(rec){
	stopVideoLog();
	}
	video.open(nombre_, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(640, 480));
	rec=1;
}

void FrameLogger::stopVideoLog()
{
	if (rec){
		video.release();
	}
	else cout <<"Ningun video abierto"<<endl;
}

void FrameLogger::log(const Mat &frame)
{
	if (!rec){
		startVideoLog();
	}
	numero++; //Solo en caso de guardar secuencia de imagenes
	video.write(frame);
	//cout << "frame numero " << numero << endl;
}