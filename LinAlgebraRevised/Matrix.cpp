#include "Matrix.h"
#include <iostream>
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
		T elements = new T[(other_mat.no_rows)*(other_mat.no_cols)];
		memcpy(elements, other_mat.elements, sizeof(T) * no_rows* no_cols);
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
void Matrix<T>::copy_elements(Matrix<T>& other_mat) {
	
	if (verify_dims_add(other_mat)) {
		std::cout << "Copying" << sizeof(T)*no_rows*no_cols << " bytes " << std::endl;
		std::cout << "Copying" << std::endl;
		other_mat.print_matrix();
		std::cout << "To this matrix" << std::endl;
		//memcpy(this->elements, other_mat.elements, no_rows * no_cols * sizeof(T));
		loop(element_counter, no_rows * no_cols) {
			std::cout << "Setting other_mat index" << element_counter << " to " << other_mat.get_element(0,0);
			this->set_element(0, 1, other_mat.get_element(0,0));
		}
	}
	else {
		throw(dimension_mismatch);
	}
}

template<class T>
void Matrix<T>::fill(Matrix<T> &other_matrix) {
	if (verify_dims_add(other_mat)) {
		loop(counter, no_rows * no_cols) {
			elements[counter] = other_matrix.elements[counter];
		}
	}
	else {
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
	if (elements == other_mat.elements && no_rows == other_mat.no_rows) {
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
