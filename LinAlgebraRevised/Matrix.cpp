#include "Matrix.h"
#include <iostream>
#include <math.h>
using namespace MatrixNamespace;
#define loop(x, n) for(int x=0; x < n; x++)


template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other_mat) {
	if (verify_dims_add(other_mat)) {
		Matrix<T> return_matrix(no_rows, no_cols);
		loop(row_counter, no_rows) {
			loop(col_counter, no_cols) {
				return_matrix.set_element(row_counter, col_counter, get_element(row_counter, col_counter) + other_mat.get_element(row_counter, col_counter));
			}
		}
		return return_matrix;
	}
	else {
		throw(dimension_mismatch);
	}

}

template<class T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &other_mat) {
	if (this == &other_mat) {
		//dereference
		return(*this);
	}
	else{
		delete[] elements; // Just in case there was any memory
						  // already allocated to this
		T* elements = new T[other_mat.no_rows*other_mat.no_cols];

		memcpy(elements, &other_mat.elements, sizeof(T) * no_rows* no_cols);
		/*
		loop(elements_counter, no_rows * no_cols) {
			elements[elements_counter] = other_mat[elements_counter];
		}
		*/
		return(*this);
	}
}
//sets the matrix's entries to zero
template<class T>
void MatrixNamespace::Matrix<T>::zeros()
{
	memset(elements, 0, sizeof(T) * no_rows * no_values);
}


template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other_mat)
{
	if (verify_dims_add(other_mat)) {
		Matrix<T> return_matrix = Matrix(no_rows, no_cols);
		loop(element, no_rows * no_cols) {
			return_matrix.elements[element] = elements[element] + (other_mat.elements[element] * -1);
		}
		return return_matrix;
	}
	else {
		throw(dimension_mismatch);
	}
}

template<class T>
Matrix<T> Matrix<T>::transpose() {
	Matrix<T> return_mat = Matrix<T>(no_cols, no_rows);
	loop(row_counter, no_rows) {
		loop(col_counter, no_cols) {
			return_mat.elements[(col_counter * no_rows) + row_counter] = elements[(row_counter* no_cols) + col_counter];
		}
	}
	return return_mat;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other_mat){
	if (verify_dims_mult(other_mat)) {
		Matrix<T> return_matrix(no_rows, other_mat.no_cols);
		loop(row_counter, no_rows) {
			loop(col_counter, other_mat.no_cols) {
				T s = 0;
				//k records the kth column of the first matrix and the kth row of the second matrix
				loop(k, no_cols) {
					s += other_mat.get_element(k, col_counter)*get_element(row_counter, k);
				}
				return_matrix.set_element(row_counter, col_counter, s);
			}
		}
		return return_matrix;
	}
	else {
		throw(dimension_mismatch);
	}
}

template<class T>
Matrix<T> Matrix<T>::operator*(const T &scalar) {
	if (verify_dims_mult(other_mat)) {
		Matrix<T> return_matrix(no_rows, other_mat.no_cols);
		loop(counter, no_rows * no_cols) {
			return_matrix[counter] = return_matrix[counter] * scalar;
		}
		return return_matrix;
	}
	else {
		throw(dimension_mismatch);
	}
}


template<class T>
void Matrix<T>::get_row(int row, T &return_array)
{
	//FMatrix<T> return_mat = Matrix(1, no_cols);
	//T* return_array = new T[no_cols];
	memcpy(&return_array, &elements[row*no_cols], no_cols * sizeof(T));
	/*
	loop(col_counter, no_cols) {
		return_mat.set_element(1, col_counter, get_element(1, col_counter));
	}
	return return_mat;
	*/
	//return return_array;
}

template<class T>
void MatrixNamespace::Matrix<T>::swap_rows(int row_index_1,int row_index_2)
{
	if (0 <= row_index_1 && row_index_1< no_rows && 0<= row_index_2  && row_index_2< no_rows){
		T* row1_copy = new T[sizeof(T) * no_cols];
		T* start_index = &elements[no_cols * row_index_1];
		//copy row 1 of matrix to row1_copy
		memcpy(row1_copy, &elements[no_cols * row_index_1], sizeof(T) * no_cols);
		//copy the elements from row 2 to row 1
		memcpy(&elements[no_cols * row_index_1], &elements[no_cols * row_index_2], sizeof(T) * no_cols);
		memcpy(&elements[no_cols * row_index_2], row1_copy, sizeof(T) * no_cols);
		//get rid of temp files
		delete row1_copy;
	}
	else {
		std::cerr << "Out of bounds error" << std::endl;
		throw(dimension_mismatch);
	}
}

template<class T>
Matrix<T> Matrix<T>::get_col(int col)
{
	Matrix<T> return_mat = Matrix(no_rows, 1);
	loop(row_counter, no_cols) {
		return_mat.set_element(row_counter, 1, get_element(row_counter, 1));
	}
	return return_mat;
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T> &other_mat)
{
	if (no_rows == other_mat.no_rows && no_cols == other_mat.no_cols) {
		loop(element_index, no_rows * no_cols) {
			if (elements[element_index] != other_mat.elements[element_index]) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

template<class T>
bool Matrix<T>::operator!=(Matrix other_mat)
{
	return false;
}

template<class T>
void Matrix<T>::set_element(int row_index, int col_index, T element)
{
	if(verify_valid_index(row_index, col_index)){
		elements[(row_index * no_cols) + col_index] = element;
	}
	else {
		std::cerr << "Dimensions do not match. Rows: " <<row_index<<"Cols"<<col_index<< "No rows"<<no_rows<<"No cols"<<no_cols<<std::endl;
		throw(dimension_mismatch);
	}
}

template<class T>
T MatrixNamespace::Matrix<T>::two_norm()
{
	//matrix norms can be defined in a number of different ways
	//must define a function |.| : K^Mxn -> R satisfying: 
	/*
	1). ||c*A|| = |c| * ||A||
	2). ||A+B|| <= ||A|| + ||B||
	3). ||A|| >= 0
	4). ||A|| = 0 iff A = 0_m,n
	return T();
	*/
	T sum = 0;
	loop(element, no_rows * no_cols) {
		sum += elements[element] * elements[element];
	}
	return sqrt(sum);
}

template<class T>
float MatrixNamespace::Matrix<T>::determinant()
{
	return 0.0f;
}

template<class T>
int* Matrix<T>::get_dimensions()
{
	int* return_array = new int[2];
	return_array[0] = no_rows;
	return_array[1] = no_cols;
	return return_array;
}

template<class T>
Matrix<T> Matrix<T>::get_inverse()
{
	return Matrix();
}

template<class T>
void Matrix<T>::print_matrix()
{
	std::cout << "Printing matrix" << std::endl;
	loop(row_counter, no_rows) {
		loop(col_counter, no_cols) {
			std::cout << get_element(row_counter, col_counter);
			std::cout << ", ";
		}
		std::cout<< std::endl;
	}
}
