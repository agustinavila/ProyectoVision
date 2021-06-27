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
	cout << "En el constructor del objeto de analizadorSimetria por defecto" << endl;
	try
	{
		cargarConfiguracion(nombreConf);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
		this->ptrFeeder = new WebcamFeeder;
	}

	this->ptrExtractor = new ExtractorLandmarksDlib(std::vector<string>{nombreModeloDlib});
}

AnalizadorSimetria::AnalizadorSimetria(string &nombrearchivo)
{
	cout << "En el constructor del objeto de analizadorSimetria con un archivo de configuracion" << endl;
	nombreConf = nombrearchivo;
	try
	{
		cargarConfiguracion(nombreConf);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
		this->ptrFeeder = new WebcamFeeder;
	}
	this->ptrExtractor = new ExtractorLandmarksDlib(std::vector<string>{nombreModeloDlib});
}

AnalizadorSimetria::~AnalizadorSimetria()
{

	delete this->ptrLogger;
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
	if (ptrLogger !=NULL)
	{
		ptrLogger->log(frame); //Guarda frames, segun parametros podria desactivarse o no
	}
	if (ptrExtractor!=NULL){
	landmarks = ptrExtractor->getLandmarks(frame);
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
	if (this->ptrExtractor != NULL)
	{
		if (extractor_ != ptrExtractor->getExtractor())
		{
			delete this->ptrExtractor;
		}
	}
	try
	{
		if (extractor_ == DLIB)
		{
			this->ptrExtractor = new ExtractorLandmarksDlib(std::vector<string>{nombreModeloDlib});
		}
		else if (extractor_ == OPENCV)
		{

			this->ptrExtractor = new ExtractorLandmarksOpenCV(std::vector<string>{nombreCascadeOpenCV, nombreLBFOpenCV});
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
	}
	try
	{
		if (tipoFeeder == KINECTFEEDER)
		{
			this->ptrFeeder = new KinectFeeder;
			if (grabarHabilitado)
			{
				empezarLog(tipoFeeder);
			}
		}
		else if (tipoFeeder == WEBCAMFEEDER)
		{
			this->ptrFeeder = new WebcamFeeder;
			if (grabarHabilitado)
			{
				empezarLog(tipoFeeder);
			}
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
	if (!fs.isOpened())
	{
		throw MiExcepcion(ERROR_ABRIR_CONF);
	}
	fs["nombreVideoEntrada"] >> nombreVideoFeeder;
	fs["tipoFeeder"] >> tipoFeeder;
	try
	{
		this->setFeeder(tipoFeeder);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
		exit(-1);
	}
	TipoExtractor extractor;
	fs["tipoExtractor"] >> extractor;
	try
	{
		this->setExtractor(extractor);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
		exit(-1);
	}
	fs["nombreVideoSalida"] >> nombreFrameLogger;
	fs["habilitarVideoLog"] >> grabarHabilitado;
	fs["nombreVideoSalida"] >> nombreFrameLogger;
	if (grabarHabilitado)
		empezarLog(tipoFeeder);
}

void AnalizadorSimetria::empezarLog(const TipoFeeder &tipoFeeder_)
{
	stopLog();
	try
	{
		this->ptrLogger = new FrameLogger(nombreFrameLogger, tipoFeeder_);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << '\n';
		this->ptrLogger = NULL;
	}
}

void AnalizadorSimetria::stopLog()
{
	if (this->ptrLogger != NULL)
	{
		delete this->ptrLogger;
		this->ptrLogger = NULL;
	}
}
