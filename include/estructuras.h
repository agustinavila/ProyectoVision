/**
 * @file estructuras.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Descripcion de distintas estructuras de datos usadas por la clase
 * @version 0.1
 * @date 2021-06-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(ESTRUCTURAS_H)
#define ESTRUCTURAS_H

#include <vector>
#include <opencv2/core/types.hpp>

using namespace std;
using namespace cv;

/**
 * @brief Enumeracion de los distintos tipos de feeder posibles
 * 
 */
enum TipoFeeder
{
	WEBCAMFEEDER,
	KINECTFEEDER,
	VIDEOFEEDER
};

/**
	 * @brief Enumeracion de los distintos tipos de extractores posibles
	 * 
	 */
enum TipoExtractor
{
	DLIB,
	OPENCV
};

/**
 * @brief Enumeracion de algunos errores comunes
 * 
 */
enum miError
{
	ERROR_ABRIR_CONF,
	ERROR_FEEDER_INICIAR,
	ERROR_FEEDER_ABRIR_DISPOSITIVO,
	ERROR_VIDEOFEEDER_ABRIR_ARCHIVO,
	ERROR_EXTRACTOR_INICIAR,
	ERROR_EXTRACTOR_CARGARARCHIVO,
	ERROR_GUARDAR_VIDEO
};

/**
 * @brief Estructura para almacenar los landmarks, discriminados segun rasgo facial
 * 
 */
struct Landmarks
{
	bool vacio = 0;
	float escala = 1;
	float rotacion = 0;
	std::vector<Point2f> menton;
	std::vector<Point2f> ojoIzq;
	std::vector<Point2f> ojoDer;
	std::vector<Point2f> cejaIzq;
	std::vector<Point2f> cejaDer;
	std::vector<Point2f> boca;
	std::vector<Point2f> nariz;
	inline const bool empty() { return vacio; };
};

class MiExcepcion : public std::exception
{
public:
	MiExcepcion(const miError &_error) : error(_error){};
	miError error;
	const virtual char *what() const throw()
	{
		switch (error)
		{
		case ERROR_ABRIR_CONF:
			return "No se pudo abrir el archivo de configuracion";
			break;

		case ERROR_FEEDER_INICIAR:
			return "No se pudo iniciar el feeder";
			break;

		case ERROR_FEEDER_ABRIR_DISPOSITIVO:
			return "No se pudo abrir el dispositivo";
			break;

		case ERROR_VIDEOFEEDER_ABRIR_ARCHIVO:
			return "No se pudo abrir el archivo de video de entrada";
			break;

		case ERROR_EXTRACTOR_INICIAR:
			return "No se pudo iniciar el extractor";
			break;

		case ERROR_EXTRACTOR_CARGARARCHIVO:
			return "No se pudo cargar el archivo de conf del extractor";
			break;

		case ERROR_GUARDAR_VIDEO:
			return "No tiene sentido guardar un video de un video ya existente";
			break;

		default:
			return "Error no documentado";
			break;
		}
	}
};

#endif // ESTRUCTURAS_H
