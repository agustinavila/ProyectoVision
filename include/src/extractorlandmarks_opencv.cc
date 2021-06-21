/**
 * @file extractorlandmarks_opencv.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../extractorlandmarks.h"
#include "../extractorlandmarks_opencv.h"

ExtractorLandmarksOpenCV::ExtractorLandmarksOpenCV()
{
	cout << "constructor del extractor de openCV... ";
	this->faceDetector.load("haarcascade_frontalface_alt2.xml");
	this->facemark = face::FacemarkLBF::create();
	this->facemark->loadModel("lbfmodel.yaml");
	cout << "listo!" << endl;
}

ExtractorLandmarksOpenCV::~ExtractorLandmarksOpenCV()
{
	this->landmarks.clear();
}

std::vector<cv::Point2f> ExtractorLandmarksOpenCV::getLandmarks(cv::Mat frame)
{
	vector<Rect> faces;
	Mat gray;
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	this->faceDetector.detectMultiScale(gray, faces);
	vector<vector<Point2f>> landmarksVector;
	this->facemark->fit(frame, faces, landmarksVector);
	this->landmarks.clear();
	this->landmarks=landmarksVector[0];
	return this->landmarks;
}