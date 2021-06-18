/**
 * @file feeder.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief implementacion del feeder
 * @version 0.1
 * @date 2021-06-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../feeder.h"
using namespace std;

/**
 * @brief Construye un nuevo objeto de la clase Feeder:: Feeder
 * 
 */
Feeder::Feeder()
{
	cout << "Construyendo Feeder"<< endl;
}

/**
 * @brief Destruye el objeto de la clase Feeder:: Feeder
 * 
 */
Feeder::~Feeder()
{
	cout << "Destruyendo Feeder"<<endl;
}

/**
 * @brief 
 * 
 * @return Mat 
 */
Mat Feeder::getFrame()
{
	cout << "getFrame por defecto, no hace nada"<<endl;
	return this->frame;
}


