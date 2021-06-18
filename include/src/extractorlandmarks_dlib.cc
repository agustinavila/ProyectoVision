/**
 * @file extractorkandmarks_dlib.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../extractorlandmarks.h"
#include "../extractorlandmarks_dlib.h"

ExtractorLandmarksDlib::ExtractorLandmarksDlib()
{
	cout << "Generando el extractor de landmarks con dlib...";
	this->detector = get_frontal_face_detector();
	//el constructor deberia poder tomar como argumento el archivo entrenado
	deserialize("shape_predictor_68_face_landmarks.dat") >> this->pose_model;
	cout << " listo!" << endl;
}

ExtractorLandmarksDlib::~ExtractorLandmarksDlib()
{
	cout << "Destruyendo el extractor de landmarks con dlib...";
	//deberia eliminar el vector?
	this->landmarks.clear();
	cout << "listo!" << endl;
}

//tengo una violacion de segmento con este metodo, revisar!!
std::vector<cv::Point2f> ExtractorLandmarksDlib::getLandmarks(cv::Mat &frame)
{
	cv_image<bgr_pixel> cimg(frame); //Convierte el Mat a un formato utilizable por dlib
	std::vector<rectangle> faces = this->detector(cimg);
	full_object_detection shape(this->pose_model(cimg, faces[0]));
	this->landmarks.clear();
	for (unsigned int i = 0; i < shape.num_parts(); ++i)
	{
		this->landmarks.push_back((cv::Point2f(shape.part(i).x(), shape.part(i).y())));
	}
	//deberia chequear que hayan puntos?
	if (this->landmarks.empty())
	{
		this->landmarks.push_back(cv::Point2f(1, 2));
	}
	return this->landmarks;
}