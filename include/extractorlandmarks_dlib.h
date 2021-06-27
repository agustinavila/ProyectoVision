/**
 * @file extractorlandmarks_dlib.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo de cabecera de la clase concreta ExtractorLandmarksDlib
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(EXTRACTORLANDMARKSDLIB_H)
#define EXTRACTORLANDMARKSDLIB_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/opencv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include "extractorlandmarks.h"

using namespace dlib;
using namespace std;

/**
 * @brief Implementación concreta de la clase abstracta ExtractorLandmarks usando dlib
 * 
 * @details Implementación de un extractor de landmarks utilizando dlib. Se implementó utilizando
 * como referencia el código de ejemplo provisto por la libreria.
 */
class ExtractorLandmarksDlib : public ExtractorLandmarks
{
private:
	/**
	 * @brief Detector de rostros de dlib
	 * 
	 */
	frontal_face_detector detector;

	/**
	 * @brief Analizador de formas generico al que se le provee
	 * 
	 */
	shape_predictor predictorforma;

	/**
	 * @brief Landmarks "crudos", sin estructura.
	 * 
	 * @details Son los dato crudos, un vector de vectores. Podrían ser de utilidad.
	 */
	std::vector<std::vector<cv::Point2f>> landmarksSerie;

	/**
	 * @brief Landmarks obtenidos ya estructurados
	 * 
	 * @details son los mismos landmarks de landmarksSerie, solo que pasado a una estructura.
	 */
	std::vector<Landmarks> landmarks;

	/**
	 * @brief Nombre del archivo con el predictor de formas.
	 * 
	 */
	string nombreDetector = "shape_predictor_68_face_landmarks.dat";

public:
	/**
	 * @brief Construye un nuevo objeto de la clase ExtractorLandmarksDlib
	 * 
	 * @details Se le debe proveer el nombre del archivo del detector.
	 */
	ExtractorLandmarksDlib(const std::vector<string> &);

	/**
	 * @brief Destruye el objeto de la clase ExtractorLandmarksDlib
	 * 
	 */
	virtual ~ExtractorLandmarksDlib();

	/**
	 * @brief Devuelve el TipoExtractor, en este caso DLIB 
	 * 
	 * @return const TipoExtractor 
	 */
	virtual const TipoExtractor getExtractor() { return DLIB; };

	/**
	 * @brief Obtiene y devuelve los landmarks
	 * 
	 * @param frame - Frame a analizar.
	 * 
	 * @return const std::vector<Landmarks> 
	 */
	virtual const std::vector<Landmarks> getLandmarks(const cv::Mat &);
};

#endif // EXTRACTORLANDMARKSDLIB_H