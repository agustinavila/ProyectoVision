#include <analizadorlandmarks.h>
#include <gtest/gtest.h>

TEST(analizador, angulo45)
{
    AnalizadorLandmarks analizador;
    ASSERT_FLOAT_EQ(analizador.calcularAngulo(cv::Point2f(0, 0), cv::Point2f(1, 1)), 45);
}
TEST(analizador, angulo45neg)
{
    AnalizadorLandmarks analizador;
    ASSERT_FLOAT_EQ(analizador.calcularAngulo(cv::Point2f(0, 0), cv::Point2f(-1, -1)), -45);
}
TEST(analizador, angulo0)
{
    AnalizadorLandmarks analizador;
    ASSERT_FLOAT_EQ(analizador.calcularAngulo(cv::Point2f(0, 0), cv::Point2f(0, 1)), 90);
}
TEST(analizador, angulo90)
{
    AnalizadorLandmarks analizador;
    ASSERT_FLOAT_EQ(analizador.calcularAngulo(cv::Point2f(0, 0), cv::Point2f(1, 0)), 0);
}

// TEST(AnalizadorLandmarks, BasicFaceRecognizer)
// {
//     AnalizadorLandmarks analizador;
//     ASSERT_FLOAT_EQ(analizador.calcularPendiente(cv::Point2f(1, 0), cv::Point2f(1, 1)), 0);
//     ASSERT_FLOAT_EQ(analizador.calcularPendiente(cv::Point2f(1, 1), cv::Point2f(1, 0)), 0);
// }