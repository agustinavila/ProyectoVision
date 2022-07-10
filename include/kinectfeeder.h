/**
 * @file kinectfeeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo de cabecera de la clase concreta KinectFeeder
 * @version 0.1
 * @date 2021-06-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#if !defined(KINECTFEEDER_H)
#define KINECTFEEDER_H
#ifdef KINECT_AVAILABLE

#include <iostream>

#include "feeder.h"
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/packet_pipeline.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace libfreenect2;

/**
 * @brief Sobrecarga de la clase Feeder para proveer objetos Mat desde una kinect
 * @details Por ahora, solo obtiene imágenes de la cámara RGB.
 * Para definir el tipo de log a consola, se debe declarar
 * una variable de entorno "LIBFREENECT2_LOGGER_LEVEL".
 */
class KinectFeeder : public Feeder {
private:
    Mat frame_;                       ///< Mat con el fotograma actual
    Freenect2 freenect2_;             ///< Objeto base de la libreria freenect2
    Freenect2Device* dev = NULL;      ///< Puntero al objeto del dispositivo abierto por freenect2
    PacketPipeline* pipeline = NULL;  ///< Puntero al pipeline para procesar la informacion
    SyncMultiFrameListener* listener; ///< Objeto framelistener, el encargado de recibir nuevos frames
    FrameMap frames_;                 ///< Objeto que contiene todos los frames de la kinect

public:
    KinectFeeder();

    virtual ~KinectFeeder();

    virtual const Feeder get_feeder_type() { return KINECTFEEDER; };

    virtual const Mat get_frame();
};

#endif // KINECTFEEDER_H
#endif