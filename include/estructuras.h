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
 * @brief Enumeracion de algunos errores comunes para mis excepciones
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
	/**
	 * @brief Define si la estructura está vacia
	 * 
	 */
	bool vacio = 0;

	/**
	 * @brief Define la escala del rostro, en caso de aplicarse. Util en caso de normalizar landmarks
	 * 
	 */
	float escala = 1;

	/**
	 * @brief Rotación en grados del rostro. Util cuando se normalizan landmarks.
	 * 
	 */
	float rotacion = 0;

	/**
	 * @brief Vector de puntos que definen el menton/contorno del rostro
	 * 
	 * @details Consiste en 17 puntos. Comienza desde la oreja izquierda,
	 * siendo el punto 8 el del centro del mentón
	 */
	std::vector<Point2f> menton;

	/**
	 * @brief Vector de puntos que definen el ojo izquierdo
	 * 
	 * @details Consiste en 6 puntos. Comienza desde la comisura interna del ojo,
	 * recorriendo el párpado superior, y siendo la comisura externa el punto 3.
	 * Finalmente recorre el parpado inferior.
	 */
	std::vector<Point2f> ojoIzq;

	/**
	 * @brief Vector de puntos que definen el ojo Derecho
	 * 
	 * @details Consiste en 6 puntos. Comienza desde la comisura interna del ojo,
	 * recorriendo el párpado superior, y siendo la comisura externa el punto 3.
	 * Finalmente recorre el parpado inferior.
	 */
	std::vector<Point2f> ojoDer;

	/**
	 * @brief Vector de puntos que definen la ceja izquierda.
	 * 
	 * @details Consiste en 5 puntos. Comienza desde el punto más central
	 * de la ceja, y su último punto es el mas alejado del centro.
	 */
	std::vector<Point2f> cejaIzq;

	/**
	 * @brief Vector de puntos que definen la ceja Derecha.
	 * 
	 * @details Consiste en 5 puntos. Comienza desde el punto más central
	 * de la ceja, y su último punto es el mas alejado del centro.
	 */
	std::vector<Point2f> cejaDer;

	/**
	 * @brief Vector de puntos que definen la boca.
	 * 
	 * @details Consiste en 18 puntos. Comienza desde la comisura externa de
	 * los labios, recorriendo el borde externo del labio comenzando por la parte superior.
	 * El punto 0 corresponde a la comisura externa izquierda,
	 * el punto 3 corresponde al punto central del borde externo superior,
	 * el punto 6 corresponde a la comisura externa derecha,
	 * el punto 9 corresponde al punto central del borde externo inferior.
	 * 
	 * El punto 10 corresponde a la comisura interna izquierda,
	 * el punto 12 corresponde al punto central del borde interno superior,
	 * el punto 14 corresponde a la comisura interna derecha,
	 * el punto 16 corresponde al punto central del borde interno inferior.
	 * 
	 */
	std::vector<Point2f> boca;

	/**
	 * @brief Vector de puntos que delimitan la nariz.
	 * 
	 * @details Consiste en 9 puntos. El punto 0 corresponde al punto superior del tabique,
	 * el punto 3 corresponde al último punto del tabique.
	 * El punto 4 corresponde al extremo izquierdo de la base de la nariz,
	 * el punto 6 corresponde a la punta de la nariz,
	 * y el punto 8 corresponde al extremo derecho de la base de la nariz
	 * 
	 */
	std::vector<Point2f> nariz;

	/**
	 * @brief Método para definir si la estructura está vacía.
	 * 
	 * @details No se si tiene sentido, ya que se puede consultar directamente a la propiedad vacio.
	 * 
	 * @return true 
	 * @return false 
	 */
	inline const bool empty() { return vacio; };
};

/**
 * @brief Clase de excepciones personal heredando de las excepciones estandar
 * 
 * @details Devuelve un texto de acuerdo al tipo de error provisto, según TipoError.
 */
class MiExcepcion : public std::exception
{
public:
	MiExcepcion(const miError &_error) : error(_error){};
	miError error;

	/**
	 * @brief Devuelve un texto según el tipo de error que se le pase.
	 * 
	 * @return const char* 
	 */
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
