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
#include "../webcamfeeder.h"

#include "../feeder.h"

WebcamFeeder::WebcamFeeder(int idx_)
{
    cout << "Abriendo webcam...";
    if (!cap_.open(idx_)) {
        cout << "No se detectó camara, verifique conexion" << endl;
    } else
        cout << "webcam abierta!" << endl;
}

WebcamFeeder::~WebcamFeeder()
{
    cout << "Liberando Webcam...";
    cap_.release();
    cout << " webcam liberada" << endl;
}

const Mat WebcamFeeder::get_frame()
{
    cap_ >> frame_;
    return frame_;
}