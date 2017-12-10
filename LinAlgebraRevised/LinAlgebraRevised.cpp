// LinAlgebraRevised.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Matrix.cpp"
#include <math.h>


using namespace std;
using namespace MatrixNamespace;



int main()
{
	cout << "In the main function" << endl;

	Matrix<int> my_matrix = Matrix<int>(2, 2);
	Matrix<int> row_1 = Matrix<int>(2, 2);
	my_matrix.set_element(0, 0, 10);
	my_matrix.set_element(0, 1, 20);
	my_matrix.set_element(1, 0, 30);
	my_matrix.set_element(1, 1, 40);

	my_matrix.print_matrix();
	row_1.set_element(0, 0, 2);
	row_1.set_element(0, 1, 0);
	row_1.set_element(1, 0, 0);
	row_1.set_element(1, 1, 2);
	cout << "Result of multiplication: " << endl;
	Matrix<int> new_mat = my_matrix * row_1;
	new_mat.print_matrix();
	
	row_1 = Matrix<int>(my_matrix);


	Matrix<int> my_matrix1 = Matrix<int>(2, 3);
	cout << "Filling my_matrix1" << endl;
	my_matrix1.set_element(0, 0, 2);
	my_matrix1.set_element(0, 1, 0);
	my_matrix1.set_element(0, 2, 1);
	my_matrix1.set_element(1, 0, 0);
	my_matrix1.set_element(1, 1, 2);
	my_matrix1.set_element(1, 2, 5);
	cout << "Transposing" << endl;
	Matrix<int> return_matrix = my_matrix1.transpose();
	return_matrix.print_matrix();

	int element_array[4] = {10,20,30,40};
	Matrix<int> mat_1 = Matrix<int>(2, 2, *element_array);

	cout << "Reinitialising my_matrix" << endl;
	mat_1.print_matrix();
	mat_1.swap_rows(0, 1);
	cout << "Swapping matrix row 0 and 1" << endl;
	mat_1.print_matrix();
	
	cout << "Press any key to continue..." << endl;
	int x;
	cin >> x;
    return 0;
}

