#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LinAlgebraRevised/Matrix.cpp"
#include "../LinAlgebraRevised/MatrixFunctions.cpp"
#include <iostream>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MatrixNamespace;
using namespace MatrixFns;

namespace MatrixFunctionsTests
{
	TEST_CLASS(UnitTest1)
	{
		TEST_METHOD(TestDefault)
		{
			Matrix<float> test = Matrix<float>(3, 4);
			test.set_element(0, 0, 1);
			test.set_element(0, 1, 3);
			test.set_element(0, 2, 3);
			test.set_element(0, 3, 2);
			test.set_element(1, 0, 2);
			test.set_element(1, 1, 6);
			test.set_element(1, 2, 9);
			test.set_element(1, 3, 7);

			test.set_element(2, 0, -1);
			test.set_element(2, 1, -3);
			test.set_element(2, 2, -3);
			test.set_element(2, 3, 4);
			PLUFactorisation<float> res = MatrixFunctions::getPLUFactors<float>(test, 0.0001);
			res.L.print_matrix();
			res.U.print_matrix();
			res.P.print_matrix();

			Matrix<float> UMatrix = Matrix<float>(3, 4);
			UMatrix.zeros();
			//UMatrix.set
			//Assert::AreEqual(UMatrix, res.U);
		}
	};
}