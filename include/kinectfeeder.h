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

#include <iostream>
#include <opencv2/opencv.hpp>
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/packet_pipeline.h>
#include "feeder.h"

using namespace std;
using namespace cv;
using namespace libfreenect2;

/**
 * @brief Sobrecarga de la clase Feeder para proveer objetos Mat desde una kinect
 * @details Por ahora, solo obtiene imágenes de la cámara RGB.
 * Para definir el tipo de log a consola, se debe declarar
 * una variable de entorno "LIBFREENECT2_LOGGER_LEVEL".
 */
class KinectFeeder : public Feeder
{
private:
	/**
	 * @brief Mat con el fotograma actual
	 * 
	 */
	Mat frame;

	/**
	 * @brief Objeto base de la libreria freenect2
	 * 
	 */
	Freenect2 freenect2;

	/**
	 * @brief Puntero al objeto del dispositivo abierto por freenect2
	 * 
	 */
	Freenect2Device *dev = NULL;

	/**
	 * @brief Puntero al pipeline para procesar la informacion
	 * 
	 */
	PacketPipeline  *pipeline = NULL;

	/**
	 * @brief Objeto framelistener, el encargado de recibir nuevos frames
	 * 
	 */
	SyncMultiFrameListener *listener;

	/**
	 * @brief Objeto que contiene todos los frames de la kinect
	 * 
	 */
	FrameMap frames;

	public:

	/**
	 * @brief Construye un nuevo objeto de la clase KinectFeeder
	 * 
	 * @details Obtiene todos los parámetros necesarios y se encarga
	 * de inicializar la Kinect.
	 */
	KinectFeeder();

	/**
	 * @brief Destruye el objeto de la clase KinectFeeder
	 * 
	 */
	virtual ~KinectFeeder();

	/**
	 * @brief Devuelve el TipoFeeder (en este caso, KINECTFEEDER)
	 * 
	 * @return const TipoFeeder 
	 */
	virtual const TipoFeeder getFeeder() {return KINECTFEEDER;};

	/**
	 * @brief Devuelve el frame actual de la kinect
	 * 
	 * @return const Mat 
	 */
	virtual const Mat getFrame();
};

#endif // KINECTFEEDER_H
