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

/**
 * @brief Construye un nuevo objeto de la clase ExtractorLandmarksDlib
 * 
 */
ExtractorLandmarksDlib::ExtractorLandmarksDlib()
{
	cout << "Generando el extractor de landmarks con dlib...";
	this->detector = get_frontal_face_detector();
	//el constructor deberia poder tomar como argumento el archivo entrenado
	deserialize("shape_predictor_68_face_landmarks.dat") >> this->pose_model;
	cout << " listo!" << endl;
}

/**
 * @brief Destruye el objeto de la clase ExtractorLandmarksDlib
 * 
 */
ExtractorLandmarksDlib::~ExtractorLandmarksDlib()
{
	cout << "Destruyendo el extractor de landmarks con dlib...";
	//deberia eliminar el vector?
	this->landmarks.clear();
	cout << "listo!" << endl;
}

/**
 * @brief Método que analiza un frame y devuelve los landmarks de un solo rostro
 * 
 * @param frame objeto Mat a analizar 
 * @return std::vector<cv::Point2f> 
 */
const std::vector<cv::Point2f> ExtractorLandmarksDlib::getLandmarks(const cv::Mat &frame)
{
	cv_image<bgr_pixel> cimg(frame); //Convierte el Mat a un formato utilizable por dlib
	std::vector<rectangle> faces = this->detector(cimg);
	this->landmarks.clear();
	if (!faces.empty())
	{
	full_object_detection shape(this->pose_model(cimg, faces[0]));
	for (unsigned int i = 0; i < shape.num_parts(); ++i)
	{
		this->landmarks.push_back((cv::Point2f(shape.part(i).x(), shape.part(i).y())));
	}
	} else {
	//deberia chequear que hayan puntos?
		landmarks.push_back(cv::Point2f(1,1));
	}
	return landmarks;
}