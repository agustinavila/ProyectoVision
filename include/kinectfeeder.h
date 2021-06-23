/**
 * @file kinectfeeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase concreta KinectFeeder
 * @version 0.1
 * @date 2021-06-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(KINECTFEEDER_H)
#define KINECTFEEDER_H

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/packet_pipeline.h>
#include "feeder.h"

using namespace std;
using namespace cv;
using namespace libfreenect2;

/**
 * @brief Sobrecarga de la clase Feeder para proveer Mat desde una kinect
 * @bug Todavia no esta funcionando
 */
class KinectFeeder : public Feeder
{
private:
	Mat frame;
	Freenect2 freenect2;
	Freenect2Device *dev = NULL;
	PacketPipeline  *pipeline = NULL;
	SyncMultiFrameListener *listener;
	FrameMap frames;

	public:
	KinectFeeder(/* args */);
	virtual ~KinectFeeder();
	virtual const Mat getFrame();
};

#endif // KINECTFEEDER_H
