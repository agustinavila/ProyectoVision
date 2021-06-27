/**
 * @file extractorlandmarks_dlib.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase concreta ExtractorLandmarks_dlib
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../extractorlandmarks.h"
#include "../extractorlandmarks_dlib.h"

ExtractorLandmarksDlib::ExtractorLandmarksDlib(const std::vector<string> &nombres)
{
	nombreDetector = nombres.front();
	cout << "Generando el extractor de landmarks con dlib...";
	detector = get_frontal_face_detector();
	try
	{
		deserialize(nombreDetector) >> predictorforma;
		cout << " listo!" << endl;
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
	}
}

ExtractorLandmarksDlib::~ExtractorLandmarksDlib()
{
	cout << "Destruyendo el extractor de landmarks con dlib...";
	landmarks.clear();
	cout << "listo!" << endl;
}

const std::vector<Landmarks> ExtractorLandmarksDlib::getLandmarks(const cv::Mat &frame)
{
	float escala;
	bool reescalado = 0;
	cv_image<bgr_pixel> cimg;
	if (frame.size().width > 800) //Si está en fullHD lo reescala
	{
		Mat frameRed;
		escala = 2;
		reescalado = 1;
		resize(frame, frameRed, Size(), 1 / escala, 1 / escala);
		cimg = cv_image<bgr_pixel>(frameRed); //Convierte el Mat a un formato utilizable por dlib
	}
	else
	{
		cimg = cv_image<bgr_pixel>(frame); //Convierte el Mat a un formato utilizable por dlib
	}
	std::vector<dlib::rectangle> caras = detector(cimg); //rectangulos con las caras detectadas
	if (caras.empty())
	{
		landmarks.clear();
		Landmarks l;
		l.vacio = 1; //marca la estructura como vacia y la devuelve
		landmarks.push_back(l);
	}
	else
	{
		landmarksSerie.clear();
		for (long unsigned int i = 0; i < caras.size(); ++i)
		{
			full_object_detection shape;
			shape = (predictorforma(cimg, caras[i]));
			std::vector<Point2f> cara;
			if (reescalado)
			{
				for (unsigned int i = 0; i < shape.num_parts(); ++i)
				{
					//lo convierte a un vector de vectores de landmarks para posteriormente pasarlo a la estructura
					cara.push_back((cv::Point2f(shape.part(i).x() * escala, shape.part(i).y() * escala)));
					//para optimizarse, se podría convertir directamente a la estructura
				}
			}
			else
			{
				for (unsigned int i = 0; i < shape.num_parts(); ++i) //se duplica el codigo para evitar la multiplicacion
				{
					cara.push_back((cv::Point2f(shape.part(i).x(), shape.part(i).y())));
				}
			}
			landmarksSerie.push_back(cara);
			landmarks = parseLandmarks(landmarksSerie); //se pasa del vector de vectores al vector de estructuras
		}
	}
	return landmarks;
}