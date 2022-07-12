/**
 * @file framelogger.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase FrameLogger
 * @version 0.1
 * @date 2021-06-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "framelogger.h"

FrameLogger::FrameLogger()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
    string timestamp = oss.str();
    int posFin = video_file_name_.rfind(".");        // busca el punto comenzando por el final
    string strExt = video_file_name_.substr(posFin); // obtiene la extension del archivo
    video_file_name_ = video_file_name_.substr(0, posFin) + timestamp + strExt;
    video_.open(video_file_name_, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(640, 480));
}

FrameLogger::FrameLogger(const string& nombre, const FeederType& feeder)
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
    string timestamp = oss.str();
    int posFin = nombre.rfind(".");        // busca el punto comenzando por el final
    string strExt = nombre.substr(posFin); // obtiene la extension del archivo
    if (feeder == FeederType::webcam_feeder) {
        video_file_name_ = nombre.substr(0, posFin) + "_WebCam_" + timestamp + strExt;
        cout << "Comenzando a grabar en el archivo " << video_file_name_ << endl;
        video_.open(video_file_name_, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(640, 480));
    }
#ifdef KINECT_AVAILABLE
    else if (feeder == FeederType::kinect_feeder) {
        video_file_name_ = nombre.substr(0, posFin) + "_Kinect_" + timestamp + strExt;
        cout << "Comenzando a grabar en el archivo " << video_file_name_ << endl;
        video_.open(video_file_name_, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(1920, 1080));
    }
#endif
    else if (feeder == FeederType::video_feeder) {
        video_file_name_ = nombre.substr(0, posFin) + "_Video_" + timestamp + strExt;
        cout << "Comenzando a grabar en el archivo " << video_file_name_ << endl;
        video_.open(video_file_name_, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(640, 480));
    } else {
        throw MiExcepcion(ERROR_GUARDAR_VIDEO);
    }
}

FrameLogger::~FrameLogger()
{
    cout << "Cerrando video de log...";
    video_.release();
    cout << "Video cerrado!" << endl;
}

void FrameLogger::log(const Mat& frame)
{
    frame_counter_++; // Solo en caso de guardar secuencia de imagenes
    video_.write(frame);
}