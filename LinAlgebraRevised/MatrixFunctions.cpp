#include "MatrixFunctions.h"
#include "Matrix.h"
#include <algorithm>
#include <stdio.h>
#include <iostream>

using namespace MatrixFns;
//A library of functions that act on matrices

const char* MatrixFunctions::unstablePivot = "Pivot is < epsilon, result is unstable";


template <typename T>
MatrixFns::PLUFactorisation<T> MatrixFunctions::getPLUFactors(const Matrix<T> &B, float epsilon) {
	Matrix<T> &A = const_cast<Matrix<T>&>(B);
	int no_rows = A.get_no_rows();
	int no_cols = A.get_no_cols();
	Matrix<T> L = Matrix<T>(no_rows, no_rows);

	Matrix<int> P = Matrix<int>(no_rows, no_rows);
	P.identity();
	Matrix<T> U = Matrix<T>(A);

	


	//iterate over each row in the matrix, swap if necessary and eliminate all below

	//finds the largest pivot
	int pivotMaxIndex = 0;

	
	Matrix<int> currentPermutation =  Matrix<int>(no_rows, no_rows);
	T maxPivotValue;
	T coefficient;
	Matrix<T> tempL = Matrix<T>(no_rows, no_rows);

	tempL.identity();
	T nextPossiblePivot;

	//iterate over each row and swap as necessary
	for (int currentRowIndex = 0; currentRowIndex < A.get_no_rows(); currentRowIndex++) {
		//get current row
		pivotMaxIndex = currentRowIndex;
		maxPivotValue = A.get_element(currentRowIndex, currentRowIndex);
		for (int counter = currentRowIndex + 1; counter < A.get_no_rows(); counter++) {
			//find biggest pivot below rowIndex
			nextPossiblePivot = A.get_element(counter, currentRowIndex);
			if (nextPossiblePivot > maxPivotValue) {
				//cout << nextPossiblePivot << " > " << maxPivotValue << endl;
				maxPivotValue = nextPossiblePivot;
				pivotMaxIndex = counter;
			}
		}

		if (pivotMaxIndex != currentRowIndex) {
			//update P
			currentPermutation.identity();
			currentPermutation.swap_rows(pivotMaxIndex, currentRowIndex);
			P = (currentPermutation * P);
		}

		if (maxPivotValue < epsilon) {
			//if 0, finished
			throw(unstablePivot);
			return MatrixFns::PLUFactorisation<T> { P, L, U };
		}

		else {

			for (int currentColIndex = currentRowIndex + 1; currentColIndex < A.get_no_rows(); currentColIndex++) {
				coefficient = -maxPivotValue / U.get_element(currentRowIndex, currentColIndex);
				tempL.set_element(currentRowIndex, currentColIndex, coefficient);
				U = (tempL * U);
				L = (tempL * L);
			}

		}
		return MatrixFns::PLUFactorisation<T> { P, L, U };
	


	}


}

