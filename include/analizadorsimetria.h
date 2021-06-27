/**
 * @file analizadorsimetria.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Clase maestra del proyecto
 * @version 0.1
 * @date 2021-06-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(ANALIZADORSIMETRIA_H)
#define ANALIZADORSIMETRIA_H

#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/video.hpp>
#include <opencv2/core/core.hpp>
#include "feeder.h"
#include "webcamfeeder.h"
#include "kinectfeeder.h"
#include "videofeeder.h"
#include "framelogger.h"
#include "extractorlandmarks.h"
#include "extractorlandmarks_dlib.h"
#include "extractorlandmarks_opencv.h"
#include "analizadorlandmarks.h"
#include "estructuras.h"

using namespace std;
using namespace cv;




/**
 * @brief Clase principal del programa
 * 
 */
class AnalizadorSimetria
{
private:
	/**
	 * @brief Propiedad que cuantiza la asimetria de un rostro
	 * 
	 */
	float asimetria;

	/**
	 * @brief Propiedad de tipo Mat que contiene el ultimo fotograma obtenido
	 * 
	 */
	Mat frame;

	/**
	 * @brief Puntero de la clase abstracta Feeder apuntando a la implementacion concreta
	 * 
	 */
	Feeder *ptrFeeder = NULL;

	/**
	 * @brief Puntero de clase abstracta ExtractorLandmarks que apunta a la implementacion concreta
	 * 
	 */
	ExtractorLandmarks *ptrExtractor = NULL;

	/**
	 * @brief Logger de fotogramas. Por el momento va registrando en un video
	 * 
	 */
	FrameLogger *ptrLogger = NULL;

	/**
	 * @brief Objeto que analiza y normaliza los landmarks
	 * 
	 */
	AnalizadorLandmarks analizadorLandmarks;

	/**
	 * @brief Vector de landmarks actual, "crudos" como se obtuvieron del extractor
	 * 
	 */
	std::vector<Landmarks> landmarks;

	/**
	 * @brief Vector de landmarks normalizado
	 * 
	 */
	std::vector<Landmarks> landmarksNorm;
	string nombreFrameLogger;
	FileStorage fs;
	string nombreConf = "config.yaml";
	string nombreModeloDlib = "shape_predictor_68_face_landmarks.dat";
	string nombreCascadeOpenCV = "haarcascade_frontalface_alt2.xml";
	string nombreLBFOpenCV = "lbfmodel.yaml";
	string nombreVideoFeeder = "video.avi";
	float threshold=2;
	TipoFeeder tipoFeeder;
	bool grabarHabilitado=0;


public:

	/**
	 * @brief Construye un nuevo objeto de la clase Analizador Simetria
	 * 
	 */
	// AnalizadorSimetria(Feeder *, ExtractorLandmarks *);

	/**
	 * @brief Construye un nuevo objeto de la clase Analizador Simetria
	 * 
	 */
	AnalizadorSimetria();

	AnalizadorSimetria(string &);

	/**
	 * @brief Destruye el objeto de la clase Analizador Simetria
	 * 
	 */
	~AnalizadorSimetria();

	/**
	 * @brief Devuelve la propiedad Frame 
	 * 
	 * @return Mat 
	 */
	Mat getFrame() { return frame; };

	/**
	 * @brief Devuelve la propiedad Asimetria 
	 * 
	 * @return const float 
	 */
	const float getAsimetria() { return asimetria; };

	/**
	 * @brief Devuelve la propiedad Landmarks 
	 * 
	 * @return const std::vector<Landmarks> 
	 */
	const std::vector<Landmarks> getLandmarks() { return landmarks; };
	
	/**
	 * @brief Devuelve la propiedad Landmarks Norm 
	 * 
	 * @return const std::vector<Landmarks> 
	 */
	const std::vector<Landmarks> getLandmarksNorm() { return landmarks; };
	
	/**
	 * @brief Setea el objeto Feeder del analizador
	 * 
	 */
	void setFeeder(TipoFeeder);
	
	TipoFeeder getFeeder() {return ptrFeeder->getFeeder();};

	/**
	 * @brief Setea el tipo concreto de Extractor del analizador
	 * 
	 */
	void setExtractor(TipoExtractor);
	
	TipoExtractor getExtractor() {return ptrExtractor->getExtractor();};
	
	/**
	 * @brief Funcion principal a llamar para operar la clase
	 * 
	 * @return Mat 
	 */
	Mat step();

	void empezarLog(const TipoFeeder&);
	void stopLog();
	void setNombreLog(const string &nombre) {this->nombreFrameLogger=nombre;};
	void cargarConfiguracion(const string &);
};

#endif // ANALIZADORSIMETRIA_H
