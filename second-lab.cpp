#include <iostream>
#include <clocale>

#include "Matrix.h"

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Rus");

	/* Инициализация переменных */
	int n = 0, m = 0;

	cout << "Введите размеры матрицы: ";
	cin >> n >> m;

	double* array = create_matrix(n, m);

	/* Инициализация объектов */
	Matrix f_matrix = Matrix();
	Matrix s_matrix = Matrix(2);
	Matrix e_matrix = Matrix(n, m, array);
	Matrix g_matrix = Matrix(e_matrix);

	/* Проверка внешних функций */
	Matrix summ = summ_matrix(e_matrix, g_matrix);
	Matrix diff = diff_matrix(e_matrix, g_matrix);

	/* Проверка перегрузки операторов */
	s_matrix += g_matrix;
	e_matrix -= g_matrix;
	s_matrix *= 5;
	cout << s_matrix << e_matrix << g_matrix << diff;

	return 0;
}