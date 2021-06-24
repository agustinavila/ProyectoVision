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
	detector = get_frontal_face_detector();
	//el constructor deberia poder tomar como argumento el archivo entrenado
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
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
	landmarks.clear();
	cout << "listo!" << endl;
}

/**
 * @brief Método que analiza un frame y devuelve los landmarks de un solo rostro
 * 
 * @param frame objeto Mat a analizar 
 * @return std::vector<cv::Point2f> 
 */
const std::vector<Landmarks> ExtractorLandmarksDlib::getLandmarks(const cv::Mat &frame)
{
	cv_image<bgr_pixel> cimg(frame); //Convierte el Mat a un formato utilizable por dlib
	std::vector<rectangle> faces = detector(cimg);
	Landmarks l;
	landmarksSerie.clear();
	landmarks.clear();
	for (long unsigned int i = 0; i < faces.size(); ++i)
	{
	full_object_detection shape;
		shape=(pose_model(cimg, faces[i]));
		std::vector<Point2f> cara;
		for (unsigned int i = 0; i < shape.num_parts(); ++i)
		{
			cara.push_back((cv::Point2f(shape.part(i).x(), shape.part(i).y())));
		}
		landmarksSerie.push_back(cara);
	}
			cout << "menton";
	for(std::vector<Point2f>::const_iterator asd=l.menton.begin();asd!=l.menton.end();asd++){
	cout << *asd << "\t";
	}
	cout << endl;
	landmarks = parseLandmarks(landmarksSerie);
	return landmarks;
}