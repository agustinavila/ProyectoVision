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
KinectFeeder::KinectFeeder() //: listener(libfreenect2::Frame::Color)
{
	if(freenect2.enumerateDevices() == 0)
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
		this->dev = freenect2.openDevice(serial, this->pipeline);
	}
	else
	{
		this->dev = freenect2.openDevice(serial);
	}
		if (this->dev == 0)
	{
		cout << "failure opening device!" << endl;
	}
	listener = new libfreenect2::SyncMultiFrameListener(libfreenect2::Frame::Color);
	this->dev->setColorFrameListener(listener);
	this->dev->startStreams(1,0);
	cout << "device serial: " << this->dev->getSerialNumber() << endl;
	cout << "device firmware: " << this->dev->getFirmwareVersion() << endl;


}

/**
 * @brief Destruye el objeto de la clase Kinect Feeder:: Kinect Feeder
 * 
 */
KinectFeeder::~KinectFeeder()
{
	this->listener->release(frames);
	this->dev->stop();
	this->dev->close();
	std::cout << "Goodbye World!" << std::endl;
}

/**
 * @brief Obtiene y devuelve un frame de la kinect
 * 
 * @return Mat 
 */
const Mat KinectFeeder::getFrame()
{
	// Mat frameOrig;
	cout<<"3...";
	listener->waitForNewFrame(frames,10);
	libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
	// libfreenect2::Frame *rgb; //= frames[libfreenect2::Frame::Color];
	// rgb->
	 cout<<"4...";
	// listener->onNewFrame(Frame::Color, rgb);
	frame= cv::Mat(rgb->height, rgb->width, CV_8UC4, rgb->data).clone();
	 cout<<"5...";
	// cout<<"6...";
	// cv::Mat(rgb->height, rgb->width, CV_8UC4, rgb->data).copyTo(frameOrig);
	// std::vector<Mat> rgbChannels(3);
	// split(frameOrig, rgbChannels);
	// rgbChannels.pop_back();
	// merge(rgbChannels, frameOrig);
	// resize(frameOrig,frame,Size(),0.3,0.3);
	this->listener->release(frames);
	return frame;
}