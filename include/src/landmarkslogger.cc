/**
 * @file landmarkslogger.cpp
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase LandmarksLogger
 * @version 0.1
 * @date 2021-06-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../landmarkslogger.h"

LandmarksLogger::LandmarksLogger()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
	string timestamp = oss.str();
	int posFin = nombreSalida.rfind(".");		 //busca el punto comenzando por el final
	string strExt = nombreSalida.substr(posFin); //obtiene la extension del archivo
	nombreSalida = nombreSalida.substr(0, posFin) + timestamp + strExt;
	fs.open(nombreSalida, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		throw MiExcepcion(ERROR_ABRIR_CONF);
	}
	fs << "datetime" << timestamp;
	fs << "feeder"
	   << "webcam";
}

LandmarksLogger::LandmarksLogger(const string &nombre, const TipoFeeder &feeder)
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
		nombreSalida = nombre.substr(0, posFin) + "_WebCam_" + timestamp + strExt;
		cout << "Comenzando a registrar en el archivo " << nombreSalida << endl;
		fs.open(nombreSalida, FileStorage::WRITE);
		if (!fs.isOpened())
		{
			throw MiExcepcion(ERROR_ABRIR_CONF);
		}
		fs << "datetime" << timestamp;
		fs << "feeder"
		   << "WEBCAM";
	}
	else if (feeder == KINECTFEEDER)
	{
		nombreSalida = nombre.substr(0, posFin) + "_Kinect_" + timestamp + strExt;
		cout << "Comenzando a registrar en el archivo " << nombreSalida << endl;
		fs.open(nombreSalida, FileStorage::WRITE);
		if (!fs.isOpened())
		{
			throw MiExcepcion(ERROR_ABRIR_CONF);
		}
		fs << "datetime" << timestamp;
		fs << "feeder"
		   << "KINECT";
	}
	else
	{
		throw MiExcepcion(ERROR_GUARDAR_VIDEO);
	}
	fs << "datos"
	   << "[";
}

LandmarksLogger::~LandmarksLogger()
{
	//Escribir tags de salida?
	cout << "Cerrando el log de landmarks...";
	fs << "]"; //Cierra el nodo de datos
	fs.release();
	cout <<"listo!"<<endl;
}

void LandmarksLogger::log(const std::vector<Landmarks> &landmarks)
{
	fs << "[";
	fs << "frame" << landmarksCont;
	fs << "landmarks"
	   << "[";
	std::vector<Landmarks>::const_iterator cii;
	std::vector<cv::Point2f>::const_iterator cipuntos;
	Landmarks l;
	for (cii = landmarks.begin(); cii != landmarks.end(); cii++)
	{
		l = *cii;
		fs << "[";
		fs << "vacio" << l.vacio;
		fs << "rotacion" << l.rotacion;
		fs << "escala" << l.escala;
		fs << "menton"
		   << "[";
		for (cipuntos = l.menton.begin(); cipuntos != l.menton.end(); cipuntos++)
		{
			fs << *cipuntos;
		}
		fs << "]";
		fs << "ojoIzq"
		   << "[";
		for (cipuntos = l.ojoIzq.begin(); cipuntos != l.ojoIzq.end(); cipuntos++)
		{
			fs << *cipuntos;
		}
		fs << "]";
		fs << "ojoDer"
		   << "[";
		for (cipuntos = l.ojoDer.begin(); cipuntos != l.ojoDer.end(); cipuntos++)
		{
			fs << *cipuntos;
		}
		fs << "]";
		fs << "cejaIzq"
		   << "[";
		for (cipuntos = l.cejaIzq.begin(); cipuntos != l.cejaIzq.end(); cipuntos++)
		{
			fs << *cipuntos;
		}
		fs << "]";
		fs << "cejaDer"
		   << "[";
		for (cipuntos = l.cejaDer.begin(); cipuntos != l.cejaDer.end(); cipuntos++)
		{
			fs << *cipuntos;
		}
		fs << "]";
		fs << "boca"
		   << "[";
		for (cipuntos = l.boca.begin(); cipuntos != l.boca.end(); cipuntos++)
		{
			fs << *cipuntos;
		}
		fs << "]";
		fs << "nariz"
		   << "[";
		for (cipuntos = l.nariz.begin(); cipuntos != l.nariz.end(); cipuntos++)
		{
			fs << *cipuntos;
		}
		fs << "]";
		fs << "]"; //cierra un landmark determinado
	}
	fs << "]"; //cierra el nodo de landmarks general
	fs << "]"; //cierra el nodo del frame
	landmarksCont++;
}