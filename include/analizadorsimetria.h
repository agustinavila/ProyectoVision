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
// clang-format off
#include <iostream>
#include <vector>

#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "feeder.h"					   //Clase abstracta Feeder
#include "webcamfeeder.h"			   //Clase concreta de Feeder para webcam
#include "videofeeder.h"			   //Clase concreta de Feeder para un video
#include "framelogger.h"			   //Clase Frame logger
#include "extractorlandmarks.h"		   //Clase abstracta de extractor de landmarks
#include "extractorlandmarks_dlib.h"   //Clase concreta del extractor usando dlib
#include "extractorlandmarks_opencv.h" //Clase concreta del extractor usando openCV
#include "analizadorlandmarks.h"	   //Clase para analizar simetria - métodos incompletos
#include "estructuras.h"			   //Estructuras, enums, excepciones
#include "landmarkslogger.h"		   //Clase para realizar el log de landmarks
// clang-format on
#ifdef KINECT_AVAILABLE
#include "kinectfeeder.h" //Clase concreta de Feeder para Kinect
#endif

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
class AnalizadorSimetria {
private:
    // clang-format off
	Feeder *ptrFeeder = NULL;					///< Puntero de la clase abstracta Feeder apuntando a la implementacion concreta
	ExtractorLandmarks *ptrExtractor = NULL;	///< Puntero de clase abstracta ExtractorLandmarks que apunta a la implementacion concreta
	FrameLogger *ptrVideoLogger = NULL;			///< Logger de fotogramas. Por el momento va registrando en un video
	LandmarksLogger *ptrLandmarksLogger = NULL; ///< Logger de landmarks. Por el momento va registrando en un archivo YAML
	AnalizadorLandmarks analizadorLandmarks;	///< Objeto que analiza y normaliza los landmarks

	FeederType tipoFeeder;		 ///< Tipo de Feeder siendo utilizado
	ExtractorType tipoExtractor; ///< Tipo de ExtractorLandmarks siendo utilizado

	std::vector<Landmarks> landmarks;	  ///< Vector de landmarks actual, "crudos" como se obtuvieron del extractor
	std::vector<Landmarks> landmarksNorm; ///< Vector de landmarks normalizado.

	FileStorage fs;															///< objeto de openCV que administra el fichero de configuracion.
	string nombreFrameLogger = "Salida.avi";								///< Nombre por defecto del archivo de salida.
	string nombreLandmarksLogger = "landmarks.yaml";						///< Nombre del archivo de salida de los landmarks
	string nombreConf = "config.yaml";										///< Nombre del archivo de configuracion.
	string nombreModeloDlib = "data/shape_predictor_68_face_landmarks.dat"; ///< Nombre del archivo del predictor utilizado por dlib
	string nombreCascadeOpenCV = "data/haarcascade_frontalface_alt2.xml";	///< Nombre del archivo del detector de rostros de openCV
	string nombreLBFOpenCV = "data/lbfmodel.yaml";							///< Nombre del archivo del detector de landmarks utilizado por openCV
	string nombreVideoFeeder = "video.avi";									///< Nombre del archivo de salida del logger de video.

	float asimetria;	 ///< Propiedad que cuantiza la asimetria de un rostro.
	Mat frame;			 ///< Propiedad de tipo cv::Mat que contiene el ultimo fotograma obtenido
	float threshold = 2; ///< Nivel de umbral de asimetria para registrar o no un rostro

	bool grabarVideoHabilitado = 0;		///< Bandera para habilitar/deshabilitar el log de video
	bool grabarLandmarksHabilitado = 0; ///< Bandera para habilitar/deshabilitar el log de landmarks
    // clang-format on
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
    AnalizadorSimetria(const string&);

    ~AnalizadorSimetria();

    Mat getFrame() { return frame; };

    const float getAsimetria() { return asimetria; };

    const std::vector<Landmarks> getLandmarks() { return landmarks; };

    const std::vector<Landmarks> getLandmarksNorm() { return landmarks; };

    FeederType get_feeder_type() { return ptrFeeder->get_feeder_type(); };

    ExtractorType getExtractor() { return ptrExtractor->get_extractor_type(); };

    /**
	 * @brief Setea tipo concreto de Feeder del analizador
	 *
	 * @details Genera un nuevo objeto de algun Feeder concreto.
	 * Si se elige el mismo tipo de feeder que el actual, no hace nada.
	 * Si no, elimina el que se estaba utilizando y genera uno nuevo.
	 */
    void setFeeder(FeederType);

    /**
	 * @brief Setea el tipo concreto de Extractor del analizador.
	 *
	 * @details Genera un nuevo objeto de un ExtractoLandmarks concreto.
	 * Si se elige el mismo tipo que el ya establecido, no hace nada.
	 * Si no, elimina el que se estaba utilizando y genera uno nuevo.
	 */
    void setExtractor(ExtractorType);

    /**
	 * @brief Setea el nombre base del video del logger.
	 *
	 * @param nombre - Nombre base del video de salida del logger
	 */
    void setNombreLog(const string& nombre) { this->nombreFrameLogger = nombre; };

    void empezarVideoLog(const FeederType&);

    void stopVideoLog();

    void empezarLandmarksLog(const FeederType&);

    void stopLandmarksLog();

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
	 * @brief Método encargado de cargar el archivo de configuración y definir las propiedades del objeto
	 *
	 * @param[in] nombreArchivo - Nombre del archivo de configuración.
	 */
    void cargarConfiguracion(const string& nombreArchivo);
};

#endif // ANALIZADORSIMETRIA_H
