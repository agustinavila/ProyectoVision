/**
 * @file videofeeder.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase concreta VideoFeeder
 * @version 0.1
 * @date 2021-06-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../videofeeder.h"

VideoFeeder::VideoFeeder(string &nombre)
{
	char buff[250];
	getcwd(buff, PATH_MAX);
	std::string cwd(buff);
	video_file_name_ = nombre;
	cout << "Cargando video..." << cwd + "/" + video_file_name_ << endl;
	if (!cap_.open(cwd + "/" + video_file_name_))
	{
		cout << "No se pudo abrir el video" << endl;
		throw MiExcepcion(ERROR_VIDEOFEEDER_ABRIR_ARCHIVO);
	}
	else
		cout << "listo!" << endl;
}

VideoFeeder::VideoFeeder()
{
	char buff[250];
	getcwd(buff, PATH_MAX);
	std::string cwd(buff);
	video_file_name_ = cwd + "/video.avi";
	cout << "Cargando video..." << video_file_name_ << endl;
	if (!cap_.open(video_file_name_))
	{
		cout << "No se pudo abrir el video por defecto " << video_file_name_ << endl;
		throw MiExcepcion(ERROR_VIDEOFEEDER_ABRIR_ARCHIVO);
	}
}

VideoFeeder::~VideoFeeder()
{
	cout << "Cerrando video del feeder...";
	cap_.release();
	cout << " video cerrado" << endl;
}

const Mat VideoFeeder::get_frame()
{
	cap_ >> frame_;
	return frame_;
}