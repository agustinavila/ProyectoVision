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

/**
 * @brief Construye un nuevo objeto de la clase FrameLogger
 * 
 */
FrameLogger::FrameLogger()
{
	//el nombre esta hardcodeado por ahora, tendria que tomar un nombre como parametro
	//y ademas adjuntarle un timestamp por si acaso
	this->video.open("outcpp.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(640, 480));
}

/**
 * @brief Destruye el objeto de la clase FrameLogger
 * 
 */
FrameLogger::~FrameLogger()
{
	cout << "Cerrando video...";
	this->video.release();
	cout << "Video cerrado!" << endl;
}

/**
 * @brief Agrega un fotograma al video final
 * 
 * @param frame 
 */
void FrameLogger::log(const Mat frame)
{
	this->numero++; //Solo en caso de guardar secuencia de imagenes
	this->video.write(frame);
	//cout << "frame numero " << numero << endl;
}