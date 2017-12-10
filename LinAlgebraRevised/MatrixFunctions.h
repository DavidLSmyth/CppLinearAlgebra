#pragma once
#include "Vector.h"
#include "Matrix.h"

template<class T>
Vector<T> Jacobi(Matrix<T> A, Vector<T> b, int max_iterations = 1000);
	//returns x (or no solution), the solution to the system Ax = b, where A is square matrix
	//Jacobi iterative scheme: 
	//instantiate x = 0
	//while norm Ax - b > tolerance and number of iterations < max_iterations:
	//update x_j as b_j - sum i = 0 to n(a_ji * x_i) / a_jj
	//should converge under the following conditions:
	//

template <class T>
Vector<T> GaussSeidel(Matrix<T> A, Vector<T> b, int max_iterations = 1000);

template <class T>
Vector<T> GaussianElimination(Matrix<T> A, Vector<T> b);

