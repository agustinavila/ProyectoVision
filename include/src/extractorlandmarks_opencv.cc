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
	faceDetector.load("../../haarcascade_frontalface_alt2.xml");
	facemark = face::createFacemarkLBF();
	facemark->loadModel("../../lbfmodel.yaml");
	cout << "listo!" << endl;
}

/**
 * @brief Destruye el objeto de la clase ExtractorLandmarksOpenCV
 * 
 */
ExtractorLandmarksOpenCV::~ExtractorLandmarksOpenCV()
{
	landmarks.clear();
}

/**
 * @brief Método que analiza un frame y devuelve los landmarks de un solo rostro
 * 
 * @param frame objeto Mat a analizar 
 * @return std::vector<cv::Point2f> 
 */
const std::vector<Landmarks> ExtractorLandmarksOpenCV::getLandmarks(const cv::Mat &frame)
{
	vector<Rect> faces;
	Mat gray;
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	faceDetector.detectMultiScale(gray, faces);
	facemark->fit(frame, faces, landmarksSerie);
	landmarks=parseLandmarks(landmarksSerie);
	return landmarks;
}
