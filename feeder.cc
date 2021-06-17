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
#include "feeder.h"
using namespace std;

Feeder::Feeder()
{
	cout << "Construyendo Feeder"<< endl;
}

Feeder::~Feeder()
{
	cout << "Destruyendo Feeder"<<endl;
}

Mat Feeder::getFrame()
{
	cout << "getFrame por defecto, no hace nada"<<endl;
	return this->frame;
}


