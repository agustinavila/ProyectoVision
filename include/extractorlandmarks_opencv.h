/**
 * @file extractorlandmarks_opencv.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo de cabecera de la clase concreta ExtractorLandmarksOpenCV
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
#include <opencv2/core/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
#include "extractorlandmarks.h"
#include "estructuras.h"

using namespace std;
using namespace cv;
//using namespace cv::face;

/**
 * @brief Clase concreta  derivada de ExtractorLandmarks para extraer landmarks utilizando openCV
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
	 * @brief Detector de rostros de openCV
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
	 * @details Se obtiene parseando el vector de vectores landmarksSerie, y se convierte
	 * en un vector de Landmarks
	 */
	std::vector<Landmarks> landmarks;

	/**
	 * @brief Nombre del archivo utilizado por openCV para detectar el rostro
	 * 
	 */
	string nombreCascade;

	/**
	 * @brief Nombre del archivo utilizado por openCV para detectar los puntos de interes
	 * 
	 */
	string nombreLBF;

public:
	/**
	 * @brief Construye un nuevo objeto de la clase ExtractorLandmarksOpenCV
	 * 
	 * @details Se le debe proveer un vector con los nombres de los archivos a utilizar.
	 * 
	 * @param nombres - Vector de strings con los nombres de los archivos necesarios
	 */
	ExtractorLandmarksOpenCV(const std::vector<string> &);

	/**
	 * @brief Destruye el objeto de la clase ExtractorLandmarksOpenCV
	 * 
	 */
	virtual ~ExtractorLandmarksOpenCV();

	/**
	 * @brief Devuelve el parametro TipoExtractor (en este caso OPENCV)
	 * 
	 * @return const TipoExtractor 
	 */
	virtual const TipoExtractor getExtractor() { return OPENCV; };

	
	/**
	 * @brief Método que analiza un frame y devuelve los landmarks de un solo rostro
	 * 
	 * @param frame objeto Mat a analizar
	 *  
	 * @return std::vector<cv::Point2f> 
	 */
	virtual const std::vector<Landmarks> getLandmarks(const cv::Mat &);
};

#endif // EXTRACTORLANDMARKS_OPENCV_H
