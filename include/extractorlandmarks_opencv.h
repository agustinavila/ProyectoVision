/**
 * @file extractorlandmarks_opencv.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase concreta ExtractorLandmarksOpenCV
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
//#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/face.hpp>
// #include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "extractorlandmarks.h"

using namespace std;
using namespace cv;
//using namespace cv::face;

/**
 * @brief Clase concreta para extraer landmarks utilizando openCV
 * 
 */
class ExtractorLandmarksOpenCV : public ExtractorLandmarks
{
private:
	Mat gray;
	Ptr<face::Facemark> facemark;
	CascadeClassifier faceDetector;
	std::vector<cv::Point2f> landmarks;
	/* data */
public:
	ExtractorLandmarksOpenCV();
	virtual ~ExtractorLandmarksOpenCV();
	virtual const std::vector<cv::Point2f> getLandmarks(const cv::Mat &);
};

#endif // EXTRACTORLANDMARKS_OPENCV_H
