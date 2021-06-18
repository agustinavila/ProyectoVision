/**
 * @file videofeeder.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../videofeeder.h"
#include <string>


VideoFeeder::VideoFeeder(string nombre)
{
	this->nombreVideo=nombre;
	cout << "Cargando video..."<<nombreVideo<<endl;
	if (!this->cap.open(nombreVideo)) //tendria que agregar la ruta hasta el directorio actual?
    {
        cout << "No se pudo abrir el video"<<endl;
     
    }
    this->cap.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
    this->cap.set(CV_CAP_PROP_FRAME_HEIGHT, 768);
}

VideoFeeder::~VideoFeeder()
{
	cout << "Cerrando video...";
	this->cap.release();
	cout << " video cerrado"<<endl;

}