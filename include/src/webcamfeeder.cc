/**
 * @file webcamfeeder.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief implementacion de la clase concreta WebcamFeeder
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
	cout << "Abriendo webcam...";
	if (!cap.open(idx))
    {
        cout << "No se detectó camara, verifique conexion"<<endl;
     
    }
    else cout << "webcam abierta!"<<endl;
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
	cap.release();
	cout << " webcam liberada"<<endl;
}

/**
 * @brief Sobrecarga del operador Feeder:getFrame(). Cuando se llama, devuelve el proximo frame de la webcam
 * 
 * @return Mat 
 */
const Mat WebcamFeeder::getFrame()
{
    cap >> frame;
    return frame;
}