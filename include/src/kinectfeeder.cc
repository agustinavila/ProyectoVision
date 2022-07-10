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
#ifdef KINECT_AVAILABLE
#include "../feeder.h"
#include "../kinectfeeder.h"

KinectFeeder::KinectFeeder()
{
	if(freenect2.enumerateDevices() == 0)
	{
		std::cout << "No hay ninguna Kinect conectada!" << std::endl;
		throw MiExcepcion(ERROR_FEEDER_ABRIR_DISPOSITIVO);
	}
	string serial = this->freenect2.getDefaultDeviceSerialNumber();
	std::cout << "SERIAL: " << serial << std::endl;
	#ifdef LIBFREENECT2_WITH_OPENCL_SUPPORT
		if (!this->pipeline)
			this->pipeline = new OpenCLPacketPipeline();
#else
		std::cout << "el pipeline OpenCL no está soportado" << endl;
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
		cout << "No se pudo abrir la kinect :(" << endl;
	}
	listener = new libfreenect2::SyncMultiFrameListener(libfreenect2::Frame::Color);
	this->dev->setColorFrameListener(listener);
	this->dev->startStreams(1,0);
	cout << "kinect serial: " << this->dev->getSerialNumber() << endl;
	cout << "kinect firmware: " << this->dev->getFirmwareVersion() << endl;


}

KinectFeeder::~KinectFeeder()
{
	this->listener->release(frames);
	this->dev->stop();
	this->dev->close();
	std::cout << "Cerrando la kinect" << std::endl;
}

const Mat KinectFeeder::getFrame()
{
	Mat frameOrig;
	listener->waitForNewFrame(frames,10);
	libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
	frame= cv::Mat(rgb->height, rgb->width, CV_8UC4, rgb->data).clone();
	this->listener->release(frames);
	//Por defecto la libreria devuelve un mat de 4 canales
	//para simplificar el procesamiento, se el elimina ese cuarto canal vacio.
	std::vector<Mat> rgbChannels(4);
	split(frame, rgbChannels);
	rgbChannels.pop_back();
	merge(rgbChannels, frame);
	return frame;
}
#endif