#pragma once


#include "Vector.h"
#include "Matrix.h"



using namespace MatrixNamespace;

namespace MatrixFns {
	template <class T>
	struct PLUFactorisation {
		Matrix<int> P;
		Matrix<T> L;
		Matrix<T> U;
	};

	class MatrixFunctions {
	public:

		template<class T>
		static Vector<T> Jacobi(Matrix<T> A, Vector<T> b, int max_iterations = 1000);
		//returns x (or no solution), the solution to the system Ax = b, where A is square matrix
		//Jacobi iterative scheme: 
		//instantiate x = 0
		//while norm Ax - b > tolerance and number of iterations < max_iterations:
		//update x_j as b_j - sum i = 0 to n(a_ji * x_i) / a_jj
		//should converge under the following conditions:
		//

		template <class T>
		static Vector<T> GaussSeidel(Matrix<T> A, Vector<T> b, int max_iterations = 1000);

		template <class T>
		static Vector<T> GaussianElimination(Matrix<T> A, Vector<T> b);

		//returns the PLU factors of A as an array of matrices
		template <typename T>
		static MatrixFns::PLUFactorisation<T> getPLUFactors(const Matrix<T>& A, float epsilon);

		template <typename T> 
		static Matrix<T> getSubMatrix(Matrix<T>& A, int start_row, int start_col, int end_row, int end_col);

	private:
		static const char unstablePivot[];
		
	};
	

}