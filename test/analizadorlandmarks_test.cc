#include <analizadorlandmarks.h>
#include <gtest/gtest.h>

struct Analizador_test : public testing::Test {
    AnalizadorLandmarks* analizador;
    void SetUp() { analizador = new AnalizadorLandmarks; }
    void TearDown() { delete analizador; }
};

TEST_F(Analizador_test, angulo_0)
{
    ASSERT_FLOAT_EQ(analizador->calcularAngulo(cv::Point2f(0, 0), cv::Point2f(1, 0)), 0);
}

TEST_F(Analizador_test, angulo_45)
{
    ASSERT_FLOAT_EQ(analizador->calcularAngulo(cv::Point2f(0, 0), cv::Point2f(1, 1)), 45);
}

TEST_F(Analizador_test, angulo_90)
{
    ASSERT_FLOAT_EQ(analizador->calcularAngulo(cv::Point2f(0, 0), cv::Point2f(0, 1)), 90);
}

TEST_F(Analizador_test, angulo_135)
{
    ASSERT_FLOAT_EQ(analizador->calcularAngulo(cv::Point2f(0, 0), cv::Point2f(-1, 1)), 135);
}

TEST_F(Analizador_test, angulo_180)
{
    ASSERT_FLOAT_EQ(analizador->calcularAngulo(cv::Point2f(0, 0), cv::Point2f(-1, 0)), 180);
}

TEST_F(Analizador_test, angulo_135_neg)
{
    ASSERT_FLOAT_EQ(analizador->calcularAngulo(cv::Point2f(0, 0), cv::Point2f(-1, -1)), -135);
}

TEST_F(Analizador_test, angulo_90_neg)
{
    ASSERT_FLOAT_EQ(analizador->calcularAngulo(cv::Point2f(0, 0), cv::Point2f(0, -1)), -90);
}

TEST_F(Analizador_test, angulo_45_neg)
{
    EXPECT_FLOAT_EQ(analizador->calcularAngulo(cv::Point2f(0, 0), cv::Point2f(1, -1)), -45);
}

TEST_F(Analizador_test, big_number)
{
    EXPECT_FLOAT_EQ(analizador->calcularAngulo(cv::Point2f(0, 0), cv::Point2f(0, 5000000000000)), 90);
}

TEST_F(Analizador_test, max1) { EXPECT_FLOAT_EQ(analizador->calcularMax(0, 1), 1); }
TEST_F(Analizador_test, max2) { EXPECT_FLOAT_EQ(analizador->calcularMax(2, 0), 2); }
TEST_F(Analizador_test, max3) { EXPECT_FLOAT_EQ(analizador->calcularMax(3, 3), 3); }
TEST_F(Analizador_test, max4) { EXPECT_FLOAT_EQ(analizador->calcularMax(30000000000000000, -3), 30000000000000000); }


// TEST(AnalizadorLandmarks, BasicFaceRecognizer)
// {
//     AnalizadorLandmarks analizador;
//     ASSERT_FLOAT_EQ(analizador->calcularPendiente(cv::Point2f(1, 0), cv::Point2f(1, 1)), 0);
//     ASSERT_FLOAT_EQ(analizador->calcularPendiente(cv::Point2f(1, 1), cv::Point2f(1, 0)), 0);
// }