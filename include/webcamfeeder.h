/**
 * @file webcamfeeder.h
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Declaracion de la clase concreta WebcamFeeder
 * @version 0.1
 * @date 2021-06-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#if !defined(WEBCAMFEEDER_H)
#define WEBCAMFEEDER_H

#include <iostream>
#include <vector>

#include "feeder.h"
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>

using namespace std;
using namespace cv;

/**
 * @brief Sobrecarga de la clase Feeder para abrir una webcam
 */
class WebcamFeeder : public Feeder {
private:
    Mat frame_;            ///< Fotograma actual
    int idx_;              ///< Índice de la Webcama abrir. Por defecto es 0
    cv::VideoCapture cap_; ///< Objeto de openCV encargado de manejar la webcam

public:
    /**
   * @brief Construye un nuevo objeto de la clase WebcamFeeder
   *
   * @details Se encarga de inicializar la webcam
   * a través del objeto de la clase VideoCapture
   *
   * @param idx_ - índice de la webcam a abrir
   */
    WebcamFeeder(int idx_ = 0);

    virtual ~WebcamFeeder();

    virtual const FeederType get_feeder_type() { return FeederType::webcam_feeder; };

    virtual const Mat get_frame();
};

#endif // WEBCAMFEEDER_H