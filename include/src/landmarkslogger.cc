/**
 * @file landmarkslogger.cc
 * @author Agustin Avila (tinto.avila@gmail.com)
 * @brief Implementacion de la clase LandmarksLogger
 * @version 0.1
 * @date 2021-06-28
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../landmarkslogger.h"

LandmarksLogger::LandmarksLogger()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
    string timestamp = oss.str();
    int posFin = log_file_name_.rfind(".");        // busca el punto comenzando por el final
    string strExt = log_file_name_.substr(posFin); // obtiene la extension del archivo
    log_file_name_ = log_file_name_.substr(0, posFin) + timestamp + strExt;
    fs_.open(log_file_name_, FileStorage::WRITE);
    if (!fs_.isOpened()) { throw MiExcepcion(ERROR_ABRIR_CONF); }
    fs_ << "datetime" << timestamp;
    fs_ << "feeder"
        << "webcam";
}

LandmarksLogger::LandmarksLogger(const string& nombre, const FeederType& feeder)
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
    string timestamp = oss.str();
    int posFin = nombre.rfind(".");        // busca el punto comenzando por el final
    string strExt = nombre.substr(posFin); // obtiene la extension del archivo
    if (feeder == FeederType::webcam_feeder) {
        log_file_name_ = nombre.substr(0, posFin) + "_WebCam_" + timestamp + strExt;
        cout << "Comenzando a registrar en el archivo " << log_file_name_ << endl;
        fs_.open(log_file_name_, FileStorage::WRITE);
        if (!fs_.isOpened()) { throw MiExcepcion(ERROR_ABRIR_CONF); }
        fs_ << "datetime" << timestamp;
        fs_ << "feeder"
            << "WEBCAM";
    } else if (feeder == FeederType::kinect_feeder) {
        log_file_name_ = nombre.substr(0, posFin) + "_Kinect_" + timestamp + strExt;
        cout << "Comenzando a registrar en el archivo " << log_file_name_ << endl;
        fs_.open(log_file_name_, FileStorage::WRITE);
        if (!fs_.isOpened()) { throw MiExcepcion(ERROR_ABRIR_CONF); }
        fs_ << "datetime" << timestamp;
        fs_ << "feeder"
            << "KINECT";
    } else {
        throw MiExcepcion(ERROR_GUARDAR_VIDEO);
    }
    fs_ << "datos"
        << "[";
}

LandmarksLogger::~LandmarksLogger()
{
    // Escribir tags de salida?
    cout << "Cerrando el log de landmarks...";
    fs_ << "]"; // Cierra el nodo de datos
    fs_.release();
    cout << "listo!" << endl;
}

void LandmarksLogger::log(const std::vector<Landmarks>& landmarks)
{
    fs_ << "[";
    fs_ << "frame" << landmarks_counter_;
    fs_ << "landmarks"
        << "[";
    std::vector<Landmarks>::const_iterator cii;
    std::vector<cv::Point2f>::const_iterator cipuntos;
    Landmarks l;
    for (cii = landmarks.begin(); cii != landmarks.end(); cii++) {
        l = *cii;
        fs_ << "[";
        fs_ << "vacio" << l.vacio;
        fs_ << "rotacion" << l.rotacion;
        fs_ << "escala" << l.escala;
        fs_ << "menton"
            << "[";
        for (cipuntos = l.menton.begin(); cipuntos != l.menton.end(); cipuntos++) { fs_ << *cipuntos; }
        fs_ << "]";
        fs_ << "ojoIzq"
            << "[";
        for (cipuntos = l.ojoIzq.begin(); cipuntos != l.ojoIzq.end(); cipuntos++) { fs_ << *cipuntos; }
        fs_ << "]";
        fs_ << "ojoDer"
            << "[";
        for (cipuntos = l.ojoDer.begin(); cipuntos != l.ojoDer.end(); cipuntos++) { fs_ << *cipuntos; }
        fs_ << "]";
        fs_ << "cejaIzq"
            << "[";
        for (cipuntos = l.cejaIzq.begin(); cipuntos != l.cejaIzq.end(); cipuntos++) { fs_ << *cipuntos; }
        fs_ << "]";
        fs_ << "cejaDer"
            << "[";
        for (cipuntos = l.cejaDer.begin(); cipuntos != l.cejaDer.end(); cipuntos++) { fs_ << *cipuntos; }
        fs_ << "]";
        fs_ << "boca"
            << "[";
        for (cipuntos = l.boca.begin(); cipuntos != l.boca.end(); cipuntos++) { fs_ << *cipuntos; }
        fs_ << "]";
        fs_ << "nariz"
            << "[";
        for (cipuntos = l.nariz.begin(); cipuntos != l.nariz.end(); cipuntos++) { fs_ << *cipuntos; }
        fs_ << "]";
        fs_ << "]"; // cierra un landmark determinado
    }
    fs_ << "]"; // cierra el nodo de landmarks general
    fs_ << "]"; // cierra el nodo del frame
    landmarks_counter_++;
}