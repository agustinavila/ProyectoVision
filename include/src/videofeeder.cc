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

/**
 * @brief Construye un nuevo objeto de la clase Video Feeder:: Video Feeder
 * 
 * @param nombre 
 */
VideoFeeder::VideoFeeder(string &nombre)
{
	char buff[250];
	getcwd( buff, PATH_MAX );
	std::string cwd( buff );
	nombreVideo = nombre;
	cout << "Cargando video..." << cwd+"/"+nombreVideo << endl;
	if (!cap.open(cwd+"/"+nombreVideo)) //tendria que agregar la ruta hasta el directorio actual?
	{
		cout << "No se pudo abrir el video" << endl;
		throw MiExcepcion(ERROR_VIDEOFEEDER_ABRIR_ARCHIVO);
	} else cout<<"listo!"<<endl;
}

VideoFeeder::VideoFeeder()
{
	nombreVideo = "video.avi";
	cout << "Cargando video..." << nombreVideo << endl;
	if (!cap.open(nombreVideo)) //tendria que agregar la ruta hasta el directorio actual?
	{
		cout << "No se pudo abrir el video" << endl;
		throw MiExcepcion(ERROR_VIDEOFEEDER_ABRIR_ARCHIVO);
	}
}

/**
 * @brief Destruye el objeto de la clase Video Feeder:: Video Feeder
 * 
 */
VideoFeeder::~VideoFeeder()
{
	cout << "Cerrando video...";
	cap.release();
	cout << " video cerrado" << endl;
}

/**
 * @brief Metodo para obtener un nuevo frame
 * 
 * @return Mat 
 */
const Mat VideoFeeder::getFrame()
{
	cap >> frame;
	return frame;
}