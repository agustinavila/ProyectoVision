/**
 * @file kinectfeeder.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase concreta KinectFeeder
 * @version 0.1
 * @date 2021-06-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../feeder.h"
#include "../kinectfeeder.h"

/**
 * @brief Construye un nuevo objeto de la clase Kinect Feeder:: Kinect Feeder
 * 
 */
KinectFeeder::KinectFeeder()
{
	if(this->freenect2.enumerateDevices() == 0)
	{
		std::cout << "no device connected!" << std::endl;
	}
	string serial = this->freenect2.getDefaultDeviceSerialNumber();
	std::cout << "SERIAL: " << serial << std::endl;
	#ifdef LIBFREENECT2_WITH_OPENCL_SUPPORT
		if (!this->pipeline)
			this->pipeline = new OpenCLPacketPipeline();
#else
		std::cout << "OpenCL pipeline is not supported!" << endl;
#endif

	if (this->pipeline)
	{
		this->dev = this->freenect2.openDevice(serial, this->pipeline);
	}
	else
	{
		this->dev = this->freenect2.openDevice(serial);
	}
		if (this->dev == 0)
	{
		cout << "failure opening device!" << endl;
	}
	this->listener=libfreenect2::SyncMultiFrameListener(Frame::Color);
	this->dev->setColorFrameListener(this->listener);
	this->dev->start();
	cout << "device serial: " << this->dev->getSerialNumber() << endl;
	cout << "device firmware: " << this->dev->getFirmwareVersion() << endl;


}

/**
 * @brief Destruye el objeto de la clase Kinect Feeder:: Kinect Feeder
 * 
 */
KinectFeeder::~KinectFeeder()
{
	this->listener.release(this->frames);
	dev->stop();
	dev->close();
	std::cout << "Goodbye World!" << std::endl;
}

/**
 * @brief Obtiene y devuelve un frame de la kinect
 * 
 * @return Mat 
 */
const Mat KinectFeeder::getFrame()
{
	Mat frame;
	this->listener.waitForNewFrame(frames);
	Frame *rgb = frames[Frame::Color];
	cv::Mat(rgb->height, rgb->width, CV_8UC4, rgb->data).copyTo(frame);
	return frame;
}