/**
 * @file webcamfeeder.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../feeder.h"
#include "../webcamfeeder.h"

/**
 * @brief Construye un nuevo objeto de la clase Webcam Feeder:: Webcam Feeder
 * @details Puede tomar como parametro \p idx, que es el indice de la webcam.
 * @param idx 
 */
WebcamFeeder::WebcamFeeder(int idx)
{
	cout << "Abriendo webcam..."<<endl;
	if (!this->cap.open(idx))
    {
        cout << "No se detectó camara, verifique conexion"<<endl;
     
    }
    // this->cap.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
    // this->cap.set(CV_CAP_PROP_FRAME_HEIGHT, 768);
}

/**
 * @brief Destruye el objeto de la clase Webcam Feeder:: Webcam Feeder
 * 
 */
WebcamFeeder::~WebcamFeeder()
{
	cout << "Liberando Webcam...";
	this->cap.release();
	cout << " webcam liberada"<<endl;
}

/**
 * @brief Sobrecarga del operador Feeder:getFrame(). Cuando se llama, devuelve el proximo frame de la webcam
 * 
 * @return Mat 
 */
Mat WebcamFeeder::getFrame()
{
    this->cap >> this->frame;
    return this->frame;
}