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

			//PLUFactorisation<float> res = MatrixFunctions::getPLUFactors<float>(test, 0.0001);
			//res.L.print_matrix();
			//res.U.print_matrix();
			//res.P.print_matrix();

			Matrix<float> UMatrix = Matrix<float>(3, 4);
			UMatrix.zeros();
			//UMatrix.set
			//Assert::AreEqual(UMatrix, res.U);
		}
		TEST_METHOD(TestSubMatrix){

			Matrix<int> my_matrix = Matrix<int>(2, 3);
			my_matrix.set_element(0, 0, 2);
			my_matrix.set_element(0, 1, 0);
			my_matrix.set_element(0, 2, 1);
			my_matrix.set_element(1, 0, 0);
			my_matrix.set_element(1, 1, 2);
			my_matrix.set_element(1, 2, 5);

			Matrix<int> my_matrix1 = MatrixFunctions::getSubMatrix(my_matrix, 0, 0, 2, 2);
			Matrix<int> my_matrix2 = MatrixFunctions::getSubMatrix(my_matrix, 0, 1, 1, 2);
			Matrix<int> my_matrix3 = MatrixFunctions::getSubMatrix(my_matrix, 0, 1, 1, 3);


			Matrix<int> sub_matrix = Matrix<int>(2, 2);
			sub_matrix.set_element(0, 0, 2);
			sub_matrix.set_element(0, 1, 0);
			sub_matrix.set_element(1, 0, 0);
			sub_matrix.set_element(1, 1, 2);
			
			Matrix<int> sub_matrix1 = Matrix<int>(1,1);
			sub_matrix1.set_element(0, 0, 0);

			Matrix<int> sub_matrix2 = Matrix<int>(1, 2);
			sub_matrix2.set_element(0, 0, 0);
			sub_matrix2.set_element(0, 1, 1);

			Assert::IsTrue(sub_matrix == my_matrix1);

			Assert::IsTrue(sub_matrix1 == my_matrix2);
			Assert::IsTrue(sub_matrix2 == my_matrix3);

		}
	};
}