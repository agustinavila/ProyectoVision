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
	nombreDetector=nombres.front();
	cout << "Generando el extractor de landmarks con dlib...";
	detector = get_frontal_face_detector();
	//el constructor deberia poder tomar como argumento el archivo entrenado
	try
	{
	deserialize(nombreDetector) >> pose_model;
	cout << " listo!" << endl;
	}
	catch(const MiExcepcion& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}

ExtractorLandmarksDlib::~ExtractorLandmarksDlib()
{
	cout << "Destruyendo el extractor de landmarks con dlib...";
	//deberia eliminar el vector?
	landmarks.clear();
	cout << "listo!" << endl;
}

const std::vector<Landmarks> ExtractorLandmarksDlib::getLandmarks(const cv::Mat &frame)
{
	cv_image<bgr_pixel> cimg(frame); //Convierte el Mat a un formato utilizable por dlib
	std::vector<rectangle> faces = detector(cimg);
	if (faces.empty())
	{
		landmarks.clear();
		Landmarks l;
		l.vacio=1;
		landmarks.push_back(l);
	}
	else
	{
		landmarksSerie.clear();
		for (long unsigned int i = 0; i < faces.size(); ++i)
		{
			full_object_detection shape;
			shape = (pose_model(cimg, faces[i]));
			std::vector<Point2f> cara;
			for (unsigned int i = 0; i < shape.num_parts(); ++i)
			{
				cara.push_back((cv::Point2f(shape.part(i).x(), shape.part(i).y())));
			}
			landmarksSerie.push_back(cara);
			landmarks = parseLandmarks(landmarksSerie);
		}
	}
	return landmarks;
}