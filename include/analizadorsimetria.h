/**
 * @file analizadorsimetria.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Archivo de cabecera de la clase base del proyecto
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
#include <opencv2/core/core.hpp>
#include "feeder.h"					   //Clase abstracta Feeder
#include "webcamfeeder.h"			   //Clase concreta de Feeder para webcam
#include "kinectfeeder.h"			   //Clase concreta de Feeder para Kinect
#include "videofeeder.h"			   //Clase concreta de Feeder para un video
#include "framelogger.h"			   //Clase Frame logger
#include "extractorlandmarks.h"		   //Clase abstracta de extractor de landmarks
#include "extractorlandmarks_dlib.h"   //Clase concreta del extractor usando dlib
#include "extractorlandmarks_opencv.h" //Clase concreta del extractor usando openCV
#include "analizadorlandmarks.h"	   //Clase para analizar simetria - métodos incompletos
#include "estructuras.h"			   //Estructuras, enums, excepciones

using namespace std;
using namespace cv;

/**
 * @brief Clase principal del programa. 
 * @details Se construye pasándole un archivo de configuración (por defecto "config.yaml"),
 * el cual es encargado de elegir el tipo de feeder y extractor a utilizar. La clase además provee
 * distintos métodos para seleccionar el tipo de feeder o extractor a utilizar.
 * Además, permite iniciar o detener el registro en video o de landmarks.
 * Una vez inicializada, su método principal es step(), el cual devuelve un nuevo frame,
 * y si está habilitado el log y el extractor de landmarks, agrega el fotograma al video
 * y analiza los nuevos landmarks.
 */
class AnalizadorSimetria
{
private:
	/**
	 * @brief Propiedad que cuantiza la asimetria de un rostro.
	 * 
	 */
	float asimetria;

	/**
	 * @brief Propiedad de tipo cv::Mat que contiene el ultimo fotograma obtenido
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
	 * @brief Vector de landmarks normalizado.
	 * 
	 */
	std::vector<Landmarks> landmarksNorm;

	/**
	 * @brief objeto de openCV que administra el fichero de configuracion.
	 * 
	 */
	FileStorage fs;

	/**
	 * @brief Nombre por defecto del archivo de salida.
	 * 
	 */
	string nombreFrameLogger = "Salida.avi";

	/**
	 * @brief Nombre del archivo de configuracion.
	 * 
	 */
	string nombreConf = "config.yaml";

	/**
	 * @brief Nombre del archivo del predictor utilizado por dlib
	 * 
	 */
	string nombreModeloDlib = "data/shape_predictor_68_face_landmarks.dat";

	/**
	 * @brief Nombre del archivo del detector de rostros de openCV
	 * 
	 */
	string nombreCascadeOpenCV = "data/haarcascade_frontalface_alt2.xml";

	/**
	 * @brief Nombre del archivo del detector de landmarks utilizado por openCV
	 * 
	 */
	string nombreLBFOpenCV = "data/lbfmodel.yaml";

	/**
	 * @brief Nombre del archivo de salida del logger de video.
	 * 
	 */
	string nombreVideoFeeder = "video.avi";

	/**
	 * @brief Nivel de umbral de asimetria para registrar o no un rostro 
	 * 
	 */
	float threshold = 2;

	/**
	 * @brief Tipo de feeder siendo utilizado
	 * 
	 */
	TipoFeeder tipoFeeder;

	/**
	 * @brief Bandera para habilitar/deshabilitar el log de video
	 * 
	 */
	bool grabarHabilitado = 0;

public:
	/**
	 * @brief Construye un nuevo objeto de la clase Analizador Simetria. Utiliza valores por defecto
	 * 
	 */
	AnalizadorSimetria();

	/**
	 * @brief Construye un nuevo objeto de la clase Analizador Simetria, proveyendole un archivo de configuración
 	* 
 	*/
	AnalizadorSimetria(string &);

	/**
	 * @brief Destruye el objeto de la clase Analizador Simetria
	 * 
	 */
	~AnalizadorSimetria();

	/**
	 * @brief Devuelve el último frame obtenido 
	 * 
	 * @return Mat - objeto del tipo cv::Mat conteniendo el fotograma actual
	 */
	Mat getFrame() { return frame; };

	/**
	 * @brief Devuelve la última asimetria calculada 
	 * 
	 * @return const float - Asimetria calculada
	 */
	const float getAsimetria() { return asimetria; };

	/**
	 * @brief Devuelve el ultimo vector de Landmarks calculado
	 * 
	 * @return const std::vector<Landmarks> - Vector de Landmarks
	 */
	const std::vector<Landmarks> getLandmarks() { return landmarks; };

	/**
	 * @brief Devuelve el último vector de Landmarks normalizado
	 * 
	 * @return const std::vector<Landmarks> - Vector de Landmarks normalizado 
	 */
	const std::vector<Landmarks> getLandmarksNorm() { return landmarks; };

	/**
	 * @brief Setea tipo concreto de Feeder del analizador
	 * 
	 * @details Genera un nuevo objeto de algun Feeder concreto.
	 * Si se elige el mismo tipo de feeder que el actual, no hace nada.
	 * Si no, elimina el que se estaba utilizando y genera uno nuevo.
	 */
	void setFeeder(TipoFeeder);

	/**
	 * @brief Devuelve el tipo concreto de Feeder utilizado
	 * 
	 * @return TipoFeeder 
	 */
	TipoFeeder getFeeder() { return ptrFeeder->getFeeder(); };

	/**
	 * @brief Setea el tipo concreto de Extractor del analizador.
	 * 
	 * @details Genera un nuevo objeto de un ExtractoLandmarks concreto.
	 * Si se elige el mismo tipo que el ya establecido, no hace nada.
	 * Si no, elimina el que se estaba utilizando y genera uno nuevo.
	 */
	void setExtractor(TipoExtractor);

	/**
	 * @brief Devuelve el tipo de  ExtractorLandmarks utilizado. 
	 * 
	 * @return TipoExtractor 
	 */
	TipoExtractor getExtractor() { return ptrExtractor->getExtractor(); };

	/**
	 * @brief Método principal a llamar para operar la clase.
	 * 
	 * @details Este método es el encargado de actualizar toda la clase.
	 * Si hay un feeder definido, intenta obtener un nuevo frame.
	 * Si el log está habilitado, le envia el frame al logger.
	 * Si hay un  extractor de landmarks, obtiene los landmarks.
	 * En caso de obtener un rostro, actualiza las propiedades de la clase
	 * y finalmente calcula la asimetría. 
	 * 
	 * @return Mat 
	 */
	Mat step();

	/**
	 * @brief Método para invocar un FrameLogger y comenzar la grabación.
	 * 
	 */
	void empezarLog(const TipoFeeder &);

	/**
	 * @brief Método para detener la grabación del FrameLogger
	 * 
	 */
	void stopLog();

	/**
	 * @brief Setea el nombre base del video del logger.
	 * 
	 * @param nombre - Nombre base del video de salida del logger
	 */
	void setNombreLog(const string &nombre) { this->nombreFrameLogger = nombre; };

	/**
	 * @brief Método encargado de cargar el archivo de configuración y definir las propiedades del objeto
	 * 
	 * @param nombreConf - Nombre del archivo de configuración.
	 */
	void cargarConfiguracion(const string &);
};

#endif // ANALIZADORSIMETRIA_H
