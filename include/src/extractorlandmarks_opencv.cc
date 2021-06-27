/**
 * @file extractorlandmarks_opencv.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase concreta ExtractorLandmarksOpenCV
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../extractorlandmarks_opencv.h"

ExtractorLandmarksOpenCV::ExtractorLandmarksOpenCV(const std::vector<string> &nombres)
{
	nombreCascade = nombres.front();
	nombreLBF = nombres.at(1);
	cout << "constructor del extractor de openCV... ";
	try
	{
		faceDetector.load(nombreCascade);
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << ": " << nombreCascade << endl;
	}
	try
	{
		facemark = face::createFacemarkLBF();
		facemark->loadModel("lbfmodel.yaml");
		cout << "listo!" << endl;
	}
	catch (const MiExcepcion &e)
	{
		std::cerr << e.what() << ": " << nombreLBF << endl;
	}
}

ExtractorLandmarksOpenCV::~ExtractorLandmarksOpenCV()
{
	landmarks.clear();
}

const std::vector<Landmarks> ExtractorLandmarksOpenCV::getLandmarks(const cv::Mat &frame)
{
	vector<Rect> faces;
	Mat gray;
	float escala;
	bool reescalado = 0;
	Mat frameRed;
	if (frame.size().width > 800) //Si está en fullHD lo reescala
	{
		escala = 2;
		reescalado = 1;
		resize(frame, frameRed, Size(), 1 / escala, 1 / escala);
		cvtColor(frameRed, gray, COLOR_BGR2GRAY);
	}
	else
	{
		escala = 1;
		cvtColor(frame, gray, COLOR_BGR2GRAY);
	}
	faceDetector.detectMultiScale(gray, faces);
	if (faces.empty())
	{
		landmarks.clear();
		Landmarks l;
		l.vacio = 1;
		landmarks.push_back(l);
	}
	else
	{
		if (reescalado)
		{
			facemark->fit(frameRed, faces, landmarksSerie);
			vector<vector<Point2f>>::iterator cara;
			vector<Point2f>::iterator punto;
			for (cara = landmarksSerie.begin(); cara != landmarksSerie.end(); cara++)
			{
				for (punto = cara->begin(); punto != cara->end(); punto++)
				{
					*punto *= escala;
				}
			}
		}
		else
		{
			facemark->fit(frame, faces, landmarksSerie);
		}
		landmarks = parseLandmarks(landmarksSerie);
	}
	return landmarks;
}
