/**
 * @file extractorlandmarks.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief implementacion de la clase abstracta ExtractorLandmarks
 * @version 0.1
 * @date 2021-06-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "extractorlandmarks.h"

ExtractorLandmarks::ExtractorLandmarks(){};

ExtractorLandmarks::ExtractorLandmarks(const std::vector<string>& nombres) {}

ExtractorLandmarks::~ExtractorLandmarks() {}

const std::vector<Landmarks>
ExtractorLandmarks::parseLandmarks(const std::vector<std::vector<cv::Point2f>>& landmarks_vector_)
{
    std::vector<Landmarks> landmarks;
    Landmarks l;
    if (landmarks_vector_.empty()) {
        l.vacio = 1;
        landmarks.push_back(l);
    } else {
        for (std::vector<std::vector<cv::Point2f>>::const_iterator cii = landmarks_vector_.begin();
             cii != landmarks_vector_.end(); cii++) {
            std::vector<cv::Point2f>::const_reverse_iterator crij;
            std::vector<cv::Point2f> vec = *cii;
            l.menton.assign(vec.begin(), vec.begin() + 16);
            l.cejaDer.assign(vec.begin() + 22, vec.begin() + 26);
            l.nariz.assign(vec.begin() + 27, vec.begin() + 35);
            l.ojoDer.assign(vec.begin() + 42, vec.begin() + 47);
            l.boca.assign(vec.begin() + 48, vec.begin() + 67);
            for (crij = vec.rend() - 22; crij != vec.rend() - 18; crij++) { l.cejaIzq.push_back(*crij); }
            for (crij = vec.rend() - 40; crij != vec.rend() - 37; crij++) { l.ojoIzq.push_back(*crij); }
            l.ojoIzq.push_back(vec.at(40)); // Se dio vuelta el codigo
            l.ojoIzq.push_back(vec.at(41)); // Para que sea simetrico al ojo derecho
            l.vacio = 0;
            landmarks.push_back(l);
        }
    }
    return landmarks;
}

const std::vector<Landmarks> ExtractorLandmarks::get_landmarks(const cv::Mat& frame) { return landmarks; }