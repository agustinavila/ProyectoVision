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

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "extractorlandmarks.h"
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/opencv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace dlib;
using namespace std;

/**
 * @brief Implementación concreta de la clase abstracta ExtractorLandmarks usando dlib
 *
 * @details Implementación de un extractor de landmarks utilizando dlib. Se implementó utilizando
 * como referencia el código de ejemplo provisto por la libreria.
 */
class ExtractorLandmarksDlib : public ExtractorLandmarks {
private:
    frontal_face_detector dlib_face_detector_; ///< Detector de rostros de dlib
    shape_predictor shape_predictor_;          ///< Analizador de formas generico al que se le provee

    string detector_filename_ =
            "shape_predictor_68_face_landmarks.dat"; ///< Nombre del archivo con el predictor de formas.

    /**
	 * @brief Landmarks "crudos", sin estructura.
	 *
	 * @details Son los dato crudos, un vector de vectores. Podrían ser de utilidad.
	 */
    std::vector<std::vector<cv::Point2f>> landmarks_serie_;

    /**
	 * @brief Landmarks obtenidos ya estructurados
	 *
	 * @details son los mismos landmarks de landmarksSerie, solo que pasado a una estructura.
	 */
    std::vector<Landmarks> landmarks_;

public:
    /**
	 * @brief Construye un nuevo objeto de la clase ExtractorLandmarksDlib
	 *
	 * @details Se le debe proveer el nombre del archivo del detector.
	 */
    ExtractorLandmarksDlib(const std::vector<string>&);

    /**
	 * @brief Destruye el objeto de la clase ExtractorLandmarksDlib
	 */
    virtual ~ExtractorLandmarksDlib();

    virtual const ExtractorType get_extractor_type() { return DLIB; };

    virtual const std::vector<Landmarks> get_landmarks(const cv::Mat& frame);
};

#endif // EXTRACTORLANDMARKSDLIB_H