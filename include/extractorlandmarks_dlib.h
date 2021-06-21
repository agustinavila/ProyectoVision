/**
 * @file extractorlandmarks_dlib.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#if !defined(EXTRACTORLANDMARKSDLIB_H)
#define EXTRACTORLANDMARKSDLIB_H

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/opencv.h>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "extractorlandmarks.h"

using namespace dlib;
using namespace std;

class ExtractorLandmarksDlib : public ExtractorLandmarks
{
private:
	frontal_face_detector detector;
	shape_predictor pose_model;
	std::vector<cv::Point2f> landmarks;

public:
	ExtractorLandmarksDlib();
	virtual ~ExtractorLandmarksDlib();
	virtual std::vector<cv::Point2f> getLandmarks(cv::Mat);
};

#endif // EXTRACTORLANDMARKSDLIB_H