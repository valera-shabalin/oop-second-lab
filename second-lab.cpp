#include <iostream>
#include <clocale>

#include "Matrix.h"

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Rus");

	int n = 0, m = 0;

	cout << "Введите размеры матрицы: ";
	cin >> n >> m;

	double* array = create_matrix(n, m);

	Matrix f_matrix = Matrix();
	Matrix s_matrix = Matrix(2);
	/* Matrix t_matrix = Matrix(array); */
	Matrix e_matrix = Matrix(n, m, array);

	cout << f_matrix << s_matrix << e_matrix;

	return 0;
}