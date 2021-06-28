/**
 * @file framelogger.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase FrameLogger
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../framelogger.h"

FrameLogger::FrameLogger()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
	string timestamp = oss.str();
	int posFin = nombreVideo.rfind(".");		//busca el punto comenzando por el final
	string strExt = nombreVideo.substr(posFin); //obtiene la extension del archivo
	nombreVideo = nombreVideo.substr(0, posFin) + timestamp + strExt;
	video.open(nombreVideo, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(640, 480));
}

FrameLogger::FrameLogger(const string &nombre, const TipoFeeder &feeder)
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
	string timestamp = oss.str();
	int posFin = nombre.rfind(".");		   //busca el punto comenzando por el final
	string strExt = nombre.substr(posFin); //obtiene la extension del archivo
	if (feeder == WEBCAMFEEDER)
	{
		nombreVideo = nombre.substr(0, posFin) + "_WebCam_" + timestamp + strExt;
		cout << "Comenzando a grabar en el archivo " << nombreVideo << endl;
		video.open(nombreVideo, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(640, 480));
	}
	else if (feeder == KINECTFEEDER)
	{
		nombreVideo = nombre.substr(0, posFin) + "_Kinect_" + timestamp + strExt;
		cout << "Comenzando a grabar en el archivo " << nombreVideo << endl;
		video.open(nombreVideo, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(1920, 1080));
	}
	else if (feeder == VIDEOFEEDER)
	{
		nombreVideo = nombre.substr(0, posFin) + "_Video_" + timestamp + strExt;
		cout << "Comenzando a grabar en el archivo "<<nombreVideo<<endl;
		video.open(nombreVideo, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(640,480));
	}
	else
	{
		throw MiExcepcion(ERROR_GUARDAR_VIDEO);
	}
}

FrameLogger::~FrameLogger()
{
	cout << "Cerrando video de log...";
	video.release();
	cout << "Video cerrado!" << endl;
}

void FrameLogger::log(const Mat &frame)
{
	frames++; //Solo en caso de guardar secuencia de imagenes
	video.write(frame);
}