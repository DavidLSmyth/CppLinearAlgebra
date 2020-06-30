#pragma once
#include "Matrix.h"

namespace MatrixNamespace {
	//Vector is a special case of Matrix
	template <class T>
	class Vector : public Matrix<T> {
	public:
		Vector<T>(const Vector<T>& other_vector) {
			/*
			this->no_rows = other_vector.no_rows;
			this->no_cols = other_vector.no_cols;
			memcpy(other_vector, this.elements, sizeof(T) * no_rows);
			*/
			Matrix(other_vector);
		}
		Vector<T>(int no_rows) {
			Matrix(no_rows, 1);
		}
		Vector<T>(int no_rows, const T*& elements) {
			Matrix(no_rows, 1, elements);
		}
		~Vector<T>() {
			~Matrix();
		};
	};
}
