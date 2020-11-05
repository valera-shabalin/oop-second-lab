#include <iostream>
#include <clocale>

#include "Matrix.h"

using namespace std;
using namespace mat;

int main()
{
	setlocale(LC_CTYPE, "Rus");

	/* Инициализация переменных */
	size_t n = 0, m = 0;

	cout << "Введите размеры матрицы: ";
	cin >> n >> m;

	double* array = create_matrix(n, m);

	Matrix e_matrix = Matrix(n, m, array);
	Matrix g_matrix = Matrix(2, 2);

	/* Проверка перегрузок */
	e_matrix += e_matrix;

	/* Проверка внешних функций */
	Matrix summ = e_matrix + e_matrix;
	Matrix diff = e_matrix - e_matrix;
	Matrix multiply = e_matrix * e_matrix;
	Matrix scalar_multiply = e_matrix * 5;

	/* Вывод результатов */
	cout << e_matrix << summ << diff << multiply << scalar_multiply;

	/* Перегрузка оператора [][] */
	cout << e_matrix[1][1];

	return 0;
}
