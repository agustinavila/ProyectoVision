/**
 * @file extractorlandmarks_opencv.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase concreta ExtractorLandmarksOpenCV
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(EXTRACTORLANDMARKS_OPENCV_H)
#define EXTRACTORLANDMARKS_OPENCV_H

#include <vector>
#include <iostream>
//#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/face.hpp>
// #include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "extractorlandmarks.h"
#include "estructuras.h"

using namespace std;
using namespace cv;
//using namespace cv::face;

/**
 * @brief Clase concreta para extraer landmarks utilizando openCV
 * 
 */
class ExtractorLandmarksOpenCV : public ExtractorLandmarks
{
private:

	/**
	 * @brief Objeto Facemark de openCV
	 * 
	 */
	Ptr<face::Facemark> facemark;
	
	/**
	 * @brief Detector de rostros provisto por openCV
	 * 
	 */
	CascadeClassifier faceDetector;
	
	/**
	 * @brief Vector de vectores de puntos, como los provee openCV
	 * 
	 */
	std::vector<std::vector<cv::Point2f>> landmarksSerie;
	
	/**
	 * @brief Vector de Landmarks obtenido del frame
	 * 
	 */
	std::vector<Landmarks> landmarks;
public:
	
	/**
	 * @brief Construye un nuevo objeto de la clase Extractor Landmarks OpenCV
	 * 
	 */
	ExtractorLandmarksOpenCV();
	
	/**
	 * @brief Destruye el objeto de la clase Extractor Landmarks OpenCV
	 * 
	 */
	virtual ~ExtractorLandmarksOpenCV();
	
	/**
	 * @brief Obtiene los landmarks del frame
	 * 
	 * @return const std::vector<Landmarks> 
	 */
	virtual const std::vector<Landmarks> getLandmarks(const cv::Mat &);
};

#endif // EXTRACTORLANDMARKS_OPENCV_H
