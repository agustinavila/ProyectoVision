/**
 * @file extractorlandmarks_opencv.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase concreta ExtractorLandmarksOpenCV
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../extractorlandmarks.h"
#include "../extractorlandmarks_opencv.h"

/**
 * @brief Construye un nuevo objeto de la clase ExtractorLandmarksOpenCV
 * 
 */
ExtractorLandmarksOpenCV::ExtractorLandmarksOpenCV()
{
	cout << "constructor del extractor de openCV... ";
	this->faceDetector.load("../../haarcascade_frontalface_alt2.xml");
	this->facemark = face::createFacemarkLBF();
	this->facemark->loadModel("../../lbfmodel.yaml");
	cout << "listo!" << endl;
}

/**
 * @brief Destruye el objeto de la clase ExtractorLandmarksOpenCV
 * 
 */
ExtractorLandmarksOpenCV::~ExtractorLandmarksOpenCV()
{
	this->landmarks.clear();
}

/**
 * @brief Método que analiza un frame y devuelve los landmarks de un solo rostro
 * 
 * @param frame objeto Mat a analizar 
 * @return std::vector<cv::Point2f> 
 */
const std::vector<cv::Point2f> ExtractorLandmarksOpenCV::getLandmarks(const cv::Mat &frame)
{
	vector<Rect> faces;
	Mat gray;
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	this->faceDetector.detectMultiScale(gray, faces);
	std::vector<std::vector<cv::Point2f>> landmarksVector;
	this->facemark->fit(frame, faces, landmarksVector);
	this->landmarks.clear();
	if (landmarksVector.empty())
	{
		landmarks.push_back(Point2f(1,1));
	}
	else
	{
		/* code */
	this->landmarks=landmarksVector[0];
	}
	
	return this->landmarks;
}
