/**
 * @file analizadorsimetria.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-06-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../analizadorsimetria.h"

// AnalizadorSimetria::AnalizadorSimetria(Feeder *feeder = new WebcamFeeder, ExtractorLandmarks *extractor = new ExtractorLandmarksDlib) : ptrFeeder(feeder), ptrExtractor(extractor)
// {
// 	cout << "En el constructor del objeto de analizadorSimetria pasandole punteros a objetos" << endl;
// }

AnalizadorSimetria::AnalizadorSimetria()
{
	cout << "Construyendo objeto de Analizador Simetria..." << endl;
	cargarConfiguracion(nombreConf);
	try
	{
		this->setFeeder(tipoFeeder);
		this->setExtractor(tipoExtractor);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
		this->setFeeder(WEBCAMFEEDER);
		this->setExtractor(OPENCV);
	}
}

AnalizadorSimetria::AnalizadorSimetria(const string &nombrearchivo)
{
	cout << "En el constructor del objeto de analizadorSimetria con un archivo de configuracion" << endl;
	nombreConf = nombrearchivo;
	cargarConfiguracion(nombreConf);
	try
	{
		this->setFeeder(tipoFeeder);
		this->setExtractor(tipoExtractor);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
		this->setFeeder(WEBCAMFEEDER);
		this->setExtractor(OPENCV);
	}
}

AnalizadorSimetria::~AnalizadorSimetria()
{
	delete this->ptrVideoLogger;
	delete this->ptrLandmarksLogger;
	delete this->ptrExtractor;
	delete this->ptrFeeder;

	cout << "destructor del analizador de simetria" << endl;
}

Mat AnalizadorSimetria::step()
{
	if (ptrFeeder != NULL)
	{
		frame = ptrFeeder->getFrame();
	}
	if (ptrVideoLogger != NULL)
	{
		ptrVideoLogger->log(frame); // Guarda frames, segun parametros podria desactivarse o no
	}
	if (ptrExtractor != NULL)
	{
		landmarks = ptrExtractor->getLandmarks(frame);
		if (ptrLandmarksLogger != NULL)
		{
			ptrLandmarksLogger->log(landmarks); // Guarda frames, segun parametros podria desactivarse o no
		}
		if (!landmarks.front().vacio)
		{
			analizadorLandmarks.setLandmarks(landmarks);
			analizadorLandmarks.normalizarLandmarks();
			asimetria = analizadorLandmarks.calcularAsimetria();
		}
		else
		{
			//	cout << "no se detecto ninguna cara" << endl;
		}
	}
	return frame;
}

void AnalizadorSimetria::setExtractor(TipoExtractor extractor_)
{
	tipoExtractor = extractor_;
	if (this->ptrExtractor != NULL)
	{
		if (tipoExtractor != ptrExtractor->getExtractor())
		{
			delete this->ptrExtractor;
		}
		else
		{
			cout << "Ya se esta utilizando el extractor solicitado" << endl;
			return;
		}
	}
	try
	{
		if (tipoExtractor == DLIB)
		{
			this->ptrExtractor = new ExtractorLandmarksDlib(std::vector<string>{nombreModeloDlib});
			if (grabarLandmarksHabilitado)
			{
				empezarLandmarksLog(tipoFeeder);
			}
		}
		else if (tipoExtractor == OPENCV)
		{
			this->ptrExtractor = new ExtractorLandmarksOpenCV(std::vector<string>{nombreCascadeOpenCV, nombreLBFOpenCV});
			if (grabarLandmarksHabilitado)
			{
				empezarLandmarksLog(tipoFeeder);
			}
		}
		else
		{
			throw MiExcepcion(ERROR_EXTRACTOR_INICIAR);
		}
	}
	catch (const MiExcepcion &e)
	{
		cerr << "No se pudo setear el extractor solicitado" << endl;
		this->ptrExtractor = NULL;
		throw;
	}
}

void AnalizadorSimetria::setFeeder(TipoFeeder feeder_)
{
	tipoFeeder = feeder_;
	if (this->ptrFeeder != NULL)
	{
		if (tipoFeeder != ptrFeeder->getFeeder())
		{
			delete this->ptrFeeder;
		}
		else
		{
			cout << "Ya se está utilizando el Feeder solicitado" << endl;
			return;
		}
	}
	try
	{
		if (tipoFeeder == WEBCAMFEEDER)
		{
			this->ptrFeeder = new WebcamFeeder;
			if (grabarVideoHabilitado)
			{
				empezarVideoLog(tipoFeeder);
			}
		}
		else if (tipoFeeder == KINECTFEEDER)
		{
#ifdef KINECT_AVAILABLE
			this->ptrFeeder = new KinectFeeder;
			if (grabarVideoHabilitado)
			{
				empezarVideoLog(tipoFeeder);
			}
#else
			throw MiExcepcion(ERROR_FEEDER_INICIAR);
#endif
		}

		else if (tipoFeeder == VIDEOFEEDER)
		{
			this->ptrFeeder = new VideoFeeder(nombreVideoFeeder);
		}
		else
		{
			throw MiExcepcion(ERROR_FEEDER_INICIAR);
		}
	}
	catch (const MiExcepcion &e)
	{
		cerr << "No se pudo setear el feeder solicitado" << endl;
		this->ptrFeeder = NULL;
		throw;
	}
}

void AnalizadorSimetria::cargarConfiguracion(const string &nombreArchivo)
{
	FileStorage fs(nombreArchivo, FileStorage::READ);
	cout << "Cargando configuración..." << endl;
	if (!fs.isOpened())
	{
		throw MiExcepcion(ERROR_ABRIR_CONF);
	}
	fs["tipoExtractor"] >> tipoExtractor;
	fs["tipoFeeder"] >> tipoFeeder;
	fs["nombreVideoEntrada"] >> nombreVideoFeeder;
	fs["nombreVideoSalida"] >> nombreFrameLogger;
	fs["nombreCascadeOpenCV"] >> nombreCascadeOpenCV;
	fs["nombreLandmarksLog"] >> nombreLandmarksLogger;
	fs["nombreLBF"] >> nombreLBFOpenCV;
	fs["nombreDetectorDlib"] >> nombreModeloDlib;
	fs["habilitarVideoLog"] >> grabarVideoHabilitado;
	fs["habilitarLandmarksLog"] >> grabarLandmarksHabilitado;
	fs.release();
}

void AnalizadorSimetria::empezarVideoLog(const TipoFeeder &tipoFeeder_)
{
	stopVideoLog();
	try
	{
		this->ptrVideoLogger = new FrameLogger(nombreFrameLogger, tipoFeeder_);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
		this->ptrVideoLogger = NULL;
	}
}

void AnalizadorSimetria::stopVideoLog()
{
	if (this->ptrVideoLogger != NULL)
	{
		delete this->ptrVideoLogger;
		this->ptrVideoLogger = NULL;
	}
}

void AnalizadorSimetria::empezarLandmarksLog(const TipoFeeder &tipoFeeder_)
{
	stopLandmarksLog();
	try
	{
		this->ptrLandmarksLogger = new LandmarksLogger(nombreLandmarksLogger, tipoFeeder_);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
		this->ptrLandmarksLogger = NULL;
	}
}

void AnalizadorSimetria::stopLandmarksLog()
{
	if (this->ptrLandmarksLogger != NULL)
	{
		delete this->ptrLandmarksLogger;
		this->ptrLandmarksLogger = NULL;
	}
}
