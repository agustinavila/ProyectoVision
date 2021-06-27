/**
 * @file extractorlandmarks_dlib.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase concreta ExtractorLandmarksDlib
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(EXTRACTORLANDMARKSDLIB_H)
#define EXTRACTORLANDMARKSDLIB_H

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/opencv.h>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "extractorlandmarks.h"

using namespace dlib;
using namespace std;

/**
 * @brief Clase concreta para extraer landmarks usando dlib
 * 
 */
class ExtractorLandmarksDlib : public ExtractorLandmarks
{
private:
	/**
	 * @brief Detector de rostros
	 * 
	 */
	frontal_face_detector detector;

	/**
	 * @brief Analizador de formas generico
	 * 
	 */
	shape_predictor pose_model;

	/**
	 * @brief Landmarks "crudos", sin estructura. Podrian ser de utilidad
	 * 
	 */
	std::vector<std::vector<cv::Point2f>> landmarksSerie;

	/**
	 * @brief Landmarks obtenidos estructurados
	 * 
	 */
	std::vector<Landmarks> landmarks;

	string nombreDetector = "shape_predictor_68_face_landmarks.dat";

public:

	/**
	 * @brief Construye un nuevo objeto de la clase Extractor Landmarks Dlib
	 * 
	 */
	ExtractorLandmarksDlib(const std::vector<string> &);

	/**
	 * @brief Destruye el objeto de la clase Extractor Landmarks Dlib
	 * 
	 */
	virtual ~ExtractorLandmarksDlib();

	virtual const TipoExtractor getExtractor() {return DLIB;};

	/**
	 * @brief Obtiene y devuelve los landmarks
	 * 
	 * @return const std::vector<Landmarks> 
	 */
	virtual const std::vector<Landmarks> getLandmarks(const cv::Mat &);
};

#endif // EXTRACTORLANDMARKSDLIB_H