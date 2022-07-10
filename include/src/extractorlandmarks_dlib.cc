/**
 * @file extractorlandmarks_dlib.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase concreta ExtractorLandmarks_dlib
 * @version 0.1
 * @date 2021-06-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../extractorlandmarks_dlib.h"

#include "../extractorlandmarks.h"

ExtractorLandmarksDlib::ExtractorLandmarksDlib(const std::vector<string>& nombres)
{
    detector_filename_ = nombres.front();
    cout << "Generando el extractor de landmarks con dlib...";
    dlib_face_detector_ = get_frontal_face_detector();
    try {
        deserialize(detector_filename_) >> shape_predictor_;
        cout << " listo!" << endl;
    } catch (const MiExcepcion& e) {
        std::cerr << e.what() << '\n';
    }
}

ExtractorLandmarksDlib::~ExtractorLandmarksDlib()
{
    cout << "Destruyendo el extractor de landmarks con dlib...";
    landmarks_.clear();
    cout << "listo!" << endl;
}

const std::vector<Landmarks> ExtractorLandmarksDlib::get_landmarks(const cv::Mat& frame)
{
    float escala;
    bool reescalado = 0;
    Mat frameRed;
    if (frame.size().width > 800) // Si está en fullHD lo reescala
    {
        escala = 2;
        reescalado = 1;
        resize(frame, frameRed, Size(), 1 / escala, 1 / escala);
    } else {
        frameRed = frame;
    }
    cv_image<bgr_pixel> cimg(frameRed);                             // Convierte el Mat a un formato utilizable por dlib
    std::vector<dlib::rectangle> caras = dlib_face_detector_(cimg); // rectangulos con las caras detectadas
    if (caras.empty()) {
        landmarks_.clear();
        Landmarks l;
        l.vacio = 1; // marca la estructura como vacia y la devuelve
        landmarks_.push_back(l);
    } else {
        landmarks_serie_.clear();
        for (long unsigned int i = 0; i < caras.size(); ++i) {
            full_object_detection shape;
            shape = (shape_predictor_(cimg, caras[i]));
            std::vector<Point2f> cara;
            if (reescalado) {
                for (unsigned int j = 0; j < shape.num_parts(); ++j) {
                    // lo convierte a un vector de vectores de landmarks para posteriormente pasarlo a la estructura
                    cara.push_back((cv::Point2f(shape.part(j).x() * escala, shape.part(j).y() * escala)));
                    // para optimizarse, se podría convertir directamente a la estructura
                }
            } else {
                for (unsigned int j = 0; j < shape.num_parts();
                     ++j) // se duplica el codigo para evitar la multiplicacion
                {
                    cara.push_back((cv::Point2f(shape.part(j).x(), shape.part(j).y())));
                }
            }
            landmarks_serie_.push_back(cara);
            landmarks_ = parseLandmarks(landmarks_serie_); // se pasa del vector de vectores al vector de estructuras
        }
    }
    return landmarks_;
}