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

WebcamFeeder::WebcamFeeder(int idx)
{
    cout << "Abriendo webcam...";
    if (!cap.open(idx))
    {
        cout << "No se detectó camara, verifique conexion" << endl;
    }
    else
        cout << "webcam abierta!" << endl;
}

WebcamFeeder::~WebcamFeeder()
{
    cout << "Liberando Webcam...";
    cap.release();
    cout << " webcam liberada" << endl;
}

const Mat WebcamFeeder::getFrame()
{
    cap >> frame;
    return frame;
}