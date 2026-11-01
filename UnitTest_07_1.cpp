#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_07/Lab_07_1.cpp" // Посилання на файл проекту

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab071
{
    TEST_CLASS(UnitTestLab071)
    {
    public:
        TEST_METHOD(TestMethodCalc)
        {
            const int rowCount = 2;
            const int colCount = 2;
            int** q = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                q[i] = new int[colCount];

            // Наповнюємо тестувальними даними:
            // q[0][0] = 10 (додатне, але i=0, j=0 — обидва парні, має ІГНОРУВАТИСЯ)
            // q[0][1] = 5  (додатне, i=0, j=1 — підходить)
            // q[1][0] = 7  (додатне, i=1, j=0 — підходить)
            // q[1][1] = -3 (від'ємне — ІГНОРУЄТЬСЯ)
            q[0][0] = 10; q[0][1] = 5;
            q[1][0] = 7;  q[1][1] = -3;

            int S = 0, k = 0;
            Calc(q, rowCount, colCount, S, k);

            Assert::AreEqual(12, S); // 5 + 7 = 12
            Assert::AreEqual(2, k);  // 2 елементи
            Assert::AreEqual(0, q[0][1]); // Обнулення виконано
            Assert::AreEqual(0, q[1][0]); // Обнулення виконано

            for (int i = 0; i < rowCount; i++)
                delete[] q[i];
            delete[] q;
        }
    };
}